#include "hostmachine.h"
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

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "网络应用软件");

// 系统菜单
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP设置");
static const char *c_sSystemControl = QT_TRANSLATE_NOOP("HostMachine", "系统控制");
static const char *c_sAbout = QT_TRANSLATE_NOOP("HostMachine", "关于");

// 工具栏
static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("HostMachine", "自检");
static const char *c_sFormat = QT_TRANSLATE_NOOP("HostMachine", "格式化");
static const char *c_sImport = QT_TRANSLATE_NOOP("HostMachine", "导入");
static const char *c_sExport = QT_TRANSLATE_NOOP("HostMachine", "导出");
static const char *c_sRecord = QT_TRANSLATE_NOOP("HostMachine", "记录");
static const char *c_sDelete = QT_TRANSLATE_NOOP("HostMachine", "删除");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("HostMachine", "刷新");
static const char *c_sPlayback = QT_TRANSLATE_NOOP("HostMachine", "回放");
static const char *c_sStop = QT_TRANSLATE_NOOP("HostMachine", "停止");

// 状态栏
static const char *c_sReady = QT_TRANSLATE_NOOP("HostMachine", "就绪");
static const char *c_sContactUs = QT_TRANSLATE_NOOP("HostMachine", "联系我们");

// 文件列表框 - 雷达数据
static const char *c_sLDData = QT_TRANSLATE_NOOP("HostMachine", "雷达数据");
static const char *c_sLDHeader1_1 = QT_TRANSLATE_NOOP("HostMachine", "原始数据区文件编号");
static const char *c_sLDHeader1_2 = QT_TRANSLATE_NOOP("HostMachine", "雷达图片区文件编号");
static const char *c_sLDHeader2 = QT_TRANSLATE_NOOP("HostMachine", "文件名称");
static const char *c_sLDHeader3 = QT_TRANSLATE_NOOP("HostMachine", "文件大小");
static const char *c_sLDHeader4 = QT_TRANSLATE_NOOP("HostMachine", "创建时间");

// 文件列表框 - 光电数据
static const char *c_sGDData = QT_TRANSLATE_NOOP("HostMachine", "光电数据");
static const char *c_sGDHeader1_1 = QT_TRANSLATE_NOOP("HostMachine", "光电图片区文件编号");
static const char *c_sGDHeader1_2 = QT_TRANSLATE_NOOP("HostMachine", "光电视频区文件编号");
static const char *c_sGDHeader2 = QT_TRANSLATE_NOOP("HostMachine", "文件名称");
static const char *c_sGDHeader3 = QT_TRANSLATE_NOOP("HostMachine", "文件大小");
static const char *c_sGDHeader4 = QT_TRANSLATE_NOOP("HostMachine", "创建时间");

// 文件列表框 - 混合数据
static const char *c_sHHData = QT_TRANSLATE_NOOP("HostMachine", "混合数据");
static const char *c_sHHHeader1 = QT_TRANSLATE_NOOP("HostMachine", "融合图片区文件编号");
static const char *c_sHHHeader2 = QT_TRANSLATE_NOOP("HostMachine", "文件名称");
static const char *c_sHHHeader3 = QT_TRANSLATE_NOOP("HostMachine", "文件大小");
static const char *c_sHHHeader4 = QT_TRANSLATE_NOOP("HostMachine", "创建时间");

// 日志输出框
static const char *c_sLogHeader1 = QT_TRANSLATE_NOOP("HostMachine", "操作时间");
static const char *c_sLogHeader2 = QT_TRANSLATE_NOOP("HostMachine", "系统信息");

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

HostMachine::HostMachine(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initLayout();
    initConnect();
}

