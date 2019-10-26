#ifndef DLGIPSETTING_H
#define DLGIPSETTING_H

#include <QDialog>

class IPAddrLineEdit;
class DlgIPSetting : public QDialog
{
    Q_OBJECT

public:
    DlgIPSetting(QWidget *parent = 0);
    ~DlgIPSetting();

    QString getIPAddr();

private:
    IPAddrLineEdit *m_pIPAddr;
};

#endif // DLGIPSETTING_H
