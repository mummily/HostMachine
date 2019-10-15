#include "hostmachine.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>

static const char *c_sHostMachine = "HostMachine";
static const char *c_sTitle = QT_TRANSLATE_NOOP("HostMachine", "网络应用软件");
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("HostMachine", "IP设置");
static const char *c_sSystemControl = QT_TRANSLATE_NOOP("HostMachine", "系统控制");
static const char *c_sAbout = QT_TRANSLATE_NOOP("HostMachine", "关于");
static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("HostMachine", "自检");
static const char *c_sFormat = QT_TRANSLATE_NOOP("HostMachine", "格式化");
static const char *c_sImport = QT_TRANSLATE_NOOP("HostMachine", "导入");
static const char *c_sExport = QT_TRANSLATE_NOOP("HostMachine", "导出");
static const char *c_sRecord = QT_TRANSLATE_NOOP("HostMachine", "记录");
static const char *c_sDelete = QT_TRANSLATE_NOOP("HostMachine", "删除");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("HostMachine", "刷新");
static const char *c_sPlayback = QT_TRANSLATE_NOOP("HostMachine", "回放");
static const char *c_sStop = QT_TRANSLATE_NOOP("HostMachine", "停止");

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
    statusBar()->addWidget(normal);//显示正常信息
    statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    statusBar()->showMessage("Temp Message", 2000);//显示临时信息2000ms 前面的正常信息被覆盖 当去掉后一项时，会一直显示

    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(tr("<a href=\"http://baidu.com\">Permantant Message</a>"));
    permanent->setOpenExternalLinks(true);//设置可以打开网站链接
    statusBar()->addPermanentWidget(permanent);//显示永久信息
}

void HostMachine::initLayout()
{

}

void HostMachine::initConnect()
{

}