HostMachine::~HostMachine()
{

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
    QAction* actIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    QAction* actSystemControl = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sSystemControl));
    QAction* actAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));
    
    // 工具栏
    QString sIcon = QString("%1/Image/icon.png").arg(qApp->applicationDirPath());
    QIcon icon(sIcon);

    QToolBar *toolBar = addToolBar("");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sCheckSelf));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sFormat));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sImport));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sExport));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sRecord));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sDelete));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sRefresh));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sPlayback));
    toolBar->addAction(icon, qApp->translate(c_sHostMachine, c_sStop));

    // 文件列表框
    QTabWidget *pTabWgt1 = new QTabWidget(this);
    { // 雷达数据
        m_pLDDataWgt1 = new QTableWidget(this);
        m_pLDDataWgt2 = new QTableWidget(this);
        initLDDataWgt();

        QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
        splitter->addWidget(m_pLDDataWgt1);
        splitter->addWidget(m_pLDDataWgt2);
        splitter->setSizes(QList<int>() << 100 << 100);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);

        pTabWgt1->addTab(splitter, qApp->translate(c_sHostMachine, c_sLDData));
    }
    { // 光电数据
        m_pGDDataWgt1 = new QTableWidget(this);
        m_pGDDataWgt2 = new QTableWidget(this);
        initGDDataWgt();

        QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
        splitter->addWidget(m_pGDDataWgt1);
        splitter->addWidget(m_pGDDataWgt2);
        splitter->setSizes(QList<int>() << 100 << 100);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);

        pTabWgt1->addTab(splitter, qApp->translate(c_sHostMachine, c_sGDData));
    }
    { // 混合数据
        m_pHHDataWgt = new QTableWidget(this);
        initHHDataWgt();
        pTabWgt1->addTab(m_pHHDataWgt, qApp->translate(c_sHostMachine, c_sHHData));
    }

    // 任务列表框
    m_pTaskWgt = new QTableWidget(this);
    initTaskWgt();

    // 日志输出框
    m_pLogWgt = new QTableWidget(this);
    initLogWgt();

    m_splitter1 = new QSplitter(Qt::Vertical, this);
    m_splitter1->addWidget(m_pTaskWgt);
    m_splitter1->addWidget(m_pLogWgt);
    QList<int> sizeList1;
    sizeList1 << 300 << 200;
    m_splitter1->setSizes(sizeList1);
    m_splitter1->setOpaqueResize(true);
    m_splitter1->setChildrenCollapsible(false);

    m_splitter2 = new QSplitter(Qt::Vertical, this);
    m_splitter2->addWidget(pTabWgt1);
    m_splitter2->addWidget(m_splitter1);
    m_splitter2->setSizes(QList<int>() << 200 << 200);
    m_splitter2->setOpaqueResize(true);
    m_splitter2->setChildrenCollapsible(false);

    // 系统状态
    QTabWidget *pTabWgt2 = new QTabWidget(this);
    // TODO 添加2个QtPropertyBrower
    m_splitter3 = new QSplitter(Qt::Horizontal, this);
    m_splitter3->addWidget(m_splitter2);
    m_splitter3->addWidget(pTabWgt2);
    m_splitter3->setSizes(QList<int>() << 500 << 200);
    m_splitter3->setOpaqueResize(true);
    m_splitter3->setChildrenCollapsible(false);

    // 状态栏
    statusBar()->setSizeGripEnabled(true);
    statusBar()->showMessage(qApp->translate(c_sHostMachine, c_sReady));

    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    QString sText = QString("<a href=\"http://www.baidu.com/\">%0").arg(qApp->translate(c_sHostMachine, c_sContactUs));
    permanent->setText(sText);
    permanent->setOpenExternalLinks(true); //设置可以打开网站链接
    statusBar()->addPermanentWidget(permanent); //显示永久信息
}

