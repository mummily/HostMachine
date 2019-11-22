
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

#include <QTcpSocket>
#include <QTcpServer>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "dlgipsetting.h"
#include "qtpropertymanager.h"
#include "decorateddoublepropertymanager.h"
#include "dlgareaformat.h"
#include "dlgsystemconfig.h"
#include "mwfilelist.h"
#include "dlgarearecord.h"
#include "dlgfileexport.h"
#include "ScopeGuard.h"

const quint16 c_uCommandPort = 6178;
const quint16 c_uDataPort = 6188;

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "网络应用软件");
static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("HostMachine", "选择要导入的文件");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("HostMachine", "DAT文件(*.dat);;所有文件(*.*)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("HostMachine", "是否停止？");
static const char *c_sIsStopTip = QT_TRANSLATE_NOOP("HostMachine", "请选择要停止的任务！");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("HostMachine", "是否删除？");
static const char *c_sYes = QT_TRANSLATE_NOOP("HostMachine", "是");
static const char *c_sNo = QT_TRANSLATE_NOOP("HostMachine", "否");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("HostMachine", "工具栏");
static const char *c_sIsExportTip = QT_TRANSLATE_NOOP("HostMachine", "请选择要导出的文件！");
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP设置");
static const char *c_sPathTitle = QT_TRANSLATE_NOOP("HostMachine", "选择导出文件路径");

// 系统菜单
static const char *c_sSystemConfig = QT_TRANSLATE_NOOP("HostMachine", "系统配置");
static const char *c_sSystemOperation = QT_TRANSLATE_NOOP("HostMachine", "系统操作");
static const char *c_sAbout = QT_TRANSLATE_NOOP("HostMachine", "关于");

// 工具栏
static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("HostMachine", "自检");
static const char *c_sFormat = QT_TRANSLATE_NOOP("HostMachine", "格式化");
static const char *c_sImport = QT_TRANSLATE_NOOP("HostMachine", "导入");
static const char *c_sExport = QT_TRANSLATE_NOOP("HostMachine", "导出");
static const char *c_sRecord = QT_TRANSLATE_NOOP("HostMachine", "记录");
static const char *c_sDelete = QT_TRANSLATE_NOOP("HostMachine", "删除");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("HostMachine", "刷新");
static const char *c_sPlayBack = QT_TRANSLATE_NOOP("HostMachine", "回放");
static const char *c_sStop = QT_TRANSLATE_NOOP("HostMachine", "停止");

// 属性区
static const char *c_sPropertyTitle1 = QT_TRANSLATE_NOOP("HostMachine", "磁盘控制面板");
static const char *c_sPropertyGroup1_1 = QT_TRANSLATE_NOOP("HostMachine", "原始数据分区");
static const char *c_sPropertyGroup1_2 = QT_TRANSLATE_NOOP("HostMachine", "雷达结果分区");
static const char *c_sPropertyGroup1_3 = QT_TRANSLATE_NOOP("HostMachine", "光电图片分区");
static const char *c_sPropertyGroup1_4 = QT_TRANSLATE_NOOP("HostMachine", "光电视频分区");
static const char *c_sPropertyGroup1_5 = QT_TRANSLATE_NOOP("HostMachine", "混合数据分区");
static const char *c_sPropertyGroup1_6 = QT_TRANSLATE_NOOP("HostMachine", "参数信息");
static const char *c_sProperty1_1 = QT_TRANSLATE_NOOP("HostMachine", "总大小");
static const char *c_sProperty1_2 = QT_TRANSLATE_NOOP("HostMachine", "已用大小");
static const char *c_sProperty1_3 = QT_TRANSLATE_NOOP("HostMachine", "未用百分比");
static const char *c_sProperty1_4 = QT_TRANSLATE_NOOP("HostMachine", "文件数量");
static const char *c_sProperty1_5 = QT_TRANSLATE_NOOP("HostMachine", "当前状态");
static const char *c_sProperty1_6 = QT_TRANSLATE_NOOP("HostMachine", "通道连接状态");
static const char *c_sProperty1_7 = QT_TRANSLATE_NOOP("HostMachine", "通道选择状态");
static const char *c_sProperty1_8 = QT_TRANSLATE_NOOP("HostMachine", "通道带宽");

// 任务列表框
static const char *c_sTaskHeader1 = QT_TRANSLATE_NOOP("HostMachine", "序号");
static const char *c_sTaskHeader2 = QT_TRANSLATE_NOOP("HostMachine", "所属分区");
static const char *c_sTaskHeader3 = QT_TRANSLATE_NOOP("HostMachine", "任务类型");
static const char *c_sTaskHeader4 = QT_TRANSLATE_NOOP("HostMachine", "任务开始时间");
static const char *c_sTaskHeader5 = QT_TRANSLATE_NOOP("HostMachine", "总大小(GB)");
static const char *c_sTaskHeader6 = QT_TRANSLATE_NOOP("HostMachine", "已完成大小(GB)");
static const char *c_sTaskHeader7 = QT_TRANSLATE_NOOP("HostMachine", "百分比");
static const char *c_sTaskHeader8 = QT_TRANSLATE_NOOP("HostMachine", "速率(MB/S)");
static const char *c_sTaskHeader9 = QT_TRANSLATE_NOOP("HostMachine", "状态");
static const char *c_sTaskHeader10 = QT_TRANSLATE_NOOP("HostMachine", "耗时");

// 日志输出
static const char *c_sOpenSoftware = QT_TRANSLATE_NOOP("HostMachine", "打开软件");

// 状态栏
static const char *c_sDisConnect = QT_TRANSLATE_NOOP("HostMachine", "未连接");
static const char *c_sReady = QT_TRANSLATE_NOOP("HostMachine", "就绪");
static const char *c_sContactUs = QT_TRANSLATE_NOOP("HostMachine", "联系我们");

// 分区状态
static const char *c_sAreaState0 = QT_TRANSLATE_NOOP("HostMachine", "空闲");
static const char *c_sAreaState1 = QT_TRANSLATE_NOOP("HostMachine", "读");
static const char *c_sAreaState2 = QT_TRANSLATE_NOOP("HostMachine", "写");
static const char *c_sAreaState3 = QT_TRANSLATE_NOOP("HostMachine", "读写");

// 通道状态
static const char *c_sChannelState0 = QT_TRANSLATE_NOOP("HostMachine", "未连接");
static const char *c_sChannelState1 = QT_TRANSLATE_NOOP("HostMachine", "连接");

// 通道选择
static const char *c_sChannelChoice0 = QT_TRANSLATE_NOOP("HostMachine", "选择");
static const char *c_sChannelChoice1 = QT_TRANSLATE_NOOP("HostMachine", "未选择");

HostMachine::HostMachine(QWidget *parent)
    : QMainWindow(parent), m_sAddr("")
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
    m_pCmdSocket->close();
    m_pDataSocket->close();
    m_pLog->close();
}

