
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
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "网络应用软件");
static const char *c_sImportFileTip = QT_TRANSLATE_NOOP("HostMachine", "选择要导入的文件");
static const char *c_sImportFileExt = QT_TRANSLATE_NOOP("HostMachine", "DAT文件(*.dat);;所有文件(*.*)");
static const char *c_sIsStop = QT_TRANSLATE_NOOP("HostMachine", "是否停止？");
static const char *c_sIsStopTip1 = QT_TRANSLATE_NOOP("HostMachine", "请选择要停止的任务！");
static const char *c_sIsStopTip2 = QT_TRANSLATE_NOOP("HostMachine", "请选择执行中的任务！");
static const char *c_sIsDelete = QT_TRANSLATE_NOOP("HostMachine", "是否删除？");
static const char *c_sYes = QT_TRANSLATE_NOOP("HostMachine", "是");
static const char *c_sNo = QT_TRANSLATE_NOOP("HostMachine", "否");
static const char *c_sToolBar = QT_TRANSLATE_NOOP("HostMachine", "工具栏");
static const char *c_sIsExportTip = QT_TRANSLATE_NOOP("HostMachine", "请选择要导出的文件！");
static const char *c_sIsDeleteTip = QT_TRANSLATE_NOOP("HostMachine", "请选择要删除的文件！");
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP设置");
static const char *c_sIPSettingTip = QT_TRANSLATE_NOOP("HostMachine", "请进行IP设置！");
static const char *c_sPathTitle = QT_TRANSLATE_NOOP("HostMachine", "选择导出文件路径");
static const char *c_sNetConnectError = QT_TRANSLATE_NOOP("HostMachine", "无法连接服务器，请检查网络连接！");
static const char *c_sPlayBackTip = QT_TRANSLATE_NOOP("HostMachine", "请选择一个文件回放！");
static const char *c_sRequestCancel = QT_TRANSLATE_NOOP("HostMachine", "有执行中任务，当前请求已取消！");

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
static const char *c_sPropertyGroup1_7 = QT_TRANSLATE_NOOP("HostMachine", "版本号");
static const char *c_sProperty1_1 = QT_TRANSLATE_NOOP("HostMachine", "总大小");
static const char *c_sProperty1_2 = QT_TRANSLATE_NOOP("HostMachine", "已用大小");
static const char *c_sProperty1_3 = QT_TRANSLATE_NOOP("HostMachine", "未用百分比");
static const char *c_sProperty1_4 = QT_TRANSLATE_NOOP("HostMachine", "文件数量");
static const char *c_sProperty1_5 = QT_TRANSLATE_NOOP("HostMachine", "当前状态");
static const char *c_sProperty1_6 = QT_TRANSLATE_NOOP("HostMachine", "通道连接状态");
static const char *c_sProperty1_7 = QT_TRANSLATE_NOOP("HostMachine", "通道选择状态");
static const char *c_sProperty1_8 = QT_TRANSLATE_NOOP("HostMachine", "通道带宽");
static const char *c_sProperty1_9 = QT_TRANSLATE_NOOP("HostMachine", "固件版本号");
static const char *c_sProperty1_10 = QT_TRANSLATE_NOOP("HostMachine", "FPGA版本号");

// 任务列表框
static const char *c_sTaskHeader1 = QT_TRANSLATE_NOOP("HostMachine", "序号");
static const char *c_sTaskHeader2 = QT_TRANSLATE_NOOP("HostMachine", "所属分区");
static const char *c_sTaskHeader3 = QT_TRANSLATE_NOOP("HostMachine", "任务类型");
static const char *c_sTaskHeader4 = QT_TRANSLATE_NOOP("HostMachine", "任务开始时间");
static const char *c_sTaskHeader5 = QT_TRANSLATE_NOOP("HostMachine", "总大小");
static const char *c_sTaskHeader6 = QT_TRANSLATE_NOOP("HostMachine", "已完成大小");
static const char *c_sTaskHeader7 = QT_TRANSLATE_NOOP("HostMachine", "百分比");
static const char *c_sTaskHeader8 = QT_TRANSLATE_NOOP("HostMachine", "速率(MB/S)");
static const char *c_sTaskHeader9 = QT_TRANSLATE_NOOP("HostMachine", "状态");
static const char *c_sTaskHeader10 = QT_TRANSLATE_NOOP("HostMachine", "耗时");

