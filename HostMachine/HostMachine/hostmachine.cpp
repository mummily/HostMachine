
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
#include "qttreepropertybrowser.h"
#include "QDateTime"
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>
#include <QProgressBar>
#include <QElapsedTimer>

#include <QTcpSocket>
#include <QTcpServer>

#include "dlgipsetting.h"
#include "qtpropertymanager.h"
#include "decorateddoublepropertymanager.h"
#include "dlgareaformat.h"
#include "dlgsystemconfig.h"
#include "mwfilelist.h"
#include "dlgarearecord.h"
#include "dlgfileexport.h"
#include "ScopeGuard.h"
#include "datasocket.h"
#include "globalfun.h"
#include "dlgfileplayblack.h"

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "����Ӧ�����");
static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("HostMachine", "ѡ��Ҫ������ļ�");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("HostMachine", "DAT�ļ�(*.dat);;�����ļ�(*.*)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("HostMachine", "�Ƿ�ֹͣ��");
static const char *c_sIsStopTip = QT_TRANSLATE_NOOP("HostMachine", "��ѡ��Ҫֹͣ������");
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
static const char *c_sProperty1_1 = QT_TRANSLATE_NOOP("HostMachine", "�ܴ�С");
static const char *c_sProperty1_2 = QT_TRANSLATE_NOOP("HostMachine", "���ô�С");
static const char *c_sProperty1_3 = QT_TRANSLATE_NOOP("HostMachine", "δ�ðٷֱ�");
static const char *c_sProperty1_4 = QT_TRANSLATE_NOOP("HostMachine", "�ļ�����");
static const char *c_sProperty1_5 = QT_TRANSLATE_NOOP("HostMachine", "��ǰ״̬");
static const char *c_sProperty1_6 = QT_TRANSLATE_NOOP("HostMachine", "ͨ������״̬");
static const char *c_sProperty1_7 = QT_TRANSLATE_NOOP("HostMachine", "ͨ��ѡ��״̬");
static const char *c_sProperty1_8 = QT_TRANSLATE_NOOP("HostMachine", "ͨ������");

// �����б��
static const char *c_sTaskHeader1 = QT_TRANSLATE_NOOP("HostMachine", "���");
static const char *c_sTaskHeader2 = QT_TRANSLATE_NOOP("HostMachine", "��������");
static const char *c_sTaskHeader3 = QT_TRANSLATE_NOOP("HostMachine", "��������");
static const char *c_sTaskHeader4 = QT_TRANSLATE_NOOP("HostMachine", "�ļ�����");
static const char *c_sTaskHeader5 = QT_TRANSLATE_NOOP("HostMachine", "����ʼʱ��");
static const char *c_sTaskHeader6 = QT_TRANSLATE_NOOP("HostMachine", "�ܴ�С");
static const char *c_sTaskHeader7 = QT_TRANSLATE_NOOP("HostMachine", "����ɴ�С");
static const char *c_sTaskHeader8 = QT_TRANSLATE_NOOP("HostMachine", "�ٷֱ�");
static const char *c_sTaskHeader9 = QT_TRANSLATE_NOOP("HostMachine", "����(MB/S)");
static const char *c_sTaskHeader10 = QT_TRANSLATE_NOOP("HostMachine", "״̬");
static const char *c_sTaskHeader11 = QT_TRANSLATE_NOOP("HostMachine", "��ʱ");

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
static const char *c_sChannelState1 = QT_TRANSLATE_NOOP("HostMachine", "����");

// ͨ��ѡ��
static const char *c_sChannelChoice0 = QT_TRANSLATE_NOOP("HostMachine", "ѡ��");
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
static const char *c_sTaskState0 = QT_TRANSLATE_NOOP("HostMachine", "ִ����");
static const char *c_sTaskState1 = QT_TRANSLATE_NOOP("HostMachine", "���");

HostMachine::HostMachine(QWidget *parent)
    : QMainWindow(parent), m_sAddr(""), m_nInterval(0)
{
    m_spcheckSelf = make_shared<tagCheckSelf>();

    initTcp();
    initUI();
    initLayout();
    initConnect();
    initData();

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
}

/*****************************************************************************
* @brief   : ��ʼ��TCP
* @author  : wb
* @date    : 2019/10/26
* @param:  : 
*****************************************************************************/
void HostMachine::initTcp()
{
    m_pCmdSocket = new QTcpSocket(this);
    m_pDataSocket = new DataSocket(this);
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

    m_pLDOriginalWgt = new MWFileList(this);
    m_pLDResultWgt = new MWFileList(this);
    m_pGDImgWgt = new MWFileList(this);
    m_pGDVidioWgt = new MWFileList(this);
    m_pHHDataWgt = new MWFileList(this);

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

    m_pElapsedTimer = new QElapsedTimer();
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
    connect(m_pDataSocket, SIGNAL(importStart(qint32, QString, float, float)), this, SLOT(slotImportStart(qint32, QString, float, float)));
    connect(m_pDataSocket, SIGNAL(importUpdate(qint32, QString, float, float)), this, SLOT(slotImportUpdate(qint32, QString, float, float)));
    connect(m_pDataSocket, SIGNAL(importCompleted(qint32, QString, float, float)), this, SLOT(slotImportCompleted(qint32, QString, float, float)));
    connect(m_pDataSocket, SIGNAL(exportStart(qint32, QString, float, float)), this, SLOT(slotExportStart(qint32, QString, float, float)));
    connect(m_pDataSocket, SIGNAL(exportUpdate(qint32, QString, float, float)), this, SLOT(slotExportUpdate(qint32, QString, float, float)));
    connect(m_pDataSocket, SIGNAL(exportCompleted(qint32, QString, float, float)), this, SLOT(slotExportCompleted(qint32, QString, float, float)));
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
    headerList <<qApp->translate(c_sHostMachine, c_sTaskHeader2)
        << qApp->translate(c_sHostMachine, c_sTaskHeader3)
        << qApp->translate(c_sHostMachine, c_sTaskHeader4)
        << qApp->translate(c_sHostMachine, c_sTaskHeader5)
        << qApp->translate(c_sHostMachine, c_sTaskHeader6)
        << qApp->translate(c_sHostMachine, c_sTaskHeader7)
        << qApp->translate(c_sHostMachine, c_sTaskHeader8)
        << qApp->translate(c_sHostMachine, c_sTaskHeader9)
        << qApp->translate(c_sHostMachine, c_sTaskHeader10)
        << qApp->translate(c_sHostMachine, c_sTaskHeader11);

    m_pTaskWgt->setShowGrid(false);
    m_pTaskWgt->setColumnCount(headerList.size());
    m_pTaskWgt->setHorizontalHeaderLabels(headerList);
    m_pTaskWgt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTaskWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* headerView = m_pTaskWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
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
    m_doubleManager = new QtDoublePropertyManager(m_pPropertyWgt);
    m_ddoubleManager = new DecoratedDoublePropertyManager(m_pPropertyWgt);
    m_intManager = new QtIntPropertyManager(m_pPropertyWgt);
    m_enumManager = new QtEnumPropertyManager(m_pPropertyWgt);

    QStringList enumAreastate;
    enumAreastate << "" 
        << qApp->translate(c_sHostMachine, c_sAreaState0)
        << qApp->translate(c_sHostMachine, c_sAreaState1)
        << qApp->translate(c_sHostMachine, c_sAreaState2)
        << qApp->translate(c_sHostMachine, c_sAreaState3);

    QStringList enumChannelstate;
    enumChannelstate << "" 
        << qApp->translate(c_sHostMachine, c_sChannelState0)
        << qApp->translate(c_sHostMachine, c_sChannelState1);

    QStringList enumChannelchoice;
    enumChannelchoice << "" 
        << qApp->translate(c_sHostMachine, c_sChannelChoice0)
        << qApp->translate(c_sHostMachine, c_sChannelChoice1);

    QStringList enumChannelWidth;
    enumChannelWidth << "" << "1.25G" << "2G" << "2.5G" << "3.125G" << "5G" << "6.25G";

    // ������Ϣ
    {
        shared_ptr<tagChannelProperty> channelProperty = make_shared<tagChannelProperty>();
        m_areaProperties.channelProperty = channelProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_6));
        m_pPropertyWgt->addProperty(topItem);

        QtProperty *item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_6));
        channelProperty->pItem1 = item;
        m_enumManager->setEnumNames(item, enumChannelstate);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_7));
        channelProperty->pItem2 = item;
        m_enumManager->setEnumNames(item, enumChannelchoice);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);

        item = m_enumManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_8));
        channelProperty->pItem3 = item;
        m_enumManager->setEnumNames(item, enumChannelWidth);
        m_enumManager->setValue(item, 0);
        topItem->addSubProperty(item);
    }
    // ԭʼ���ݷ���
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_areaProperties.ldProperty1 = areaProperty;

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

        item = m_ddoubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_ddoubleManager->setValue(item, 0);
        m_ddoubleManager->setMinimum(item, 0);
        m_ddoubleManager->setSuffix(item, "%");
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
        m_areaProperties.ldProperty2 = areaProperty;

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

        item = m_ddoubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_ddoubleManager->setValue(item, 0);
        m_ddoubleManager->setMinimum(item, 0);
        m_ddoubleManager->setDecimals(item, 2);
        m_ddoubleManager->setSuffix(item, "%");
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
        m_areaProperties.gdProperty1 = areaProperty;

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

        item = m_ddoubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_ddoubleManager->setValue(item, 0);
        m_ddoubleManager->setMinimum(item, 0);
        m_ddoubleManager->setDecimals(item, 2);
        m_ddoubleManager->setSuffix(item, "%");
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
        m_areaProperties.gdProperty2 = areaProperty;

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

        item = m_ddoubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_ddoubleManager->setValue(item, 0);
        m_ddoubleManager->setMinimum(item, 0);
        m_ddoubleManager->setSuffix(item, "%");
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
        m_areaProperties.hhProperty = areaProperty;

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

        item = m_ddoubleManager->addProperty(qApp->translate(c_sHostMachine, c_sProperty1_3));
        areaProperty->pItem3 = item;
        m_ddoubleManager->setValue(item, 0);
        m_ddoubleManager->setMinimum(item, 0);
        m_ddoubleManager->setSuffix(item, "%");
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

    QMessageBox::warning(this, windowTitle(), qApp->translate(c_sHostMachine, c_sCmdDisconnect));
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

    QMessageBox::warning(this, windowTitle(), qApp->translate(c_sHostMachine, c_sDataDisconnect));
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
        shared_ptr<tagAreaInfo> areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        m_spcheckSelf->areaInfo0 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        m_spcheckSelf->areaInfo1 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        m_spcheckSelf->areaInfo2 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        m_spcheckSelf->areaInfo3 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        m_spcheckSelf->areaInfo4 = areaInfo;

        shared_ptr<tagChannelInfo> channelInfo = make_shared<tagChannelInfo>();
        channelInfo->read(in);
        m_spcheckSelf->channelInfo = channelInfo;

        readCheckSelf();
    }
    else if (respondType == SC_Format)
    {
        quint32 state;
        in >> state;

        readFormat(state);
    }
    else if (respondType == SC_SystemConfig)
    {
        quint32 choice, state;
        in >> choice >> state;

        readSystemConfig(choice, state);
    }
    else if (respondType == SC_TaskQuery)
    {
        quint32 tasknum;
        in >> tasknum;

        list<tagTaskInfo> lstTaskInfo;
        for (int index = 0; index < tasknum; ++index)
        {
            tagTaskInfo taskInfo;
            in >> taskInfo.flag >> taskInfo.area >> taskInfo.type
                >> taskInfo.finishedsize >> taskInfo.speed >> taskInfo.percent >> taskInfo.state;
            lstTaskInfo.push_back(taskInfo);
        }

        readTaskQuery(lstTaskInfo);
    }
    else if (respondType == SC_Record)
    {
        quint32 area, state;
        in >> area >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readRecord(area, state);
        if (state == 0x00)
        {
            readRecord(area, state);
        }
    }
    else if (respondType == SC_PlayBack)
    {
        quint32 area, state;
        in >> area >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readPlayBack(area, state);
    }
    else if (respondType == SC_TaskStop)
    {
        quint32 area, tasktype, state;
        in >> area >> tasktype >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readTaskStop(area, tasktype, state);
    }
    else if (respondType == SC_Delete)
    {
        quint32 area, state;
        in >> area >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readDelete(area, state);
    }
    else if (respondType == SC_Refresh)
    {
        tagAreaFileInfos fileInfos;
        in >> fileInfos.areano >> fileInfos.fileno >> fileInfos.filenum;

        list<shared_ptr<tagAreaFileInfo>> lstFileInfo;
        for (int nIndex=0;nIndex<fileInfos.filenum;++nIndex)
        {
            char filename[128] = {0};
            in.readRawData(filename, sizeof(filename));

            quint64 datetime;
            quint32 fileno;
            quint64 filesize;
            in >> datetime >> fileno >> filesize;

            shared_ptr<tagAreaFileInfo> spFileInfo = make_shared<tagAreaFileInfo>();
            spFileInfo->sFileName = QString::fromLocal8Bit(filename);

            spFileInfo->datetime = QDateTime::fromMSecsSinceEpoch(datetime);

            spFileInfo->fileno = fileno;
            spFileInfo->filesize = filesize;

            lstFileInfo.push_back(spFileInfo);
        }
        fileInfos.lstFileInfo.swap(lstFileInfo);

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(fileInfos.areano);
        pWMFileList->readRefresh(fileInfos);
    }
    else if (respondType == SC_Import)
    {
        quint32 areano, state;
        in >> areano;

        char filename[128] = {0};
        in.readRawData(filename, sizeof(filename));

        in >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(areano);
        pWMFileList->readImport(state);
        if (state == 0x00)
        {
            QTimer::singleShot(10, m_pDataSocket, SLOT(slotImport()));
        }
        else
        {
            m_pDataSocket->importFileList.clear();
        }
    }
    else if (respondType == SC_Export)
    {
        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->currentWidget();
        pWMFileList->m_pProgressBar->reset();

        quint32 areano, state;
        in >> areano >> state;
        if (state != 0x00)
        {
            m_lstExportParam.clear();
            pWMFileList->statusBar()->hide();
            QMessageBox::information(this, windowTitle(), tr("����ʧ�ܣ�"));
        }
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
    DlgIPSetting dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    m_sAddr = dlg.getIPAddr();
    m_pIPLabel->setText(m_sAddr);
    m_pDataSocket->sIPAddr = m_sAddr;
    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    m_pDataSocket->connectToHost(QHostAddress(m_sAddr), c_uDataPort);
}