/*****************************************************************************
* @brief   : 初始化TCP
* @author  : wb
* @date    : 2019/10/26
* @param:  : 
*****************************************************************************/
void HostMachine::initTcp()
{
    m_pCmdSocket = new QTcpSocket(this);
    m_pDataSocket = new QTcpSocket(this);
}

/*****************************************************************************
* @brief   : 初始化UI
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initUI()
{
    setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    resize(1124, 726);

    // 菜单栏
    // 菜单项：IP设置
    m_pActIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    m_pActIPSetting->setStatusTip(m_pActIPSetting->text());

    // 菜单项：系统设置
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
    // 菜单项：关于
    m_pActAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));
    m_pActAbout->setStatusTip(m_pActAbout->text());

    // 文件列表框
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

    // 任务列表框
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

    // 属性区
    m_pPropertyWgt = new QtTreePropertyBrowser();
    initPropertyWgt();

    QDockWidget *pDockWgt = new QDockWidget(qApp->translate(c_sHostMachine, c_sPropertyTitle1), this);
    pDockWgt->setFeatures(QDockWidget::AllDockWidgetFeatures);
    pDockWgt->setAllowedAreas(Qt::RightDockWidgetArea);
    pDockWgt->setWidget(m_pPropertyWgt);
    addDockWidget(Qt::RightDockWidgetArea, pDockWgt);

    // 状态栏
    statusBar()->setSizeGripEnabled(true);

    m_pCmdLabel = new QLabel(this);
    QString sCmdLabel = QString("%1 %2").arg(c_uCommandPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pCmdLabel->setText(sCmdLabel);
    statusBar()->addPermanentWidget(m_pCmdLabel); //显示状态信息

    m_pDataLabel = new QLabel(this);
    QString sDataLabel = QString("%1 %2").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pDataLabel->setText(sDataLabel);
    statusBar()->addPermanentWidget(m_pDataLabel); //显示状态信息    

    QLabel *contactUs = new QLabel(this);
    contactUs->setFrameStyle(QFrame::Box|QFrame::Sunken);
    QString sText = QString("<a href=\"http://www.baidu.com/\">%0").arg(qApp->translate(c_sHostMachine, c_sContactUs));
    contactUs->setText(sText);
    contactUs->setOpenExternalLinks(true); //设置可以打开网站链接
    statusBar()->addPermanentWidget(contactUs); //显示永久信息
}

/*****************************************************************************
* @brief   : 初始化布局
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
* @brief   : 初始化信号槽
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initConnect()
{
    // Menubar & Toolbar
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotIPSetting()));

    connect(m_pActCheckSelf, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActCheckSelf, SIGNAL(triggered(bool)), this, SLOT(slotCheckSelf()));

    connect(m_pActFormat, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActFormat, SIGNAL(triggered(bool)), this, SLOT(slotFormat()));

    connect(m_pActSystemConfig, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActSystemConfig, SIGNAL(triggered(bool)), this, SLOT(slotSystemConfig()));

    connect(m_pTabWgt, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));

    // TCP
    connect(m_pCmdSocket, SIGNAL(connected()), this, SLOT(connectedCmd()));
    connect(m_pCmdSocket, SIGNAL(disconnected()), this, SLOT(disconnectCmd()));
    connect(m_pCmdSocket, SIGNAL(readyRead()), this, SLOT(readyReadCmd()));
    connect(m_pCmdSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorCmd()));

    connect(m_pDataSocket, SIGNAL(connected()), this, SLOT(connectedData()));
    connect(m_pDataSocket, SIGNAL(disconnected()), this, SLOT(disconnectData()));
    connect(m_pDataSocket, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    connect(m_pDataSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorData()));
}

/*****************************************************************************
* @brief   : 初始化任务区
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initTaskWgt()
{
    QStringList headerList;
    headerList << qApp->translate(c_sHostMachine, c_sTaskHeader1) 
        << qApp->translate(c_sHostMachine, c_sTaskHeader2)
        << qApp->translate(c_sHostMachine, c_sTaskHeader3)
        << qApp->translate(c_sHostMachine, c_sTaskHeader4)
        << qApp->translate(c_sHostMachine, c_sTaskHeader5)
        << qApp->translate(c_sHostMachine, c_sTaskHeader6)
        << qApp->translate(c_sHostMachine, c_sTaskHeader7)
        << qApp->translate(c_sHostMachine, c_sTaskHeader8)
        << qApp->translate(c_sHostMachine, c_sTaskHeader9)
        << qApp->translate(c_sHostMachine, c_sTaskHeader10);

    m_pTaskWgt->setShowGrid(false);
    m_pTaskWgt->setColumnCount(headerList.size());
    m_pTaskWgt->setHorizontalHeaderLabels(headerList);
    QHeaderView* headerView = m_pTaskWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
}

/*****************************************************************************
* @brief   : 初始化磁盘控制面板
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

    // 参数信息
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
    // 原始数据分区
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
    // 雷达结果分区
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
    // 光电图片分区
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
    // 光电视频分区
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
    // 混合数据分区
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
* @brief   : TCP连接
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::connectedCmd()
{
    QString sLabel = QString("%0 %1").arg(c_uCommandPort).arg(qApp->translate(c_sHostMachine, c_sReady));
    m_pCmdLabel->setText(sLabel);
}

void HostMachine::connectedData()
{
    QString sLabel = QString("%0 %1").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sReady));
    m_pDataLabel->setText(sLabel);
}

/*****************************************************************************
* @brief   : TCP断开
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::disconnectCmd()
{
    // 状态
    m_pCmdLabel->setText(qApp->translate(c_sHostMachine, c_sDisConnect));
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2019/11/10
* @param:  : 
*****************************************************************************/
void HostMachine::disconnectData()
{
    // 状态
    m_pDataLabel->setText(qApp->translate(c_sHostMachine, c_sDisConnect));
}

