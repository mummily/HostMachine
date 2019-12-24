#include "dlgareaformat.h"
#include <QLabel>
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>

static const char *c_sDlgAreaFormat = "DlgAreaFormat";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgAreaFormat", "格式化");
static const char *c_sArea0 = QT_TRANSLATE_NOOP("DlgAreaFormat", "原始数据分区");
static const char *c_sArea1 = QT_TRANSLATE_NOOP("DlgAreaFormat", "雷达结果分区");
static const char *c_sArea2 = QT_TRANSLATE_NOOP("DlgAreaFormat", "光电图片分区");
static const char *c_sArea3 = QT_TRANSLATE_NOOP("DlgAreaFormat", "光电视频分区");
static const char *c_sArea4 = QT_TRANSLATE_NOOP("DlgAreaFormat", "混合数据分区");

static const char *c_sUseInfo = QT_TRANSLATE_NOOP("DlgAreaFormat", "已分配大小（LBA）/总大小（LBA）：");

static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgAreaFormat", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgAreaFormat", "取消");

DlgAreaFormat::DlgAreaFormat(qint64 nTotalSize, qint64 nSize1, qint64 nSize2, qint64 nSize3, qint64 nSize4, qint64 nSize5, QWidget *parent)
    : QDialog(parent), m_nTotalSize(nTotalSize), m_nSize1(nSize1), m_nSize2(nSize2), m_nSize3(nSize3), m_nSize4(nSize4), m_nSize5(nSize5)
{
    initUI();
    initConnect();
    initData();

    m_pRadio1->setChecked(true);
}

DlgAreaFormat::~DlgAreaFormat()
{

}

