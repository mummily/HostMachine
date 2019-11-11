#include "mwfilelist.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QTableWidget>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QHeaderView>
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "QDateTime"
#include <QFrame>
#include <QGroupBox>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>

#include <QTcpSocket>
#include <QTcpServer>

#include "dlgipsetting.h"
#include "constdef.h"
#include "qtpropertymanager.h"
#include "decorateddoublepropertymanager.h"
#include "dlgareaformat.h"
#include "dlgsystemconfig.h"
#include "dlgarearecord.h"
#include "dlgfileplayblack.h"
#include "dlgfileexport.h"

static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("MWFileList", "选择要导入的文件");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("MWFileList", "DAT文件 (*.dat)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("MWFileList", "是否停止？");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("MWFileList", "是否删除？");
static const char *c_sYes = QT_TRANSLATE_NOOP("MWFileList", "是");
static const char *c_sNo = QT_TRANSLATE_NOOP("MWFileList", "否");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("MWFileList", "工具栏");
static const char *c_sFileName1 = QT_TRANSLATE_NOOP("MWFileList", "文件名称");

MWFileList::MWFileList(QTcpSocket *pCmdSocket, QTcpSocket *pDataSocket, QWidget *parent)
    : QMainWindow(parent), m_pCmdSocket(pCmdSocket), m_pDataSocket(pDataSocket)
{
    initUI();
    initConnect();
}

MWFileList::~MWFileList()
{
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
    QToolBar *toolBar = addToolBar(qApp->translate(c_sHostMachine, c_sToolBar));
    toolBar->toggleViewAction()->setEnabled(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setAllowedAreas(Qt::TopToolBarArea);
    toolBar->setMovable(false);
    toolBar->setStyleSheet("QToolBar {border: none;}");

    QString sIcon = QString("%1/Image/import.png").arg(qApp->applicationDirPath());
    m_pActImport = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sImport));
    m_pActImport->setStatusTip(m_pActImport->text());

    sIcon = QString("%1/Image/export.png").arg(qApp->applicationDirPath());
    m_pActExport = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sExport));
    m_pActExport->setStatusTip(m_pActExport->text());

    sIcon = QString("%1/Image/record.png").arg(qApp->applicationDirPath());
    m_pActRecord = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sRecord));
    m_pActRecord->setStatusTip(m_pActRecord->text());

    sIcon = QString("%1/Image/delete.png").arg(qApp->applicationDirPath());
    m_pActDelete = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sDelete));
    m_pActDelete->setStatusTip(m_pActDelete->text());

    sIcon = QString("%1/Image/refresh.png").arg(qApp->applicationDirPath());
    m_pActRefresh = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sRefresh));
    m_pActRefresh->setStatusTip(m_pActRefresh->text());

    sIcon = QString("%1/Image/playback.png").arg(qApp->applicationDirPath());
    m_pActPlayBack = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sPlayback));
    m_pActPlayBack->setStatusTip(m_pActPlayBack->text());

    sIcon = QString("%1/Image/stop.png").arg(qApp->applicationDirPath());
    m_pActStop = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sStop));
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
    connect(m_pActRecord, SIGNAL(triggered(bool)), this, SLOT(slotRecord()));

    connect(m_pActPlayBack, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActPlayBack, SIGNAL(triggered(bool)), this, SLOT(slotPlayBack()));

    connect(m_pActImport, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActImport, SIGNAL(triggered(bool)), this, SLOT(slotImport()));

    connect(m_pActExport, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActExport, SIGNAL(triggered(bool)), this, SLOT(slotExport()));

    connect(m_pActStop, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActStop, SIGNAL(triggered(bool)), this, SLOT(slotStop()));

    connect(m_pActDelete, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActDelete, SIGNAL(triggered(bool)), this, SLOT(slotDelete()));

    connect(m_pActRefresh, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActRefresh, SIGNAL(triggered(bool)), this, SLOT(slotRefresh()));

    connect(m_pCmdSocket, SIGNAL(readyRead()), this, SLOT(slotCmdReadyRead()));
    connect(m_pCmdSocket, SIGNAL(readyRead()), this, SLOT(slotDataReadyRead()));
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
    headerList << qApp->translate(c_sHostMachine, c_sFileNo) 
        << qApp->translate(c_sHostMachine, c_sFileName1)
        << qApp->translate(c_sHostMachine, c_sFileSize)
        << qApp->translate(c_sHostMachine, c_sCreateDate)
        << qApp->translate(c_sHostMachine, c_sFileType)
        << qApp->translate(c_sHostMachine, c_sLBASize);

    m_pFileListWgt->setColumnCount(headerList.size());
    m_pFileListWgt->setHorizontalHeaderLabels(headerList);
    m_pFileListWgt->setShowGrid(true);

    QHeaderView* headerView = m_pFileListWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
}

