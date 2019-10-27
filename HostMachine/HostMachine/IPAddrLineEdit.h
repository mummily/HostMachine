// IPAddrLineEdit.h 
#pragma once 

#include <QWidget> 

class QLineEdit; 
class QLabel; 
class IPPartLineEdit; 

class IPAddrLineEdit : public QWidget 
{ 
    Q_OBJECT 
public: 
    IPAddrLineEdit(QWidget* pParent = 0); 
    ~IPAddrLineEdit(); 

    void settext(const QString &text); 
    QString text(); 
    void setStyleSheet(const QString &styleSheet); 

signals: 
    void textchanged(const QString& text); 
    void textedited(const QString &text); 

    private slots: 
        void slotTextChanged(const QString& text); 
        void slotTextEdited(const QString &text); 

private: 
    IPPartLineEdit  *m_pEdtPart1;
    IPPartLineEdit  *m_pEdtPart2;
    IPPartLineEdit  *m_pEdtPart3;
    IPPartLineEdit  *m_pEdtPart4;

    QLabel          *m_pLabeldot1;
    QLabel          *m_pLabeldot2;
    QLabel          *m_pLabeldot3;
};