/*****************************************************************************
* @brief   : TCP连接错误
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::errorCmd()
{
    statusBar()->showMessage(m_pCmdSocket->errorString());
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2019/11/10
* @param:  : 
*****************************************************************************/
void HostMachine::errorData()
{
    statusBar()->showMessage(m_pDataSocket->errorString());
}

/*****************************************************************************
* @brief   : 应答消息响应
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
        if (tasknum > 0)
        {
            list<tagTaskInfo> lstTaskInfo;
            for (int index=0;index<tasknum;++index)
            {
                tagTaskInfo taskInfo;
                in >> taskInfo.flag >> taskInfo.area >> taskInfo.type
                    >> taskInfo.finishedsize >> taskInfo.speed >> taskInfo.percent >> taskInfo.state;
                lstTaskInfo.push_back(taskInfo);
            }

            readTaskQuery(lstTaskInfo);
        }
    }
    else if (respondType == SC_Record)
    {
        quint32 area, state;
        in >> area >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readRecord(area, state);
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
            char* filename = new char[128];
            memset(filename, 0, sizeof(char)*128);
            in.readRawData(filename, 128);

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
            delete filename;
        }
        fileInfos.lstFileInfo.swap(lstFileInfo);

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(fileInfos.areano);
        pWMFileList->readRefresh(fileInfos);
    }
    else if (respondType == SC_Import)
    {
        quint32 areano, state;
        in >> areano;

        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);
        in.readRawData(filename, 128);

        in >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(areano);
        if (state != 0x00)
        {
            QString sMsg = QString("%0 Import Error!").arg(filename);
            pWMFileList->statusBar()->showMessage(sMsg);
            return;
        }

        m_pDataSocket->connectToHost(QHostAddress(m_sAddr), c_uDataPort);
        SCOPE_EXIT([&]{ m_pDataSocket->close();});

        QString sFile = QString::fromLocal8Bit(filename);
        QFileInfo fileInfo = sFile;
        qint64 fileSize = fileInfo.size();
        QString sHeader = QString("%0##%1##%2").arg(areano).arg(fileInfo.fileName()).arg(fileSize);
        qint64 len = m_pDataSocket->write(sHeader.toUtf8());
        m_pDataSocket->waitForBytesWritten();
        if (len == -1)
            return;

        QFile file;
        file.setFileName(sFile);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                tr("打开文件失败！"));
            return;
        }

        float newFileSize = fileSize;
        QString sFileUnit;
        formatSize(fileSize, newFileSize, sFileUnit);

        qint64 bufferLen = 0;
        len = 0;
        do
        {
            char buffer[c_bufferSize] = {0};
            len = file.read(buffer, sizeof(buffer));
            len = m_pDataSocket->write(buffer, len);
            bufferLen += len;

            float newBufferLen = bufferLen;
            QString sBufferUnit;
            formatSize(bufferLen, newBufferLen, sBufferUnit);
            QString sMsg = QString("%0 Import %1 %2/%3 %4").arg(filename).arg(newBufferLen).arg(sBufferUnit).arg(newFileSize).arg(sFileUnit);
            pWMFileList->statusBar()->showMessage(sMsg);
        } while (len > 0);

        file.close();

        reallyRefresh();
    }
}

/*****************************************************************************
* @brief   : 
* @author  : wb
* @date    : 2019/11/10
* @param:  : 
*****************************************************************************/
void HostMachine::readyReadData()
{
    QDataStream in(m_pDataSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_pDataSocket->bytesAvailable() < sizeof(quint32))
        return;

    quint32 respondType;
    in >> respondType;
    if (respondType == SC_Export)
    {
        quint32 area, state;
        in >> area >> state;

        MWFileList* pWMFileList = (MWFileList*)m_pTabWgt->widget(area);
        pWMFileList->readExport(area, state);
    }
    else if (respondType == SC_Import)
    {
        return;
        QString sFile = "C:\\Users\\wangbin\\Desktop\\1109.dat"/*QString::fromLocal8Bit(filename)*/;

        QFile file;
        file.setFileName(sFile);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
                tr("打开文件失败！"));
            return;
        }
        QFileInfo info(sFile);
        float filesize = info.size();

        qint64 len = 0;
        do
        {
            char buffer[c_bufferSize] = {0};
            len = file.read(buffer, sizeof(buffer));
            len = m_pDataSocket->write(buffer, len);
        } while (len > 0);

        file.close();

        slotRefresh();
    }
}