// 日志输出
static const char *c_sOpenSoftware = QT_TRANSLATE_NOOP("HostMachine", "打开软件");
static const char *c_sCloseSoftware = QT_TRANSLATE_NOOP("HostMachine", "关闭软件");

// 状态栏
static const char *c_sDisConnect = QT_TRANSLATE_NOOP("HostMachine", "未连接");
static const char *c_sReady = QT_TRANSLATE_NOOP("HostMachine", "就绪");
static const char *c_sContactUs = QT_TRANSLATE_NOOP("HostMachine", "联系我们");
static const char *c_sCmdDisconnect = QT_TRANSLATE_NOOP("HostMachine", "命令连接已断开！");
static const char *c_sDataDisconnect = QT_TRANSLATE_NOOP("HostMachine", "数据连接已断开！");

// 分区状态
static const char *c_sAreaState0 = QT_TRANSLATE_NOOP("HostMachine", "空闲");
static const char *c_sAreaState1 = QT_TRANSLATE_NOOP("HostMachine", "读");
static const char *c_sAreaState2 = QT_TRANSLATE_NOOP("HostMachine", "写");
static const char *c_sAreaState3 = QT_TRANSLATE_NOOP("HostMachine", "读写");

// 通道状态
static const char *c_sChannelState0 = QT_TRANSLATE_NOOP("HostMachine", "未连接");
static const char *c_sChannelState1 = QT_TRANSLATE_NOOP("HostMachine", "已连接");

// 通道选择
static const char *c_sChannelChoice0 = QT_TRANSLATE_NOOP("HostMachine", "已选择");
static const char *c_sChannelChoice1 = QT_TRANSLATE_NOOP("HostMachine", "未选择");

// 格式化结果
static const char *c_sFormatResult0 = QT_TRANSLATE_NOOP("HostMachine", "格式化成功");
static const char *c_sFormatResult1 = QT_TRANSLATE_NOOP("HostMachine", "格式化失败");
static const char *c_sFormatResult2 = QT_TRANSLATE_NOOP("HostMachine", "其它运行异常");

// 系统配置结果
static const char *c_sSystemConfigResult0 = QT_TRANSLATE_NOOP("HostMachine", "系统配置成功");
static const char *c_sSystemConfigResult1 = QT_TRANSLATE_NOOP("HostMachine", "系统配置失败");
static const char *c_sSystemConfigResult2 = QT_TRANSLATE_NOOP("HostMachine", "其它运行异常");

