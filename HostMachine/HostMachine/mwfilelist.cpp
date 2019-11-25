#include "mwfilelist.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QProgressBar>
#include <QFile>
#include "common.h"
#include "globalfun.h"

static const char *c_sMWFileList = "MWFileList";
static const char *c_sTitle = QT_TRANSLATE_NOOP("MWFileList", "ɾ��");
static const char *c_sImport = QT_TRANSLATE_NOOP("MWFileList", "����");
static const char *c_sExport = QT_TRANSLATE_NOOP("MWFileList", "����");
static const char *c_sRecord = QT_TRANSLATE_NOOP("MWFileList", "��¼");
static const char *c_sDelete = QT_TRANSLATE_NOOP("MWFileList", "ɾ��");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("MWFileList", "ˢ��");
static const char *c_sPlayBack = QT_TRANSLATE_NOOP("MWFileList", "�ط�");
static const char *c_sStop = QT_TRANSLATE_NOOP("MWFileList", "ֹͣ");
static const char *c_sFileNo = QT_TRANSLATE_NOOP("MWFileList", "�ļ����");
static const char *c_sFileName1 = QT_TRANSLATE_NOOP("MWFileList", "�ļ�����");
static const char *c_sFileSize = QT_TRANSLATE_NOOP("MWFileList", "�ļ���С");
static const char *c_sCreateDate = QT_TRANSLATE_NOOP("MWFileList", "����ʱ��");
static const char *c_sFileType = QT_TRANSLATE_NOOP("MWFileList", "�ļ�����");
static const char *c_sLBASize = QT_TRANSLATE_NOOP("MWFileList", "LBA��С��KB��");
static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("MWFileList", "ѡ��Ҫ������ļ�");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("MWFileList", "DAT�ļ�(*.dat);;�����ļ�(*.*)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("MWFileList", "�Ƿ�ֹͣ��");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("MWFileList", "�Ƿ�ɾ����");
static const char *c_sYes = QT_TRANSLATE_NOOP("MWFileList", "��");
static const char *c_sNo = QT_TRANSLATE_NOOP("MWFileList", "��");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("MWFileList", "������");

MWFileList::MWFileList(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initConnect();
}

MWFileList::~MWFileList()
{
}

/*****************************************************************************
* @brief   : ��ʼ��UI
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void MWFileList::initUI()
{
    // ������
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

    m_pProgressBar = new QProgressBar(statusBar());
    m_pProgressBar->setStyleSheet("QProgressBar { border: none;background-color: rgb(240, 240, 240) }");
    m_pProgressBar->setFixedHeight(20);

    statusBar()->setSizeGripEnabled(false);

    initFileListWgt();
}

/*****************************************************************************
* @brief   : ��ʼ���źŲ�
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void MWFileList::initConnect()
{
    connect(m_pActRecord, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActRecord, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotRecord()));

    connect(m_pActPlayBack, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActPlayBack, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotPlayBack()));

    connect(m_pActImport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActImport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotImport()));

    connect(m_pActExport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActExport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotExport()));

    connect(m_pActStop, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActStop, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotStop()));

    connect(m_pActDelete, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActDelete, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotDelete()));

    connect(m_pActRefresh, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotLogRecordAct()));
    connect(m_pActRefresh, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotRefresh()));
}

/*****************************************************************************
* @brief   : ��ʼ�����״�����
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
    m_pFileListWgt->setSelectionBehavior(QAbstractItemView::SelectRows);     // ����ѡ����Ϊʱÿ��ѡ��һ��
    m_pFileListWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);      // ���ñ��Ϊֻ��
    m_pFileListWgt->setShowGrid(true);                                       // ������ʾ������


    QHeaderView* headerView = m_pFileListWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
    for (int nColumn = 0; nColumn < m_pFileListWgt->columnCount(); ++nColumn)
    {
        headerView->setSectionResizeMode(nColumn, QHeaderView::ResizeToContents);
    }
}

/*****************************************************************************
* @brief   : Ӧ��-��¼
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readRecord(quint32 area, quint32 state)
{
    m_pProgressBar->hide();
    statusBar()->showMessage((state == 0x00) ? "record success" : "record error");
}

/*****************************************************************************
* @brief   : Ӧ��-�ط�
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readPlayBack(quint32 area, quint32 state)
{
    m_pProgressBar->hide();
    statusBar()->showMessage((state == 0x00) ? "playback success" : "playback error");
}

/*****************************************************************************
* @brief   : Ӧ��-����
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readExport(quint32 area, quint32 state)
{
    m_pProgressBar->hide();
    statusBar()->showMessage((state == 0x00) ? "export success" : "export error");
}

/*****************************************************************************
* @brief   : Ӧ��-ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readTaskStop(quint32 area, quint32 tasktype, quint32 state)
{
    m_pProgressBar->hide();
    statusBar()->showMessage((state == 0x00) ? "stop success" : "stop error");
}

/*****************************************************************************
* @brief   : Ӧ��-ɾ��
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void MWFileList::readDelete(quint32 area, quint32 state)
{
    m_pProgressBar->hide();
    statusBar()->showMessage((state == 0x00) ? "delete success" : "delete error");
}

/*****************************************************************************
* @brief   : Ӧ��-ˢ��
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
        CGlobalFun::formatSize(spFileInfo->filesize, newFileSize, sUnit);
        QString sFileSize = QString("%0%1").arg(newFileSize).arg(sUnit);
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 2, new QTableWidgetItem(sFileSize));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 3, new QTableWidgetItem(spFileInfo->datetime.toString("yyyy-MM-dd hh:mm:ss")));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 4, new QTableWidgetItem(sExt));
        QString sFileLBA = QString("%0").arg(spFileInfo->filesize / c_bSizeMax);
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 5, new QTableWidgetItem(sFileLBA));
    }
}

void MWFileList::updateProcess(QString fileName, float buffer, float total)
{
    float newFileSize = total;
    QString sFileUnit;
    CGlobalFun::formatSize(total, newFileSize, sFileUnit);

    float newBufferLen = buffer;
    QString sBufferUnit;
    CGlobalFun::formatSize(buffer, newBufferLen, sBufferUnit);

    m_pProgressBar->show();
    m_pProgressBar->setMinimum(0);
    m_pProgressBar->setMaximum(total);
    m_pProgressBar->setValue(buffer);

    QString sFormat = QString("%0 -> %1 %2/%3 %4  %p%").arg(fileName).arg(newBufferLen).arg(sBufferUnit).arg(newFileSize).arg(sFileUnit);
    m_pProgressBar->setFormat(sFormat);
}

void MWFileList::resizeEvent(QResizeEvent * event)
{
    QMainWindow::resizeEvent(event);
    m_pProgressBar->setFixedWidth(m_pFileListWgt->width());
}
