#include "mwfilelist.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include "dlgfileplayblack.h"
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkReply"
#include "QFile"

static const char *c_sMWFileList = "MWFileList";
static const char *c_sTitle = QT_TRANSLATE_NOOP("MWFileList", "删除");
static const char *c_sImport = QT_TRANSLATE_NOOP("MWFileList", "导入");
static const char *c_sExport = QT_TRANSLATE_NOOP("MWFileList", "导出");
static const char *c_sRecord = QT_TRANSLATE_NOOP("MWFileList", "记录");
static const char *c_sDelete = QT_TRANSLATE_NOOP("MWFileList", "删除");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("MWFileList", "刷新");
static const char *c_sPlayBack = QT_TRANSLATE_NOOP("MWFileList", "回放");
static const char *c_sStop = QT_TRANSLATE_NOOP("MWFileList", "停止");
static const char *c_sFileNo = QT_TRANSLATE_NOOP("MWFileList", "文件编号");
static const char *c_sFileName1 = QT_TRANSLATE_NOOP("MWFileList", "文件名称");
static const char *c_sFileSize = QT_TRANSLATE_NOOP("MWFileList", "文件大小");
static const char *c_sCreateDate = QT_TRANSLATE_NOOP("MWFileList", "创建时间");
static const char *c_sFileType = QT_TRANSLATE_NOOP("MWFileList", "文件类型");
static const char *c_sLBASize = QT_TRANSLATE_NOOP("MWFileList", "LBA大小（KB）");
static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("MWFileList", "选择要导入的文件");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("MWFileList", "DAT文件 (*.dat)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("MWFileList", "是否停止？");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("MWFileList", "是否删除？");
static const char *c_sPlayBackTip = QT_TRANSLATE_NOOP("MWFileList", "请选择一个文件回放！");
static const char *c_sYes = QT_TRANSLATE_NOOP("MWFileList", "是");
static const char *c_sNo = QT_TRANSLATE_NOOP("MWFileList", "否");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("MWFileList", "工具栏");

MWFileList::MWFileList(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initConnect();
}

MWFileList::~MWFileList()
{
}


void formatSize(qint64 oldBytes, float& newBytes, QString& sUnit)
{
    newBytes = oldBytes;
    sUnit = "B";

    if (oldBytes / c_mSizeMax > 0)
    {
        newBytes = oldBytes / (float)c_mSizeMax;
        sUnit = "GB";
    }
    else if (oldBytes / c_kSizeMax > 0)
    {
        newBytes = oldBytes / (float)c_kSizeMax;
        sUnit = "MB";
    }
    else if (oldBytes / c_bSizeMax > 0)
    {
        newBytes = oldBytes / (float)c_bSizeMax;
        sUnit = "KB";
    }
}

/*****************************************************************************
* @brief   : 初始化UI
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void MWFileList::initUI()
{
    // 工具栏
    QToolBar *toolBar = addToolBar(qApp->translate(c_sMWFileList, c_sToolBar));
    toolBar->toggleViewAction()->setEnabled(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setAllowedAreas(Qt::TopToolBarArea);
    toolBar->setMovable(false);
    toolBar->setStyleSheet("QToolBar {border: none;}");

    QString sIcon = QString("%1/Image/import.png").arg(qApp->applicationDirPath());
    m_pActImport = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sImport));
    m_pActImport->setStatusTip(m_pActImport->text());

    sIcon = QString("%1/Image/export.png").arg(qApp->applicationDirPath());
    m_pActExport = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sExport));
    m_pActExport->setStatusTip(m_pActExport->text());

    sIcon = QString("%1/Image/record.png").arg(qApp->applicationDirPath());
    m_pActRecord = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sRecord));
    m_pActRecord->setStatusTip(m_pActRecord->text());

    sIcon = QString("%1/Image/delete.png").arg(qApp->applicationDirPath());
    m_pActDelete = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sDelete));
    m_pActDelete->setStatusTip(m_pActDelete->text());

    sIcon = QString("%1/Image/refresh.png").arg(qApp->applicationDirPath());
    m_pActRefresh = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sRefresh));
    m_pActRefresh->setStatusTip(m_pActRefresh->text());

    sIcon = QString("%1/Image/playback.png").arg(qApp->applicationDirPath());
    m_pActPlayBack = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sPlayBack));
    m_pActPlayBack->setStatusTip(m_pActPlayBack->text());

    sIcon = QString("%1/Image/stop.png").arg(qApp->applicationDirPath());
    m_pActStop = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sMWFileList, c_sStop));
    m_pActStop->setStatusTip(m_pActStop->text());

    m_pFileListWgt = new QTableWidget(this);
    // m_pFileListWgt->setStyleSheet("QTableWidget { border: none;}");
    setCentralWidget(m_pFileListWgt);

    this->statusBar()->showMessage("statusBar");
    statusBar()->setSizeGripEnabled(false);

    initFileListWgt();
}

/*****************************************************************************
* @brief   : 初始化信号槽
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void MWFileList::initConnect()
{
    connect(m_pActRecord, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActRecord, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotRecord()));

    connect(m_pActPlayBack, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActPlayBack, SIGNAL(triggered(bool)), this, SLOT(slotPlayBack()));

    connect(m_pActImport, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActImport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotImport()));

    connect(m_pActExport, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActExport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotExport()));

    connect(m_pActStop, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActStop, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotStop()));

    connect(m_pActDelete, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActDelete, SIGNAL(triggered(bool)), this, SLOT(slotDelete()));

    connect(m_pActRefresh, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActRefresh, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotRefresh()));

    connect(this, SIGNAL(sigDelete(QList<quint32>)), parentWidget(), SLOT(slotDelete(QList<quint32>)));
    connect(this, SIGNAL(sigPlayBack(quint32, quint32, quint32, quint32, quint32, quint32)),
        parentWidget(), SLOT(slotPlayBack(quint32, quint32, quint32, quint32, quint32, quint32)));
}

/*****************************************************************************
* @brief   : 初始化：雷达数据
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void MWFileList::initFileListWgt()
{
    QStringList headerList;
    headerList << qApp->translate(c_sMWFileList, c_sFileNo)
        << qApp->translate(c_sMWFileList, c_sFileName1)
        << qApp->translate(c_sMWFileList, c_sFileSize)
        << qApp->translate(c_sMWFileList, c_sCreateDate)
        << qApp->translate(c_sMWFileList, c_sFileType)
        << qApp->translate(c_sMWFileList, c_sLBASize);

    m_pFileListWgt->setColumnCount(headerList.size());
    m_pFileListWgt->setHorizontalHeaderLabels(headerList);
    m_pFileListWgt->setSelectionBehavior(QAbstractItemView::SelectRows);     // 设置选择行为时每次选择一行
    m_pFileListWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);      // 设置表格为只读
    m_pFileListWgt->setShowGrid(true);                                       // 设置显示格子线


    QHeaderView* headerView = m_pFileListWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
    for (int nColumn = 0; nColumn < m_pFileListWgt->columnCount(); ++nColumn)
    {
        headerView->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
    }
}

/*****************************************************************************
* @brief   : 应答-记录
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readRecord(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "record success" : "record error");
}

/*****************************************************************************
* @brief   : 应答-回放
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readPlayBack(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "playback success" : "playback error");
}

/*****************************************************************************
* @brief   : 应答-导入
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readImport(quint32 area, char* filename, quint32 state)
{
//     if (state != 0x00)
//     {
//         statusBar()->showMessage("import error");
//         return;
//     }

    QString sFileName = QString::fromLocal8Bit(filename);
    m_pFile = new QFile(sFileName);
    m_pFile->open(QIODevice::ReadOnly);
    QByteArray data = m_pFile->readAll ();
    m_pFile->close ();

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);    //往该目录中上传文件
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    QByteArray bytefile = m_pFile->readAll();

    //QString sUrl = QString("http://%0:%1/%2/%3").arg(m_pDataSocket->localAddress().toString()).arg(c_uDataPort).arg(m_pTabWgt->currentIndex()).arg(sFileName);
    QUrl url("http://127.0.0.1:6188/0/1.txt");    //如这里指定的上传文件至HTTP服务器目录中的upload目录中
    url.setUserName("wangbin");
    url.setPassword("5tgb6yhn");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    QNetworkReply* pNetworkReply = accessManager->post(request, data);

    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(loadError(QNetworkReply::NetworkError)));
    connect(pNetworkReply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(loadProgress(qint64, qint64)));
}


void MWFileList::replyFinished(QNetworkReply* pNetworkReply)
{
    if (pNetworkReply->error() == QNetworkReply::NoError)
    {
        pNetworkReply->deleteLater();
    }
    else
    {
        QMessageBox::critical(NULL, tr("Error"), "Failed!!!");
    }
}

void MWFileList::loadError(QNetworkReply::NetworkError code)
{
    qDebug() << "Error: ";
}

/*****************************************************************************
* @brief   : 应答-导出
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readExport(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "export success" : "export error");
}

/*****************************************************************************
* @brief   : 应答-停止
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readTaskStop(quint32 area, quint32 tasktype, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "stop success" : "stop error");
}

/*****************************************************************************
* @brief   : 应答-删除
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readDelete(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "delete success" : "delete error");
}

/*****************************************************************************
* @brief   : 应答-刷新
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readRefresh(tagAreaFileInfos &fileInfos)
{
    while (m_pFileListWgt->rowCount() > 0)
    {
        m_pFileListWgt->removeRow(m_pFileListWgt->rowCount() - 1);
    }
    foreach(shared_ptr<tagAreaFileInfo> spFileInfo, fileInfos.lstFileInfo)
    {
        m_pFileListWgt->setRowCount(m_pFileListWgt->rowCount() + 1);

        QString sFileName = spFileInfo->sFileName;
        int nIndex = sFileName.lastIndexOf('.');
        QString sExt = sFileName.right(sFileName.count() - nIndex - 1);
        sFileName = sFileName.left(nIndex);

        QString sFileNo = QString("%0").arg(spFileInfo->fileno);
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 0, new QTableWidgetItem(sFileNo));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 1, new QTableWidgetItem(sFileName));
        float newFileSize = spFileInfo->filesize;
        QString sUnit = "";
        formatSize(spFileInfo->filesize, newFileSize, sUnit);
        QString sFileSize = QString("%0%1").arg(newFileSize).arg(sUnit);
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 2, new QTableWidgetItem(sFileSize));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 3, new QTableWidgetItem(spFileInfo->datetime.toString("yyyy-MM-dd hh:mm:ss")));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 4, new QTableWidgetItem(sExt));
        QString sFileLBA = QString("%0").arg(spFileInfo->filesize / c_bSizeMax);
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 5, new QTableWidgetItem(sFileLBA));
    }
}

/*****************************************************************************
* @brief   : 点击Action时，日志记录
* @author  : wb
* @date    : 2019/11/02
* @param:  : 无
*****************************************************************************/
void MWFileList::slotLogRecord()
{
    QAction* pAction = qobject_cast<QAction *>(sender());
    if (NULL == pAction)
        return;

    logRecord(pAction->text());
}

/*****************************************************************************
* @brief   : 日志记录
* @author  : wb
* @date    : 2019/11/02
* @param:  : 传入的系统信息
*****************************************************************************/
void MWFileList::logRecord(QString sText)
{
    QString sDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void MWFileList::slotDelete()
{
    QList<QTableWidgetItem*> selectedItems = m_pFileListWgt->selectedItems();
    QList<quint32> fileNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        fileNos.push_back(m_pFileListWgt->item(pItem->row(), 0)->text().toInt());
    }

    // Test Start
    fileNos.push_back(0);
    // Test End

    if (fileNos.size() < 1)
        return;

    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sMWFileList, c_sTitle));
    box.setText(qApp->translate(c_sMWFileList, c_sIsDelete));
    box.setIcon(QMessageBox::Question);
    box.addButton(qApp->translate(c_sMWFileList, c_sYes), QMessageBox::RejectRole);
    box.addButton(qApp->translate(c_sMWFileList, c_sNo), QMessageBox::AcceptRole);
    if (QMessageBox::AcceptRole != box.exec())
    {
        return;
    }

    emit sigDelete(fileNos);
}

