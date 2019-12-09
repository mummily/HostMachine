#include <QtWidgets/QApplication>
#include <QPushButton>
#include "hostmachineserver.h"
#include "QHostAddress"
#include "../HostMachine/taskcommon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HostMachineServer server1;
    if (!server1.listen(QHostAddress::Any, c_uCommandPort)) // 命令端口
    {
        return 1;
    }

    HostMachineServer server2;
    if (!server2.listen(QHostAddress::Any, c_uDataPort)) // 数据端口
    {
        return 1;
    }
    
    QPushButton quitButton("Quit");
    quitButton.setWindowTitle("Host Machine Service");

    QObject::connect(&quitButton, SIGNAL(clicked()), &a, SLOT(quit()));
    quitButton.show();

    return a.exec();
}