void DlgAreaFormat::initUI()
{
    setWindowTitle(qApp->translate(c_sDlgAreaFormat, c_sTitle));
    setFixedSize(376, 200);

    m_pRadio1 = new QRadioButton(qApp->translate(c_sDlgAreaFormat, c_sArea0), this);
    m_pRadio2 = new QRadioButton(qApp->translate(c_sDlgAreaFormat, c_sArea1), this);
    m_pRadio3 = new QRadioButton(qApp->translate(c_sDlgAreaFormat, c_sArea2), this);
    m_pRadio4 = new QRadioButton(qApp->translate(c_sDlgAreaFormat, c_sArea3), this);
    m_pRadio5 = new QRadioButton(qApp->translate(c_sDlgAreaFormat, c_sArea4), this);

    m_spinbox1 = new QSpinBox(this);
    m_spinbox1->setSuffix("LBA");
    m_spinbox1->setMinimum(1);
    m_spinbox1->setMaximum(m_nTotalSize);
    m_spinbox1->setSingleStep(1);
    m_spinbox1->setReadOnly(true);

    m_spinbox2 = new QSpinBox(this);
    m_spinbox2->setSuffix("LBA");
    m_spinbox2->setMinimum(1);
    m_spinbox2->setMaximum(m_nTotalSize);
    m_spinbox2->setSingleStep(1);
    m_spinbox2->setReadOnly(true);

    m_spinbox3 = new QSpinBox(this);
    m_spinbox3->setSuffix("LBA");
    m_spinbox3->setMinimum(1);
    m_spinbox3->setMaximum(m_nTotalSize);
    m_spinbox3->setSingleStep(1);
    m_spinbox3->setReadOnly(true);

    m_spinbox4 = new QSpinBox(this);
    m_spinbox4->setSuffix("LBA");
    m_spinbox4->setMinimum(1);
    m_spinbox4->setMaximum(m_nTotalSize);
    m_spinbox4->setSingleStep(1);
    m_spinbox4->setReadOnly(true);

    m_spinbox5 = new QSpinBox(this);
    m_spinbox5->setSuffix("LBA");
    m_spinbox5->setMinimum(1);
    m_spinbox5->setMaximum(m_nTotalSize);
    m_spinbox5->setSingleStep(1);
    m_spinbox5->setReadOnly(true);

    m_slider1 = new QSlider(this);
    m_slider1->setOrientation(Qt::Horizontal);
    m_slider1->setMinimum(m_spinbox1->minimum());
    m_slider1->setMaximum(m_spinbox1->maximum());
    m_slider1->hide();

    m_slider2 = new QSlider(this);
    m_slider2->setOrientation(Qt::Horizontal);
    m_slider2->setMinimum(m_spinbox2->minimum());
    m_slider2->setMaximum(m_spinbox2->maximum());
    m_slider2->hide();

    m_slider3 = new QSlider(this);
    m_slider3->setOrientation(Qt::Horizontal);
    m_slider3->setMinimum(m_spinbox3->minimum());
    m_slider3->setMaximum(m_spinbox3->maximum());
    m_slider3->hide();

    m_slider4 = new QSlider(this);
    m_slider4->setOrientation(Qt::Horizontal);
    m_slider4->setMinimum(m_spinbox4->minimum());
    m_slider4->setMaximum(m_spinbox4->maximum());
    m_slider4->hide();

    m_slider5 = new QSlider(this);
    m_slider5->setOrientation(Qt::Horizontal);
    m_slider5->setMinimum(m_spinbox5->minimum());
    m_slider5->setMaximum(m_spinbox5->maximum());
    m_slider5->hide();

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(m_pRadio1, 0, 0);
    gridLayout->addWidget(m_spinbox1, 0, 1);
    gridLayout->addWidget(m_slider1, 0, 2);

    gridLayout->addWidget(m_pRadio2, 1, 0);
    gridLayout->addWidget(m_spinbox2, 1, 1);
    gridLayout->addWidget(m_slider2, 1, 2);

    gridLayout->addWidget(m_pRadio3, 2, 0);
    gridLayout->addWidget(m_spinbox3, 2, 1);
    gridLayout->addWidget(m_slider3, 2, 2);

    gridLayout->addWidget(m_pRadio4, 3, 0);
    gridLayout->addWidget(m_spinbox4, 3, 1);
    gridLayout->addWidget(m_slider4, 3, 2);

    gridLayout->addWidget(m_pRadio5, 4, 0);
    gridLayout->addWidget(m_spinbox5, 4, 1);
    gridLayout->addWidget(m_slider5, 4, 2);

    m_pLabel = new QLabel(this);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgAreaFormat, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgAreaFormat, c_sCancel), this);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(m_btnOk);
    hLayout->addWidget(m_btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addLayout(gridLayout);
    vLayout->addSpacing(10);
    vLayout->addWidget(m_pLabel);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);

    setLayout(vLayout);
}

