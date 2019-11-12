#include "mwfilelist.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTableWidget>
#include <QHeaderView>

static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("MWFileList", "ѡ��Ҫ������ļ�");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("MWFileList", "DAT�ļ� (*.dat)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("MWFileList", "�Ƿ�ֹͣ��");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("MWFileList", "�Ƿ�ɾ����");
static const char *c_sYes = QT_TRANSLATE_NOOP("MWFileList", "��");
static const char *c_sNo = QT_TRANSLATE_NOOP("MWFileList", "��");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("MWFileList", "������");
static const char *c_sFileName1 = QT_TRANSLATE_NOOP("MWFileList", "�ļ�����");

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
* @brief   : ��ʼ���źŲ�
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void MWFileList::initConnect()
{
    connect(m_pActRecord, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActRecord, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotRecord()));

    connect(m_pActPlayBack, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActPlayBack, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotPlayBack()));

    connect(m_pActImport, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActImport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotImport()));

    connect(m_pActExport, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActExport, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotExport()));

    connect(m_pActStop, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActStop, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotStop()));

    connect(m_pActDelete, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActDelete, SIGNAL(triggered(bool)), parentWidget(), SLOT(slotDelete()));

    connect(m_pActRefresh, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
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
* @brief   : Ӧ��-��¼
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::readRecord(quint32 area, quint32 state)
{
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
    statusBar()->showMessage((state == 0x00) ? "playback success" : "playback error");
}

/*****************************************************************************
* @brief   : Ӧ��-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::readImport(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "import success" : "import error");
}

/*****************************************************************************
* @brief   : Ӧ��-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::readExport(quint32 area, quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "export success" : "export error");
}

/*****************************************************************************
* @brief   : Ӧ��-ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void MWFileList::readStop(quint32 area, quint32 state)
{
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
#pragma message("MWFileList::readRefresh ˢ���ļ��б�������")
}

/*****************************************************************************
* @brief   : ���Actionʱ����־��¼
* @author  : wb
* @date    : 2019/11/02
* @param:  : ��
*****************************************************************************/
void MWFileList::slotLogRecord()
{
    QAction* pAction = qobject_cast<QAction *>(sender());
    if (NULL == pAction)
        return;

    logRecord(pAction->text());
}

/*****************************************************************************
* @brief   : ��־��¼
* @author  : wb
* @date    : 2019/11/02
* @param:  : �����ϵͳ��Ϣ
*****************************************************************************/
void MWFileList::logRecord(QString sText)
{
    QString sDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}