/*****************************************************************************
* @brief   : 初始化布局
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initLayout()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(m_splitter3);
}

/*****************************************************************************
* @brief   : 初始化信号槽
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initConnect()
{

}

/*****************************************************************************
* @brief   : 初始化：雷达数据
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initLDDataWgt()
{
    QStringList headerList1;
    headerList1 << qApp->translate(c_sHostMachine, c_sLDHeader1_1) 
        << qApp->translate(c_sHostMachine, c_sLDHeader2)
        << qApp->translate(c_sHostMachine, c_sLDHeader3)
        << qApp->translate(c_sHostMachine, c_sLDHeader4);

    m_pLDDataWgt1->setColumnCount(headerList1.size());
    m_pLDDataWgt1->setHorizontalHeaderLabels(headerList1);
    QHeaderView* headerView1 = m_pLDDataWgt1->horizontalHeader();
    headerView1->setDefaultAlignment(Qt::AlignLeft);
    headerView1->setStretchLastSection(true);
    headerView1->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    QStringList headerList2;
    headerList2 << qApp->translate(c_sHostMachine, c_sLDHeader1_2) 
        << qApp->translate(c_sHostMachine, c_sLDHeader2)
        << qApp->translate(c_sHostMachine, c_sLDHeader3)
        << qApp->translate(c_sHostMachine, c_sLDHeader4);

    m_pLDDataWgt2->setColumnCount(headerList2.size());
    m_pLDDataWgt2->setHorizontalHeaderLabels(headerList2);
    QHeaderView* headerView2 = m_pLDDataWgt2->horizontalHeader();
    headerView2->setDefaultAlignment(Qt::AlignLeft);
    headerView2->setStretchLastSection(true);
    headerView2->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    m_pLDDataWgt1->setShowGrid(true);
    m_pLDDataWgt1->setShowGrid(true);
}

/*****************************************************************************
* @brief   : 初始化光电数据
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initGDDataWgt()
{
    QStringList headerList1;
    headerList1 << qApp->translate(c_sHostMachine, c_sGDHeader1_1) 
        << qApp->translate(c_sHostMachine, c_sGDHeader2)
        << qApp->translate(c_sHostMachine, c_sGDHeader3)
        << qApp->translate(c_sHostMachine, c_sGDHeader4);

    m_pGDDataWgt1->setColumnCount(headerList1.size());
    m_pGDDataWgt1->setHorizontalHeaderLabels(headerList1);
    QHeaderView* headerView1 = m_pGDDataWgt1->horizontalHeader();
    headerView1->setDefaultAlignment(Qt::AlignLeft);
    headerView1->setStretchLastSection(true);
    headerView1->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    QStringList headerList2;
    headerList2 << qApp->translate(c_sHostMachine, c_sGDHeader1_2) 
        << qApp->translate(c_sHostMachine, c_sGDHeader2)
        << qApp->translate(c_sHostMachine, c_sGDHeader3)
        << qApp->translate(c_sHostMachine, c_sGDHeader4);

    m_pGDDataWgt2->setColumnCount(headerList2.size());
    m_pGDDataWgt2->setHorizontalHeaderLabels(headerList2);
    QHeaderView* headerView2 = m_pGDDataWgt2->horizontalHeader();
    headerView2->setDefaultAlignment(Qt::AlignLeft);
    headerView2->setStretchLastSection(true);
    headerView2->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    m_pGDDataWgt1->setShowGrid(true);
    m_pGDDataWgt2->setShowGrid(true);
}

/*****************************************************************************
* @brief   : 初始化混合数据
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initHHDataWgt()
{
    QStringList headerList;
    headerList << qApp->translate(c_sHostMachine, c_sHHHeader1) 
        << qApp->translate(c_sHostMachine, c_sHHHeader2)
        << qApp->translate(c_sHostMachine, c_sHHHeader3)
        << qApp->translate(c_sHostMachine, c_sHHHeader4);

    m_pHHDataWgt->setColumnCount(headerList.size());
    m_pHHDataWgt->setHorizontalHeaderLabels(headerList);
    QHeaderView* headerView = m_pHHDataWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
    headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    m_pHHDataWgt->setShowGrid(true);
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
* @brief   : 初始化日志区
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initLogWgt()
{
    QStringList headerList;
    headerList << qApp->translate(c_sHostMachine, c_sLogHeader1) 
        << qApp->translate(c_sHostMachine, c_sLogHeader2);

    m_pLogWgt->setColumnCount(headerList.size());
    m_pLogWgt->setHorizontalHeaderLabels(headerList);
    QHeaderView* headerView = m_pLogWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
    // headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    // headerView->setSectionResizeMode(1, QHeaderView::Stretch);

    m_pLogWgt->setShowGrid(true);
}
