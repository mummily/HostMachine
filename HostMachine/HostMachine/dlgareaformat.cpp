#include "dlgareaformat.h"
#include <QLabel>
#include <QApplication>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>

static const char *c_sDlgAreaFormat = "DlgAreaFormat";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgAreaFormat", "格式化");
static const char *c_sArea0 = QT_TRANSLATE_NOOP("DlgAreaFormat", "原始数据分区");
static const char *c_sArea1 = QT_TRANSLATE_NOOP("DlgAreaFormat", "雷达结果分区");
static const char *c_sArea2 = QT_TRANSLATE_NOOP("DlgAreaFormat", "光电图片分区");
static const char *c_sArea3 = QT_TRANSLATE_NOOP("DlgAreaFormat", "光电视频分区");
static const char *c_sArea4 = QT_TRANSLATE_NOOP("DlgAreaFormat", "混合数据分区");

static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgAreaFormat", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgAreaFormat", "取消");

DlgAreaFormat::DlgAreaFormat(int nSize1, int nSize2, int nSize3, int nSize4, int nSize5, QWidget *parent)
    : QDialog(parent), m_nSize1(nSize1), m_nSize2(nSize2), m_nSize3(nSize3), m_nSize4(nSize4), m_nSize5(nSize5)
{
    initUI();
    initConnect();
    initData();
}

DlgAreaFormat::~DlgAreaFormat()
{

}

void DlgAreaFormat::initUI()
{
    setWindowTitle(qApp->translate(c_sDlgAreaFormat, c_sTitle));
    setFixedSize(376, 200);

    QLabel* lable1 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea0) + "(1~200)", this);
    QLabel* lable2 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea1) + "(1~200)", this);
    QLabel* lable3 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea2) + "(1~200)", this);
    QLabel* lable4 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea3) + "(1~200)", this);
    QLabel* lable5 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea4) + "(1~200)", this);

    m_spinbox1 = new QSpinBox(this);
    m_spinbox1->setSuffix(" LBA");
    m_spinbox1->setMinimum(1);
    m_spinbox1->setMaximum(200);
    m_spinbox1->setSingleStep(1);

    m_spinbox2 = new QSpinBox(this);
    m_spinbox2->setSuffix(" LBA");
    m_spinbox2->setMinimum(1);
    m_spinbox2->setMaximum(200);
    m_spinbox2->setSingleStep(1);

    m_spinbox3 = new QSpinBox(this);
    m_spinbox3->setSuffix(" LBA");
    m_spinbox3->setMinimum(1);
    m_spinbox3->setMaximum(200);
    m_spinbox3->setSingleStep(1);

    m_spinbox4 = new QSpinBox(this);
    m_spinbox4->setSuffix(" LBA");
    m_spinbox4->setMinimum(1);
    m_spinbox4->setMaximum(200);
    m_spinbox4->setSingleStep(1);

    m_spinbox5 = new QSpinBox(this);
    m_spinbox5->setSuffix(" LBA");
    m_spinbox5->setMinimum(1);
    m_spinbox5->setMaximum(200);
    m_spinbox5->setSingleStep(1);

    m_slider1 = new QSlider(this);
    m_slider1->setOrientation(Qt::Horizontal);
    m_slider1->setMinimum(m_spinbox1->minimum());
    m_slider1->setMaximum(m_spinbox1->maximum());

    m_slider2 = new QSlider(this);
    m_slider2->setOrientation(Qt::Horizontal);
    m_slider2->setMinimum(m_spinbox2->minimum());
    m_slider2->setMaximum(m_spinbox2->maximum());

    m_slider3 = new QSlider(this);
    m_slider3->setOrientation(Qt::Horizontal);
    m_slider3->setMinimum(m_spinbox3->minimum());
    m_slider3->setMaximum(m_spinbox3->maximum());

    m_slider4 = new QSlider(this);
    m_slider4->setOrientation(Qt::Horizontal);
    m_slider4->setMinimum(m_spinbox4->minimum());
    m_slider4->setMaximum(m_spinbox4->maximum());

    m_slider5 = new QSlider(this);
    m_slider5->setOrientation(Qt::Horizontal);
    m_slider5->setMinimum(m_spinbox5->minimum());
    m_slider5->setMaximum(m_spinbox5->maximum());

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_spinbox1, 0, 1);
    gridLayout->addWidget(m_slider1, 0, 2);

    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_spinbox2, 1, 1);
    gridLayout->addWidget(m_slider2, 1, 2);

    gridLayout->addWidget(lable3, 2, 0);
    gridLayout->addWidget(m_spinbox3, 2, 1);
    gridLayout->addWidget(m_slider3, 2, 2);

    gridLayout->addWidget(lable4, 3, 0);
    gridLayout->addWidget(m_spinbox4, 3, 1);
    gridLayout->addWidget(m_slider4, 3, 2);

    gridLayout->addWidget(lable5, 4, 0);
    gridLayout->addWidget(m_spinbox5, 4, 1);
    gridLayout->addWidget(m_slider5, 4, 2);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgAreaFormat, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgAreaFormat, c_sCancel), this);

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

void DlgAreaFormat::initConnect()
{
    connect(m_spinbox1, SIGNAL(valueChanged(int)), m_slider1, SLOT(setValue(int)));
    connect(m_slider1, SIGNAL(valueChanged(int)), m_spinbox1, SLOT(setValue(int)));

    connect(m_spinbox2, SIGNAL(valueChanged(int)), m_slider2, SLOT(setValue(int)));
    connect(m_slider2, SIGNAL(valueChanged(int)), m_spinbox2, SLOT(setValue(int)));

    connect(m_spinbox3, SIGNAL(valueChanged(int)), m_slider3, SLOT(setValue(int)));
    connect(m_slider3, SIGNAL(valueChanged(int)), m_spinbox3, SLOT(setValue(int)));

    connect(m_spinbox4, SIGNAL(valueChanged(int)), m_slider4, SLOT(setValue(int)));
    connect(m_slider4, SIGNAL(valueChanged(int)), m_spinbox4, SLOT(setValue(int)));

    connect(m_spinbox5, SIGNAL(valueChanged(int)), m_slider5, SLOT(setValue(int)));
    connect(m_slider5, SIGNAL(valueChanged(int)), m_spinbox5, SLOT(setValue(int)));

    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgAreaFormat::slotOk()
{
    m_nSize1 = m_spinbox1->value();
    m_nSize2 = m_spinbox2->value();
    m_nSize3 = m_spinbox3->value();
    m_nSize4 = m_spinbox4->value();
    m_nSize5 = m_spinbox5->value();

    accept();
}

void DlgAreaFormat::initData()
{
    m_spinbox1->setValue(m_nSize1);
    m_spinbox2->setValue(m_nSize2);
    m_spinbox3->setValue(m_nSize3);
    m_spinbox4->setValue(m_nSize4);
    m_spinbox5->setValue(m_nSize5);
}
