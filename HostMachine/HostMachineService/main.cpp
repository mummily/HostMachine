#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QDebug>
#include "hostmachineserver.h"
#include "QHostAddress"

const quint16 c_uCommandPort = 6178;
const quint16 c_uDataPort = 6188;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HostMachineServer server1;
    if (!server1.listen(QHostAddress::Any, c_uCommandPort)) // ����˿�
    {
        return 1;
    }

//     HostMachineServer server2;
//     if (!server2.listen(QHostAddress::Any, c_uDataPort)) // ���ݶ˿�
//     {
//         return 1;
//     }
    
    QPushButton quitButton("Quit");
    quitButton.setWindowTitle("Host Machine Service");

    QObject::connect(&quitButton, SIGNAL(clicked()), &a, SLOT(quit()));
    quitButton.show();

    return a.exec();
}
