#include "dlgareaformat.h"
#include <QLabel>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSplitter>

static const char *c_sDlgAreaFormat = "DlgAreaFormat";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DlgAreaFormat", "格式化");
static const char *c_sArea0 = QT_TRANSLATE_NOOP("DlgAreaFormat", "原始数据分区");
static const char *c_sArea1 = QT_TRANSLATE_NOOP("DlgAreaFormat", "雷达结果分区");
static const char *c_sArea2 = QT_TRANSLATE_NOOP("DlgAreaFormat", "光电图片分区");
static const char *c_sArea3 = QT_TRANSLATE_NOOP("DlgAreaFormat", "光电视频分区");
static const char *c_sArea4 = QT_TRANSLATE_NOOP("DlgAreaFormat", "混合数据分区");

static const char *c_sConfirm = QT_TRANSLATE_NOOP("DlgAreaFormat", "确定");
static const char *c_sCancel = QT_TRANSLATE_NOOP("DlgAreaFormat", "取消");

DlgAreaFormat::DlgAreaFormat(int nTotalSize, int nSize1, int nSize2, int nSize3, int nSize4, int nSize5, QWidget *parent)
    : QDialog(parent), m_nTotalSize(nTotalSize), m_nSize1(nSize1), m_nSize2(nSize2), m_nSize3(nSize3), m_nSize4(nSize4), m_nSize5(nSize5)
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
    setFixedSize(476, 260);

    auto createLineEdit=[&](QLineEdit* &pLineEdit)->void
    {
        pLineEdit = new QLineEdit(this);
        pLineEdit->setReadOnly(true);
    };

    QLabel* lable1 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea0), this);
    QLabel* lable2 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea1), this);
    QLabel* lable3 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea2), this);
    QLabel* lable4 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea3), this);
    QLabel* lable5 = new QLabel(qApp->translate(c_sDlgAreaFormat, c_sArea4), this);

    createLineEdit(m_pLineEdit1);
    createLineEdit(m_pLineEdit2);
    createLineEdit(m_pLineEdit3);
    createLineEdit(m_pLineEdit4);
    createLineEdit(m_pLineEdit5);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(lable1, 0, 0);
    gridLayout->addWidget(m_pLineEdit1, 0, 1);

    gridLayout->addWidget(lable2, 1, 0);
    gridLayout->addWidget(m_pLineEdit2, 1, 1);

    gridLayout->addWidget(lable3, 2, 0);
    gridLayout->addWidget(m_pLineEdit3, 2, 1);

    gridLayout->addWidget(lable4, 3, 0);
    gridLayout->addWidget(m_pLineEdit4, 3, 1);

    gridLayout->addWidget(lable5, 4, 0);
    gridLayout->addWidget(m_pLineEdit5, 4, 1);

    auto createLabel=[&](QLabel* &pLabel)->void
    {
        pLabel = new QLabel(this);
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setMinimumWidth(1);
        pLabel->setStyleSheet("QLabel { border:2px solid rgb(128, 128, 128)}");
    };

    createLabel(m_pLabel1);
    createLabel(m_pLabel2);
    createLabel(m_pLabel3);
    createLabel(m_pLabel4);
    createLabel(m_pLabel5);

    m_pSplitter = new QSplitter(this);
    m_pSplitter->setOrientation(Qt::Horizontal);
    m_pSplitter->setLineWidth(1);
    m_pSplitter->addWidget(m_pLabel1);
    m_pSplitter->addWidget(m_pLabel2);
    m_pSplitter->addWidget(m_pLabel3);
    m_pSplitter->addWidget(m_pLabel4);
    m_pSplitter->addWidget(m_pLabel5);
    m_pSplitter->setSizes(QList<int>() << m_nSize1 << m_nSize2 << m_nSize3 << m_nSize4 << m_nSize5);
    m_pSplitter->setFixedHeight(50);
    m_pSplitter->setHidden(false);
    m_pSplitter->setChildrenCollapsible(false);

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
    vLayout->addWidget(m_pSplitter);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);

    setLayout(vLayout);
}

void DlgAreaFormat::initConnect()
{
    connect(m_pSplitter, SIGNAL(splitterMoved(int, int)), this, SLOT(slotSplitterMoved(int, int)));

    connect(m_btnOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DlgAreaFormat::initData()
{
    QString sSize1 = QString::number(m_nSize1);
    QString sSize2 = QString::number(m_nSize2);
    QString sSize3 = QString::number(m_nSize3);
    QString sSize4 = QString::number(m_nSize4);
    QString sSize5 = QString::number(m_nSize5);

    m_pLineEdit1->setText(sSize1);
    m_pLineEdit2->setText(sSize2);
    m_pLineEdit3->setText(sSize3);
    m_pLineEdit4->setText(sSize4);
    m_pLineEdit5->setText(sSize5);

    m_pLabel1->setText(sSize1 + " LBA");
    m_pLabel2->setText(sSize2 + " LBA");
    m_pLabel3->setText(sSize3 + " LBA");
    m_pLabel4->setText(sSize4 + " LBA");
    m_pLabel5->setText(sSize5 + " LBA");
}

void DlgAreaFormat::slotSplitterMoved(int pos, int index)
{
    if (index == 1)
    {
        int total = m_nSize1 + m_nSize2;
        m_nSize1 = m_pLabel1->width() * total / (m_pLabel1->width() + m_pLabel2->width());
        m_nSize2 = total - m_nSize1;
    }
    else if (index == 2)
    {
        int total = m_nSize2 + m_nSize3;
        m_nSize2 = m_pLabel2->width() * total / (m_pLabel2->width() + m_pLabel3->width());
        m_nSize3 = total - m_nSize2;
    }
    else if (index == 3)
    {
        int total = m_nSize3 + m_nSize4;
        m_nSize3 = m_pLabel3->width() * total / (m_pLabel3->width() + m_pLabel4->width());
        m_nSize4 = total - m_nSize3;
    }
    else if (index == 4)
    {
        int total = m_nSize4 + m_nSize5;
        m_nSize4 = m_pLabel4->width() * total / (m_pLabel4->width() + m_pLabel5->width());
        m_nSize5 = total - m_nSize4;
    }

    initData();
}
