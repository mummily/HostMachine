#include "dlgfileexport.h"
#include <QDoubleSpinBox>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

static const char *c_sDlgFileExport = "DlgFileExport";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgFileExport", "分段导出配置框");
static const char *c_sLabel1 = QT_TRANSLATE_NOOP("DlgFileExport", "导出文件偏移");
static const char *c_sLabel2 = QT_TRANSLATE_NOOP("DlgFileExport", "导出文件大小");
static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgFileExport", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgFileExport", "取消");

DlgFileExport::DlgFileExport(float filesize, QWidget *parent)
    : QDialog(parent), m_filesize(filesize)
{
    initUI();
    initConnect();
}

DlgFileExport::~DlgFileExport()
{

}

void DlgFileExport::initUI()
{
    setWindowTitle(qApp->translate(c_sDlgFileExport, c_sTitle));
    setFixedSize(376, 200);

    QLabel *lable1 = new QLabel(qApp->translate(c_sDlgFileExport, c_sLabel1), this);
    QLabel *lable2 = new QLabel(qApp->translate(c_sDlgFileExport, c_sLabel2), this);

    m_spinBox1 = new QDoubleSpinBox(this);
    m_spinBox1->setSuffix(" MB");
    m_spinBox1->setDecimals(3);
    m_spinBox1->setSingleStep(0.001);
    m_spinBox1->setMinimum(0.0);
    m_spinBox1->setMaximum(m_filesize);
    m_spinBox1->setValue(0);

    m_spinBox2 = new QDoubleSpinBox(this);
    m_spinBox2->setSuffix(" MB");
    m_spinBox2->setDecimals(3);
    m_spinBox2->setSingleStep(0.001);
    m_spinBox2->setMinimum(0.0);
    m_spinBox2->setMaximum(m_filesize - m_spinBox1->value());
    m_spinBox2->setValue(m_filesize);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgFileExport, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgFileExport, c_sCancel), this);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_spinBox1, 0, 1);
    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_spinBox2, 1, 1);

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

void DlgFileExport::initConnect()
{
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));

    connect(m_spinBox1, SIGNAL(valueChanged(double)), this, SLOT(slotSpinBoxValueChanged(double)));
}

void DlgFileExport::slotOk()
{
    startpos = m_spinBox1->value();
    exportsize = m_spinBox2->value();

    accept();
}

void DlgFileExport::slotSpinBoxValueChanged(double value)
{
    m_spinBox2->setMaximum(m_filesize - value);
}
