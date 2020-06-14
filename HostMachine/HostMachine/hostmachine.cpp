
#include "hostmachine.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QTableWidget>
#include <QTabWidget>
#include <QSplitter>
#include <QHeaderView>
#include <QDateTime>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>
#include <QProgressBar>
#include <QElapsedTimer>
#include <QPushButton>

#include <QTcpSocket>
#include <QTcpServer>

#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "decorateddoublepropertymanager.h"

#include "dlgipsetting.h"
#include "dlgareaformat.h"
#include "dlgsystemconfig.h"
#include "mwfilelist.h"
#include "dlgarearecord.h"
#include "dlgfileexport.h"
#include "datasocket.h"
#include "globalfun.h"
#include "dlgfileplayblack.h"
#include "taskstoptype.h"
#include "config.h"

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "����Ӧ�����");
static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("HostMachine", "ѡ��Ҫ������ļ�");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("HostMachine", "DAT�ļ�(*.dat);;�����ļ�(*.*)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("HostMachine", "�Ƿ�ֹͣ��");
static const char *c_sIsStopTip1 = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��Ҫֹͣ������");
static const char *c_sIsStopTip2 = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��ִ���е�����");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("HostMachine", "�Ƿ�ɾ����");
static const char *c_sYes = QT_TRANSLATE_NOOP("HostMachine", "��");
static const char *c_sNo = QT_TRANSLATE_NOOP("HostMachine", "��");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("HostMachine", "������");
static const char *c_sIsExportTip = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��Ҫ�������ļ���");
static const char *c_sIsDeleteTip = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��Ҫɾ�����ļ���");
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP����");
static const char *c_sIPSettingTip = QT_TRANSLATE_NOOP("HostMachine", "�����IP���ã�");
static const char *c_sPathTitle = QT_TRANSLATE_NOOP("HostMachine", "ѡ�񵼳��ļ�·��");
static const char *c_sNetConnectError = QT_TRANSLATE_NOOP("HostMachine", "�޷����ӷ������������������ӣ�");
static const char *c_sPlayBackTip = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��һ���ļ��طţ�");
static const char *c_sRequestCancel = QT_TRANSLATE_NOOP("HostMachine", "��ִ�������񣬵�ǰ������ȡ����");

// ϵͳ�˵�
static const char *c_sSystemConfig = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ����");
static const char *c_sSystemOperation = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ����");
static const char *c_sAbout = QT_TRANSLATE_NOOP("HostMachine", "����");

// ������
static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("HostMachine", "�Լ�");
static const char *c_sFormat = QT_TRANSLATE_NOOP("HostMachine", "��ʽ��");
static const char *c_sImport = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sExport = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sRecord = QT_TRANSLATE_NOOP("HostMachine", "��¼");
static const char *c_sDelete = QT_TRANSLATE_NOOP("HostMachine", "ɾ��");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("HostMachine", "ˢ��");
static const char *c_sPlayBack = QT_TRANSLATE_NOOP("HostMachine", "�ط�");
static const char *c_sStop = QT_TRANSLATE_NOOP("HostMachine", "ֹͣ");

// ������
static const char *c_sPropertyTitle1 = QT_TRANSLATE_NOOP("HostMachine", "���̿������");
static const char *c_sPropertyGroup1_1 = QT_TRANSLATE_NOOP("HostMachine", "ԭʼ���ݷ���");
static const char *c_sPropertyGroup1_2 = QT_TRANSLATE_NOOP("HostMachine", "�״�������");
static const char *c_sPropertyGroup1_3 = QT_TRANSLATE_NOOP("HostMachine", "���ͼƬ����");
static const char *c_sPropertyGroup1_4 = QT_TRANSLATE_NOOP("HostMachine", "�����Ƶ����");
static const char *c_sPropertyGroup1_5 = QT_TRANSLATE_NOOP("HostMachine", "������ݷ���");
static const char *c_sPropertyGroup1_6 = QT_TRANSLATE_NOOP("HostMachine", "������Ϣ");
static const char *c_sPropertyGroup1_7 = QT_TRANSLATE_NOOP("HostMachine", "�汾��");
static const char *c_sProperty1_1 = QT_TRANSLATE_NOOP("HostMachine", "�ܴ�С");
static const char *c_sProperty1_2 = QT_TRANSLATE_NOOP("HostMachine", "���ô�С");
static const char *c_sProperty1_3 = QT_TRANSLATE_NOOP("HostMachine", "δ�ðٷֱ�");
static const char *c_sProperty1_4 = QT_TRANSLATE_NOOP("HostMachine", "�ļ�����");
static const char *c_sProperty1_5 = QT_TRANSLATE_NOOP("HostMachine", "��ǰ״̬");
static const char *c_sProperty1_6 = QT_TRANSLATE_NOOP("HostMachine", "ͨ������״̬");
static const char *c_sProperty1_7 = QT_TRANSLATE_NOOP("HostMachine", "ͨ��ѡ��״̬");
static const char *c_sProperty1_8 = QT_TRANSLATE_NOOP("HostMachine", "ͨ������");
static const char *c_sProperty1_9 = QT_TRANSLATE_NOOP("HostMachine", "�̼��汾��");
static const char *c_sProperty1_10 = QT_TRANSLATE_NOOP("HostMachine", "FPGA�汾��");

// �����б��
static const char *c_sTaskHeader1 = QT_TRANSLATE_NOOP("HostMachine", "���");
static const char *c_sTaskHeader2 = QT_TRANSLATE_NOOP("HostMachine", "��������");
static const char *c_sTaskHeader3 = QT_TRANSLATE_NOOP("HostMachine", "��������");
static const char *c_sTaskHeader4 = QT_TRANSLATE_NOOP("HostMachine", "����ʼʱ��");
static const char *c_sTaskHeader5 = QT_TRANSLATE_NOOP("HostMachine", "�ܴ�С");
static const char *c_sTaskHeader6 = QT_TRANSLATE_NOOP("HostMachine", "����ɴ�С");
static const char *c_sTaskHeader7 = QT_TRANSLATE_NOOP("HostMachine", "�ٷֱ�");
static const char *c_sTaskHeader8 = QT_TRANSLATE_NOOP("HostMachine", "����(MB/S)");
static const char *c_sTaskHeader9 = QT_TRANSLATE_NOOP("HostMachine", "״̬");
static const char *c_sTaskHeader10 = QT_TRANSLATE_NOOP("HostMachine", "��ʱ");

// ��־���
static const char *c_sOpenSoftware = QT_TRANSLATE_NOOP("HostMachine", "�����");
static const char *c_sCloseSoftware = QT_TRANSLATE_NOOP("HostMachine", "�ر����");

// ״̬��
static const char *c_sDisConnect = QT_TRANSLATE_NOOP("HostMachine", "δ����");
static const char *c_sReady = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sContactUs = QT_TRANSLATE_NOOP("HostMachine", "��ϵ����");
static const char *c_sCmdDisconnect = QT_TRANSLATE_NOOP("HostMachine", "���������ѶϿ���");
static const char *c_sDataDisconnect = QT_TRANSLATE_NOOP("HostMachine", "���������ѶϿ���");

// ����״̬
static const char *c_sAreaState0 = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sAreaState1 = QT_TRANSLATE_NOOP("HostMachine", "��");
static const char *c_sAreaState2 = QT_TRANSLATE_NOOP("HostMachine", "д");
static const char *c_sAreaState3 = QT_TRANSLATE_NOOP("HostMachine", "��д");

// ͨ��״̬
static const char *c_sChannelState0 = QT_TRANSLATE_NOOP("HostMachine", "δ����");
static const char *c_sChannelState1 = QT_TRANSLATE_NOOP("HostMachine", "������");

// ͨ��ѡ��
static const char *c_sChannelChoice0 = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��");
static const char *c_sChannelChoice1 = QT_TRANSLATE_NOOP("HostMachine", "δѡ��");

// ��ʽ�����
static const char *c_sFormatResult0 = QT_TRANSLATE_NOOP("HostMachine", "��ʽ���ɹ�");
static const char *c_sFormatResult1 = QT_TRANSLATE_NOOP("HostMachine", "��ʽ��ʧ��");
static const char *c_sFormatResult2 = QT_TRANSLATE_NOOP("HostMachine", "���������쳣");

// ϵͳ���ý��
static const char *c_sSystemConfigResult0 = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ���óɹ�");
static const char *c_sSystemConfigResult1 = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ����ʧ��");
static const char *c_sSystemConfigResult2 = QT_TRANSLATE_NOOP("HostMachine", "���������쳣");

// ����״̬
static const char *c_sTaskState0 = QT_TRANSLATE_NOOP("HostMachine", "�ȴ�ִ��");
static const char *c_sTaskState1 = QT_TRANSLATE_NOOP("HostMachine", "ִ����");
static const char *c_sTaskState2 = QT_TRANSLATE_NOOP("HostMachine", "���");
static const char *c_sTaskState3 = QT_TRANSLATE_NOOP("HostMachine", "����");

HostMachine::HostMachine(QWidget *parent)
    : QMainWindow(parent), m_sAddr(""), m_bShowTaskStop(false), m_sImportPath(""), m_sExportPath(""),
    m_nProgressBarUpdateInterval(c_uProgressBarUpdateInterval), m_nProcessEventInterval(c_uProcessEventInterval)
{
    initData();
    initUI();
    initLayout();
    initConnect();

    QTimer::singleShot(10, this, SLOT(slotInit()));
}

HostMachine::~HostMachine()
{
    slotLogRecord(qApp->translate(c_sHostMachine, c_sCloseSoftware));
    closeLog();

    m_pCmdSocket->disconnect(this, SLOT(disconnectCmd()));
    m_pCmdSocket->close();
    m_pDataSocket->disconnect(this, SLOT(disconnectData()));
    m_pDataSocket->close();

    QString sConfigFile = QString("%0/%1.json").arg(qApp->applicationDirPath()).arg(qApp->applicationName());
    if (QFile::exists(sConfigFile))
    {
        Config config(sConfigFile);
        config.write("import.path", m_sImportPath);
        config.write("export.path", m_sExportPath);

        config.write("playback.type", m_spPlayBack->type);
        config.write("playback.prftime", m_spPlayBack->prftime);
        config.write("playback.datanum", m_spPlayBack->datanum);
        config.write("playback.prf", m_spPlayBack->prf);
        config.write("playback.cpi", m_spPlayBack->cpi);

        config.sync();
    }
}

/*****************************************************************************
* @brief   : ��ʼ��UI
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initUI()
{
    setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    resize(1124, 726);

    // �˵���
    // �˵��IP����
    m_pActIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    m_pActIPSetting->setStatusTip(m_pActIPSetting->text());

    // �˵��ϵͳ����
    m_pMenuSystemControl = menuBar()->addMenu(qApp->translate(c_sHostMachine, c_sSystemOperation));
    m_pMenuSystemControl->setStatusTip(m_pMenuSystemControl->title());
    {
        QString sIcon = QString("%1/Image/checkself.png").arg(qApp->applicationDirPath());
        m_pActCheckSelf = m_pMenuSystemControl->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sCheckSelf));
        m_pActCheckSelf->setStatusTip(m_pActCheckSelf->text());

        sIcon = QString("%1/Image/format.png").arg(qApp->applicationDirPath());
        m_pActFormat = m_pMenuSystemControl->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sFormat));
        m_pActFormat->setStatusTip(m_pActFormat->text());

        sIcon = QString("%1/Image/config.png").arg(qApp->applicationDirPath());
        m_pActSystemConfig = m_pMenuSystemControl->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sSystemConfig));
        m_pActSystemConfig->setStatusTip(m_pActSystemConfig->text());
    }
    // �˵������
    m_pActAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));
    m_pActAbout->setStatusTip(m_pActAbout->text());

    // �ļ��б��
    m_pTabWgt = new QTabWidget(this);
    m_pTabWgt->setTabPosition(QTabWidget::South);
    m_pTabWgt->setDocumentMode(true);

    m_pLDOriginalWgt = new CMWFileList(this);
    m_pLDResultWgt = new CMWFileList(this);
    m_pGDImgWgt = new CMWFileList(this);
    m_pGDVidioWgt = new CMWFileList(this);
    m_pHHDataWgt = new CMWFileList(this);

    m_pTabWgt->addTab(m_pLDOriginalWgt, qApp->translate(c_sHostMachine, c_sPropertyGroup1_1));
    m_pTabWgt->addTab(m_pLDResultWgt, qApp->translate(c_sHostMachine, c_sPropertyGroup1_2));
    m_pTabWgt->addTab(m_pGDImgWgt, qApp->translate(c_sHostMachine, c_sPropertyGroup1_3));
    m_pTabWgt->addTab(m_pGDVidioWgt, qApp->translate(c_sHostMachine, c_sPropertyGroup1_4));
    m_pTabWgt->addTab(m_pHHDataWgt, qApp->translate(c_sHostMachine, c_sPropertyGroup1_5));

    // �����б��
    m_pTaskWgt = new QTableWidget(this);
    initTaskWgt();

    m_pSplitter = new QSplitter(Qt::Vertical, this);
    m_pSplitter->addWidget(m_pTabWgt);
    m_pSplitter->addWidget(m_pTaskWgt);
    QList<int> sizeList;
    sizeList << 400 << 200;
    m_pSplitter->setSizes(sizeList);
    m_pSplitter->setOpaqueResize(true);
    m_pSplitter->setChildrenCollapsible(false);

    // ������
    m_pPropertyWgt = new QtTreePropertyBrowser();
    initPropertyWgt();

    QDockWidget *pDockWgt = new QDockWidget(qApp->translate(c_sHostMachine, c_sPropertyTitle1), this);
    pDockWgt->setFeatures(QDockWidget::AllDockWidgetFeatures);
    pDockWgt->setAllowedAreas(Qt::RightDockWidgetArea);
    pDockWgt->setWidget(m_pPropertyWgt);
    addDockWidget(Qt::RightDockWidgetArea, pDockWgt);

    // ״̬��
    statusBar()->setSizeGripEnabled(true);

    m_pIPLabel = new QLabel(this);
    statusBar()->addPermanentWidget(m_pIPLabel); //��ʾIP��Ϣ

    m_pCmdLabel = new QLabel(this);
    QString sCmdLabel = QString("%1 %2").arg(c_uCommandPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pCmdLabel->setText(sCmdLabel);
    statusBar()->addPermanentWidget(m_pCmdLabel); //��ʾ״̬��Ϣ

    m_pDataLabel = new QLabel(this);
    QString sDataLabel = QString("%1 %2").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pDataLabel->setText(sDataLabel);
    statusBar()->addPermanentWidget(m_pDataLabel); //��ʾ״̬��Ϣ    

    QLabel *contactUs = new QLabel(this);
    contactUs->setFrameStyle(QFrame::Sunken);
    QString sText = QString("<a href=\"http://www.baidu.com/\">%0").arg(qApp->translate(c_sHostMachine, c_sContactUs));
    contactUs->setText(sText);
    contactUs->setOpenExternalLinks(true); //���ÿ��Դ���վ����
    statusBar()->addPermanentWidget(contactUs); //��ʾ������Ϣ
}

/*****************************************************************************
* @brief   : ��ʼ������
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initLayout()
{
    m_pSplitter->setContentsMargins(3, 0, 0, 0);
    setCentralWidget(m_pSplitter);
}

/*****************************************************************************
* @brief   : ��ʼ���źŲ�
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initConnect()
{
    // Menubar & Toolbar
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotLogRecordAct()));
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotIPSetting()));

    connect(m_pActCheckSelf, SIGNAL(triggered(bool)), this, SLOT(slotLogRecordAct()));
    connect(m_pActCheckSelf, SIGNAL(triggered(bool)), this, SLOT(slotCheckSelf()));

    connect(m_pActFormat, SIGNAL(triggered(bool)), this, SLOT(slotLogRecordAct()));
    connect(m_pActFormat, SIGNAL(triggered(bool)), this, SLOT(slotFormat()));

    connect(m_pActSystemConfig, SIGNAL(triggered(bool)), this, SLOT(slotLogRecordAct()));
    connect(m_pActSystemConfig, SIGNAL(triggered(bool)), this, SLOT(slotSystemConfig()));

    connect(m_pTabWgt, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));

    // TCP
    connect(m_pCmdSocket, SIGNAL(connected()), this, SLOT(connectedCmd()));
    connect(m_pCmdSocket, SIGNAL(disconnected()), this, SLOT(disconnectCmd()));
    connect(m_pCmdSocket, SIGNAL(readyRead()), this, SLOT(readyReadCmd()));
    connect(m_pCmdSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorCmd()));

    connect(m_pDataSocket, SIGNAL(connected()), this, SLOT(connectedData()));
    connect(m_pDataSocket, SIGNAL(disconnected()), this, SLOT(disconnectData()));
    connect(m_pDataSocket, SIGNAL(readyRead()), m_pDataSocket, SLOT(readyRead()));
    connect(m_pDataSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorData()));

    connect(m_pDataSocket, SIGNAL(importStart(qint32, QString, qint64, qint64)), this, SLOT(slotImportStart(qint32, QString, qint64, qint64)));
    connect(m_pDataSocket, SIGNAL(importUpdate(qint32, QString, qint64, qint64)), this, SLOT(slotImportUpdate(qint32, QString, qint64, qint64)));
    connect(m_pDataSocket, SIGNAL(importStop(qint32, QString, qint64, qint64)), this, SLOT(slotImportStop(qint32, QString, qint64, qint64)));
    connect(m_pDataSocket, SIGNAL(importCompleted(qint32, QString, qint64, qint64)), this, SLOT(slotImportCompleted(qint32, QString, qint64, qint64)));

    connect(m_pDataSocket, SIGNAL(exportStart(qint32, QString, qint64, qint64)), this, SLOT(slotExportStart(qint32, QString, qint64, qint64)));
    connect(m_pDataSocket, SIGNAL(exportUpdate(qint32, QString, qint64, qint64)), this, SLOT(slotExportUpdate(qint32, QString, qint64, qint64)));
    connect(m_pDataSocket, SIGNAL(exportStop(qint32, QString, qint64, qint64)), this, SLOT(slotExportStop(qint32, QString, qint64, qint64)));
    connect(m_pDataSocket, SIGNAL(exportCompleted(qint32, QString, qint64, qint64)), this, SLOT(slotExportCompleted(qint32, QString, qint64, qint64)));
}

/*****************************************************************************
* @brief   : ��ʼ��������
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initTaskWgt()
{
    QStringList headerList;
    headerList << "" // TaskType
        << qApp->translate(c_sHostMachine, c_sTaskHeader1)
        << qApp->translate(c_sHostMachine, c_sTaskHeader2)
        << qApp->translate(c_sHostMachine, c_sTaskHeader3)
        << qApp->translate(c_sHostMachine, c_sTaskHeader4)
        << qApp->translate(c_sHostMachine, c_sTaskHeader5)
        << qApp->translate(c_sHostMachine, c_sTaskHeader6)
        << qApp->translate(c_sHostMachine, c_sTaskHeader7)
        << qApp->translate(c_sHostMachine, c_sTaskHeader8)
        << qApp->translate(c_sHostMachine, c_sTaskHeader9)
        << qApp->translate(c_sHostMachine, c_sTaskHeader10)
        << "";

    m_pTaskWgt->setShowGrid(false);
    m_pTaskWgt->setColumnCount(headerList.size());
    m_pTaskWgt->setHorizontalHeaderLabels(headerList);
    m_pTaskWgt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTaskWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTaskWgt->setColumnHidden(0, true);
    m_pTaskWgt->setColumnHidden(11, !m_bShowTaskStop);

    for(int nIndex = 0; nIndex < c_uTaskQueryNum; ++ nIndex)
    {
        m_pTaskWgt->insertRow(nIndex);
        m_pTaskWgt->setRowHidden(nIndex, true);
        m_pTaskWgt->setItem(nIndex, 0, new QTableWidgetItem(QString::number(nIndex))); // ��������
        m_pTaskWgt->setItem(nIndex, 1, new QTableWidgetItem("")); // ���
        m_pTaskWgt->setItem(nIndex, 2, new QTableWidgetItem("")); // ��������
        m_pTaskWgt->setItem(nIndex, 3, new QTableWidgetItem("")); // ��������
        m_pTaskWgt->setItem(nIndex, 4, new QTableWidgetItem("")); // ����ʼʱ��
        m_pTaskWgt->setItem(nIndex, 5, new QTableWidgetItem("")); // �ܴ�С
        m_pTaskWgt->setItem(nIndex, 6, new QTableWidgetItem("")); // ����ɴ�С
        m_pTaskWgt->setItem(nIndex, 7, new QTableWidgetItem("")); // �ٷֱ�
        m_pTaskWgt->setItem(nIndex, 8, new QTableWidgetItem("")); // ����
        m_pTaskWgt->setItem(nIndex, 9, new QTableWidgetItem("")); // ����״̬
        m_pTaskWgt->setItem(nIndex, 10, new QTableWidgetItem("")); // ��ʱ

        QPushButton *btnTaskStop = new QPushButton(qApp->translate(c_sHostMachine, c_sStop), m_pTaskWgt);
        btnTaskStop->setFixedWidth(100);
        m_pTaskWgt->setCellWidget(nIndex, 11, btnTaskStop);
        connect(btnTaskStop, SIGNAL(clicked(bool)), this, SLOT(slotTaskStop()));
    }

    QHeaderView* headerView = m_pTaskWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);

    m_pTaskWgt->verticalHeader()->hide();
}

/*****************************************************************************
* @brief   : ��ʼ�����̿������
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initPropertyWgt()
{
    m_groupManager = new QtGroupPropertyManager(m_pPropertyWgt);
    m_stringManager = new QtStringPropertyManager(m_pPropertyWgt);
    m_doubleManager = new DecoratedDoublePropertyManager(m_pPropertyWgt);
    m_intManager = new QtIntPropertyManager(m_pPropertyWgt);
    m_enumManager = new QtEnumPropertyManager(m_pPropertyWgt);

    QStringList enumAreastate;
    enumAreastate << "" 
        << qApp->translate(c_sHostMachine, c_sAreaState0)
        << qApp->translate(c_sHostMachine, c_sAreaState1)
        << qApp->translate(c_sHostMachine, c_sAreaState2)
        << qApp->translate(c_sHostMachine, c_sAreaState3);

    // ������Ϣ
    {
        shared_ptr<tagChannelProperty> channelProperty = make_shared<tagChannelProperty>();
        m_spAreaProperties->channelProperty = channelProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_6));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_stringManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_6));
        channelProperty->pItem1 = item;
        m_stringManager->setValue(item, "");
        topItem->addSubProperty(item);

        item = m_stringManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_7));
        channelProperty->pItem2 = item;
        m_stringManager->setValue(item, "");
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_8));
        channelProperty->pItem3 = item;

        QStringList enumChannelWidth;
        enumChannelWidth << "" << "1.25G" << "2G" << "2.5G" << "3.125G" << "5G" << "6.25G";

        m_enumManager->setEnumNames(item, enumChannelWidth);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }
    // �汾����Ϣ
    {
        shared_ptr<tagVersionProperty> versionProperty = make_shared<tagVersionProperty>();
        m_spAreaProperties->versionProperty = versionProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_7));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_stringManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_9));
        versionProperty->pItem1 = item;
        m_stringManager->setValue(item, "");
        topItem->addSubProperty(item);

        item = m_stringManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_10));
        versionProperty->pItem2 = item;
        m_stringManager->setValue(item, "");
        topItem->addSubProperty(item);
    }
    // ԭʼ���ݷ���
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_spAreaProperties->ldProperty1 = areaProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_1));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_1));
        areaProperty->pItem1 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_2));
        areaProperty->pItem2 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setSuffix(item, "%");
        topItem->addSubProperty(item);

        item = m_intManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_4));
        areaProperty->pItem4 = item;
        m_intManager->setValue(item, 0);
        m_intManager->setMinimum(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_5));
        areaProperty->pItem5 = item;
        m_enumManager->setEnumNames(item, enumAreastate);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }
    // �״�������
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_spAreaProperties->ldProperty2 = areaProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_2));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_1));
        areaProperty->pItem1 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_2));
        areaProperty->pItem2 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 2);
        m_doubleManager->setSuffix(item, "%");
        topItem->addSubProperty(item);

        item = m_intManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_4));
        areaProperty->pItem4 = item;
        m_intManager->setValue(item, 0);
        m_intManager->setMinimum(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_5));
        areaProperty->pItem5 = item;
        m_enumManager->setEnumNames(item, enumAreastate);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }
    // ���ͼƬ����
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_spAreaProperties->gdProperty1 = areaProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_3));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_1));
        areaProperty->pItem1 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_2));
        areaProperty->pItem2 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 2);
        m_doubleManager->setSuffix(item, "%");
        topItem->addSubProperty(item);

        item = m_intManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_4));
        areaProperty->pItem4 = item;
        m_intManager->setValue(item, 0);
        m_intManager->setMinimum(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_5));
        areaProperty->pItem5 = item;
        m_enumManager->setEnumNames(item, enumAreastate);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }
    // �����Ƶ����
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_spAreaProperties->gdProperty2 = areaProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_4));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_1));
        areaProperty->pItem1 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_2));
        areaProperty->pItem2 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setSuffix(item, "%");
        topItem->addSubProperty(item);

        item = m_intManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_4));
        areaProperty->pItem4 = item;
        m_intManager->setValue(item, 0);
        m_intManager->setMinimum(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_5));
        areaProperty->pItem5 = item;
        m_enumManager->setEnumNames(item, enumAreastate);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }
    // ������ݷ���
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_spAreaProperties->hhProperty = areaProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_5));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_1));
        areaProperty->pItem1 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_2));
        areaProperty->pItem2 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setDecimals(item, 3);
        topItem->addSubProperty(item);

        item = m_doubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_doubleManager->setValue(item, 0);
        m_doubleManager->setMinimum(item, 0);
        m_doubleManager->setSuffix(item, "%");
        topItem->addSubProperty(item);

        item = m_intManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_4));
        areaProperty->pItem4 = item;
        m_intManager->setValue(item, 0);
        m_intManager->setMinimum(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_5));
        areaProperty->pItem5 = item;
        m_enumManager->setEnumNames(item, enumAreastate);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }

    m_pPropertyWgt->setPropertiesWithoutValueMarked(true);
    m_pPropertyWgt->setRootIsDecorated(false);
    m_pPropertyWgt->setHeaderVisible(false);
}

/*****************************************************************************
* @brief   : TCP����
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::connectedCmd()
{
    QString sLabel = QString("%0 %1").arg(c_uCommandPort).arg(qApp->translate(c_sHostMachine, c_sReady));
    m_pCmdLabel->setText(sLabel);

    QString sInfo = QString("%0 %1").arg(m_sAddr).arg(sLabel);
    slotLogRecord(sInfo);
}

void HostMachine::connectedData()
{
    QString sLabel = QString("%0 %1").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sReady));
    m_pDataLabel->setText(sLabel);

    QString sInfo = QString("%0 %1").arg(m_sAddr).arg(sLabel);
    slotLogRecord(sInfo);
}

/*****************************************************************************
* @brief   : TCP�Ͽ�
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::disconnectCmd()
{
    // ״̬
    QString sLabel = QString("%0 %1").arg(c_uCommandPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pCmdLabel->setText(sLabel);

    QString sLog = QString("%0 %1").arg(m_sAddr).arg(sLabel);
    slotLogRecord(sLog);

    // QMessageBox::warning(this, windowTitle(), qApp->translate(c_sHostMachine, c_sCmdDisconnect));
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2019/11/10
* @param:  : 
*****************************************************************************/
void HostMachine::disconnectData()
{
    // ״̬
    QString sLabel = QString("%0 %1").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pDataLabel->setText(sLabel);

    QString sLog = QString("%0 %1").arg(m_sAddr).arg(sLabel);
    slotLogRecord(sLog);

    // QMessageBox::warning(this, windowTitle(), qApp->translate(c_sHostMachine, c_sDataDisconnect));
}

/*****************************************************************************
* @brief   : TCP���Ӵ���
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::errorCmd()
{
    QString sLog = QString("%1 %2 %3").arg(m_sAddr).arg(c_uCommandPort).arg(m_pCmdSocket->errorString());
    slotLogRecord(sLog);
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2019/11/10
* @param:  : 
*****************************************************************************/
void HostMachine::errorData()
{
    QString sLog = QString("%1 %2 %3").arg(m_sAddr).arg(c_uDataPort).arg(m_pDataSocket->errorString());
    slotLogRecord(sLog);
}

/*****************************************************************************
* @brief   : Ӧ����Ϣ��Ӧ
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::readyReadCmd()
{
    QDataStream in(m_pCmdSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_pCmdSocket->bytesAvailable() < sizeof(quint32))
        return;

    quint32 respondType;
    in >> respondType;
    if (respondType == SC_CheckSelf)
    {
        // �����ܴ�С
        in >> m_spcheckSelf->totalsize;

        if (nullptr == m_spcheckSelf->areaInfo0)
            m_spcheckSelf->areaInfo0 = make_shared<tagAreaInfo>();
        m_spcheckSelf->areaInfo0->read(in);

        if (nullptr == m_spcheckSelf->areaInfo1)
            m_spcheckSelf->areaInfo1 = make_shared<tagAreaInfo>();
        m_spcheckSelf->areaInfo1->read(in);

        if (nullptr == m_spcheckSelf->areaInfo2)
            m_spcheckSelf->areaInfo2 = make_shared<tagAreaInfo>();
        m_spcheckSelf->areaInfo2->read(in);

        if (nullptr == m_spcheckSelf->areaInfo3)
            m_spcheckSelf->areaInfo3 = make_shared<tagAreaInfo>();
        m_spcheckSelf->areaInfo3->read(in);

        if (nullptr == m_spcheckSelf->areaInfo4)
            m_spcheckSelf->areaInfo4 = make_shared<tagAreaInfo>();
        m_spcheckSelf->areaInfo4->read(in);

        if (nullptr == m_spcheckSelf->channelInfo)
            m_spcheckSelf->channelInfo = make_shared<tagChannelInfo>();
        m_spcheckSelf->channelInfo->read(in);

        if (nullptr == m_spcheckSelf->versionInfo)
            m_spcheckSelf->versionInfo = make_shared<tagVersionInfo>();
        m_spcheckSelf->versionInfo->read(in);

        in.device()->readAll();

        readCheckSelf();
    }
    else if (respondType == SC_Format)
    {
        quint32 state;
        in >> state;
        in.device()->readAll();

        readFormat(state);
    }
    else if (respondType == SC_SystemConfig)
    {
        quint32 choice, state;
        in >> choice >> state;

        in.device()->readAll();

        readSystemConfig(choice, state);
    }
    else if (respondType == SC_TaskQuery)
    {
        quint32 tasknum = 0;
        in >> tasknum;
        m_lstTaskInfo.clear();
        for (int index = 0; index < c_uTaskQueryNum; ++index)
        {
            shared_ptr<tagTaskInfo> spTaskInfo = make_shared<tagTaskInfo>();
            in >> spTaskInfo->flag >> spTaskInfo->area >> spTaskInfo->type
                >> spTaskInfo->finishedsize >> spTaskInfo->speed >> spTaskInfo->percent >> spTaskInfo->state;
            m_lstTaskInfo.push_back(spTaskInfo);
        }

        in.device()->readAll();
        readTaskQuery();

        if (!queryTaskInvalid())
        {
            m_nTimer = 0;
        }
        else
        {
            m_nTimer ++;
        }

        if (m_nTimer >= 5)
        {
            m_nTimer = 0;
        }
        else
        {
            QTimer::singleShot(c_uTaskQueryInterval, this, SLOT(slotTaskQuery()));
        }
    }
    else if (respondType == SC_Record)
    {
        quint32 area, state;
        in >> area >> state;
        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readRecord(area, state);

        if (state == 0x00)
        {
            auto itFind = std::find_if(m_lstTaskQueryParam.begin(), m_lstTaskQueryParam.end(), [&](shared_ptr<tagTaskQueryParam> spTaskQueryParam)->bool
            {
                return spTaskQueryParam->type == 0 && spTaskQueryParam->areano == area;
            });

            (*itFind)->dtStart = QDateTime::currentDateTime();

            QTimer::singleShot(10, this, SLOT(slotRefresh()));
            QTimer::singleShot(10, this, SLOT(slotTaskQuery()));
        }
    }
    else if (respondType == SC_PlayBack)
    {
        quint32 area, state;
        in >> area >> state;
        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readPlayBack(area, state);

        if (state == 0x00)
        {
            QTimer::singleShot(10, this, SLOT(slotRefresh()));
            QTimer::singleShot(10, this, SLOT(slotTaskQuery()));
        }
    }
    else if (respondType == SC_TaskStop)
    {
        quint32 tasktype, state;
        in >> tasktype >> state;
        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->currentWidget();
        pWMFileList->readTaskStop(tasktype, state);

        QTimer::singleShot(10, this, SLOT(slotRefresh()));
        QTimer::singleShot(10, this, SLOT(slotTaskQuery()));
    }
    else if (respondType == SC_Stop)
    {
        quint32 area, state;
        in >> area >> state;
        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->currentWidget();
        pWMFileList->readStop(state);

        QTimer::singleShot(10, this, SLOT(slotRefresh()));
        QTimer::singleShot(10, this, SLOT(slotTaskQuery()));
    }
    else if (respondType == SC_Delete)
    {
        quint32 area, state;
        in >> area >> state;
        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readDelete(area, state);

        if (0x00 == state)
        {
            QTimer::singleShot(10, this, SLOT(slotRefresh()));
        }
    }
    else if (respondType == SC_Refresh)
    {
        auto spFileInfos = make_shared<tagAreaFileInfos>();
        in >> spFileInfos->areano >> spFileInfos->filenum;

        for (int nIndex=0; nIndex < spFileInfos->filenum; ++nIndex)
        {
            char filename[40] = {0};
            in.readRawData(filename, sizeof(filename));

            quint64 datetime;
            quint32 fileno;
            quint32 filesize;
            in >> datetime >> fileno >> filesize;

            shared_ptr<tagAreaFileInfo> spFileInfo = make_shared<tagAreaFileInfo>();
            spFileInfo->sFileName = QString::fromLocal8Bit(filename);

            spFileInfo->datetime = CGlobalFun::Int2Dt(datetime);

            spFileInfo->fileno = fileno;
            spFileInfo->filesize = filesize;

            spFileInfos->lstFileInfo.push_back(spFileInfo);
        }

        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(spFileInfos->areano);
        pWMFileList->readRefresh(spFileInfos.get());
    }
    else if (respondType == SC_Import)
    {
        quint32 areano, state;
        in >> areano >> state;
        in.device()->readAll();

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(areano);
        pWMFileList->readImport(state);
        if (state == 0x00)
        {
            QTimer::singleShot(10, m_pDataSocket, SLOT(slotImport()));
        }
    }
    else if (respondType == SC_Export)
    {
        quint32 areano, state;
        in >> areano >> state;
        in.device()->readAll();
    }
}

/*****************************************************************************
* @brief   : IP����
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotIPSetting()
{
    // �������ӣ�����IP�豣֤��ִ��������
    if (m_pCmdSocket->state() == QAbstractSocket::ConnectedState)
    {
        reallyTaskQuery();

        if (!queryTaskInvalid())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sRequestCancel));
            return;
        }
    }

    DlgIPSetting dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    m_sAddr = dlg.getIPAddr();
    m_pIPLabel->setText(m_sAddr);
    m_pDataSocket->sIPAddr = m_sAddr;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    m_pCmdSocket->waitForConnected(c_uWaitForMsecs);

    m_pDataSocket->connectToHost(QHostAddress(m_sAddr), c_uDataPort);
    m_pDataSocket->waitForConnected(c_uWaitForMsecs);

    m_pDataSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024*1024*20);
    m_pDataSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 1024*1024*8);

    // ����IP��ַ�󣬴���һ��ˢ��
    slotRefresh();
}

/*****************************************************************************
* @brief   : �Լ�
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::reallyCheckSelf()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_CheckSelf << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : ����-�Լ�
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotCheckSelf()
{
    if (!reConnectCmd())
        return;

    reallyCheckSelf();
}

/*****************************************************************************
* @brief   : ����-��ʽ��
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotFormat()
{
    if (!reConnectCmd())
        return;

    // �Ƿ���ִ��������
    reallyTaskQuery();
    if (!queryTaskInvalid())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sRequestCancel));
        return;
    }

    // �Լ�
    reallyCheckSelf();

    DlgAreaFormat dlg(m_spcheckSelf->totalsize, m_spcheckSelf->areaInfo0->areasize, m_spcheckSelf->areaInfo1->areasize,
        m_spcheckSelf->areaInfo2->areasize, m_spcheckSelf->areaInfo3->areasize,
        m_spcheckSelf->areaInfo4->areasize, this);
    if (QDialog::Accepted != dlg.exec())
        return;

    reConnectCmd();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Format << quint32(dlg.Size1())
        << quint32(dlg.Size2())
        << quint32(dlg.Size3())
        << quint32(dlg.Size4())
        << quint32(dlg.Size5())
        << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : ����-ϵͳ����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotSystemConfig()
{
    if (!reConnectCmd())
        return;

    // �Ƿ���ִ��������
    reallyTaskQuery();
    if (!queryTaskInvalid())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sRequestCancel));
        return;
    }

    DlgSystemConfig dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    reConnectCmd();

    quint32 bandwidth = dlg.Bandwidth();
    quint32 channelchoice = dlg.Channelchoice();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_SystemConfig << channelchoice << bandwidth << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : �����ѯ
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::reallyTaskQuery()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_TaskQuery << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}


/*****************************************************************************
* @brief   : ����-�����ѯ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotTaskQuery()
{
    if (m_sAddr.isEmpty())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sIPSettingTip));
        return;
    }

    if (m_pCmdSocket->state() != QAbstractSocket::ConnectedState)
    {
        m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
        if (!m_pCmdSocket->waitForConnected(c_uWaitForMsecs))
        {
            Q_ASSERT(false);
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    reallyTaskQuery();
}

/*****************************************************************************
* @brief   : ����-��¼
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRecord()
{
    if (!reConnectCmd())
        return;

    DlgAreaRecord dlg(m_pTabWgt->currentIndex(), this);
    if (QDialog::Accepted != dlg.exec())
        return;

    reConnectCmd();

    QString sFileName = dlg.Filename();
    QList<quint32> lstAreano = dlg.Areas();
    foreach(quint32 areano, lstAreano)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);

        quint64 time = CGlobalFun::Dt2Int(QDateTime::currentDateTime());
        out << CS_Record << areano << time;

        char filename[40] = {0};
        QByteArray ba = sFileName.toLocal8Bit();
        strncpy(filename, ba.data(), sizeof(filename));

        out.writeRawData(filename, sizeof(filename));
        out << c_uRequestEndTag;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
    }
}

/*****************************************************************************
* @brief   : ����-�ط�
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotPlayBack()
{
    if (!reConnectCmd())
        return;

    CMWFileList* pFileList = (CMWFileList*)m_pTabWgt->currentWidget();
    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;
    QList<QTableWidgetItem*> selectedItems = pFileListWgt->selectedItems();
    QSet<quint32> fileNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        fileNos.insert(pItem->row());
    }

    if (fileNos.size() != 1)
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sPlayBack), qApp->translate(c_sHostMachine, c_sPlayBackTip));
        return;
    }

    DlgFilePlayblack dlg(m_spPlayBack->type, m_spPlayBack->prftime, m_spPlayBack->datanum, m_spPlayBack->prf, m_spPlayBack->cpi, this);
    if (QDialog::Accepted != dlg.exec())
        return;

    m_spPlayBack->type = dlg.Type();
    m_spPlayBack->prftime = dlg.Prftime();
    m_spPlayBack->datanum = dlg.Datanum();
    m_spPlayBack->prf = dlg.Prf();
    m_spPlayBack->cpi = dlg.Cpi();

    reConnectCmd();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_PlayBack << m_pTabWgt->currentIndex()
        << pFileListWgt->item(*fileNos.begin(), 0)->text().toInt()
        << m_spPlayBack->type
        << m_spPlayBack->prftime
        << m_spPlayBack->datanum
        << m_spPlayBack->prf
        << m_spPlayBack->cpi
        << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : ����-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotImport()
{
    if (!reConnectCmd())
        return;

    if (!reConnectData())
        return;

    QStringList importFileList = QFileDialog::getOpenFileNames(this, qApp->translate(c_sHostMachine, c_sImportFileTip),
        m_sImportPath, qApp->translate(c_sHostMachine, c_sImportFileExt));
    if (importFileList.isEmpty())
        return;
    
    QDir dir = importFileList.first();
    if (dir.cdUp())
        m_sImportPath = dir.path();

    m_lstImportParam.clear();
    foreach (QString filePath, importFileList)
    {
        m_lstImportParam.push_back(make_shared<tagImportParam>(m_pTabWgt->currentIndex(), filePath));
    }

    slotForeachImport();
}

void HostMachine::slotForeachImport()
{
    CMWFileList* pFileList = (CMWFileList*)m_pTabWgt->currentWidget();
    if (m_lstImportParam.isEmpty())
    {
        pFileList->m_pProgressBar->hide();
        reallyTaskQuery();
        return;
    }

    shared_ptr<tagImportParam> spImportParam = m_lstImportParam.first();
    m_lstImportParam.pop_front();

    bool bOk = m_pDataSocket->preImport(spImportParam->areano, spImportParam->filePath);
    if (!bOk)
        return;

    reConnectCmd();
    reConnectData();

    // �ļ���С
    QFileInfo fileInfo(spImportParam->filePath);
    qint32 filesize = fileInfo.size() / c_bSizeMax; // LBA
    if (filesize % 4 != 0)
        filesize += (4 - filesize % 4);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Import << m_pTabWgt->currentIndex() << filesize
        << CGlobalFun::Dt2Int(QDateTime::currentDateTime());

    // �ļ���
    char filename[40] = {0};
    QByteArray ba = fileInfo.fileName().toLocal8Bit();
    strncpy(filename, ba.data(), sizeof(filename));
    out.writeRawData(filename, sizeof(filename));
    out << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : ����-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotExport()
{
    if (!reConnectCmd())
        return;

    if (!reConnectData())
        return;

    CMWFileList* pFileList = (CMWFileList*)m_pTabWgt->currentWidget();
    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;
    QList<QTableWidgetItem*> selectedItems = pFileListWgt->selectedItems();
    if (selectedItems.count() < 1)
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle), qApp->translate(c_sHostMachine, c_sIsExportTip));
        return;
    }

    QSet<quint32> rowNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        rowNos.insert(pItem->row());
    }

    m_lstExportParam.clear();
    if (rowNos.count() == 1)
    {
        double filesize = pFileListWgt->item(*rowNos.begin(), 5)->text().toDouble(); // ���������е��ļ���С��
        DlgFileExport dlg(filesize, m_sExportPath, this);
        if (QDialog::Accepted != dlg.exec())
            return;

        m_sExportPath = dlg.ExportPath();

        shared_ptr<tagExportParam> spExportParam = make_shared<tagExportParam>();
        spExportParam->fileNo = pFileListWgt->item(*rowNos.begin(), 0)->text().toInt();
        spExportParam->startPos = dlg.Startpos();
        spExportParam->fileSize = dlg.Exportsize();
        spExportParam->filePath = QString("%0/%1.%2").arg(m_sExportPath)
            .arg(pFileListWgt->item(*rowNos.begin(), 1)->text() + QDateTime::currentDateTime().toString("hh_mm_ss"))
            .arg(pFileListWgt->item(*rowNos.begin(), 4)->text());

        m_lstExportParam.push_back(spExportParam);
    }
    else
    {
        QString sExportPath = QFileDialog::getExistingDirectory(this, qApp->translate(c_sHostMachine, c_sPathTitle), "./");
        if(sExportPath.isEmpty())
            return;

        foreach (quint32 rowNo, rowNos)
        {
            shared_ptr<tagExportParam> spExportParam = make_shared<tagExportParam>();
            spExportParam->fileNo = pFileListWgt->item(rowNo, 0)->text().toInt();
            spExportParam->startPos = 0;
            spExportParam->fileSize = pFileListWgt->item(rowNo, 5)->text().toInt();
            spExportParam->filePath = QString("%0/%1.%2").arg(sExportPath)
                .arg(pFileListWgt->item(rowNo, 1)->text()).arg(pFileListWgt->item(rowNo, 4)->text());

            m_lstExportParam.push_back(spExportParam);
        }
    }

    reConnectCmd();
    reConnectData();

    slotForeachExport();
}

/*****************************************************************************
* @brief   : ����
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotForeachExport()
{
    CMWFileList* pFileList = (CMWFileList*)m_pTabWgt->currentWidget();
    if (m_lstExportParam.size() < 1)
    {
        pFileList->m_pProgressBar->hide();
        reallyTaskQuery();
        return;
    }

    shared_ptr<tagExportParam> spExportParam = m_lstExportParam.first();
    m_lstExportParam.pop_front();

    reConnectCmd();
    reConnectData();

    m_pDataSocket->preExport(m_pTabWgt->currentIndex(), spExportParam->filePath, (qint64)spExportParam->fileSize * c_bSizeMax);

    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Export << (quint32)m_pTabWgt->currentIndex()
        << spExportParam->fileNo
        << spExportParam->startPos
        << spExportParam->fileSize
        << c_uRequestEndTag;

    m_pCmdSocket->write(block);
}

/*****************************************************************************
* @brief   : ����-����ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::reallyTaskStop(qint32 tasktype)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_TaskStop << tasktype << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : ����-����ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotStop()
{
    if (!reConnectCmd())
        return;

    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    box.setText(qApp->translate(c_sHostMachine, c_sIsStop));
    box.setIcon(QMessageBox::Question);
    box.addButton(qApp->translate(c_sHostMachine, c_sYes), QMessageBox::YesRole);
    box.addButton(qApp->translate(c_sHostMachine, c_sNo), QMessageBox::NoRole);
    if (QMessageBox::AcceptRole != box.exec())
        return;

    m_pDataSocket->m_bExportStop = true;
    m_pDataSocket->m_bImportStop = true;

    reConnectCmd();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Stop << m_pTabWgt->currentIndex() << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : ����-ɾ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotDelete()
{
    if (!reConnectCmd())
        return;

    // �Ƿ�ɾ��
    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    box.setText(qApp->translate(c_sHostMachine, c_sIsDelete));
    box.setIcon(QMessageBox::Question);
    QPushButton *yesBtn = box.addButton(qApp->translate(c_sHostMachine, c_sYes), QMessageBox::YesRole);
    QPushButton *noBtn = box.addButton(qApp->translate(c_sHostMachine, c_sNo), QMessageBox::NoRole);
    box.setDefaultButton(yesBtn);
    if (box.exec())
        return;

    reConnectCmd();

    // �Ƿ���ִ��������
    reallyTaskQuery();
    if (!queryTaskInvalid())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sRequestCancel));
        return;
    }

    // �ж�ѡ����
    CMWFileList* pFileList = (CMWFileList*)m_pTabWgt->currentWidget();
    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;
    QList<QTableWidgetItem*> selectedItems = pFileListWgt->selectedItems();
    if (selectedItems.count() < 1)
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sIsDeleteTip));
        return;
    }

    QSet<quint32> rowNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        rowNos.insert(pItem->row());
    }

    foreach(quint32 rowNo, rowNos)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_Delete << (quint32)m_pTabWgt->currentIndex()
            << (quint32)pFileListWgt->item(rowNo, 0)->text().toInt()
            << c_uRequestEndTag;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
    }
}

/*****************************************************************************
* @brief   : ˢ��
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::reallyRefresh()
{
    // ��յ�ǰ�����ļ��б��������ļ�
    QTableWidget* pFileListWgt = ((CMWFileList*)m_pTabWgt->currentWidget())->m_pFileListWgt;
    while (pFileListWgt->rowCount() > 0)
    {
        pFileListWgt->removeRow(pFileListWgt->rowCount() - 1);
    }

    // ˢ��ǰ���Լ�
    reallyCheckSelf();

    shared_ptr<tagAreaInfo> areaInfo = nullptr;
    switch (m_pTabWgt->currentIndex())
    {
    case 0:
        areaInfo = m_spcheckSelf->areaInfo0;
        break;
    case 1:
        areaInfo = m_spcheckSelf->areaInfo1;
        break;
    case 2:
        areaInfo = m_spcheckSelf->areaInfo2;
        break;
    case 3:
        areaInfo = m_spcheckSelf->areaInfo3;
        break;
    case 4:
        areaInfo = m_spcheckSelf->areaInfo4;
        break;
    }

    for (int nIndex = 0; nIndex <= areaInfo->areafilenum; )
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_Refresh << qint32(m_pTabWgt->currentIndex())
            << nIndex // ��ʼ�ļ����
            << c_uRefreshFileNum // ˢ���ļ���
            << c_uRequestEndTag;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);

        nIndex += c_uRefreshFileNum;
    }
}


/*****************************************************************************
* @brief   : ����-ˢ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRefresh()
{
    if (!reConnectCmd())
        return;

    reallyRefresh();
}

/*****************************************************************************
* @brief   : Ӧ��-�Լ�
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readCheckSelf()
{
    auto updatevalue=[&](shared_ptr<tagAreaProperty> areaProperty, shared_ptr<tagAreaInfo> areaInfo)->void
    {
        float newSize = 0.0;
        QString sUnit = "";
        CGlobalFun::formatSize((qint64)areaInfo->areasize * c_bSizeMax, newSize, sUnit);
        m_doubleManager->setValue(areaProperty->pItem1, (double)newSize);
        m_doubleManager->setSuffix(areaProperty->pItem1, sUnit);

        CGlobalFun::formatSize((qint64)(areaInfo->areasize - areaInfo->areaunuse) * c_bSizeMax, newSize, sUnit);
        m_doubleManager->setValue(areaProperty->pItem2, (double)newSize);
        m_doubleManager->setSuffix(areaProperty->pItem2, sUnit);

        m_doubleManager->setValue(areaProperty->pItem3, areaInfo->areaunuse / areaInfo->areasize *100);
        m_intManager->setValue(areaProperty->pItem4, areaInfo->areafilenum);
        m_enumManager->setValue(areaProperty->pItem5, areaInfo->areastate + 1);
    };

    updatevalue(m_spAreaProperties->ldProperty1, m_spcheckSelf->areaInfo0);
    updatevalue(m_spAreaProperties->ldProperty2, m_spcheckSelf->areaInfo1);
    updatevalue(m_spAreaProperties->gdProperty1, m_spcheckSelf->areaInfo2);
    updatevalue(m_spAreaProperties->gdProperty2, m_spcheckSelf->areaInfo3);
    updatevalue(m_spAreaProperties->hhProperty, m_spcheckSelf->areaInfo4);

    // ͨ��״̬
    QString sChannelState = CGlobalFun::formatChannel(m_spcheckSelf->channelInfo->state);
    if (sChannelState != "")
    {
        sChannelState.append(" ");
        sChannelState.append(qApp->translate(c_sHostMachine, c_sChannelState1));
    }
    else
    {
        sChannelState.append(qApp->translate(c_sHostMachine, c_sChannelState0));
    }

    m_stringManager->setValue(m_spAreaProperties->channelProperty->pItem1, sChannelState);

    // ͨ��ѡ��
    QString sChannelChoice = CGlobalFun::formatChannel(m_spcheckSelf->channelInfo->choice);
    if (sChannelChoice != "")
    {
        sChannelChoice.append(" ");
        sChannelChoice.append(qApp->translate(c_sHostMachine, c_sChannelChoice0));
    }
    else
    {
        sChannelChoice.append(qApp->translate(c_sHostMachine, c_sChannelChoice1));
    }

    m_stringManager->setValue(m_spAreaProperties->channelProperty->pItem2, sChannelChoice);

    // ͨ������
    m_enumManager->setValue(m_spAreaProperties->channelProperty->pItem3, m_spcheckSelf->channelInfo->bandwidth + 1);

    // �汾��
    m_stringManager->setValue(m_spAreaProperties->versionProperty->pItem1, CGlobalFun::formatVersionNo(m_spcheckSelf->versionInfo->hardversion));
    m_stringManager->setValue(m_spAreaProperties->versionProperty->pItem2, CGlobalFun::formatVersionNo(m_spcheckSelf->versionInfo->fpgaversion));
}

/*****************************************************************************
* @brief   : Ӧ��-��ʽ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readFormat(quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sHostMachine, c_sFormatResult0);
    }
    else if (state == 0x01)
    {
        sInfo = qApp->translate(c_sHostMachine, c_sFormatResult1);
    }
    else
    {
        sInfo = qApp->translate(c_sHostMachine, c_sFormatResult2);
    }

    statusBar()->showMessage(sInfo);
    slotLogRecord(sInfo);
}

/*****************************************************************************
* @brief   : Ӧ��-ϵͳ����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readSystemConfig(quint32 choice, quint32 state)
{
    QString sInfo = "";
    if (state == 0x00)
    {
        sInfo = qApp->translate(c_sHostMachine, c_sSystemConfigResult0);
    }
    else if (state == 0x01)
    {
        sInfo = qApp->translate(c_sHostMachine, c_sSystemConfigResult1);
    }
    else
    {
        sInfo = qApp->translate(c_sHostMachine, c_sSystemConfigResult2);
    }

    statusBar()->showMessage(sInfo);
    slotLogRecord(sInfo);
}

/*****************************************************************************
* @brief   : Ӧ��-�����ѯ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readTaskQuery()
{
    if (m_lstTaskInfo.empty())
        return;

    int nSerialNum = 1;
    for (int nRow = 0; nRow < m_pTaskWgt->rowCount(); ++ nRow)
    {
        int nTaskType = m_pTaskWgt->item(nRow, 0)->text().toInt();
        auto itTaskInfo = std::find_if(m_lstTaskInfo.begin(), m_lstTaskInfo.end(), [&](shared_ptr<tagTaskInfo> spTaskInfo)->bool
        {
            return (spTaskInfo->type == nTaskType);
        });

        if (itTaskInfo == m_lstTaskInfo.end())
            continue;

        shared_ptr<tagTaskInfo> spTaskInfo = *itTaskInfo;
        m_pTaskWgt->setRowHidden(nRow, (0 == spTaskInfo->flag));
        if (0 == spTaskInfo->flag)
            continue;

        auto itTaskQueryParam = std::find_if(m_lstTaskQueryParam.begin(), m_lstTaskQueryParam.end(), [&](shared_ptr<tagTaskQueryParam> spTaskQueryParam)->bool
        {
            if (spTaskInfo->type == 13) // ���뵼��
                return spTaskQueryParam->type == 1;
            else // ��¼
                return spTaskQueryParam->areano == spTaskInfo->area;
        });

        shared_ptr<tagTaskQueryParam> spTaskQueryParam = *itTaskQueryParam;

        m_pTaskWgt->item(nRow, 1)->setText(QString::number(nSerialNum++)); // ���
        m_pTaskWgt->item(nRow, 2)->setText(m_pTabWgt->tabBar()->tabText(spTaskInfo->area)); // ��������
        m_pTaskWgt->item(nRow, 3)->setText(QString::number(spTaskInfo->type)); // ��������
        m_pTaskWgt->item(nRow, 4)->setText(spTaskQueryParam->dtStart.toString("yyyy-MM-dd hh:mm:ss")); // ����ʼʱ��

        qint64 finishedsize = (qint64)spTaskInfo->finishedsize * c_bSizeMax;
        if (spTaskInfo->type == 13)
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(spTaskQueryParam->filesize)); // �ܴ�С
        else // ��¼�����ܴ�С=����ɴ�С
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(finishedsize)); // �ܴ�С
        m_pTaskWgt->item(nRow, 6)->setText(CGlobalFun::formatSize(finishedsize)); // ����ɴ�С
        m_pTaskWgt->item(nRow, 7)->setText(QString::number(spTaskInfo->percent) + "%"); // �ٷֱ�
        m_pTaskWgt->item(nRow, 8)->setText(CGlobalFun::formatSize(spTaskInfo->speed * c_bSizeMax) + "/s"); // ����
        m_pTaskWgt->item(nRow, 9)->setText(qApp->translate(c_sHostMachine, c_sTaskState1)); // ����״̬
        m_pTaskWgt->item(nRow, 10)->setText(QString::number(spTaskQueryParam->dtStart.secsTo(QDateTime::currentDateTime())) + "s"); // ��ʱ
        m_pTaskWgt->cellWidget(nRow, 11)->show();
    }

    m_pTaskWgt->viewport()->update();
}

/*****************************************************************************
* @brief   : ���Actionʱ����־��¼
* @author  : wb
* @date    : 2019/11/02
* @param:  : ��
*****************************************************************************/
void HostMachine::slotLogRecordAct()
{
    QAction* pAction = qobject_cast<QAction *>(sender());
    if (NULL == pAction)
        return;

    QString sLog = QString("> %0").arg(pAction->text());
    slotLogRecord(sLog);
}

/*****************************************************************************
* @brief   : ��־��¼
* @author  : wb
* @date    : 2019/11/02
* @param:  : �������Ϣ����¼���ļ���
*****************************************************************************/
void HostMachine::slotLogRecord(QString sText)
{
    QString sDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QTextStream in(m_pLog);
    in << sDateTime << " " << sText << "\r\n";
}

/*****************************************************************************
* @brief   : �����ʼ������Ӧ�Ĳۺ���
* @author  : wb
* @date    : 2019/11/02
* @param:  : ��
*****************************************************************************/
void HostMachine::slotInit()
{
    // ��־��¼-�����
    slotLogRecord(qApp->translate(c_sHostMachine, c_sOpenSoftware));

    // ��һ��Tabҳ��Ч
    emit m_pTabWgt->currentChanged(0);
    // ��IP����
    emit m_pActIPSetting->triggered();
}

/*****************************************************************************
* @brief   : Tab�����л�
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotTabChanged(int index)
{
    QString sTabText = m_pTabWgt->tabText(index);
    foreach (QtBrowserItem * pBrowserItem, m_pPropertyWgt->topLevelItems())
    {
        QString sItemText = pBrowserItem->property()->propertyName();
        if (sItemText == qApp->translate(c_sHostMachine, c_sPropertyGroup1_6)
            || sItemText == qApp->translate(c_sHostMachine, c_sPropertyGroup1_7)
            || sItemText == sTabText)
        {
            m_pPropertyWgt->setExpanded(pBrowserItem, true);
        }
        else
        {
            m_pPropertyWgt->setExpanded(pBrowserItem, false);
        }
    }
}

/*****************************************************************************
* @brief   : ��ʼ������
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::initData()
{
    m_pCmdSocket = new QTcpSocket(this);
    m_pDataSocket = new CDataSocket(this);
    m_spcheckSelf = make_shared<tagCheckSelf>();
    m_spAreaProperties = make_shared<tagAreaProperties>();
    m_spTaskStopType = make_shared<TaskStopType>();
    m_spPlayBack = make_shared<tagPlayBack>();

    m_pElapsedTimer = new QElapsedTimer();
    m_nTimer = 0;

    m_lstTaskQueryParam.clear();
    m_lstTaskQueryParam.push_back(make_shared<tagTaskQueryParam>(0, 0, 0, QDateTime::currentDateTime()));
    m_lstTaskQueryParam.push_back(make_shared<tagTaskQueryParam>(0, 1, 0, QDateTime::currentDateTime()));
    m_lstTaskQueryParam.push_back(make_shared<tagTaskQueryParam>(0, 2, 0, QDateTime::currentDateTime()));
    m_lstTaskQueryParam.push_back(make_shared<tagTaskQueryParam>(0, 3, 0, QDateTime::currentDateTime()));
    m_lstTaskQueryParam.push_back(make_shared<tagTaskQueryParam>(0, 4, 0, QDateTime::currentDateTime()));
    m_lstTaskQueryParam.push_back(make_shared<tagTaskQueryParam>(1, 0, 0, QDateTime::currentDateTime()));

    // �Ƿ���ʾ����ֹͣ��
    QString sConfigFile = QString("%0/%1.json").arg(qApp->applicationDirPath()).arg(qApp->applicationName());
    if (QFile::exists(sConfigFile))
    {
        Config config(sConfigFile);
        m_bShowTaskStop = config.readBool("tasklist.showstop");
        m_sImportPath = config.readString("import.path");
        m_sExportPath = config.readString("export.path");

        m_spPlayBack->type = config.readInt("playback.type");
        m_spPlayBack->prftime = config.readInt("playback.prftime");
        m_spPlayBack->datanum = config.readInt("playback.datanum");
        m_spPlayBack->prf = config.readInt("playback.prf");
        m_spPlayBack->cpi = config.readInt("playback.cpi");
    }

    // ��־
    QString sLogFile = QString("%0/%1.log").arg(qApp->applicationDirPath()).arg(qApp->applicationName());
    QFileInfo info(sLogFile);
    if (info.size() / c_kSizeMax > 10) // 10M
    {
        QString sNewName = QString("%0/%1_%2.log").arg(qApp->applicationDirPath())
            .arg(qApp->applicationName()).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
        QFile::rename(sLogFile, sNewName);
    }

    m_pLog = new QFile(sLogFile);
    m_pLog->open(QIODevice::WriteOnly|QIODevice::Append);
}

/*****************************************************************************
* @brief   : ���뿪ʼ
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotImportStart(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
    m_pElapsedTimer->restart();
    m_nProcessEventInterval = c_uProcessEventInterval;
    m_nProgressBarUpdateInterval = c_uProgressBarUpdateInterval;

    auto itFind = std::find_if(m_lstTaskQueryParam.begin(), m_lstTaskQueryParam.end(), [&](shared_ptr<tagTaskQueryParam> spTaskQueryParam)->bool
    {
        return spTaskQueryParam->type == 1;
    });

    (*itFind)->filesize = total;
    (*itFind)->dtStart = QDateTime::currentDateTime();

    QTimer::singleShot(10, this, SLOT(slotRefresh()));
    QTimer::singleShot(10, this, SLOT(slotTaskQuery()));
}

/*****************************************************************************
* @brief   : ������½���
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotImportUpdate(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
    if (m_pElapsedTimer->elapsed() / m_nProcessEventInterval != 0)
    {
        m_nProcessEventInterval += c_uProcessEventInterval;
        qApp->processEvents();
    }

    if (m_pElapsedTimer->elapsed() / m_nProgressBarUpdateInterval != 0)
    {
        m_nProgressBarUpdateInterval += c_uProgressBarUpdateInterval;

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(areano);
        if (nullptr == pWMFileList)
            return;

        pWMFileList->updateProcess(fileName, buffer, total, m_pElapsedTimer->elapsed());

        reallyTaskQuery();
    }
}

/*****************************************************************************
* @brief   : �������
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotImportCompleted(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
    CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(areano);
    pWMFileList->updateProcess(fileName, buffer, total);

    reallyRefresh();
    slotForeachImport();
}

/*****************************************************************************
* @brief   : ������ʼ
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotExportStart(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
    m_pElapsedTimer->restart();
    m_nProcessEventInterval = c_uProcessEventInterval;
    m_nProgressBarUpdateInterval = c_uProgressBarUpdateInterval;

    auto itFind = std::find_if(m_lstTaskQueryParam.begin(), m_lstTaskQueryParam.end(), [&](shared_ptr<tagTaskQueryParam> spTaskQueryParam)->bool
    {
        return spTaskQueryParam->type == 1;
    });

    (*itFind)->filesize = total;
    (*itFind)->dtStart = QDateTime::currentDateTime();

    QTimer::singleShot(10, this, SLOT(slotRefresh()));
    QTimer::singleShot(10, this, SLOT(slotTaskQuery()));

    CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(areano);
    if (nullptr == pWMFileList)
        return;

    pWMFileList->m_preBuffer = 0;
    pWMFileList->m_preElapsed = 0;
}

/*****************************************************************************
* @brief   : �������½���
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotExportUpdate(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
    if (m_pElapsedTimer->elapsed() / m_nProcessEventInterval != 0)
    {
        m_nProcessEventInterval += c_uProcessEventInterval;
        qApp->processEvents();
    }

    if (m_pElapsedTimer->elapsed() / m_nProgressBarUpdateInterval != 0)
    {
        m_nProgressBarUpdateInterval += c_uProgressBarUpdateInterval;

        CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(areano);
        if (nullptr == pWMFileList)
            return;

        pWMFileList->updateProcess(fileName, buffer, total, m_pElapsedTimer->elapsed());

        reallyTaskQuery();
    }
}

/*****************************************************************************
* @brief   : �������
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::slotExportCompleted(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
    CMWFileList* pWMFileList = (CMWFileList*)m_pTabWgt->widget(areano);
    if (nullptr == pWMFileList)
        return;

    pWMFileList->updateProcess(fileName, buffer, total);
    slotForeachExport();
}

/*****************************************************************************
* @brief   : �ر�log��¼
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::closeLog()
{
    QTextStream in(m_pLog);
    in << "****************************************" << "\r\n";
    m_pLog->close();
}

/*****************************************************************************
* @brief   : ����˿�����
* @author  : wb
* @date    : 2019/12/30
* @param:  : 
*****************************************************************************/
bool HostMachine::reConnectCmd()
{
    if (m_sAddr.isEmpty())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sIPSettingTip));
        return false;
    }

    m_pCmdSocket->disconnectFromHost();
    m_pCmdSocket->waitForDisconnected(c_uWaitForMsecs);
    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    if (!m_pCmdSocket->waitForConnected(c_uWaitForMsecs))
    {
        Q_ASSERT(false);
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sNetConnectError));
        return false;
    }

    return true;
}