// 任务状态
static const char *c_sTaskState0 = QT_TRANSLATE_NOOP("HostMachine", "等待执行");
static const char *c_sTaskState1 = QT_TRANSLATE_NOOP("HostMachine", "执行中");
static const char *c_sTaskState2 = QT_TRANSLATE_NOOP("HostMachine", "完成");
static const char *c_sTaskState3 = QT_TRANSLATE_NOOP("HostMachine", "其它");

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

    m_pIPLabel = new QLabel(this);
    statusBar()->addPermanentWidget(m_pIPLabel); //显示IP信息

    m_pCmdLabel = new QLabel(this);
    QString sCmdLabel = QString("%1 %2").arg(c_uCommandPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pCmdLabel->setText(sCmdLabel);
    statusBar()->addPermanentWidget(m_pCmdLabel); //显示状态信息

    m_pDataLabel = new QLabel(this);
    QString sDataLabel = QString("%1 %2").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pDataLabel->setText(sDataLabel);
    statusBar()->addPermanentWidget(m_pDataLabel); //显示状态信息    

    QLabel *contactUs = new QLabel(this);
    contactUs->setFrameStyle(QFrame::Sunken);
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
* @brief   : 初始化任务区
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
        m_pTaskWgt->setItem(nIndex, 0, new QTableWidgetItem(QString::number(nIndex))); // 任务类型
        m_pTaskWgt->setItem(nIndex, 1, new QTableWidgetItem("")); // 序号
        m_pTaskWgt->setItem(nIndex, 2, new QTableWidgetItem("")); // 所属分区
        m_pTaskWgt->setItem(nIndex, 3, new QTableWidgetItem("")); // 任务类型
        m_pTaskWgt->setItem(nIndex, 4, new QTableWidgetItem("")); // 任务开始时间
        m_pTaskWgt->setItem(nIndex, 5, new QTableWidgetItem("")); // 总大小
        m_pTaskWgt->setItem(nIndex, 6, new QTableWidgetItem("")); // 已完成大小
        m_pTaskWgt->setItem(nIndex, 7, new QTableWidgetItem("")); // 百分比
        m_pTaskWgt->setItem(nIndex, 8, new QTableWidgetItem("")); // 速率
        m_pTaskWgt->setItem(nIndex, 9, new QTableWidgetItem("")); // 任务状态
        m_pTaskWgt->setItem(nIndex, 10, new QTableWidgetItem("")); // 耗时

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
* @brief   : 初始化磁盘控制面板
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

    // 参数信息
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
    // 版本号信息
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
    // 原始数据分区
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
    // 雷达结果分区
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
    // 光电图片分区
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
    // 光电视频分区
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
    // 混合数据分区
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
* @brief   : TCP连接
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
* @brief   : TCP断开
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::disconnectCmd()
{
    // 状态
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
    // 状态
    QString sLabel = QString("%0 %1").arg(c_uDataPort).arg(qApp->translate(c_sHostMachine, c_sDisConnect));
    m_pDataLabel->setText(sLabel);

    QString sLog = QString("%0 %1").arg(m_sAddr).arg(sLabel);
    slotLogRecord(sLog);

    // QMessageBox::warning(this, windowTitle(), qApp->translate(c_sHostMachine, c_sDataDisconnect));
}

/*****************************************************************************
* @brief   : TCP连接错误
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
        // 磁盘总大小
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
* @brief   : IP设置
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotIPSetting()
{
    // 若已连接，重设IP需保证无执行中任务
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

    // 设置IP地址后，触发一次刷新
    slotRefresh();
}

/*****************************************************************************
* @brief   : 自检
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
* @brief   : 请求-自检
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
* @brief   : 请求-格式化
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotFormat()
{
    if (!reConnectCmd())
        return;

    // 是否有执行中任务
    reallyTaskQuery();
    if (!queryTaskInvalid())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sRequestCancel));
        return;
    }

    // 自检
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
* @brief   : 请求-系统设置
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotSystemConfig()
{
    if (!reConnectCmd())
        return;

    // 是否有执行中任务
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
* @brief   : 任务查询
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
* @brief   : 请求-任务查询
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
* @brief   : 请求-记录
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
* @brief   : 请求-回放
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
* @brief   : 请求-导入
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

    // 文件大小
    QFileInfo fileInfo(spImportParam->filePath);
    qint32 filesize = fileInfo.size() / c_bSizeMax; // LBA
    if (filesize % 4 != 0)
        filesize += (4 - filesize % 4);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Import << m_pTabWgt->currentIndex() << filesize
        << CGlobalFun::Dt2Int(QDateTime::currentDateTime());

    // 文件名
    char filename[40] = {0};
    QByteArray ba = fileInfo.fileName().toLocal8Bit();
    strncpy(filename, ba.data(), sizeof(filename));
    out.writeRawData(filename, sizeof(filename));
    out << c_uRequestEndTag;

    m_pCmdSocket->write(block);
    m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);
}

/*****************************************************************************
* @brief   : 请求-导出
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
        double filesize = pFileListWgt->item(*rowNos.begin(), 5)->text().toDouble(); // 来自所在行的文件大小列
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
* @brief   : 导出
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
* @brief   : 请求-任务停止
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
* @brief   : 请求-分区停止
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
* @brief   : 请求-删除
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotDelete()
{
    if (!reConnectCmd())
        return;

    // 是否删除
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

    // 是否有执行中任务
    reallyTaskQuery();
    if (!queryTaskInvalid())
    {
        QMessageBox::information(this, qApp->translate(c_sHostMachine, c_sTitle),
            qApp->translate(c_sHostMachine, c_sRequestCancel));
        return;
    }

    // 判断选择项
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
* @brief   : 刷新
* @author  : wb
* @date    : 2019/12/02
* @param:  : 
*****************************************************************************/
void HostMachine::reallyRefresh()
{
    // 清空当前分区文件列表区所有文件
    QTableWidget* pFileListWgt = ((CMWFileList*)m_pTabWgt->currentWidget())->m_pFileListWgt;
    while (pFileListWgt->rowCount() > 0)
    {
        pFileListWgt->removeRow(pFileListWgt->rowCount() - 1);
    }

    // 刷新前先自检
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
            << nIndex // 起始文件编号
            << c_uRefreshFileNum // 刷新文件数
            << c_uRequestEndTag;

        m_pCmdSocket->write(block);
        m_pCmdSocket->waitForReadyRead(c_uWaitForMsecs);

        nIndex += c_uRefreshFileNum;
    }
}


