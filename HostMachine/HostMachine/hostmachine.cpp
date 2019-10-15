#include "hostmachine.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "����Ӧ�����");
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP����");
static const char *c_sSystemControl = QT_TRANSLATE_NOOP("HostMachine", "ϵͳ����");
static const char *c_sAbout = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("HostMachine", "�Լ�");
static const char *c_sFormat = QT_TRANSLATE_NOOP("HostMachine", "��ʽ��");
static const char *c_sImport = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sExport = QT_TRANSLATE_NOOP("HostMachine", "����");
static const char *c_sRecord = QT_TRANSLATE_NOOP("HostMachine", "��¼");
static const char *c_sDelete = QT_TRANSLATE_NOOP("HostMachine", "ɾ��");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("HostMachine", "ˢ��");
static const char *c_sPlayback = QT_TRANSLATE_NOOP("HostMachine", "�ط�");
static const char *c_sStop = QT_TRANSLATE_NOOP("HostMachine", "ֹͣ");

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

    QAction* actIPSetting = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sIPSetting));
    QAction* actSystemControl = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sSystemControl));
    QAction* actAbout = menuBar()->addAction(qApp->translate(c_sHostMachine, c_sAbout));

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

    // Status Bar
    QLabel *normal=new QLabel("Normal Message",this);
    statusBar()->addWidget(normal);//��ʾ������Ϣ
    statusBar()->setSizeGripEnabled(false);//ȥ��״̬�����½ǵ�����
    statusBar()->showMessage("Temp Message", 2000);//��ʾ��ʱ��Ϣ2000ms ǰ���������Ϣ������ ��ȥ����һ��ʱ����һֱ��ʾ

    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(tr("<a href=\"http://baidu.com\">Permantant Message</a>"));
    permanent->setOpenExternalLinks(true);//���ÿ��Դ���վ����
    statusBar()->addPermanentWidget(permanent);//��ʾ������Ϣ
}

void HostMachine::initLayout()
{

}

void HostMachine::initConnect()
{

}