/*****************************************************************************
* @brief   : ���ݶ˿�����
* @author  : wb
* @date    : 2019/12/30
* @param:  : 
*****************************************************************************/
bool HostMachine::reConnectData()
{
    if (m_sAddr.isEmpty())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sIPSettingTip));
        return false;
    }

    m_pDataSocket->disconnectFromHost();
    m_pDataSocket->waitForDisconnected(c_uWaitForMsecs);
    m_pDataSocket->connectToHost(QHostAddress(m_sAddr), c_uDataPort);
    if (!m_pDataSocket->waitForConnected(c_uWaitForMsecs))
    {
        Q_ASSERT(false);
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sNetConnectError));
        return false;
    }

    return true;
}

/*****************************************************************************
* @brief   : ��ѯ�������Ƿ�����Ч��
* @author  : wb
* @date    : 2019/12/30
* @param:  : 
*****************************************************************************/
bool HostMachine::queryTaskInvalid()
{
    bool bAll = std::all_of(m_lstTaskInfo.begin(), m_lstTaskInfo.end(), [&](shared_ptr<tagTaskInfo> spTaskInfo)->bool
    {
        return spTaskInfo->flag == 0;
    });

    return bAll;
}

/*****************************************************************************
* @brief   : ����ֹͣ
* @author  : wb
* @date    : 2019/12/30
* @param:  : 
*****************************************************************************/
void HostMachine::slotTaskStop()
{
    int nRow = 0;
    for (; nRow < m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->cellWidget(nRow, 11) == sender())
        {
            break;
        }
    }

    quint32 tasktype = m_pTaskWgt->item(nRow, 0)->text().toInt();

    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    box.setText(qApp->translate(c_sHostMachine, c_sIsStop));
    box.setIcon(QMessageBox::Question);
    box.addButton(qApp->translate(c_sHostMachine, c_sYes), QMessageBox::YesRole);
    box.addButton(qApp->translate(c_sHostMachine, c_sNo), QMessageBox::NoRole);
    if (QMessageBox::AcceptRole != box.exec())
        return;

    m_pDataSocket->m_bExportStop = true;
    m_pDataSocket->m_bImportStop = true;

    reConnectCmd();

    reallyTaskStop(tasktype);
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2020/01/24
* @param:  : 
*****************************************************************************/
void HostMachine::slotImportStop(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2020/01/24
* @param:  : 
*****************************************************************************/
void HostMachine::slotExportStop(qint32 areano, QString fileName, qint64 buffer, qint64 total)
{
}