/*****************************************************************************
* @brief   : IP设置
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
//     m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
//     m_pDataSocket->connectToHost(QHostAddress(m_sAddr), c_uDataPort);
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
* @brief   : 请求-自检
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotCheckSelf()
{
    DlgAreaFormat dlg(m_spcheckSelf->areaInfo0->areasize, m_spcheckSelf->areaInfo1->areasize,
        m_spcheckSelf->areaInfo2->areasize, m_spcheckSelf->areaInfo3->areasize,
        m_spcheckSelf->areaInfo4->areasize, this);
    if (QDialog::Accepted != dlg.exec())
        return;

    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

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
* @brief   : 请求-格式化
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotFormat()
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

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
* @brief   : 请求-系统设置
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotSystemConfig()
{
    DlgSystemConfig dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

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
* @brief   : 请求-任务查询
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotTaskQuery()
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});


}



/*****************************************************************************
* @brief   : 请求-记录
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRecord()
{
    DlgAreaRecord dlg(m_pTabWgt->currentIndex(), this);
    if (QDialog::Accepted != dlg.exec())
        return;

    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

    QString sFileName = dlg.Filename();
    QList<quint32> lstAreano = dlg.Areas();
    foreach(quint32 areano, lstAreano)
    {
        quint64 time = QDateTime::currentMSecsSinceEpoch();
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);

        QByteArray ba = sFileName.toLatin1();
        filename = ba.data();

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_Record << areano << time;
        out.writeRawData(filename, 128);

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead();

        // delete[] filename;
    }
}

/*****************************************************************************
* @brief   : 请求-回放
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotPlayBack(quint32 fileno, quint32 type, quint32 prftime, quint32 datanum, quint32 prf, quint32 cpi)
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_PlayBack << m_pTabWgt->currentIndex() << fileno // 文件编号
        << type << prftime << prftime << datanum << cpi;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : 请求-导入
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotImport()
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

#pragma message("MWFileList::slotImport 导入是选定一个分区执行导入，可单个可批量")

    QString sFile = QFileDialog::getOpenFileName(this, qApp->translate(c_sHostMachine, c_sImportFileTip),
        "/", qApp->translate(c_sHostMachine, c_sImportFileExt));
    if (sFile.isEmpty())
        return;

    QFileInfo info(sFile);

    // 分区号
    int areano = m_pTabWgt->currentIndex();
    float filesize = info.size();
    // 开始时间
    qint64 startTime = QDateTime::currentMSecsSinceEpoch();
    // 文件名
    char* filename = new char[128];
    memset(filename, 0, sizeof(char)*128);
    QByteArray ba = sFile.toLatin1();
    filename = ba.data();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Import << m_pTabWgt->currentIndex() << filesize
        << startTime;
    out.writeRawData(filename, 128);

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : 请求-导出
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotExport()
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

    MWFileList* pFileList = (MWFileList*)m_pTabWgt->currentWidget();
    QTableWidget *pFileListWgt = pFileList->m_pFileListWgt;
    QList<QTableWidgetItem*> selectedItems = pFileListWgt->selectedItems();
    QSet<quint32> rowNos;
    foreach(QTableWidgetItem* pItem, selectedItems)
    {
        rowNos.insert(pItem->row());
    }

    if (rowNos.size() < 1)
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle), qApp->translate(c_sHostMachine, c_sIsExportTip));
        return;
    }

    float fStartPos = 0.0;
    float fExportSize = 0.0;
    QString sExportPath = "";
    if (rowNos.count() == 1)
    {
        float filesize = pFileList->m_pFileListWgt->item(*rowNos.begin(), 5)->text().toFloat(); // 来着所在行的文件大小列
        DlgFileExport dlg(filesize, this);
        if (QDialog::Accepted != dlg.exec())
            return;

        fStartPos = dlg.Startpos();
        fExportSize = dlg.Exportsize();
        sExportPath = dlg.ExportPath();
    }
    else
    {
        sExportPath = QFileDialog::getExistingDirectory(this, qApp->translate(c_sHostMachine, c_sPathTitle), "./");
        if(sExportPath.isEmpty())
            return;
    }

    foreach (quint32 rowNo, rowNos)
    {
        QString sFileName = QString("%0.%1").arg(pFileListWgt->item(rowNo, 1)->text()).arg(pFileListWgt->item(rowNo, 4)->text());
        QString sLocalPath = QString("%0/%1_%2_%3").arg(sExportPath).arg(m_pTabWgt->currentIndex()).arg(pFileListWgt->item(rowNo, 0)->text()).arg(sFileName);

        m_pFile = new QFile(sLocalPath);
        m_pFile->open(QIODevice::WriteOnly);

        QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
        accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
        QString sUrl = QString("http://%0:%1/%2/%3").arg(m_pDataSocket->localAddress().toString()).arg(c_uDataPort).arg(m_pTabWgt->currentIndex()).arg(sFileName);
        QUrl url(sUrl);

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
        m_pNetworkReply = accessManager->get(request);

        connect((QObject *)m_pNetworkReply, SIGNAL(readyRead()), this, SLOT(readContent()));
        connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
        connect(m_pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
        connect(m_pNetworkReply, SIGNAL(downloadProgress(qint64 ,qint64)), pFileList, SLOT(loadProgress(qint64 ,qint64)));
    }
}

void HostMachine::readContent()
{
    m_pFile->write(m_pNetworkReply->readAll());
}

void HostMachine::replyFinished(QNetworkReply* pNetworkReply)
{
    if(pNetworkReply->error() == QNetworkReply::NoError)
    {
        pNetworkReply->deleteLater();
        m_pFile->flush();
        m_pFile->close();
    }
    else
    {
        QMessageBox::critical(NULL, tr("Error"), "Failed!");
    }
}


void HostMachine::loadError(QNetworkReply::NetworkError code)
{
    qDebug()<<"Error: "<< m_pNetworkReply->error();
}

/*****************************************************************************
* @brief   : 请求-停止
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotStop()
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

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
* @brief   : 请求-删除
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotDelete(QList<quint32> fileNos)
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

    foreach(quint32 fileno, fileNos)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << CS_Delete << m_pTabWgt->currentIndex() << fileno;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead();
    }
}

void HostMachine::reallyRefresh()
{
    // 刷新前先自检
    reallyCheckSelf();

    // 起始文件编号
    quint32 fileno = 1;
    // 刷新文件数
    quint32 filenum = 8;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Refresh << m_pTabWgt->currentIndex() << fileno << filenum;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead();
}


/*****************************************************************************
* @brief   : 请求-刷新
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRefresh()
{
    if (m_sAddr.isEmpty())
        return;

    m_pCmdSocket->connectToHost(QHostAddress(m_sAddr), c_uCommandPort);
    SCOPE_EXIT([&]{ m_pCmdSocket->close();});

    reallyRefresh();
}

/*****************************************************************************
* @brief   : 应答-自检
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
* @brief   : 应答-格式化
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readFormat(quint32 state)
{
    statusBar()->showMessage((state == 0x00) ? "format success" : "format error");
}

/*****************************************************************************
* @brief   : 应答-系统设置
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readSystemConfig(quint32 choice, quint32 state)
{
    QString sMsg = QString("Channel %0 Config %1").arg(choice).arg((state == 0x00) ? "success" : "error");
    statusBar()->showMessage(sMsg);
}

/*****************************************************************************
* @brief   : 应答-任务查询
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readTaskQuery(list<tagTaskInfo>& lstTaskInfo)
{

}

/*****************************************************************************
* @brief   : 点击Action时，日志记录
* @author  : wb
* @date    : 2019/11/02
* @param:  : 无
*****************************************************************************/
void HostMachine::slotLogRecord()
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
* @param:  : 传入的信息，记录到文件中
*****************************************************************************/
void HostMachine::logRecord(QString sText)
{
    QString sDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QTextStream in(m_pLog);
    in << sDateTime << "\n";
    in << sText << "\n";
}

/*****************************************************************************
* @brief   : 界面初始化后响应的槽函数
* @author  : wb
* @date    : 2019/11/02
* @param:  : 无
*****************************************************************************/
void HostMachine::slotInit()
{
    // 日志记录：打开软件
    logRecord(qApp->translate(c_sHostMachine, c_sOpenSoftware));

    emit m_pTabWgt->currentChanged(0);
    // 打开IP设置
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

void HostMachine::formatSize(qint64 oldBytes, float& newBytes, QString& sUnit)
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