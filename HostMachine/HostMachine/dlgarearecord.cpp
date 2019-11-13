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
#include <QGroupBox>

static const char *c_sDlgAreaRecord = "DlgAreaRecord";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgAreaRecord", "记录");
static const char *c_sAreaChoice = QT_TRANSLATE_NOOP("DlgAreaRecord", "分区选择");
static const char *c_sFileName = QT_TRANSLATE_NOOP("DlgAreaRecord", "文件名");
static const char *c_sArea1 = QT_TRANSLATE_NOOP("DlgAreaRecord", "原始数据分区");
static const char *c_sArea2 = QT_TRANSLATE_NOOP("DlgAreaRecord", "雷达结果分区");
static const char *c_sArea3 = QT_TRANSLATE_NOOP("DlgAreaRecord", "光电图片分区");
static const char *c_sArea4 = QT_TRANSLATE_NOOP("DlgAreaRecord", "光电视频分区");
static const char *c_sArea5 = QT_TRANSLATE_NOOP("DlgAreaRecord", "混合数据分区");
static const char *c_sTip1 = QT_TRANSLATE_NOOP("DlgAreaRecord", "请选择记录分区！");
static const char *c_sTip2 = QT_TRANSLATE_NOOP("DlgAreaRecord", "请输入文件名！");
static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgAreaRecord", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgAreaRecord", "取消");

DlgAreaRecord::DlgAreaRecord(quint32 areano, QWidget *parent)
    : QDialog(parent), m_areno(areano)
{
    initUI();
    initConnect();
    initData();
}

DlgAreaRecord::~DlgAreaRecord()
{

}

void DlgAreaRecord::initUI()
{
    setWindowTitle(qApp->translate(c_sDlgAreaRecord, c_sTitle));
    setFixedSize(376, 200);

    QGroupBox* groupBox = new QGroupBox(this);
    groupBox->setTitle(qApp->translate(c_sDlgAreaRecord, c_sAreaChoice));

    m_checkBox1 = new QCheckBox(this);
    m_checkBox1->setText(qApp->translate(c_sDlgAreaRecord, c_sArea1));
    m_checkBox2 = new QCheckBox(this);
    m_checkBox2->setText(qApp->translate(c_sDlgAreaRecord, c_sArea2));
    m_checkBox3 = new QCheckBox(this);
    m_checkBox3->setText(qApp->translate(c_sDlgAreaRecord, c_sArea3));
    m_checkBox4 = new QCheckBox(this);
    m_checkBox4->setText(qApp->translate(c_sDlgAreaRecord, c_sArea4));
    m_checkBox5 = new QCheckBox(this);
    m_checkBox5->setText(qApp->translate(c_sDlgAreaRecord, c_sArea5));

    QGridLayout* areaLayout = new QGridLayout();
    areaLayout->addWidget(m_checkBox1, 0, 0);
    areaLayout->addWidget(m_checkBox2, 0, 1);
    areaLayout->addWidget(m_checkBox3, 1, 0);
    areaLayout->addWidget(m_checkBox4, 1, 1);
    areaLayout->addWidget(m_checkBox5, 2, 0);
    groupBox->setLayout(areaLayout);

    QLabel* lable2 = new QLabel(qApp->translate(c_sDlgAreaRecord, c_sFileName), this);
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QLabel* lable3 = new QLabel(".dat", this);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(lable2);
    hLayout1->addWidget(m_lineEdit);
    hLayout1->addWidget(lable3);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgAreaRecord, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgAreaRecord, c_sCancel), this);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();
    hLayout2->addWidget(m_btnOk);
    hLayout2->addWidget(m_btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addWidget(groupBox);
    vLayout->addLayout(hLayout1);
    vLayout->addStretch();
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);
}

void DlgAreaRecord::initConnect()
{
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgAreaRecord::slotOk()
{
    if (m_checkBox1->isChecked())
        lstArea.push_back(0);
    if (m_checkBox2->isChecked())
        lstArea.push_back(1);
    if (m_checkBox3->isChecked())
        lstArea.push_back(2);
    if (m_checkBox4->isChecked())
        lstArea.push_back(3);
    if (m_checkBox5->isChecked())
        lstArea.push_back(4);
    if (lstArea.size() < 1)
    {
        QMessageBox::information(this, windowTitle(), qApp->translate(c_sDlgAreaRecord, c_sTip1));
        return;
    }

    if (m_lineEdit->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, windowTitle(), qApp->translate(c_sDlgAreaRecord, c_sTip2));
        return;
    }

    filename = m_lineEdit->text() + ".dat";

    accept();
}

void DlgAreaRecord::initData()
{
    switch (m_areno)
    {
    case 0:
        m_checkBox1->setChecked(true);
        break;
    case 1:
        m_checkBox2->setChecked(true);
        break;
    case 2:
        m_checkBox3->setChecked(true);
        break;
    case 3:
        m_checkBox4->setChecked(true);
        break;
    case 4:
        m_checkBox5->setChecked(true);
        break;
    }
}
