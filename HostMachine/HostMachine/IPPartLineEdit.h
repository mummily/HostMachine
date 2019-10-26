#pragma once 

#include <QLineEdit> 

class QWidget; 
class QFocusEvent; 
class QKeyEvent; 

class IPPartLineEdit : public QLineEdit 
{ 
    Q_OBJECT 
public: 
    IPPartLineEdit(QWidget *parent = 0); 
    ~IPPartLineEdit(void); 

    void set_nexttab_edit(QLineEdit *pNextTab) { m_pEdtNextTab = pNextTab; } 

protected: 
    virtual void focusInEvent(QFocusEvent *e); 
    virtual void keyPressEvent(QKeyEvent *event);

    private slots: 
        void text_edited(const QString& text); 

private: 
    QLineEdit *m_pEdtNextTab; 
}; 
