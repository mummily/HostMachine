#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

class HostMachine : public QMainWindow
{
    Q_OBJECT

public:
    HostMachine(QWidget *parent = 0);
    ~HostMachine();

private:
    void initUI();
    void initLayout();
    void initConnect();
};

#endif // HOSTMACHINE_H
