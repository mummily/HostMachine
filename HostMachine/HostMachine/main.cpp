#include "hostmachine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HostMachine w;
    w.show();
    return a.exec();
}
