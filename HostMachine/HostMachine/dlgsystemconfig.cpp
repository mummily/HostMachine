#include "dlgsystemconfig.h"
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include "constdef.h"

DlgSystemConfig::DlgSystemConfig(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    initConnect();
}

DlgSystemConfig::~DlgSystemConfig()
{

}

void DlgSystemConfig::initUI()
{
    setWindowTitle(qApp->translate(c_sHostMachine, c_sSystemConfig));
    setFixedSize(376, 200);

    QLabel* lable1 = new QLabel(qApp->translate(c_sHostMachine, c_sProperty1_7), this);
    QLabel* lable2 = new QLabel(qApp->translate(c_sHostMachine, c_sProperty1_8), this);

    m_comboBox1 = new QComboBox(this);
    m_comboBox1->addItems(QStringList() << "0" << "1");
    m_comboBox2 = new QComboBox(this);
    m_comboBox2->addItems(QStringList() << "1.25G" << "2G" << "2.5G" << "3.125G" << "5G" << "6.25G");

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_comboBox1, 0, 1);
    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_comboBox2, 1, 1);

    m_btnOk = new QPushButton(qApp->translate(c_sHostMachine, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sHostMachine, c_sCancel), this);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(m_btnOk);
    hLayout->addWidget(m_btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);

    setLayout(vLayout);
}

void DlgSystemConfig::initConnect()
{
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgSystemConfig::slotOk()
{
    choice = m_comboBox1->currentIndex();
    bandwidth = m_comboBox2->currentIndex();

    accept();
}