void MWFileList::slotPlayBack()
{
    QList<QTableWidgetItem*> selectedItems = m_pFileListWgt->selectedItems();
    QList<quint32> fileNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        fileNos.push_back(m_pFileListWgt->item(pItem->row(), 0)->text().toInt());
    }

    // Test Start
    fileNos.push_back(0);
    // Test End

    if (fileNos.size() != 1)
    {
        QMessageBox::information(this, qApp->translate(c_sMWFileList, c_sPlayBack), qApp->translate(c_sMWFileList, c_sPlayBackTip));
        return;
    }

    DlgFilePlayblack dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    emit sigPlayBack(fileNos.first(), dlg.Type(), dlg.Prftime(), dlg.Datanum(), dlg.Prf(), dlg.Cpi());
}

void MWFileList::loadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    QString sSentUnit = "";
    QString sTotalUnit = "";
    float newBytesSent = bytesSent;
    float newBytesTotal = bytesTotal;
    formatSize(bytesSent, newBytesSent, sSentUnit);
    formatSize(bytesTotal, newBytesTotal, sTotalUnit);

    QString sMessage = QString("%0%1/%2%3").arg(newBytesSent).arg(sSentUnit).arg(newBytesTotal).arg(sTotalUnit);
    statusBar()->showMessage(sMessage);
}