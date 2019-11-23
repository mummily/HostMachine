#include "dlgsystemconfig.h"
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>

static const char *c_sDlgSystemConfig = "DlgSystemConfig";
static const char *c_sSystemConfig = QT_TRANSLATE_NOOP("DlgSystemConfig", "系统配置");
static const char *c_sChannelChoice = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道选择");
static const char *c_sBandWidthChoice = QT_TRANSLATE_NOOP("DlgSystemConfig", "带宽选择");
static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgSystemConfig", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgSystemConfig", "取消");

static const char *c_sChannel1 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道1");
static const char *c_sChannel2 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道2");
static const char *c_sChannel3 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道3");
static const char *c_sChannel4 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道4");
static const char *c_sChannel5 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道5");
static const char *c_sChannel6 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道6");
static const char *c_sChannel7 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道7");
static const char *c_sChannel8 = QT_TRANSLATE_NOOP("DlgSystemConfig", "单通道8");
static const char *c_sChannel9 = QT_TRANSLATE_NOOP("DlgSystemConfig", "双通道(1&2)");
static const char *c_sChannel10 = QT_TRANSLATE_NOOP("DlgSystemConfig", "双通道(3&4)");
static const char *c_sChannel11 = QT_TRANSLATE_NOOP("DlgSystemConfig", "双通道(5&6)");
static const char *c_sChannel12 = QT_TRANSLATE_NOOP("DlgSystemConfig", "双通道(7&8)");
static const char *c_sChannel13 = QT_TRANSLATE_NOOP("DlgSystemConfig", "四通道(1&2&3&4)");
static const char *c_sChannel14 = QT_TRANSLATE_NOOP("DlgSystemConfig", "四通道(5&6&7&8)");
static const char *c_sChannel15 = QT_TRANSLATE_NOOP("DlgSystemConfig", "八通道");

static const char *c_sChannel101 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道1");
static const char *c_sChannel102 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道2");
static const char *c_sChannel103 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道3");
static const char *c_sChannel104 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道4");
static const char *c_sChannel105 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道5");
static const char *c_sChannel106 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道6");
static const char *c_sChannel107 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道7");
static const char *c_sChannel108 = QT_TRANSLATE_NOOP("DlgSystemConfig", "通道8");

DlgSystemConfig::DlgSystemConfig(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    initConnect();
    initData();
}

DlgSystemConfig::~DlgSystemConfig()
{

}

void DlgSystemConfig::initUI()
{
    setWindowTitle(qApp->translate(c_sDlgSystemConfig, c_sSystemConfig));
    setFixedSize(376, 200);

    QLabel* lable1 = new QLabel(qApp->translate(c_sDlgSystemConfig, c_sChannelChoice), this);
    QLabel* lable2 = new QLabel(qApp->translate(c_sDlgSystemConfig, c_sBandWidthChoice), this);

    m_comboBox1 = new QComboBox(this);
    m_comboBox1->addItems(QStringList() << qApp->translate(c_sDlgSystemConfig, c_sChannel1)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel2)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel3)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel4)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel5)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel6)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel7)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel8)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel9)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel10)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel11)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel12)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel13)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel14)
        << qApp->translate(c_sDlgSystemConfig, c_sChannel15));
    m_comboBox1->setMaxVisibleItems(m_comboBox1->count());
    m_comboBox1->setCurrentIndex(-1);

    m_comboBox2 = new QComboBox(this);
    m_comboBox2->addItems(QStringList() << "1.25G" << "2G" << "2.5G" << "3.125G" << "5G" << "6.25G");
    m_comboBox2->setCurrentIndex(-1);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_comboBox1, 0, 1);
    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_comboBox2, 1, 1);

    QGroupBox* groupBox = new QGroupBox(this);
    groupBox->setTitle(qApp->translate(c_sDlgSystemConfig, c_sChannelChoice));
    m_checkBox1 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel101));
    m_checkBox1->setEnabled(false);
    m_checkBox2 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel102));
    m_checkBox2->setEnabled(false);
    m_checkBox3 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel103));
    m_checkBox3->setEnabled(false);
    m_checkBox4 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel104));
    m_checkBox4->setEnabled(false);
    m_checkBox5 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel105));
    m_checkBox5->setEnabled(false);
    m_checkBox6 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel106));
    m_checkBox6->setEnabled(false);
    m_checkBox7 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel107));
    m_checkBox7->setEnabled(false);
    m_checkBox8 = new QCheckBox(qApp->translate(c_sDlgSystemConfig, c_sChannel108));
    m_checkBox8->setEnabled(false);

    QGridLayout *channelLayout = new QGridLayout();
    channelLayout->addWidget(m_checkBox1, 0, 0);
    channelLayout->addWidget(m_checkBox2, 0, 1);
    channelLayout->addWidget(m_checkBox3, 1, 0);
    channelLayout->addWidget(m_checkBox4, 1, 1);
    channelLayout->addWidget(m_checkBox5, 2, 0);
    channelLayout->addWidget(m_checkBox6, 2, 1);
    channelLayout->addWidget(m_checkBox7, 3, 0);
    channelLayout->addWidget(m_checkBox8, 3, 1);
    groupBox->setLayout(channelLayout);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addLayout(gridLayout);
    hLayout1->addWidget(groupBox);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgSystemConfig, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgSystemConfig, c_sCancel), this);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();
    hLayout2->addWidget(m_btnOk);
    hLayout2->addWidget(m_btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addLayout(hLayout1);
    vLayout->addStretch();
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);
}

