#include "hostmachine.h"
#include <QTranslator>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("E:\\_Code\\HostMachine\\HostMachine\\HostMachine\\hostmachine_zh.qm");
    a.installTranslator(&translator);

    HostMachine w;
    w.show();
    return a.exec();
}
