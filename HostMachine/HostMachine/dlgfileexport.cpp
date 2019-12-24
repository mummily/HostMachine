#include "dlgfileexport.h"
#include <QDoubleSpinBox>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include "QFileDialog"
#include "QMessageBox"

static const char *c_sDlgFileExport = "DlgFileExport";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgFileExport", "分段导出配置框");
static const char *c_sLabel1 = QT_TRANSLATE_NOOP("DlgFileExport", "导出文件偏移");
static const char *c_sLabel2 = QT_TRANSLATE_NOOP("DlgFileExport", "导出文件大小");
static const char *c_sLabel3 = QT_TRANSLATE_NOOP("DlgFileExport", "导出文件路径");
static const char *c_sPathTip = QT_TRANSLATE_NOOP("DlgFileExport", "请选择导出文件路径！");
static const char *c_sPathTitle = QT_TRANSLATE_NOOP("DlgFileExport", "选择导出文件路径");
static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgFileExport", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgFileExport", "取消");

DlgFileExport::DlgFileExport(qint32 filesize, QWidget *parent)
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
    QLabel *lable3 = new QLabel(qApp->translate(c_sDlgFileExport, c_sLabel3), this);

    m_spinBox1 = new QDoubleSpinBox(this);
    m_spinBox1->setSuffix(" LBA");
    m_spinBox1->setDecimals(3);
    m_spinBox1->setSingleStep(0.001);
    m_spinBox1->setMinimum(0.0);
    m_spinBox1->setMaximum(m_filesize);
    m_spinBox1->setValue(0);

    m_spinBox2 = new QDoubleSpinBox(this);
    m_spinBox2->setSuffix(" LBA");
    m_spinBox2->setDecimals(3);
    m_spinBox2->setSingleStep(0.001);
    m_spinBox2->setMinimum(0.0);
    m_spinBox2->setMaximum(m_filesize - m_spinBox1->value());
    m_spinBox2->setValue(m_filesize);

    m_btnOk = new QPushButton(qApp->translate(c_sDlgFileExport, c_sConfirm), this);
    m_btnCancel = new QPushButton(qApp->translate(c_sDlgFileExport, c_sCancel), this);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(lable1);
    hLayout1->addWidget(m_spinBox1);
    hLayout1->addStretch();

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(lable2);
    hLayout2->addWidget(m_spinBox2);
    hLayout2->addStretch();

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setReadOnly(true);
    m_btnBrowser = new QPushButton(this);
    m_btnBrowser->setText("...");
    m_btnBrowser->setFixedWidth(30);

    QHBoxLayout* hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(lable3);
    hLayout3->addWidget(m_lineEdit);
    hLayout3->addWidget(m_btnBrowser);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(m_btnOk);
    hLayout->addWidget(m_btnCancel);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);

    setLayout(vLayout);
}

void DlgFileExport::initConnect()
{
    connect(m_btnBrowser, SIGNAL(clicked(bool)), this, SLOT(slotBrowser()));
    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(slotOk()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));

    connect(m_spinBox1, SIGNAL(valueChanged(double)), this, SLOT(slotSpinBoxValueChanged(double)));
}

void DlgFileExport::slotOk()
{
    if (m_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, windowTitle(), qApp->translate(c_sDlgFileExport, c_sPathTip));
        return;
    }

    startpos = m_spinBox1->value();
    exportsize = m_spinBox2->value();
    m_sExportPath = m_lineEdit->text();

    accept();
}

void DlgFileExport::slotSpinBoxValueChanged(double value)
{
    m_spinBox2->setMaximum(m_filesize - value);
}

void DlgFileExport::slotBrowser()
{
    QString sPath = QFileDialog::getExistingDirectory(this, qApp->translate(c_sDlgFileExport, c_sPathTitle), "./");
    if(sPath.isEmpty())
        return;

    m_lineEdit->setText(sPath);
}
