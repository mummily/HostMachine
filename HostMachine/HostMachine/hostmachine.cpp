
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
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "QDateTime"
#include <QFrame>
#include <QGroupBox>
#include <QPushButton>
#include <QTimer>

#include <QTcpSocket>
#include <QTcpServer>

#include "dlgipsetting.h"
#include "constdef.h"

HostMachine::HostMachine(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initTcp();
    initLayout();
    initConnect();

    QTimer::singleShot(10, this, SLOT(slotIPSetting()));
}

HostMachine::~HostMachine()
{

}

/*****************************************************************************
* @brief   : 初始化TCP
* @author  : wb
* @date    : 2019/10/26
* @param:  : 
*****************************************************************************/
void HostMachine::initTcp()
{
    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->listen();
    m_pTcpSocket = new QTcpSocket(this);
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
    
    // 工具栏
    QToolBar *toolBar = addToolBar("");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QString sIcon = QString("%1/Image/checkself.png").arg(qApp->applicationDirPath());
    m_pActCheckSelf = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sCheckSelf));
    m_pActCheckSelf->setStatusTip(m_pActCheckSelf->text());

    sIcon = QString("%1/Image/format.png").arg(qApp->applicationDirPath());
    m_pActFormat = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sFormat));
    m_pActFormat->setStatusTip(m_pActFormat->text());

    sIcon = QString("%1/Image/import.png").arg(qApp->applicationDirPath());
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
    m_pActPlayback = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sPlayback));
    m_pActPlayback->setStatusTip(m_pActPlayback->text());

    sIcon = QString("%1/Image/stop.png").arg(qApp->applicationDirPath());
    m_pActStop = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sStop));
    m_pActStop->setStatusTip(m_pActStop->text());

    // 菜单栏
    m_pActIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    m_pActIPSetting->setStatusTip(m_pActIPSetting->text());
    m_pActSystemSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sSystemSetting));
    m_pActSystemSetting->setStatusTip(m_pActSystemSetting->text());
    m_menuSystemControl = menuBar()->addMenu(qApp->translate(c_sHostMachine, c_sSystemOperation));
    m_menuSystemControl->setStatusTip(m_menuSystemControl->title());
    {
        m_menuSystemControl->addAction(m_pActCheckSelf);
        m_menuSystemControl->addAction(m_pActFormat);
    }
    m_pActAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));
    m_pActAbout->setStatusTip(m_pActAbout->text());

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

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(pTabWgt1);
    splitter->addWidget(m_pTaskWgt);
    splitter->addWidget(m_pLogWgt);
    QList<int> sizeList;
    sizeList << 300 << 200 << 100;
    splitter->setSizes(sizeList);
    splitter->setOpaqueResize(true);
    splitter->setChildrenCollapsible(false);

    // 属性区
    QTabWidget *pTabWgt2 = new QTabWidget(this);
    m_pPropertyWgt1 = new QtTreePropertyBrowser();
    initPropertyWgt1();
    m_pPropertyWgt2 = new QFrame(this);
    initPropertyWgt2();
    pTabWgt2->addTab(m_pPropertyWgt1, qApp->translate(c_sHostMachine, c_sPropertyTitle1));
    pTabWgt2->addTab(m_pPropertyWgt2, qApp->translate(c_sHostMachine, c_sPropertyTitle2));
    m_pSplitter = new QSplitter(Qt::Horizontal, this);
    m_pSplitter->addWidget(splitter);
    m_pSplitter->addWidget(pTabWgt2);
    m_pSplitter->setSizes(QList<int>() << 500 << 200);
    m_pSplitter->setOpaqueResize(true);
    m_pSplitter->setChildrenCollapsible(false);

    // 状态栏
    statusBar()->setSizeGripEnabled(true);
    
    m_pStateLabel = new QLabel(this);
    m_pStateLabel->setText(qApp->translate(c_sHostMachine, c_sDisConnect));
    statusBar()->addPermanentWidget(m_pStateLabel); //显示状态信息

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
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(m_pSplitter);
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
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotIPSetting()));

    // TCP
    connect(m_pTcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_pTcpSocket, SIGNAL(disconnect()), this, SLOT(disconnect()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
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

/*****************************************************************************
* @brief   : 初始化磁盘控制面板
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initPropertyWgt1()
{
    QtVariantPropertyManager *variantManager = new QtVariantPropertyManager();
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
    m_pPropertyWgt1->setFactoryForManager(variantManager, variantFactory);

    // 原始数据分区
    {
        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
            qApp->translate(c_sHostMachine, c_sPropertyGroup1_1));

        QtVariantProperty *item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_1));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_2));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_3));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Int,
            qApp->translate(c_sHostMachine, c_sProperty1_4));
        item->setValue(100);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 1);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_5));
        QStringList enumNames1_5;
        enumNames1_5 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_5);
        item->setValue(1);
        topItem->addSubProperty(item);

        m_pPropertyWgt1->addProperty(topItem);
    }
    // 雷达结果分区
    {
        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
            qApp->translate(c_sHostMachine, c_sPropertyGroup1_2));

        QtVariantProperty *item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_1));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_2));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_3));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Int,
            qApp->translate(c_sHostMachine, c_sProperty1_4));
        item->setValue(100);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 1);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_5));
        QStringList enumNames1_5;
        enumNames1_5 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_5);
        item->setValue(1);
        topItem->addSubProperty(item);

        m_pPropertyWgt1->addProperty(topItem);
    }
    // 光电图片分区
    {
        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
            qApp->translate(c_sHostMachine, c_sPropertyGroup1_3));

        QtVariantProperty *item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_1));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_2));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_3));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Int,
            qApp->translate(c_sHostMachine, c_sProperty1_4));
        item->setValue(100);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 1);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_5));
        QStringList enumNames1_5;
        enumNames1_5 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_5);
        item->setValue(1);
        topItem->addSubProperty(item);

        m_pPropertyWgt1->addProperty(topItem);
    }
    // 光电视频分区
    {
        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
            qApp->translate(c_sHostMachine, c_sPropertyGroup1_4));

        QtVariantProperty *item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_1));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_2));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_3));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Int,
            qApp->translate(c_sHostMachine, c_sProperty1_4));
        item->setValue(100);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 1);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_5));
        QStringList enumNames1_5;
        enumNames1_5 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_5);
        item->setValue(1);
        topItem->addSubProperty(item);

        m_pPropertyWgt1->addProperty(topItem);
    }
    // 混合数据分区
    {
        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
            qApp->translate(c_sHostMachine, c_sPropertyGroup1_5));

        QtVariantProperty *item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_1));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_2));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Double,
            qApp->translate(c_sHostMachine, c_sProperty1_3));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Int,
            qApp->translate(c_sHostMachine, c_sProperty1_4));
        item->setValue(100);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 1);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_5));
        QStringList enumNames1_5;
        enumNames1_5 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_5);
        item->setValue(1);
        topItem->addSubProperty(item);

        m_pPropertyWgt1->addProperty(topItem);
    }
    // 参数信息
    {
        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
            qApp->translate(c_sHostMachine, c_sPropertyGroup1_6));

        QtVariantProperty *item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_6));
        QStringList enumNames1_6;
        enumNames1_6 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_6);
        item->setValue(1);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
            qApp->translate(c_sHostMachine, c_sProperty1_7));
        QStringList enumNames1_7;
        enumNames1_7 << "Enum0" << "Enum1" << "Enum2";
        item->setAttribute(QLatin1String("enumNames"), enumNames1_7);
        item->setValue(1);
        topItem->addSubProperty(item);

        item = variantManager->addProperty(QVariant::Int,
            qApp->translate(c_sHostMachine, c_sProperty1_8));
        item->setValue(20);
        item->setAttribute(QLatin1String("minimum"), 0);
        item->setAttribute(QLatin1String("maximum"), 100);
        item->setAttribute(QLatin1String("singleStep"), 10);
        item->setAttribute(QLatin1String("readOnly"), true);
        topItem->addSubProperty(item);

        m_pPropertyWgt1->addProperty(topItem);
    }
    m_pPropertyWgt1->setPropertiesWithoutValueMarked(true);
    m_pPropertyWgt1->setRootIsDecorated(false);

    m_pPropertyWgt1->setHeaderVisible(false);
}

/*****************************************************************************
* @brief   : 初始化基本参数
* @author  : wb
* @date    : 2019/10/21
* @param:  : 无；该函数自成体系，函数体内实现UI、Layout、Connect的建立
*****************************************************************************/
void HostMachine::initPropertyWgt2()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    m_pPropertyWgt2->setLayout(mainLayout);

    {
        // 所属分区
        QGridLayout *gridLayout = new QGridLayout();
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_1), this), 0, 0);
        gridLayout->addWidget(new QLineEdit(this), 0, 1);

        // 记录文件名
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_2), this), 1, 0);
        gridLayout->addWidget(new QLineEdit(this), 1, 1);

        mainLayout->addLayout(gridLayout);
    }

    // 导出参数
    {
        QGridLayout *gridLayout = new QGridLayout();

        // 导出路径
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_3), this), 0, 0);

        QLineEdit* edtExportPath = new QLineEdit(this);
        gridLayout->addWidget(edtExportPath, 0, 1);

        QHBoxLayout *layoutExportPath = new QHBoxLayout();
        layoutExportPath->setContentsMargins(0, 0, 0, 0);
        edtExportPath->setLayout(layoutExportPath);

        // 导出路径按钮
        QPushButton *btnExportPath = new QPushButton("...", this);
        btnExportPath->setFixedWidth(24);
        layoutExportPath->addWidget(btnExportPath, 0, Qt::AlignRight);

        edtExportPath->setTextMargins(0, 0, btnExportPath->width(), 0);

        // 文件编号
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_4), this), 1, 0);
        gridLayout->addWidget(new QLineEdit(this), 1, 1);

        // 原始文件大小
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_5), this), 2, 0);
        gridLayout->addWidget(new QLineEdit(this), 2, 1);

        // 文件偏移
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_6), this), 3, 0);
        gridLayout->addWidget(new QLineEdit(this), 3, 1);

        // 导出文件大小
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_7), this), 4, 0);
        gridLayout->addWidget(new QLineEdit(this), 4, 1);

        // 导出参数
        QGroupBox* groupBox = new QGroupBox(qApp->translate(c_sHostMachine, c_sPropertyGroup2_1), this);
        groupBox->setLayout(gridLayout);

        mainLayout->addWidget(groupBox);
    }

    // 回放参数
    {
        QGridLayout *gridLayout = new QGridLayout();

        // 文件编号
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_8), this), 0, 0);
        gridLayout->addWidget(new QLineEdit(this), 0, 1);

        // PRF_TIME(us)
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_9), this), 1, 0);
        gridLayout->addWidget(new QLineEdit(this), 1, 1);

        // NUM
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_10), this), 2, 0);
        gridLayout->addWidget(new QLineEdit(this), 2, 1);

        // HEAD_PRF(H)
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_11), this), 3, 0);
        gridLayout->addWidget(new QLineEdit(this), 3, 1);

        // HEAD_CPI(H)
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_12), this), 4, 0);
        gridLayout->addWidget(new QLineEdit(this), 4, 1);

        QGroupBox* groupBox = new QGroupBox(qApp->translate(c_sHostMachine, c_sPropertyGroup2_2), this);
        groupBox->setLayout(gridLayout);

        mainLayout->addWidget(groupBox);
    }

    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(new QPushButton(qApp->translate(c_sHostMachine, c_sConfirm), this));
    hBoxLayout->addWidget(new QPushButton(qApp->translate(c_sHostMachine, c_sCancel), this));

    mainLayout->addLayout(hBoxLayout);

    mainLayout->addStretch();
}

void HostMachine::connected()
{
    // 状态
    m_pStateLabel->setText(qApp->translate(c_sHostMachine, c_sReady));
}

void HostMachine::disconnect()
{
    // 状态
    m_pStateLabel->setText(qApp->translate(c_sHostMachine, c_sDisConnect));
}

void HostMachine::readyRead()
{

}

void HostMachine::error()
{

}

void HostMachine::slotIPSetting()
{
    DlgIPSetting dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    m_pTcpSocket->connectToHost(/*QHostAddress::LocalHost*/QHostAddress(dlg.getIPAddr()), m_pTcpServer->serverPort());
}