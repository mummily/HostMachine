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

static const char *c_sDlgIPSetting = "DlgIPSetting";
static const char *c_sIPSetting = QT_TRANSLATE_NOOP("DlgIPSetting", "IP����");
static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgIPSetting", "ȷ��");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgIPSetting", "ȡ��");

DlgIPSetting::DlgIPSetting(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(qApp->translate(c_sDlgIPSetting, c_sIPSetting));
    setFixedSize(376, 160);

    QLabel* label = new QLabel(qApp->translate(c_sDlgIPSetting, c_sIPSetting), this);
    m_pIPAddr = new IPAddrLineEdit(this);
    m_pIPAddr->settext("127.0.0.1");

    label->setGeometry(50, 50, 50, 20);
    m_pIPAddr->setGeometry(100, 50, 200, 20);

    QPushButton* btnOk = new QPushButton(qApp->translate(c_sDlgIPSetting, c_sConfirm), this);
    QPushButton* btnCancel = new QPushButton(qApp->translate(c_sDlgIPSetting, c_sCancel), this);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnOk);
    hLayout->addWidget(btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addStretch();
    vLayout->addLayout(hLayout);

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
