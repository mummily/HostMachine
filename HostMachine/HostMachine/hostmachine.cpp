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

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "����Ӧ�����");

// ϵͳ�˵�
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP����");
static const char *c_sSystemControl = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ����");
static const char *c_sAbout = QT_TRANSLATE_NOOP("HostMachine", "����");

// ������
static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("HostMachine", "�Լ�");
static const char *c_sFormat = QT_TRANSLATE_NOOP("HostMachine", "��ʽ��");
static const char *c_sImport = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sExport = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sRecord = QT_TRANSLATE_NOOP("HostMachine", "��¼");
static const char *c_sDelete = QT_TRANSLATE_NOOP("HostMachine", "ɾ��");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("HostMachine", "ˢ��");
static const char *c_sPlayback = QT_TRANSLATE_NOOP("HostMachine", "�ط�");
static const char *c_sStop = QT_TRANSLATE_NOOP("HostMachine", "ֹͣ");

// ״̬��
static const char *c_sContactUs = QT_TRANSLATE_NOOP("HostMachine", "<a href=\"http://baidu.com\">��ϵ����</a>");

// �ļ��б�� - �״�����
static const char *c_sLDData = QT_TRANSLATE_NOOP("HostMachine", "�״�����");
static const char *c_sLDHeader1_1 = QT_TRANSLATE_NOOP("HostMachine", "ԭʼ�������ļ����");
static const char *c_sLDHeader1_2 = QT_TRANSLATE_NOOP("HostMachine", "�״�ͼƬ���ļ����");
static const char *c_sLDHeader2 = QT_TRANSLATE_NOOP("HostMachine", "�ļ�����");
static const char *c_sLDHeader3 = QT_TRANSLATE_NOOP("HostMachine", "�ļ���С");
static const char *c_sLDHeader4 = QT_TRANSLATE_NOOP("HostMachine", "����ʱ��");

// �ļ��б�� - �������
static const char *c_sGDData = QT_TRANSLATE_NOOP("HostMachine", "�������");
static const char *c_sGDHeader1_1 = QT_TRANSLATE_NOOP("HostMachine", "���ͼƬ���ļ����");
static const char *c_sGDHeader1_2 = QT_TRANSLATE_NOOP("HostMachine", "�����Ƶ���ļ����");
static const char *c_sGDHeader2 = QT_TRANSLATE_NOOP("HostMachine", "�ļ�����");
static const char *c_sGDHeader3 = QT_TRANSLATE_NOOP("HostMachine", "�ļ���С");
static const char *c_sGDHeader4 = QT_TRANSLATE_NOOP("HostMachine", "����ʱ��");

// �ļ��б�� - �������
static const char *c_sHHData = QT_TRANSLATE_NOOP("HostMachine", "�������");
static const char *c_sHHHeader1 = QT_TRANSLATE_NOOP("HostMachine", "�ں�ͼƬ���ļ����");
static const char *c_sHHHeader2 = QT_TRANSLATE_NOOP("HostMachine", "�ļ�����");
static const char *c_sHHHeader3 = QT_TRANSLATE_NOOP("HostMachine", "�ļ���С");
static const char *c_sHHHeader4 = QT_TRANSLATE_NOOP("HostMachine", "����ʱ��");

// ��־�����
static const char *c_sLogHeader1 = QT_TRANSLATE_NOOP("HostMachine", "����ʱ��");
static const char *c_sLogHeader2 = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ��Ϣ");

// �����б��
static const char *c_sTaskHeader1 = QT_TRANSLATE_NOOP("HostMachine", "���");
static const char *c_sTaskHeader2 = QT_TRANSLATE_NOOP("HostMachine", "��������");
static const char *c_sTaskHeader3 = QT_TRANSLATE_NOOP("HostMachine", "��������");
static const char *c_sTaskHeader4 = QT_TRANSLATE_NOOP("HostMachine", "����ʼʱ��");
static const char *c_sTaskHeader5 = QT_TRANSLATE_NOOP("HostMachine", "�ܴ�С(GB)");
static const char *c_sTaskHeader6 = QT_TRANSLATE_NOOP("HostMachine", "����ɴ�С(GB)");
static const char *c_sTaskHeader7 = QT_TRANSLATE_NOOP("HostMachine", "�ٷֱ�");
static const char *c_sTaskHeader8 = QT_TRANSLATE_NOOP("HostMachine", "����(MB/S)");
static const char *c_sTaskHeader9 = QT_TRANSLATE_NOOP("HostMachine", "״̬");
static const char *c_sTaskHeader10 = QT_TRANSLATE_NOOP("HostMachine", "��ʱ");

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

