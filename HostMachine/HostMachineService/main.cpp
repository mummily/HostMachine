#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QDebug>
#include "hostmachineserver.h"
#include "QHostAddress"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() <<sizeof(quint32);
    qDebug() <<sizeof(quint64);

    HostMachineServer server;
    if (!server.listen(QHostAddress::Any, 6178))
    {
        return 1;
    }
    
    QPushButton quitButton("Quit");
    quitButton.setWindowTitle("Host Machine Service");

    QObject::connect(&quitButton, SIGNAL(clicked()), &a, SLOT(quit()));
    quitButton.show();

    return a.exec();
}
