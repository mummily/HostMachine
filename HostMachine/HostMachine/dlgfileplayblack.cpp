#include "dlgfileplayblack.h"
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QPushButton>

// 回放请求
static const char *c_sDlgFilePlayblack = "DlgFilePlayblack";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgFilePlayblack", "回放参数");
static const char *c_sType = QT_TRANSLATE_NOOP("DlgFilePlayblack", "回放类型");
static const char *c_sType1 = QT_TRANSLATE_NOOP("DlgFilePlayblack", "主动回放");
static const char *c_sType2 = QT_TRANSLATE_NOOP("DlgFilePlayblack", "被动回放");
static const char *c_sPRFTime = QT_TRANSLATE_NOOP("DlgFilePlayblack", "PRF时间");
static const char *c_sDataNum = QT_TRANSLATE_NOOP("DlgFilePlayblack", "数据个数");
static const char *c_sPRF = QT_TRANSLATE_NOOP("DlgFilePlayblack", "PRF数据帧头");
static const char *c_sCPI = QT_TRANSLATE_NOOP("DlgFilePlayblack", "CPI数据帧头");

static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgFilePlayblack", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgFilePlayblack", "取消");

DlgFilePlayblack::DlgFilePlayblack(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    initConnect();
}

DlgFilePlayblack::~DlgFilePlayblack()
{

}

void DlgFilePlayblack::initUI()
{
    setWindowTitle(qApp->translate(c_sDlgFilePlayblack, c_sTitle));
    setFixedSize(376, 200);

    QLabel* lable1 = new QLabel(qApp->translate(c_sDlgFilePlayblack, c_sType), this);
    QLabel* lable2 = new QLabel(qApp->translate(c_sDlgFilePlayblack, c_sPRFTime), this);
    QLabel* lable3 = new QLabel(qApp->translate(c_sDlgFilePlayblack, c_sDataNum), this);
    QLabel* lable4 = new QLabel(qApp->translate(c_sDlgFilePlayblack, c_sPRF), this);
    QLabel* lable5 = new QLabel(qApp->translate(c_sDlgFilePlayblack, c_sCPI), this);

    m_comboBox = new QComboBox(this);
    m_comboBox->addItems(QStringList() << qApp->translate(c_sDlgFilePlayblack, c_sType1)
        << qApp->translate(c_sDlgFilePlayblack, c_sType2));

    m_sbPRFTime = new QSpinBox(this);
    m_sbPRFTime->setSuffix(" us");
    m_sbPRFTime->setMinimum(1);
    m_sbPRFTime->setMaximum(65536);
    m_sbPRFTime->setSingleStep(1);
    QLabel* lbPRFTime = new QLabel("(1~65536)", this);

    m_sbDataNum = new QSpinBox(this);
    m_sbDataNum->setMinimum(1);
    m_sbDataNum->setMaximum(100);
    m_sbDataNum->setSingleStep(1);

    m_sbPRF = new QSpinBox(this);
    m_sbPRF->setMinimum(1);
    m_sbPRF->setMaximum(100);
    m_sbPRF->setSingleStep(1);

    m_sbCPI = new QSpinBox(this);
    m_sbCPI->setMinimum(1);
    m_sbCPI->setMaximum(100);
    m_sbCPI->setSingleStep(1);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_comboBox, 0, 1);
    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_sbPRFTime, 1, 1);
    gridLayout->addWidget(lbPRFTime, 1, 2);
    gridLayout->addWidget(lable3, 2, 0);
    gridLayout->addWidget(m_sbDataNum, 2, 1);
    gridLayout->addWidget(lable4, 3, 0);
    gridLayout->addWidget(m_sbPRF, 3, 1);
    gridLayout->addWidget(lable5, 4, 0);
    gridLayout->addWidget(m_sbCPI, 4, 1);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgFilePlayblack, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgFilePlayblack, c_sCancel), this);

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

void DlgFilePlayblack::initConnect()
{
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgFilePlayblack::slotOk()
{
    type = m_comboBox->currentIndex() + 1;
    prftime = m_sbPRFTime->value();
    datanum = m_sbDataNum->value();
    prf = m_sbPRF->value();
    cpi = m_sbCPI->value();

    accept();
}