void DlgAreaFormat::initConnect()
{
    connect(m_spinbox1, SIGNAL(valueChanged(int)), m_slider1, SLOT(setValue(int)));
    connect(m_slider1, SIGNAL(valueChanged(int)), m_spinbox1, SLOT(setValue(int)));
    connect(m_spinbox1, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));
    connect(m_slider1, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    connect(m_spinbox2, SIGNAL(valueChanged(int)), m_slider2, SLOT(setValue(int)));
    connect(m_slider2, SIGNAL(valueChanged(int)), m_spinbox2, SLOT(setValue(int)));
    connect(m_spinbox2, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));
    connect(m_slider2, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    connect(m_spinbox3, SIGNAL(valueChanged(int)), m_slider3, SLOT(setValue(int)));
    connect(m_slider3, SIGNAL(valueChanged(int)), m_spinbox3, SLOT(setValue(int)));
    connect(m_spinbox3, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));
    connect(m_slider3, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    connect(m_spinbox4, SIGNAL(valueChanged(int)), m_slider4, SLOT(setValue(int)));
    connect(m_slider4, SIGNAL(valueChanged(int)), m_spinbox4, SLOT(setValue(int)));
    connect(m_spinbox4, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));
    connect(m_slider4, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    connect(m_spinbox5, SIGNAL(valueChanged(int)), m_slider5, SLOT(setValue(int)));
    connect(m_slider5, SIGNAL(valueChanged(int)), m_spinbox5, SLOT(setValue(int)));
    connect(m_spinbox5, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));
    connect(m_slider5, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    connect(m_pRadio1, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(m_pRadio2, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(m_pRadio3, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(m_pRadio4, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(m_pRadio5, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    
    connect(m_pRadio1, SIGNAL(toggled(bool)), m_slider1, SLOT(setVisible(bool)));
    connect(m_pRadio2, SIGNAL(toggled(bool)), m_slider2, SLOT(setVisible(bool)));
    connect(m_pRadio3, SIGNAL(toggled(bool)), m_slider3, SLOT(setVisible(bool)));
    connect(m_pRadio4, SIGNAL(toggled(bool)), m_slider4, SLOT(setVisible(bool)));
    connect(m_pRadio5, SIGNAL(toggled(bool)), m_slider5, SLOT(setVisible(bool)));

    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgAreaFormat::initData()
{
    m_spinbox1->setValue(m_nSize1);
    m_spinbox2->setValue(m_nSize2);
    m_spinbox3->setValue(m_nSize3);
    m_spinbox4->setValue(m_nSize4);
    m_spinbox5->setValue(m_nSize5);
}

void DlgAreaFormat::slotValueChanged(int value)
{
    if (sender() == m_spinbox1 || sender() == m_slider1)
        m_nSize1 = m_spinbox1->value();
    else if (sender() == m_spinbox2 || sender() == m_slider2)
        m_nSize2 = m_spinbox2->value();
    else if (sender() == m_spinbox3 || sender() == m_slider3)
        m_nSize3 = m_spinbox3->value();
    else if (sender() == m_spinbox4 || sender() == m_slider4)
        m_nSize4 = m_spinbox4->value();
    else
        m_nSize5 = m_spinbox5->value();
    
    if (m_nSize1 + m_nSize2 + m_nSize3 + m_nSize4 + m_nSize5 == m_nTotalSize)
        m_btnOk->setEnabled(true);
    else
        m_btnOk->setEnabled(false);
    
    QString sInfo = QString("%1%2/%3").arg(qApp->translate(c_sDlgAreaFormat, c_sUseInfo)).arg(m_nSize1+m_nSize2+m_nSize3+m_nSize4+m_nSize5).arg(m_nTotalSize);
    m_pLabel->setText(sInfo);
}

void DlgAreaFormat::slotRadioToggled(bool checked)
{
    if (sender() == m_pRadio1)
    {
        m_slider1->setMaximum(m_nTotalSize - m_nSize2 - m_nSize3 - m_nSize4 - m_nSize5);
        m_slider1->setValue(m_nSize1);
        m_spinbox1->setReadOnly(!checked);
    }
    else if (sender() == m_pRadio2)
    {
        m_slider2->setMaximum(m_nTotalSize - m_nSize1 - m_nSize3 - m_nSize4 - m_nSize5);
        m_slider2->setValue(m_nSize2);
        m_spinbox2->setReadOnly(!checked);
    }
    else if (sender() == m_pRadio3)
    {
        m_slider3->setMaximum(m_nTotalSize - m_nSize1 - m_nSize2 - m_nSize4 - m_nSize5);
        m_slider3->setValue(m_nSize3);
        m_spinbox3->setReadOnly(!checked);
    }
    else if (sender() == m_pRadio4)
    {
        m_slider4->setMaximum(m_nTotalSize - m_nSize1 - m_nSize2 - m_nSize3 - m_nSize5);
        m_slider4->setValue(m_nSize4);
        m_spinbox4->setReadOnly(!checked);
    }
    else
    {
        m_slider5->setMaximum(m_nTotalSize - m_nSize1 - m_nSize2 - m_nSize3 - m_nSize4);
        m_slider5->setValue(m_nSize5);
        m_spinbox5->setReadOnly(!checked);
    }
}
