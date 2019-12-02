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
static const char *c_sArea = QT_TRANSLATE_NOOP("MWFileList", "����");

// ˢ�½��
static const char *c_sRefreshResult = QT_TRANSLATE_NOOP("MWFileList", "ˢ�³ɹ�");

// �طŽ��
static const char *c_sPlayBackResult0 = QT_TRANSLATE_NOOP("MWFileList", "�طųɹ�");
static const char *c_sPlayBackResult1 = QT_TRANSLATE_NOOP("MWFileList", "���������쳣");

// ɾ�����
static const char *c_sDeleteResult0 = QT_TRANSLATE_NOOP("MWFileList", "ɾ���ɹ�");
static const char *c_sDeleteResult1 = QT_TRANSLATE_NOOP("MWFileList", "���������쳣");

// ��¼���
static const char *c_sRecordResult0 = QT_TRANSLATE_NOOP("MWFileList", "��ʼ��¼");
static const char *c_sRecordResult1 = QT_TRANSLATE_NOOP("MWFileList", "��Դ����");
static const char *c_sRecordResult2 = QT_TRANSLATE_NOOP("MWFileList", "���������쳣");

// ����ֹͣ���
static const char *c_sTaskStopResult0 = QT_TRANSLATE_NOOP("MWFileList", "����ֹͣ�ɹ�");
static const char *c_sTaskStopResult1 = QT_TRANSLATE_NOOP("MWFileList", "���������쳣");

// ������
static const char *c_sImportResult0 = QT_TRANSLATE_NOOP("MWFileList", "��ʼ����");
static const char *c_sImportResult1 = QT_TRANSLATE_NOOP("MWFileList", "��Դ����");
static const char *c_sImportResult2 = QT_TRANSLATE_NOOP("MWFileList", "���������쳣");

// �������
static const char *c_sExportResult0 = QT_TRANSLATE_NOOP("MWFileList", "��ʼ����");
static const char *c_sExportResult1 = QT_TRANSLATE_NOOP("MWFileList", "��Դ����");
static const char *c_sExportResult2 = QT_TRANSLATE_NOOP("MWFileList", "���������쳣");


CMWFileList::CMWFileList(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initConnect();
}

CMWFileList::~CMWFileList()
{
}

/*****************************************************************************
* @brief   : ��ʼ��UI
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void CMWFileList::initUI()
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

    m_pProgressBar = new QProgressBar(this);
    m_pProgressBar->setStyleSheet("QProgressBar { border: none;background-color: rgb(240, 240, 240) }");
    m_pProgressBar->setFixedHeight(20);

    statusBar()->addWidget(m_pProgressBar, 1);
    statusBar()->setSizeGripEnabled(false);

    initFileListWgt();
}

/*****************************************************************************
* @brief   : ��ʼ���źŲ�
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void CMWFileList::initConnect()
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

    // ����
    connect(this, SIGNAL(siglogRecord(QString)), parentWidget(), SLOT(slotLogRecord(QString)));
}

/*****************************************************************************
* @brief   : ��ʼ�����״�����
* @author  : wb
* @date    : 2019/10/19
* @param:  :
*****************************************************************************/
void CMWFileList::initFileListWgt()
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
* @brief   : Ӧ��-ˢ��
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void CMWFileList::readRefresh(tagAreaFileInfos &fileInfos)
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
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 2, new QTableWidgetItem(CGlobalFun::formatSize(spFileInfo->filesize)));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 3, new QTableWidgetItem(spFileInfo->datetime.toString("yyyy-MM-dd hh:mm:ss")));
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 4, new QTableWidgetItem(sExt));
        QString sFileLBA = QString("%0").arg(spFileInfo->filesize / c_bSizeMax);
        m_pFileListWgt->setItem(m_pFileListWgt->rowCount() - 1, 5, new QTableWidgetItem(sFileLBA));
    }

    QString sInfo = qApp->translate(c_sMWFileList, c_sRefreshResult);

    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);
    emit siglogRecord(sInfo);
}

void CMWFileList::updateProcess(QString fileName, float buffer, float total)
{
    m_pProgressBar->show();
    m_pProgressBar->setMinimum(0);
    m_pProgressBar->setMaximum(total);
    m_pProgressBar->setValue(buffer);

    QString sFormat = QString("%0 -> %1/%2  %p%").arg(fileName).arg(CGlobalFun::formatSize(buffer)).arg(CGlobalFun::formatSize(total));
    m_pProgressBar->setFormat(sFormat);
}

void CMWFileList::readPlayBack(quint32 area, quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sPlayBackResult0);
    }
    else
    {
        sInfo = qApp->translate(c_sMWFileList, c_sPlayBackResult1);
    }

    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);

    QString sLog = QString("%0 %1").arg(area).arg(sInfo);
    emit siglogRecord(sLog);
}

void CMWFileList::readRecord(quint32 area, quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sRecordResult0);
    }
    else if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sRecordResult1);
    }
    else
    {
        sInfo = qApp->translate(c_sMWFileList, c_sRecordResult2);
    }

    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);

    QString sLog = QString("%0 %1").arg(area).arg(sInfo);
    emit siglogRecord(sLog);
}

void CMWFileList::readDelete(quint32 area, quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sDeleteResult0);
    }
    else
    {
        sInfo = qApp->translate(c_sMWFileList, c_sDeleteResult1);
    }

    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);
    QString sLog = QString("%0%1 %2").arg(qApp->translate(c_sMWFileList, c_sArea)).arg(area).arg(sInfo);
    emit siglogRecord(sLog);
}

/*****************************************************************************
* @brief   : Ӧ��-ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void CMWFileList::readTaskStop(quint32 area, quint32 tasktype, quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sTaskStopResult0);
    }
    else
    {
        sInfo = qApp->translate(c_sMWFileList, c_sTaskStopResult1);
    }

    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);

    QString sLog = QString("%0 %1").arg(area).arg(sInfo);
    emit siglogRecord(sLog);
}

/*****************************************************************************
* @brief   : Ӧ��-����
* @author  : wb
* @date    : 2019/10/28
* @param:  :
*****************************************************************************/
void CMWFileList::readExport(quint32 area, quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sExportResult0);
    }
    else if (state == 0x01)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sExportResult1);
    }
    else
    {
        sInfo = qApp->translate(c_sMWFileList, c_sExportResult2);
    }

    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);

    QString sLog = QString("%0 %1").arg(area).arg(sInfo);
    emit siglogRecord(sLog);
}

void CMWFileList::readImport(quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sImportResult0);
    }
    else if (state == 0x01)
    {
        sInfo = qApp->translate(c_sMWFileList, c_sImportResult1);
    }
    else
    {
        sInfo = qApp->translate(c_sMWFileList, c_sImportResult2);
    }

    m_pProgressBar->reset();
    m_pProgressBar->hide();
    statusBar()->showMessage(sInfo);
}
