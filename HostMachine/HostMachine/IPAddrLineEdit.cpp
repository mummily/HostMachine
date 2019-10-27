// IPAddrLineEdit.cpp 
#include "IPAddrLineEdit.h" 
#include <QRegExpValidator> 
#include <QLabel> 
#include "IPPartLineEdit.h" 

IPAddrLineEdit::IPAddrLineEdit(QWidget* pParent /* = 0 */) 
    : QWidget(pParent) 
{ 
    m_pEdtPart1 = new IPPartLineEdit(this); 
    m_pEdtPart2 = new IPPartLineEdit(this); 
    m_pEdtPart3 = new IPPartLineEdit(this); 
    m_pEdtPart4 = new IPPartLineEdit(this); 

    m_pLabeldot1 = new QLabel(this); 
    m_pLabeldot1->setText(" ."); 
    m_pLabeldot1->setAlignment(Qt::AlignCenter); 

    m_pLabeldot2 = new QLabel(this); 
    m_pLabeldot2->setText(" ."); 
    m_pLabeldot2->setAlignment(Qt::AlignCenter); 

    m_pLabeldot3 = new QLabel(this); 
    m_pLabeldot3->setText(" ."); 
    m_pLabeldot3->setAlignment(Qt::AlignCenter); 

    int nWidth = 50;
    m_pEdtPart1->setGeometry(QRect(0, 0, nWidth, 20)); 
    m_pEdtPart2->setGeometry(QRect(nWidth, 0, nWidth, 20)); 
    m_pEdtPart3->setGeometry(QRect(nWidth * 2, 0, nWidth, 20)); 
    m_pEdtPart4->setGeometry(QRect(nWidth * 3, 0, nWidth, 20)); 

    m_pLabeldot1->setGeometry(QRect(nWidth - 3, 1, 6, 18)); 
    m_pLabeldot2->setGeometry(QRect(nWidth * 2 - 3, 1, 6, 18)); 
    m_pLabeldot3->setGeometry(QRect(nWidth * 3 - 3, 1, 6, 18)); 

    QWidget::setTabOrder(m_pEdtPart1, m_pEdtPart2); 
    QWidget::setTabOrder(m_pEdtPart2, m_pEdtPart3); 
    QWidget::setTabOrder(m_pEdtPart3, m_pEdtPart4); 
    m_pEdtPart1->set_nexttab_edit(m_pEdtPart2); 
    m_pEdtPart2->set_nexttab_edit(m_pEdtPart3); 
    m_pEdtPart3->set_nexttab_edit(m_pEdtPart4); 

    connect(m_pEdtPart1, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&))); 
    connect(m_pEdtPart2, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&))); 
    connect(m_pEdtPart3, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&))); 
    connect(m_pEdtPart4, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&))); 

    connect(m_pEdtPart1, SIGNAL(textEdited (const QString&)), this, SLOT(slotTextEdited(const QString&))); 
    connect(m_pEdtPart2, SIGNAL(textEdited (const QString&)), this, SLOT(slotTextEdited(const QString&))); 
    connect(m_pEdtPart3, SIGNAL(textEdited (const QString&)), this, SLOT(slotTextEdited(const QString&))); 
    connect(m_pEdtPart4, SIGNAL(textEdited (const QString&)), this, SLOT(slotTextEdited(const QString&))); 
} 

IPAddrLineEdit::~IPAddrLineEdit() 
{ 

} 

void IPAddrLineEdit::slotTextChanged(const QString& /*text*/) 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = m_pEdtPart1->text(); 
    ippart2 = m_pEdtPart2->text(); 
    ippart3 = m_pEdtPart3->text(); 
    ippart4 = m_pEdtPart4->text(); 

    QString ipaddr = QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 

    emit textchanged(ipaddr); 
} 

void IPAddrLineEdit::slotTextEdited(const QString &/*text*/) 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = m_pEdtPart1->text(); 
    ippart2 = m_pEdtPart2->text(); 
    ippart3 = m_pEdtPart3->text(); 
    ippart4 = m_pEdtPart4->text(); 

    QString ipaddr = QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 

    emit textedited(ipaddr); 
} 

void IPAddrLineEdit::settext(const QString &text) 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    QString qstring_validate = text; 

    // IP地址验证 
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)"); 
    QRegExpValidator regexp_validator(regexp, this); 
    int nPos = 0; 
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos); 
    // IP合法 
    if (state == QValidator::Acceptable) 
    { 
        QStringList ippartlist = text.split("."); 

        int strcount = ippartlist.size(); 
        int index = 0; 
        if (index < strcount) 
        { 
            ippart1 = ippartlist.at(index); 
        } 
        if (++index < strcount) 
        { 
            ippart2 = ippartlist.at(index); 
        } 
        if (++index < strcount) 
        { 
            ippart3 = ippartlist.at(index); 
        } 
        if (++index < strcount) 
        { 
            ippart4 = ippartlist.at(index); 
        } 
    } 

    m_pEdtPart1->setText(ippart1); 
    m_pEdtPart2->setText(ippart2); 
    m_pEdtPart3->setText(ippart3); 
    m_pEdtPart4->setText(ippart4); 
} 

QString IPAddrLineEdit::text() 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = m_pEdtPart1->text(); 
    ippart2 = m_pEdtPart2->text(); 
    ippart3 = m_pEdtPart3->text(); 
    ippart4 = m_pEdtPart4->text(); 

    return QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 
} 

void IPAddrLineEdit::setStyleSheet(const QString &styleSheet) 
{ 
    m_pEdtPart1->setStyleSheet(styleSheet); 
    m_pEdtPart2->setStyleSheet(styleSheet); 
    m_pEdtPart3->setStyleSheet(styleSheet); 
    m_pEdtPart4->setStyleSheet(styleSheet); 
}