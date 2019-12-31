#include "hostmachine.h"
#include <QTranslator>
#include <QtWidgets/QApplication>
#include "dlgareaformat.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString sTrans = QString("%0/translation/hostmachine_zh.qm").arg(a.applicationDirPath());

    QTranslator translator;
    translator.load(sTrans);
    a.installTranslator(&translator);

    qint64 nTotal = 2199023255552+97655193*4;
    DlgAreaFormat dlg(nTotal,2199023255552, 97655193, 97655193, 97655193, 97655193);
    dlg.exec();
    return 0;

    HostMachine w;
    w.show();
    return a.exec();
}