/*****************************************************************************
* @brief   : 请求-刷新
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
* @brief   : 应答-自检
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

    // 通道状态
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

    // 通道选择
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

    // 通道带宽
    m_enumManager->setValue(m_spAreaProperties->channelProperty->pItem3, m_spcheckSelf->channelInfo->bandwidth + 1);

    // 版本号
    m_stringManager->setValue(m_spAreaProperties->versionProperty->pItem1, CGlobalFun::formatVersionNo(m_spcheckSelf->versionInfo->hardversion));
    m_stringManager->setValue(m_spAreaProperties->versionProperty->pItem2, CGlobalFun::formatVersionNo(m_spcheckSelf->versionInfo->fpgaversion));
}

/*****************************************************************************
* @brief   : 应答-格式化
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
* @brief   : 应答-系统设置
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
* @brief   : 应答-任务查询
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
            if (spTaskInfo->type == 13) // 导入导出
                return spTaskQueryParam->type == 1;
            else // 记录
                return spTaskQueryParam->areano == spTaskInfo->area;
        });

        shared_ptr<tagTaskQueryParam> spTaskQueryParam = *itTaskQueryParam;

        m_pTaskWgt->item(nRow, 1)->setText(QString::number(nSerialNum++)); // 序号
        m_pTaskWgt->item(nRow, 2)->setText(m_pTabWgt->tabBar()->tabText(spTaskInfo->area)); // 所属分区
        m_pTaskWgt->item(nRow, 3)->setText(QString::number(spTaskInfo->type)); // 任务类型
        m_pTaskWgt->item(nRow, 4)->setText(spTaskQueryParam->dtStart.toString("yyyy-MM-dd hh:mm:ss")); // 任务开始时间

        qint64 finishedsize = (qint64)spTaskInfo->finishedsize * c_bSizeMax;
        if (spTaskInfo->type == 13)
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(spTaskQueryParam->filesize)); // 总大小
        else // 记录任务，总大小=已完成大小
            m_pTaskWgt->item(nRow, 5)->setText(CGlobalFun::formatSize(finishedsize)); // 总大小
        m_pTaskWgt->item(nRow, 6)->setText(CGlobalFun::formatSize(finishedsize)); // 已完成大小
        m_pTaskWgt->item(nRow, 7)->setText(QString::number(spTaskInfo->percent) + "%"); // 百分比
        m_pTaskWgt->item(nRow, 8)->setText(CGlobalFun::formatSize(spTaskInfo->speed * c_bSizeMax) + "/s"); // 速率
        m_pTaskWgt->item(nRow, 9)->setText(qApp->translate(c_sHostMachine, c_sTaskState1)); // 任务状态
        m_pTaskWgt->item(nRow, 10)->setText(QString::number(spTaskQueryParam->dtStart.secsTo(QDateTime::currentDateTime())) + "s"); // 耗时
        m_pTaskWgt->cellWidget(nRow, 11)->show();
    }

    m_pTaskWgt->viewport()->update();
}

/*****************************************************************************
* @brief   : 点击Action时，日志记录
* @author  : wb
* @date    : 2019/11/02
* @param:  : 无
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
* @brief   : 日志记录
* @author  : wb
* @date    : 2019/11/02
* @param:  : 传入的信息，记录到文件中
*****************************************************************************/
void HostMachine::slotLogRecord(QString sText)
{
    QString sDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QTextStream in(m_pLog);
    in << sDateTime << " " << sText << "\r\n";
}

/*****************************************************************************
* @brief   : 界面初始化后响应的槽函数
* @author  : wb
* @date    : 2019/11/02
* @param:  : 无
*****************************************************************************/
void HostMachine::slotInit()
{
    // 日志记录-打开软件
    slotLogRecord(qApp->translate(c_sHostMachine, c_sOpenSoftware));

    // 第一个Tab页有效
    emit m_pTabWgt->currentChanged(0);
    // 打开IP设置
    emit m_pActIPSetting->triggered();
}

/*****************************************************************************
* @brief   : Tab索引切换
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
* @brief   : 初始化数据
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

    // 是否显示任务停止列
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

    // 日志
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
* @brief   : 导入开始
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
* @brief   : 导入更新进度
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
* @brief   : 导入完成
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
* @brief   : 导出开始
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
* @brief   : 导出更新进度
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
* @brief   : 导出完成
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
* @brief   : 关闭log记录
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
* @brief   : 命令端口重连
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
* @brief   : 数据端口重连
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
* @brief   : 查询的任务是否都是无效的
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
* @brief   : 任务停止
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
