#include "dlgipsetting.h"
#include "constdef.h"
#include <QApplication>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QLabel>
#include <QRegExp>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "IPAddrLineEdit.h"

DlgIPSetting::DlgIPSetting(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(qApp->translate(c_sHostMachine, c_sIPSetting));
    setFixedSize(376, 160);

    // QLabel* label = new QLabel(qApp->translate(c_sHostMachine, c_sIPSetting), this);
    m_pIPAddr = new IPAddrLineEdit(this);
    m_pIPAddr->settext("127.0.0.1");
    m_pIPAddr->setFixedHeight(50);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addSpacing(100);
    // hLayout1->addWidget(label);
    hLayout1->addWidget(m_pIPAddr);

    QPushButton* btnOk = new QPushButton(qApp->translate(c_sHostMachine, c_sConfirm), this);
    QPushButton* btnCancel = new QPushButton(qApp->translate(c_sHostMachine, c_sCancel), this);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();
    hLayout2->addWidget(btnOk);
    hLayout2->addWidget(btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addSpacing(30);
    vLayout->addLayout(hLayout1);
    vLayout->addStretch();
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);

    connect(btnOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

DlgIPSetting::~DlgIPSetting()
{

}

QString DlgIPSetting::getIPAddr()
{
     return m_pIPAddr->text();
}
