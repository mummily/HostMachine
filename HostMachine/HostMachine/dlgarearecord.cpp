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

    m_comboBox = new QComboBox(this);
    m_comboBox->addItems(QStringList() << qApp->translate(c_sHostMachine, c_sPropertyGroup1_1)
        << qApp->translate(c_sHostMachine, c_sPropertyGroup1_2)
        << qApp->translate(c_sHostMachine, c_sPropertyGroup1_3)
        << qApp->translate(c_sHostMachine, c_sPropertyGroup1_4)
        << qApp->translate(c_sHostMachine, c_sPropertyGroup1_5));

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QLabel* lable3 = new QLabel(".dat", this);

    // QHBoxLayout* hLayout1 = new QHBoxLayout();
    // hLayout1->addWidget(lable1);
    // hLayout1->addWidget(m_comboBox);

    // QHBoxLayout* hLayout2 = new QHBoxLayout();
    // hLayout2->addWidget(lable2);
    // hLayout2->addWidget(m_lineEdit);
    // hLayout2->addWidget(lable3);
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_comboBox, 0, 1);
    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_lineEdit, 1, 1);
    gridLayout->addWidget(lable3, 1, 2);

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

    area = m_comboBox->currentIndex();
    filename = m_lineEdit->text() + ".dat";

    accept();
}
