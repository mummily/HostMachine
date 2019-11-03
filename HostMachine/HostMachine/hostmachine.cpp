
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
#include <QMessageBox>

#include <QTcpSocket>
#include <QTcpServer>

#include "dlgipsetting.h"
#include "constdef.h"
#include "qtpropertymanager.h"
#include "decorateddoublepropertymanager.h"
#include "dlgareaformat.h"

HostMachine::HostMachine(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initTcp();
    initLayout();
    initConnect();

    QTimer::singleShot(10, this, SLOT(slotInit()));
}

HostMachine::~HostMachine()
{
    m_pTcpSocket->close();
}

/*****************************************************************************
* @brief   : ��ʼ��TCP
* @author  : wb
* @date    : 2019/10/26
* @param:  : 
*****************************************************************************/
void HostMachine::initTcp()
{
    m_pTcpSocket = new QTcpSocket(this);
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

    // ������
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
    m_pActPlayBack = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sPlayback));
    m_pActPlayBack->setStatusTip(m_pActPlayBack->text());

    sIcon = QString("%1/Image/stop.png").arg(qApp->applicationDirPath());
    m_pActStop = toolBar->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sStop));
    m_pActStop->setStatusTip(m_pActStop->text());

    // �˵���
    m_pActIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    m_pActIPSetting->setStatusTip(m_pActIPSetting->text());
    m_menuSystemControl = menuBar()->addMenu(qApp->translate(c_sHostMachine, c_sSystemOperation));
    m_menuSystemControl->setStatusTip(m_menuSystemControl->title());
    {
        m_menuSystemControl->addAction(m_pActCheckSelf);
        m_menuSystemControl->addAction(m_pActFormat);

        sIcon = QString("%1/Image/config.png").arg(qApp->applicationDirPath());
        m_pActSystemConfig = m_menuSystemControl->addAction(QIcon(sIcon), qApp->translate(c_sHostMachine, c_sSystemConfig));
        m_pActSystemConfig->setStatusTip(m_pActSystemConfig->text());
    }
    m_pActAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));
    m_pActAbout->setStatusTip(m_pActAbout->text());

    // �ļ��б��
    QTabWidget *pTabWgt1 = new QTabWidget(this);
    { // �״�����
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
    { // �������
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
    { // �������
        m_pHHDataWgt = new QTableWidget(this);
        initHHDataWgt();
        pTabWgt1->addTab(m_pHHDataWgt, qApp->translate(c_sHostMachine, c_sHHData));
    }

    // �����б��
    m_pTaskWgt = new QTableWidget(this);
    initTaskWgt();

    // ��־�����
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

    // ������
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

    // ״̬��
    statusBar()->setSizeGripEnabled(true);

    m_pStateLabel = new QLabel(this);
    m_pStateLabel->setText(qApp->translate(c_sHostMachine, c_sDisConnect));
    statusBar()->addPermanentWidget(m_pStateLabel); //��ʾ״̬��Ϣ

    QLabel *contactUs = new QLabel(this);
    contactUs->setFrameStyle(QFrame::Box|QFrame::Sunken);
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
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(m_pSplitter);
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
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActIPSetting, SIGNAL(triggered(bool)), this, SLOT(slotIPSetting()));

    connect(m_pActCheckSelf, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActCheckSelf, SIGNAL(triggered(bool)), this, SLOT(slotCheckSelf()));

    connect(m_pActFormat, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActFormat, SIGNAL(triggered(bool)), this, SLOT(slotFormat()));

    connect(m_pActSystemConfig, SIGNAL(triggered(bool)), this, SLOT(slotLogRecord()));
    connect(m_pActSystemConfig, SIGNAL(triggered(bool)), this, SLOT(slotSystemConfig()));

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


//     connect(m_pActTaskQuery, SIGNAL(triggered(bool)), this, SLOT(slotTaskQuery()));
//     connect(m_pActTaskStop, SIGNAL(triggered(bool)), this, SLOT(slotTaskStop()));

    // TCP
    connect(m_pTcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_pTcpSocket, SIGNAL(disconnect()), this, SLOT(disconnect()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
}

/*****************************************************************************
* @brief   : ��ʼ�����״�����
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
* @brief   : ��ʼ���������
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
* @brief   : ��ʼ���������
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
* @brief   : ��ʼ��������
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
* @brief   : ��ʼ����־��
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
    m_pLogWgt->setColumnWidth(0, 150);

    m_pLogWgt->setHorizontalHeaderLabels(headerList);
    QHeaderView* headerView = m_pLogWgt->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignLeft);
    headerView->setStretchLastSection(true);
    QHeaderView* verticalHeader = m_pLogWgt->verticalHeader();
    verticalHeader->hide();                                // �б�������
    verticalHeader->setDefaultSectionSize(20);             // ����Ĭ���и�

    m_pLogWgt->setSelectionMode(QAbstractItemView::SingleSelection);    // ����ѡ���ģʽΪ��ѡ��
    m_pLogWgt->setSelectionBehavior(QAbstractItemView::SelectRows);     // ����ѡ����Ϊʱÿ��ѡ��һ��
    m_pLogWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);      // ���ñ��Ϊֻ��
    m_pLogWgt->setShowGrid(true);                                       // ������ʾ������
}

/*****************************************************************************
* @brief   : ��ʼ�����̿������
* @author  : wb
* @date    : 2019/10/19
* @param:  : 
*****************************************************************************/
void HostMachine::initPropertyWgt1()
{
    m_groupManager = new QtGroupPropertyManager(m_pPropertyWgt1);
    m_stringManager = new QtStringPropertyManager(m_pPropertyWgt1);
    m_doubleManager = new QtDoublePropertyManager(m_pPropertyWgt1);
    m_ddoubleManager = new DecoratedDoublePropertyManager(m_pPropertyWgt1);
    m_intManager = new QtIntPropertyManager(m_pPropertyWgt1);
    m_enumManager = new QtEnumPropertyManager(m_pPropertyWgt1);

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

    // ԭʼ���ݷ���
    {
        shared_ptr<tagAreaProperty> areaProperty = make_shared<tagAreaProperty>();
        m_areaProperties.ldProperty1 = areaProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_1));
        m_pPropertyWgt1->addProperty(topItem);

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
        m_pPropertyWgt1->addProperty(topItem);

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
        m_pPropertyWgt1->addProperty(topItem);

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
        m_pPropertyWgt1->addProperty(topItem);

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
        m_pPropertyWgt1->addProperty(topItem);

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
    // ������Ϣ
    {
        shared_ptr<tagChannelProperty> channelProperty = make_shared<tagChannelProperty>();
        m_areaProperties.channelProperty = channelProperty;

        QtProperty *topItem = m_groupManager->addProperty(qApp->translate(c_sHostMachine, c_sPropertyGroup1_6));
        m_pPropertyWgt1->addProperty(topItem);

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

    m_pPropertyWgt1->setPropertiesWithoutValueMarked(true);
    m_pPropertyWgt1->setRootIsDecorated(false);
    m_pPropertyWgt1->setHeaderVisible(false);
}

/*****************************************************************************
* @brief   : ��ʼ����������
* @author  : wb
* @date    : 2019/10/21
* @param:  : �ޣ��ú����Գ���ϵ����������ʵ��UI��Layout��Connect�Ľ���
*****************************************************************************/
void HostMachine::initPropertyWgt2()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    m_pPropertyWgt2->setLayout(mainLayout);

    {
        // ��������
        QGridLayout *gridLayout = new QGridLayout();
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_1), this), 0, 0);
        gridLayout->addWidget(new QLineEdit(this), 0, 1);

        // ��¼�ļ���
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_2), this), 1, 0);
        gridLayout->addWidget(new QLineEdit(this), 1, 1);

        mainLayout->addLayout(gridLayout);
    }

    // ��������
    {
        QGridLayout *gridLayout = new QGridLayout();

        // ����·��
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_3), this), 0, 0);

        QLineEdit* edtExportPath = new QLineEdit(this);
        gridLayout->addWidget(edtExportPath, 0, 1);

        QHBoxLayout *layoutExportPath = new QHBoxLayout();
        layoutExportPath->setContentsMargins(0, 0, 0, 0);
        edtExportPath->setLayout(layoutExportPath);

        // ����·����ť
        QPushButton *btnExportPath = new QPushButton("...", this);
        btnExportPath->setFixedWidth(24);
        layoutExportPath->addWidget(btnExportPath, 0, Qt::AlignRight);

        edtExportPath->setTextMargins(0, 0, btnExportPath->width(), 0);

        // �ļ����
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_4), this), 1, 0);
        gridLayout->addWidget(new QLineEdit(this), 1, 1);

        // ԭʼ�ļ���С
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_5), this), 2, 0);
        gridLayout->addWidget(new QLineEdit(this), 2, 1);

        // �ļ�ƫ��
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_6), this), 3, 0);
        gridLayout->addWidget(new QLineEdit(this), 3, 1);

        // �����ļ���С
        gridLayout->addWidget(new QLabel(qApp->translate(c_sHostMachine, c_sProperty2_7), this), 4, 0);
        gridLayout->addWidget(new QLineEdit(this), 4, 1);

        // ��������
        QGroupBox* groupBox = new QGroupBox(qApp->translate(c_sHostMachine, c_sPropertyGroup2_1), this);
        groupBox->setLayout(gridLayout);

        mainLayout->addWidget(groupBox);
    }

    // �طŲ���
    {
        QGridLayout *gridLayout = new QGridLayout();

        // �ļ����
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

/*****************************************************************************
* @brief   : TCP����
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::connected()
{
    m_pStateLabel->setText(qApp->translate(c_sHostMachine, c_sReady));
}

/*****************************************************************************
* @brief   : TCP�Ͽ�
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::disconnect()
{
    // ״̬
    m_pStateLabel->setText(qApp->translate(c_sHostMachine, c_sDisConnect));
}

/*****************************************************************************
* @brief   : TCP���Ӵ���
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::error()
{
    statusBar()->showMessage(m_pTcpSocket->errorString());
}

/*****************************************************************************
* @brief   : Ӧ����Ϣ��Ӧ
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::readyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_pTcpSocket->bytesAvailable() < sizeof(quint32))
        return;

    quint32 respondType;
    in >> respondType;
    if (respondType == SC_CheckSelf)
    {
        tagCheckSelf checkSelf;

        shared_ptr<tagAreaInfo> areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        checkSelf.areaInfo0 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        checkSelf.areaInfo1 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        checkSelf.areaInfo2 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        checkSelf.areaInfo3 = areaInfo;

        areaInfo = make_shared<tagAreaInfo>();
        areaInfo->read(in);
        checkSelf.areaInfo4 = areaInfo;

        shared_ptr<tagChannelInfo> channelInfo = make_shared<tagChannelInfo>();
        channelInfo->read(in);
        checkSelf.channelInfo = channelInfo;

        readCheckSelf(checkSelf);
    }
    else if (respondType == SC_Format)
    {
        quint32 state;
        in >> state;

        readFormat(state);
    }
    else if (respondType == SC_SystemConfig)
    {
        quint32 state;
        in >> state;

        readSystemConfig(state);
    }
    else if (respondType == SC_Record)
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
    else if (respondType == SC_Import)
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
        readRefresh();
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
    else if (respondType == SC_TaskStop)
    {
        qint32 tasktype, taskrespond;
        in >> tasktype >> taskrespond;

        readTaskStop(tasktype, taskrespond);
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

    QString sAddr = dlg.getIPAddr();
    m_pTcpSocket->connectToHost(QHostAddress(sAddr), 6178);
}

/*****************************************************************************
* @brief   : ����-�Լ�
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotCheckSelf()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_CheckSelf;

    m_pTcpSocket->write(block);
    m_pTcpSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : ����-��ʽ��
* @author  : wb
* @date    : 2019/10/27
* @param:  : 
*****************************************************************************/
void HostMachine::slotFormat()
{
    DlgAreaFormat dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << CS_Format << quint32(dlg.Size1())
        << quint32(dlg.Size2())
        << quint32(dlg.Size3())
        << quint32(dlg.Size4())
        << quint32(dlg.Size5());

    m_pTcpSocket->write(block);
    m_pTcpSocket->waitForReadyRead();
}

/*****************************************************************************
* @brief   : ����-ϵͳ����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotSystemConfig()
{

}

/*****************************************************************************
* @brief   : ����-��¼
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRecord()
{
    quint32 type = CS_Record;
    quint32 areano = 0;
    quint64 time = QDateTime::currentMSecsSinceEpoch();
    char* filename = new char[128];
    memset(filename, 0, sizeof(filename));
    QString sFileName = "D:/123.txt";
    strcpy(filename, (const char*)sFileName.toLocal8Bit());

    delete[] filename;
}

/*****************************************************************************
* @brief   : ����-�ط�
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotPlayBack()
{

}

/*****************************************************************************
* @brief   : ����-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotImport()
{
    // ������
    quint32 areano = 0;
    quint32 filesize = 5;
    // ��ʼʱ��
    qint64 startTime = QDateTime::currentMSecsSinceEpoch();
    // �ļ���
    QChar* filename = new QChar[128];
    QString sFileName(filename);
    delete filename;
}

/*****************************************************************************
* @brief   : ����-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotExport()
{

}

/*****************************************************************************
* @brief   : ����-ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotStop()
{

}

/*****************************************************************************
* @brief   : ����-ɾ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotDelete()
{

}

/*****************************************************************************
* @brief   : ����-ˢ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotRefresh()
{

}

/*****************************************************************************
* @brief   : ����-�����ѯ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotTaskQuery()
{

}

/*****************************************************************************
* @brief   : ����-����ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::slotTaskStop()
{

}

/*****************************************************************************
* @brief   : Ӧ��-�Լ�
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readCheckSelf(tagCheckSelf &checkSelf)
{
    auto updatevalue=[&](shared_ptr<tagAreaProperty> areaProperty, shared_ptr<tagAreaInfo> areaInfo)->void
    {
        m_doubleManager->setValue(areaProperty->pItem1, areaInfo->areasize);
        m_doubleManager->setValue(areaProperty->pItem2, areaInfo->areasize - areaInfo->areaunuse);
        m_ddoubleManager->setValue(areaProperty->pItem3, areaInfo->areaunuse *100 / areaInfo->areasize);
        m_intManager->setValue(areaProperty->pItem4, areaInfo->areafilenum);
        m_enumManager->setValue(areaProperty->pItem5, areaInfo->areastate + 1);
    };

    updatevalue(m_areaProperties.ldProperty1, checkSelf.areaInfo0);
    updatevalue(m_areaProperties.ldProperty2, checkSelf.areaInfo1);
    updatevalue(m_areaProperties.gdProperty1, checkSelf.areaInfo2);
    updatevalue(m_areaProperties.gdProperty2, checkSelf.areaInfo3);
    updatevalue(m_areaProperties.hhProperty, checkSelf.areaInfo4);

    m_enumManager->setValue(m_areaProperties.channelProperty->pItem1, checkSelf.channelInfo->state + 1);
    m_enumManager->setValue(m_areaProperties.channelProperty->pItem2, checkSelf.channelInfo->choice + 1);
    m_enumManager->setValue(m_areaProperties.channelProperty->pItem3, checkSelf.channelInfo->bandwidth + 1);
}

/*****************************************************************************
* @brief   : Ӧ��-��ʽ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readFormat(quint32 state)
{
    qDebug() << "HostMachine::readFormat";
}

/*****************************************************************************
* @brief   : Ӧ��-ϵͳ����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readSystemConfig(quint32 state)
{
    if (state == 0x00)
    {
        statusBar()->showMessage("format success");
    }
}

/*****************************************************************************
* @brief   : Ӧ��-��¼
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readRecord(quint32 area, quint32 state)
{
}

/*****************************************************************************
* @brief   : Ӧ��-�ط�
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readPlayBack(quint32 area, quint32 state)
{

}

/*****************************************************************************
* @brief   : Ӧ��-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readImport(quint32 area, quint32 state)
{

}

/*****************************************************************************
* @brief   : Ӧ��-����
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readExport(quint32 area, quint32 state)
{

}

/*****************************************************************************
* @brief   : Ӧ��-ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readStop(quint32 area, quint32 state)
{

}

/*****************************************************************************
* @brief   : Ӧ��-ɾ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readDelete(quint32 area, quint32 state)
{

}

/*****************************************************************************
* @brief   : Ӧ��-ˢ��
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readRefresh()
{

}

/*****************************************************************************
* @brief   : Ӧ��-�����ѯ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readTaskQuery(list<tagTaskInfo>& lstTaskInfo)
{

}

/*****************************************************************************
* @brief   : Ӧ��-����ֹͣ
* @author  : wb
* @date    : 2019/10/28
* @param:  : 
*****************************************************************************/
void HostMachine::readTaskStop(qint32 tasktype, qint32 taskrespond)
{

}

/*****************************************************************************
* @brief   : ���Actionʱ����־��¼
* @author  : wb
* @date    : 2019/11/02
* @param:  : ��
*****************************************************************************/
void HostMachine::slotLogRecord()
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
void HostMachine::logRecord(QString sText)
{
    m_pLogWgt->setRowCount(m_pLogWgt->rowCount() + 1);
    QTableWidgetItem *pItem0 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    m_pLogWgt->setItem(m_pLogWgt->rowCount() - 1, 0, pItem0);
    QTableWidgetItem *pItem1 = new QTableWidgetItem(sText);
    m_pLogWgt->setItem(m_pLogWgt->rowCount() - 1, 1, pItem1);
    m_pLogWgt->scrollToBottom();
}

/*****************************************************************************
* @brief   : �����ʼ������Ӧ�Ĳۺ���
* @author  : wb
* @date    : 2019/11/02
* @param:  : ��
*****************************************************************************/
void HostMachine::slotInit()
{
    // ��־��¼�������
    logRecord(qApp->translate(c_sHostMachine, c_sLogOpenSoftware));

    // ��IP����
    emit m_pActIPSetting->triggered();
}