/*****************************************************************************
* @brief   : 应答消息响应
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void MWFileList::slotCmdReadyRead()
{
    QDataStream in(m_pCmdSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_pCmdSocket->bytesAvailable() < sizeof(quint32))
        return;

    quint32 respondType;
    in >> respondType;
    if (respondType == SC_Record)
    {
        quint32 area, state;
        in >> area >> state;

        readRecord(area, state);
    }
    else if (respondType == SC_PlayBack)
    {
        quint32 area, state;
        in >> area >> state;

        readPlayBack(area, state);
    }
    else if (respondType == SC_Stop)
    {
        quint32 area, state;
        in >> area >> state;

        readStop(area, state);
    }
    else if (respondType == SC_Delete)
    {
        quint32 area, state;
        in >> area >> state;

        readDelete(area, state);
    }
    else if (respondType == SC_Refresh)
    {
        tagAreaFileInfos fileInfos;
        memset(&fileInfos, 0, sizeof(tagAreaFileInfos));
        in >> fileInfos.areano >> fileInfos.fileno >> fileInfos.filenum;

        list<shared_ptr<tagAreaFileInfo>> lstFileInfo;
        for (int nIndex=0;nIndex<fileInfos.filenum;++nIndex)
        {
            char* filename = new char[128];
            memset(filename, 0, sizeof(char)*128);

            quint64 datetime;
            quint32 fileno;
            float filesize;
            in >> filename >> datetime >> fileno >> filesize;

            shared_ptr<tagAreaFileInfo> spFileInfo = make_shared<tagAreaFileInfo>();
            spFileInfo->sFileName = QString::fromLocal8Bit(filename);
            spFileInfo->datetime = QDateTime::fromMSecsSinceEpoch(datetime);
            spFileInfo->fileno = fileno;
            spFileInfo->filesize = filesize;

            lstFileInfo.push_back(spFileInfo);
        }
        fileInfos.lstFileInfo.swap(lstFileInfo);
        readRefresh(fileInfos);
    }
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2019/11/10
* @param:  : 
*****************************************************************************/
void MWFileList::slotDataReadyRead()
{
    QDataStream in(m_pDataSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_pDataSocket->bytesAvailable() < sizeof(quint32))
        return;

    quint32 respondType;
    in >> respondType;
    if (respondType == SC_Import)
    {
        quint32 area, state;
        in >> area >> state;

        readImport(area, state);
    }
    else if (respondType == SC_Export)
    {
        quint32 area, state;
        in >> area >> state;

        readExport(area, state);
    }
}