void HostMachine::initUI()
{
    setWindowTitle(qApp->translate(c_sHostMachine, c_sTitle));
    resize(1124, 726);
    
    // �˵���
    QAction* actIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    QAction* actSystemControl = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sSystemControl));
    QAction* actAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));
    
    // ������
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

    // ϵͳ״̬
    QTabWidget *pTabWgt2 = new QTabWidget(this);
    // TODO ���2��QtPropertyBrower
    m_splitter3 = new QSplitter(Qt::Horizontal, this);
    m_splitter3->addWidget(m_splitter2);
    m_splitter3->addWidget(pTabWgt2);
    m_splitter3->setSizes(QList<int>() << 500 << 200);
    m_splitter3->setOpaqueResize(true);
    m_splitter3->setChildrenCollapsible(false);

    // ״̬��
    statusBar()->setSizeGripEnabled(true);
    statusBar()->showMessage("Normal Message");

    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(qApp->translate(c_sHostMachine, c_sContactUs));
    permanent->setOpenExternalLinks(true);//���ÿ��Դ���վ����
    statusBar()->addPermanentWidget(permanent);//��ʾ������Ϣ
}

void HostMachine::initLayout()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(m_splitter3);
}

void HostMachine::initConnect()
{

}

void HostMachine::initLDDataWgt()
{
    QStringList headerList1;
    headerList1 << qApp->translate(c_sHostMachine, c_sLDHeader1_1) 
        << qApp->translate(c_sHostMachine, c_sLDHeader2)
        << qApp->translate(c_sHostMachine, c_sLDHeader3)
        << qApp->translate(c_sHostMachine, c_sLDHeader4);

    m_pLDDataWgt1->setColumnCount(headerList1.size());
    m_pLDDataWgt1->setHorizontalHeaderLabels(headerList1);

    QStringList headerList2;
    headerList2 << qApp->translate(c_sHostMachine, c_sLDHeader1_2) 
        << qApp->translate(c_sHostMachine, c_sLDHeader2)
        << qApp->translate(c_sHostMachine, c_sLDHeader3)
        << qApp->translate(c_sHostMachine, c_sLDHeader4);

    m_pLDDataWgt2->setColumnCount(headerList2.size());
    m_pLDDataWgt2->setHorizontalHeaderLabels(headerList2);
}

void HostMachine::initGDDataWgt()
{
    QStringList headerList1;
    headerList1 << qApp->translate(c_sHostMachine, c_sGDHeader1_1) 
        << qApp->translate(c_sHostMachine, c_sGDHeader2)
        << qApp->translate(c_sHostMachine, c_sGDHeader3)
        << qApp->translate(c_sHostMachine, c_sGDHeader4);

    m_pGDDataWgt1->setColumnCount(headerList1.size());
    m_pGDDataWgt1->setHorizontalHeaderLabels(headerList1);

    QStringList headerList2;
    headerList2 << qApp->translate(c_sHostMachine, c_sGDHeader1_2) 
        << qApp->translate(c_sHostMachine, c_sGDHeader2)
        << qApp->translate(c_sHostMachine, c_sGDHeader3)
        << qApp->translate(c_sHostMachine, c_sGDHeader4);

    m_pGDDataWgt2->setColumnCount(headerList2.size());
    m_pGDDataWgt2->setHorizontalHeaderLabels(headerList2);
}

void HostMachine::initHHDataWgt()
{
    QStringList headerList;
    headerList << qApp->translate(c_sHostMachine, c_sHHHeader1) 
        << qApp->translate(c_sHostMachine, c_sHHHeader2)
        << qApp->translate(c_sHostMachine, c_sHHHeader3)
        << qApp->translate(c_sHostMachine, c_sHHHeader4);

    m_pHHDataWgt->setColumnCount(headerList.size());
    m_pHHDataWgt->setHorizontalHeaderLabels(headerList);
}

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

    m_pTaskWgt->setColumnCount(headerList.size());
    m_pTaskWgt->setHorizontalHeaderLabels(headerList);
}

void HostMachine::initLogWgt()
{
    QStringList headerList;
    headerList << qApp->translate(c_sHostMachine, c_sLogHeader1) 
        << qApp->translate(c_sHostMachine, c_sLogHeader2);

    m_pLogWgt->setColumnCount(headerList.size());
    m_pLogWgt->setHorizontalHeaderLabels(headerList);
}