void HostMachine::reallyCheckSelf()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_CheckSelf;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : ����-�Լ�
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotCheckSelf()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

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
    if (m_sAddr.isEmpty())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sIPSettingTip));
        return;
    }

    if (m_pCmdSocket->state() != QAbstractSocket::ConnectedState)
    {
        m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    reallyCheckSelf();

    DlgAreaFormat dlg(m_spcheckSelf->areaInfo0->areasize, m_spcheckSelf->areaInfo1->areasize,
        m_spcheckSelf->areaInfo2->areasize, m_spcheckSelf->areaInfo3->areasize,
        m_spcheckSelf->areaInfo4->areasize, this);
    if (QDialog::Accepted != dlg.exec())
        return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Format << quint32(dlg.Size1())
        << quint32(dlg.Size2())
        << quint32(dlg.Size3())
        << quint32(dlg.Size4())
        << quint32(dlg.Size5());

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : ����-ϵͳ����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotSystemConfig()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    DlgSystemConfig dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    quint32 bandwidth = dlg.Bandwidth();
    QList<quint32> lstChannel = dlg.ChannelChoice();

    foreach(quint32 channel, lstChannel)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_SystemConfig << channel << bandwidth;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead();
    }
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }


}



/*****************************************************************************
* @brief   : ����-��¼
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRecord()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    DlgAreaRecord dlg(m_pTabWgt->currentIndex(), this);
    if (QDialog::Accepted != dlg.exec())
        return;

    QString sFileName = dlg.Filename();
    QList<quint32> lstAreano = dlg.Areas();
    foreach(quint32 areano, lstAreano)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);

        quint64 time = QDateTime::currentMSecsSinceEpoch();
        out << CS_Record << areano << time;

        char filename[128] = {0};
        QByteArray ba = sFileName.toLocal8Bit();
        strncpy(filename, ba.data(), sizeof(filename));

        out.writeRawData(filename, sizeof(filename));

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead();
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
    if (m_sAddr.isEmpty())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sIPSettingTip));
        return;
    }

    if (m_pCmdSocket->state() != QAbstractSocket::ConnectedState)
    {
        m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    MWFileList* pFileList = (MWFileList*)m_pTabWgt->currentWidget();
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

    DlgFilePlayblack dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_PlayBack << m_pTabWgt->currentIndex() << *fileNos.begin()
        << dlg.Type() << dlg.Prftime() << dlg.Datanum() << dlg.Prf() << dlg.Cpi();

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : ����-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotImport()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    QStringList importFileList = QFileDialog::getOpenFileNames(this, qApp->translate(c_sHostMachine, c_sImportFileTip),
        "/", qApp->translate(c_sHostMachine, c_sImportFileExt));
    if (importFileList.isEmpty())
        return;

    m_pDataSocket->areano = m_pTabWgt->currentIndex();
    m_pDataSocket->importFileList = importFileList;

    // �ļ���С
    float filesize = 0;
    foreach(QString sImportFile, importFileList)
    {
        QFileInfo info(sImportFile);
        filesize += info.size();
    }

    filesize = filesize / c_bSizeMax; // LBA

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Import << m_pTabWgt->currentIndex() << filesize
        << QDateTime::currentMSecsSinceEpoch();

    // �ļ���
    QString sFileName = importFileList.first();
    char filename[128] = {0};
    QByteArray ba = sFileName.toLocal8Bit();
    strncpy(filename, ba.data(), sizeof(filename));
    out.writeRawData(filename, sizeof(filename));

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : ����-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotExport()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    MWFileList* pFileList = (MWFileList*)m_pTabWgt->currentWidget();
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

    if (rowNos.count() == 1)
    {
        float filesize = pFileListWgt->item(*rowNos.begin(), 5)->text().toFloat(); // ���������е��ļ���С��
        DlgFileExport dlg(filesize, this);
        if (QDialog::Accepted != dlg.exec())
            return;

        m_pDataSocket->exportFilePath = dlg.ExportPath();
        shared_ptr<tagExportParam> spExportParam = make_shared<tagExportParam>();
        spExportParam->rowNo = *rowNos.begin();
        spExportParam->startPos = dlg.Startpos();
        spExportParam->fileSize = dlg.Exportsize();

        m_lstExportParam.push_back(spExportParam);
    }
    else
    {
        QString sExportPath = QFileDialog::getExistingDirectory(this, qApp->translate(c_sHostMachine, c_sPathTitle), "./");
        if(sExportPath.isEmpty())
            return;

        m_pDataSocket->exportFilePath = sExportPath;

        foreach (quint32 rowNo, rowNos)
        {
            shared_ptr<tagExportParam> spExportParam = make_shared<tagExportParam>();
            spExportParam->rowNo = rowNo;
            spExportParam->startPos = 0;
            spExportParam->fileSize = pFileListWgt->item(rowNo, 5)->text().toFloat();

            m_lstExportParam.push_back(spExportParam);
        }
    }

    slotForeachExport();
}

void HostMachine::slotForeachExport()
{
    if (m_lstExportParam.size() < 1)
        return;

    shared_ptr<tagExportParam> spExportParam = m_lstExportParam.first();
    m_lstExportParam.pop_front();

    MWFileList* pFileList = (MWFileList*)m_pTabWgt->currentWidget();
    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;
    QString sFileName = QString("%0.%1").arg(pFileListWgt->item(spExportParam->rowNo, 1)->text()) // �ļ�����
        .arg(pFileListWgt->item(spExportParam->rowNo, 4)->text());// �ļ���׺

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Export << m_pTabWgt->currentIndex();

    char filename[128] = {0};
    QByteArray ba = sFileName.toLocal8Bit();
    strncpy(filename, ba.data(), sizeof(filename));
    out.writeRawData(filename, sizeof(filename));

    out << spExportParam->startPos << spExportParam->fileSize;

    m_pCmdSocket->write(block);
}

/*****************************************************************************
* @brief   : ����-ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotStop()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    QList<QTableWidgetItem*> selectedItems = m_pTaskWgt->selectedItems();
    QList<quint32> rowNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        rowNos.push_back(pItem->row());
    }

    if (rowNos.size() < 1)
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle), qApp->translate(c_sHostMachine, c_sIsStopTip));
        return;
    }

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

    foreach (quint32 rowNo, rowNos)
    {
        quint32 tasktype = m_pTaskWgt->item(rowNo, 0)->text().toInt();

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_TaskStop << m_pTabWgt->currentIndex() << tasktype;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead();
    }
}

/*****************************************************************************
* @brief   : ����-ɾ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotDelete()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

    MWFileList* pFileList = (MWFileList*)m_pTabWgt->currentWidget();
    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;
    QList<QTableWidgetItem*> selectedItems = pFileListWgt->selectedItems();
    if (selectedItems.count() < 1)
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle), qApp->translate(c_sHostMachine, c_sIsDeleteTip));
        return;
    }

    QMessageBox box(this);
    box.setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    box.setText(qApp->translate(c_sHostMachine, c_sIsDelete));
    box.setIcon(QMessageBox::Question);
    box.addButton(qApp->translate(c_sHostMachine, c_sYes), QMessageBox::YesRole);
    box.addButton(qApp->translate(c_sHostMachine, c_sNo), QMessageBox::NoRole);
    if (box.exec())
    {
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
        out << CS_Delete << m_pTabWgt->currentIndex();

        QString sFileName = pFileListWgt->item(rowNo, 1)->text() + "." + pFileListWgt->item(rowNo, 4)->text();
        QByteArray ba = sFileName.toLocal8Bit();
        char filename[128] = {0};
        strncpy(filename, ba, sizeof(filename));
        out.writeRawData(filename, sizeof(filename));

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead();
    }

    reallyRefresh();
}

void HostMachine::reallyRefresh()
{
    // ˢ��ǰ���Լ�
    reallyCheckSelf();

    // ��ʼ�ļ����
    quint32 fileno = 1;
    // ˢ���ļ���
    quint32 filenum = 8;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Refresh << m_pTabWgt->currentIndex() << fileno << filenum;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}


/*****************************************************************************
* @brief   : ����-ˢ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRefresh()
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
        if (!m_pCmdSocket->waitForConnected())
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                qApp->translate(c_sHostMachine, c_sNetConnectError));
            return;
        }
    }

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
        m_doubleManager->setValue(areaProperty->pItem1, areaInfo->areasize);
        m_doubleManager->setValue(areaProperty->pItem2, areaInfo->areasize - areaInfo->areaunuse);
        m_ddoubleManager->setValue(areaProperty->pItem3, areaInfo->areaunuse *100 / areaInfo->areasize);
        m_intManager->setValue(areaProperty->pItem4, areaInfo->areafilenum);
        m_enumManager->setValue(areaProperty->pItem5, areaInfo->areastate + 1);
    };

    updatevalue(m_areaProperties.ldProperty1, m_spcheckSelf->areaInfo0);
    updatevalue(m_areaProperties.ldProperty2, m_spcheckSelf->areaInfo1);
    updatevalue(m_areaProperties.gdProperty1, m_spcheckSelf->areaInfo2);
    updatevalue(m_areaProperties.gdProperty2, m_spcheckSelf->areaInfo3);
    updatevalue(m_areaProperties.hhProperty, m_spcheckSelf->areaInfo4);

    m_enumManager->setValue(m_areaProperties.channelProperty->pItem1, m_spcheckSelf->channelInfo->state + 1);
    m_enumManager->setValue(m_areaProperties.channelProperty->pItem2, m_spcheckSelf->channelInfo->choice + 1);
    m_enumManager->setValue(m_areaProperties.channelProperty->pItem3, m_spcheckSelf->channelInfo->bandwidth + 1);
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
        qApp->translate(c_sHostMachine, c_sFormatResult0);
    }
    else if (state == 0x01)
    {
        qApp->translate(c_sHostMachine, c_sFormatResult1);
    }
    else
    {
        qApp->translate(c_sHostMachine, c_sFormatResult2);
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
        qApp->translate(c_sHostMachine, c_sSystemConfigResult0);
    }
    else if (state == 0x01)
    {
        qApp->translate(c_sHostMachine, c_sSystemConfigResult1);
    }
    else
    {
        qApp->translate(c_sHostMachine, c_sSystemConfigResult2);
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
void HostMachine::readTaskQuery(list<tagTaskInfo>& lstTaskInfo)
{
    if (lstTaskInfo.empty())
        return;
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

void HostMachine::slotTabChanged(int index)
{
    QString sTabText = m_pTabWgt->tabText(index);
    foreach (QtBrowserItem * pBrowserItem, m_pPropertyWgt->topLevelItems())
    {
        QString sItemText = pBrowserItem->property()->propertyName();
        if (sItemText == qApp->translate(c_sHostMachine, c_sPropertyGroup1_6)
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

void HostMachine::initData()
{
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

void HostMachine::slotImportStart(qint32 areano, QString fileName, float buffer, float total)
{
    // �����ظ��У�ɾ��
    for (int nRow=0; nRow<m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->item(nRow, 0)->text() == m_pTabWgt->tabBar()->tabText(areano)
            && m_pTaskWgt->item(nRow, 1)->text() == qApp->translate(c_sHostMachine, c_sImport)
            && m_pTaskWgt->item(nRow, 2)->text() == fileName)
        {
            m_pTaskWgt->removeRow(nRow);
            break;
        }
    }

    // �������
    m_pTaskWgt->insertRow(m_pTaskWgt->rowCount());
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 0, new QTableWidgetItem(m_pTabWgt->tabBar()->tabText(areano)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 1, new QTableWidgetItem(qApp->translate(c_sHostMachine, c_sImport)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 2, new QTableWidgetItem(fileName));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 4, new QTableWidgetItem(CGlobalFun::formatSize(total)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 5, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 6, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 7, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 8, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 9, new QTableWidgetItem("0"));
    m_pTaskWgt->viewport()->update();
    m_pElapsedTimer->restart();
    m_nInterval = 100;
}

void HostMachine::slotImportUpdate(qint32 areano, QString fileName, float buffer, float total)
{
    if (m_pElapsedTimer->elapsed() / m_nInterval == 0)
        return;
    m_nInterval += 100;

    MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(areano);
    pWMFileList->updateProcess(fileName, buffer, total);

    for (int nRow=0; nRow<m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->item(nRow, 0)->text() == m_pTabWgt->tabBar()->tabText(areano)
            && m_pTaskWgt->item(nRow, 1)->text() == qApp->translate(c_sHostMachine, c_sImport)
            && m_pTaskWgt->item(nRow, 2)->text() == fileName)
        {
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(buffer));
            QString sPecent = QString("%0%").arg(buffer*100/total);
            m_pTaskWgt->item(nRow, 6)->setText(sPecent);
            QString sSpeed = QString("%0").arg(1000 * buffer / c_kSizeMax / m_pElapsedTimer->elapsed());
            m_pTaskWgt->item(nRow, 7)->setText(sSpeed);
            m_pTaskWgt->item(nRow, 8)->setText(qApp->translate(c_sHostMachine, c_sTaskState0));
            m_pTaskWgt->item(nRow, 9)->setText(CGlobalFun::formatElapsedTime(m_pElapsedTimer->elapsed()));
            m_pTaskWgt->viewport()->update();
            break;
        }
    }
}

void HostMachine::slotImportCompleted(qint32 areano, QString fileName, float buffer, float total)
{
    MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(areano);
    pWMFileList->updateProcess(fileName, buffer, total);
    for (int nRow=0; nRow<m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->item(nRow, 0)->text() == m_pTabWgt->tabBar()->tabText(areano)
            && m_pTaskWgt->item(nRow, 1)->text() == qApp->translate(c_sHostMachine, c_sImport)
            && m_pTaskWgt->item(nRow, 2)->text() == fileName)
        {
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(buffer));
            QString sPecent = QString("%0%").arg(buffer*100/total);
            m_pTaskWgt->item(nRow, 6)->setText(sPecent);
            QString sSpeed = QString("%0").arg(1000 * buffer / c_kSizeMax / m_pElapsedTimer->elapsed());
            m_pTaskWgt->item(nRow, 7)->setText(sSpeed);
            m_pTaskWgt->item(nRow, 8)->setText(qApp->translate(c_sHostMachine, c_sTaskState1));
            m_pTaskWgt->item(nRow, 9)->setText(CGlobalFun::formatElapsedTime(m_pElapsedTimer->elapsed()));
            m_pTaskWgt->viewport()->update();
            break;
        }
    }

    reallyRefresh();
}

void HostMachine::readRecord(quint32 area, quint32 state)
{
    m_pTaskWgt->setRowCount(m_pTaskWgt->rowCount() + 1);

    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 0, new QTableWidgetItem(m_pTabWgt->tabBar()->tabText(area)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 1, new QTableWidgetItem(qApp->translate(c_sHostMachine, c_sRecord)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 2, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
}

void HostMachine::closeLog()
{
    QTextStream in(m_pLog);
    in << "****************************************" << "\r\n";
    m_pLog->close();
}

void HostMachine::slotExportStart(qint32 areano, QString fileName, float buffer, float total)
{
    // �����ظ��У�ɾ��
    for (int nRow=0; nRow<m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->item(nRow, 0)->text() == m_pTabWgt->tabBar()->tabText(areano)
            && m_pTaskWgt->item(nRow, 1)->text() == qApp->translate(c_sHostMachine, c_sExport)
            && m_pTaskWgt->item(nRow, 2)->text() == fileName)
        {
            m_pTaskWgt->removeRow(nRow);
            break;
        }
    }

    // �������
    m_pTaskWgt->insertRow(m_pTaskWgt->rowCount());
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 0, new QTableWidgetItem(m_pTabWgt->tabBar()->tabText(areano)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 1, new QTableWidgetItem(qApp->translate(c_sHostMachine, c_sExport)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 2, new QTableWidgetItem(fileName));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 4, new QTableWidgetItem(CGlobalFun::formatSize(total)));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 5, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 6, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 7, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 8, new QTableWidgetItem(""));
    m_pTaskWgt->setItem(m_pTaskWgt->rowCount() - 1, 9, new QTableWidgetItem("0"));
    m_pTaskWgt->viewport()->update();
    m_pElapsedTimer->restart();
    m_nInterval = 100;
}

void HostMachine::slotExportUpdate(qint32 areano, QString fileName, float buffer, float total)
{
    if (m_pElapsedTimer->elapsed() / m_nInterval == 0)
        return;
    m_nInterval += 100;

    MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(areano);
    pWMFileList->updateProcess(fileName, buffer, total);

    for (int nRow=0; nRow<m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->item(nRow, 0)->text() == m_pTabWgt->tabBar()->tabText(areano)
            && m_pTaskWgt->item(nRow, 1)->text() == qApp->translate(c_sHostMachine, c_sExport)
            && m_pTaskWgt->item(nRow, 2)->text() == fileName)
        {
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(buffer));
            QString sPecent = QString("%0%").arg(buffer*100/total);
            m_pTaskWgt->item(nRow, 6)->setText(sPecent);
            QString sSpeed = QString("%0").arg(1000 * buffer / c_kSizeMax / m_pElapsedTimer->elapsed());
            m_pTaskWgt->item(nRow, 7)->setText(sSpeed);
            m_pTaskWgt->item(nRow, 8)->setText(qApp->translate(c_sHostMachine, c_sTaskState0));
            m_pTaskWgt->item(nRow, 9)->setText(CGlobalFun::formatElapsedTime(m_pElapsedTimer->elapsed()));
            m_pTaskWgt->viewport()->update();
            break;
        }
    }
}

void HostMachine::slotExportCompleted(qint32 areano, QString fileName, float buffer, float total)
{
    MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(areano);
    pWMFileList->updateProcess(fileName, buffer, total);
    for (int nRow=0; nRow<m_pTaskWgt->rowCount(); ++nRow)
    {
        if (m_pTaskWgt->item(nRow, 0)->text() == m_pTabWgt->tabBar()->tabText(areano)
            && m_pTaskWgt->item(nRow, 1)->text() == qApp->translate(c_sHostMachine, c_sExport)
            && m_pTaskWgt->item(nRow, 2)->text() == fileName)
        {
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(buffer));
            QString sPecent = QString("%0%").arg(buffer*100/total);
            m_pTaskWgt->item(nRow, 6)->setText(sPecent);
            QString sSpeed = QString("%0").arg(1000 * buffer / c_kSizeMax / m_pElapsedTimer->elapsed());
            m_pTaskWgt->item(nRow, 7)->setText(sSpeed);
            m_pTaskWgt->item(nRow, 8)->setText(qApp->translate(c_sHostMachine, c_sTaskState1));
            m_pTaskWgt->item(nRow, 9)->setText(CGlobalFun::formatElapsedTime(m_pElapsedTimer->elapsed()));
            m_pTaskWgt->viewport()->update();
            break;
        }
    }

    if (m_lstExportParam.size() > 0)
        slotForeachExport();
}
