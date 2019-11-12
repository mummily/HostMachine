#include "dlgarearecord.h"
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include "constdef.h"

DlgAreaRecord::DlgAreaRecord(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    initConnect();
}

DlgAreaRecord::~DlgAreaRecord()
{

}

void DlgAreaRecord::initUI()
{
    setWindowTitle(qApp->translate(c_sHostMachine, c_sRecord));
    setFixedSize(376, 200);

    QLabel* lable1 = new QLabel(qApp->translate(c_sHostMachine, c_sAreaNumber), this);
    QLabel* lable2 = new QLabel(qApp->translate(c_sHostMachine, c_sFileName), this);

    m_checkBox1 = new QCheckBox(this);
    m_checkBox1->setText(qApp->translate(c_sHostMachine, c_sPropertyGroup1_1));
    m_checkBox2 = new QCheckBox(this);
    m_checkBox2->setText(qApp->translate(c_sHostMachine, c_sPropertyGroup1_2));
    m_checkBox3 = new QCheckBox(this);
    m_checkBox3->setText(qApp->translate(c_sHostMachine, c_sPropertyGroup1_3));
    m_checkBox4 = new QCheckBox(this);
    m_checkBox4->setText(qApp->translate(c_sHostMachine, c_sPropertyGroup1_4));
    m_checkBox5 = new QCheckBox(this);
    m_checkBox5->setText(qApp->translate(c_sHostMachine, c_sPropertyGroup1_5));

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QLabel* lable3 = new QLabel(".dat", this);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_checkBox1, 0, 1);
    gridLayout->addWidget(m_checkBox2, 1, 1);
    gridLayout->addWidget(m_checkBox3, 2, 1);
    gridLayout->addWidget(m_checkBox4, 3, 1);
    gridLayout->addWidget(m_checkBox5, 4, 1);
    gridLayout->addWidget(lable2, 5, 0);
    gridLayout->addWidget(m_lineEdit, 5, 1);
    gridLayout->addWidget(lable3, 5, 2);

    m_btnOk = new QPushButton(qApp->translate(c_sHostMachine, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sHostMachine, c_sCancel), this);

    QHBoxLayout* hLayout3 = new QHBoxLayout();
    hLayout3->addStretch();
    hLayout3->addWidget(m_btnOk);
    hLayout3->addWidget(m_btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addLayout(hLayout3);

    setLayout(vLayout);
}

void DlgAreaRecord::initConnect()
{
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgAreaRecord::slotOk()
{
    if (m_lineEdit->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, windowTitle(), qApp->translate(c_sHostMachine, c_sFileNameTip));
        return;
    }

    if (m_checkBox1->isChecked())
    {
        lstArea.push_back(0);
    }
    if (m_checkBox2->isChecked())
    {
        lstArea.push_back(1);
    }
    if (m_checkBox3->isChecked())
    {
        lstArea.push_back(2);
    }
    if (m_checkBox4->isChecked())
    {
        lstArea.push_back(3);
    }
    if (m_checkBox5->isChecked())
    {
        lstArea.push_back(4);
    }

    filename = m_lineEdit->text() + ".dat";

    accept();
}