/*****************************************************************************
* @brief   : 请求-记录
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotRecord()
{
    DlgAreaRecord dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    quint32 areano = dlg.Area(); 
    quint64 time = QDateTime::currentMSecsSinceEpoch();
    char* filename = new char[128];
    memset(filename, 0, sizeof(char)*128);
    QString sFileName = dlg.Filename();

    QByteArray ba = sFileName.toLatin1();
    filename = ba.data();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Record << areano << time;
    out.writeBytes(filename, 128-4);

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();

    // delete[] filename;
}

/*****************************************************************************
* @brief   : 请求-回放
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotPlayBack()
{
    DlgFilePlayblack dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
#pragma message("MWFileList::slotPlayBack 完善分区号、文件编号")
    out << CS_PlayBack << quint32(0) << quint32(0) // 文件编号
        << dlg.Type() << dlg.Prftime() << dlg.Datanum() << dlg.Prf() << dlg.Cpi();

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : 请求-导入
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotImport()
{
#pragma message("MWFileList::slotImport 导入是选定一个分区执行导入，可单个可批量")

    QString sFile = QFileDialog::getOpenFileName(
        this, qApp->translate(c_sHostMachine, c_sImportFileTip),
        "/",
        qApp->translate(c_sHostMachine, c_sImportFileExt));
    if (sFile.isEmpty())
        return;

    QFileInfo info(sFile);

    // 分区号
    quint32 areano = 0;
    float filesize = info.size() / 1024.0;
    // 开始时间
    qint64 startTime = QDateTime::currentMSecsSinceEpoch();
    // 文件名
    char* filename = new char[128];
    memset(filename, 0, sizeof(char)*128);
    QByteArray ba = sFile.toLatin1();
    filename = ba.data();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Import << areano << filesize
        << startTime;
    out.writeBytes(filename, 128-4);

    m_pDataSocket->write(block);
    m_pDataSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : 请求-导出
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotExport()
{
    // 分区号
    quint32 areano = 0;

    // 1个执行单个导出 >1个执行多个导出
    int nCount = 1;

    if (nCount == 1)
    {
        float filesize = 1.3;
        DlgFileExport dlg(filesize, this);
        if (QDialog::Accepted != dlg.exec())
            return;

        // 文件编号
        quint32 fileno = 1;

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_Export << areano << fileno
            << dlg.Startpos() << dlg.Exportsize();

        m_pDataSocket->write(block);
        m_pDataSocket->waitForReadyRead();
    }
    else
    {
#pragma message("MWFileList::slotExport 批量导出")
    }
}

/*****************************************************************************
* @brief   : 请求-停止
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotStop()
{
    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    box.setText(qApp->translate(c_sHostMachine, c_sIsStop));
    box.setIcon(QMessageBox::Question);
    box.addButton(qApp->translate(c_sHostMachine, c_sYes), QMessageBox::RejectRole);
    box.addButton(qApp->translate(c_sHostMachine, c_sNo), QMessageBox::AcceptRole);
    if (QMessageBox::AcceptRole != box.exec())
    {
        return;
    }

    // 分区号
    quint32 areano = 0;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Stop << areano;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : 请求-删除
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotDelete()
{
#pragma message("MWFileList::slotDelete 批量删除")
    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    box.setText(qApp->translate(c_sHostMachine, c_sIsDelete));
    box.setIcon(QMessageBox::Question);
    box.addButton(qApp->translate(c_sHostMachine, c_sYes), QMessageBox::RejectRole);
    box.addButton(qApp->translate(c_sHostMachine, c_sNo), QMessageBox::AcceptRole);
    if (QMessageBox::AcceptRole != box.exec())
    {
        return;
    }

    // 分区号
    quint32 areano = 0;

    // 文件编号
    quint32 fileno = 1;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Delete << areano << fileno;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : 请求-刷新
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::slotRefresh()
{
    // 分区号
    quint32 areano = 0;

    // 起始文件编号
    quint32 fileno = 1;
    // 刷新文件数
    quint32 filenum = 8;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Refresh << areano << fileno << filenum;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
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
void MWFileList::readImport(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "import success" : "import error");
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
void MWFileList::readStop(quint32 area, quint32 state)
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
#pragma message("MWFileList::readRefresh 刷新文件列表区界面")
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