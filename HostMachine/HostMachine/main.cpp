#include "hostmachine.h"
#include <QTranslator>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString sTrans = QString("%0/translation/hostmachine_zh.qm").arg(a.applicationDirPath());

    QTranslator translator;
    translator.load(sTrans);
    a.installTranslator(&translator);

    HostMachine w;
    w.show();
    return a.exec();
}