void DlgSystemConfig::initConnect()
{
    connect(m_comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChannelChanged(int)));
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgSystemConfig::slotOk()
{
    lstChannelChoice.clear();
    if (m_checkBox1->isChecked())
        lstChannelChoice.push_back(1);
    if (m_checkBox2->isChecked())
        lstChannelChoice.push_back(2);
    if (m_checkBox3->isChecked())
        lstChannelChoice.push_back(3);
    if (m_checkBox4->isChecked())
        lstChannelChoice.push_back(4);
    if (m_checkBox5->isChecked())
        lstChannelChoice.push_back(5);
    if (m_checkBox6->isChecked())
        lstChannelChoice.push_back(6);
    if (m_checkBox7->isChecked())
        lstChannelChoice.push_back(7);
    if (m_checkBox8->isChecked())
        lstChannelChoice.push_back(8);

    bandwidth = m_comboBox2->currentIndex();

    accept();
}

void DlgSystemConfig::slotChannelChanged(int index)
{
    m_checkBox1->setChecked(false);
    m_checkBox2->setChecked(false);
    m_checkBox3->setChecked(false);
    m_checkBox4->setChecked(false);
    m_checkBox5->setChecked(false);
    m_checkBox6->setChecked(false);
    m_checkBox7->setChecked(false);
    m_checkBox8->setChecked(false);
    switch (index)
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
    case 5:
        m_checkBox6->setChecked(true);
        break;
    case 6:
        m_checkBox7->setChecked(true);
        break;
    case 7:
        m_checkBox8->setChecked(true);
        break;
    case 8:
        m_checkBox1->setChecked(true);
        m_checkBox2->setChecked(true);
        break;
    case 9:
        m_checkBox3->setChecked(true);
        m_checkBox4->setChecked(true);
        break;
    case 10:
        m_checkBox5->setChecked(true);
        m_checkBox6->setChecked(true);
        break;
    case 11:
        m_checkBox7->setChecked(true);
        m_checkBox8->setChecked(true);
        break;
    case 12:
        m_checkBox1->setChecked(true);
        m_checkBox2->setChecked(true);
        m_checkBox3->setChecked(true);
        m_checkBox4->setChecked(true);
        break;
    case 13:
        m_checkBox5->setChecked(true);
        m_checkBox6->setChecked(true);
        m_checkBox7->setChecked(true);
        m_checkBox8->setChecked(true);
        break;
    case 14:
        m_checkBox1->setChecked(true);
        m_checkBox2->setChecked(true);
        m_checkBox3->setChecked(true);
        m_checkBox4->setChecked(true);
        m_checkBox5->setChecked(true);
        m_checkBox6->setChecked(true);
        m_checkBox7->setChecked(true);
        m_checkBox8->setChecked(true);
        break;
    }
}


void DlgSystemConfig::initData()
{
    m_comboBox1->setCurrentIndex(0);
    m_comboBox2->setCurrentIndex(0);
}