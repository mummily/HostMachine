// MyIpPartLineEdit.cpp 
#include "IPPartLineEdit.h" 
#include <QIntValidator> 
#include <QKeyEvent> 

IPPartLineEdit::IPPartLineEdit(QWidget *parent/* = 0*/) 
    : QLineEdit(parent) 
{ 
    m_pEdtNextTab = NULL; 

    this->setMaxLength(3); 
    this->setFrame(false); 
    this->setAlignment(Qt::AlignCenter); 

    QValidator *validator = new QIntValidator(0, 255, this); 
    this->setValidator(validator); 

    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(text_edited(const QString&))); 
} 

IPPartLineEdit::~IPPartLineEdit(void) 
{ 
} 

void IPPartLineEdit::focusInEvent(QFocusEvent *e) 
{ 
    this->selectAll(); 
    QLineEdit::focusInEvent(e); 
} 

void IPPartLineEdit::keyPressEvent(QKeyEvent *event) 
{ 
    if (event->key() == Qt::Key_Period) 
    { 
        if (m_pEdtNextTab) 
        { 
            m_pEdtNextTab->setFocus(); 
            m_pEdtNextTab->selectAll(); 
        } 
    } 
    QLineEdit::keyPressEvent(event); 
} 

void IPPartLineEdit::text_edited(const QString& text) 
{ 
    QIntValidator v(0, 255, this); 
    QString ipaddr = text; 
    int pos = 0; 
    QValidator::State state = v.validate(ipaddr, pos);
    if (state != QValidator::Acceptable) 
        return;

    if (ipaddr.size() < 2) 
        return;

    if (NULL == m_pEdtNextTab)
        return;

    if (ipaddr.size() == 2) 
    { 
        int ipnum = ipaddr.toInt(); 

        if (ipnum > 25) 
        { 
            m_pEdtNextTab->setFocus(); 
            m_pEdtNextTab->selectAll(); 
        } 
    } 
    else 
    { 
        m_pEdtNextTab->setFocus(); 
        m_pEdtNextTab->selectAll(); 
    } 
}