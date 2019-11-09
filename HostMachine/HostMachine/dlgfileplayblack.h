#ifndef DLGFILEPLAYBLACK_H
#define DLGFILEPLAYBLACK_H

#include <QDialog>

class QPushButton;
class QComboBox;
class QSpinBox;
class DlgFilePlayblack : public QDialog
{
    Q_OBJECT

public:
    DlgFilePlayblack(QWidget *parent = 0);
    ~DlgFilePlayblack();

public:
    quint32 Cpi() const { return cpi; }
    quint32 Prf() const { return prf; }
    quint32 Datanum() const { return datanum; }
    quint32 Prftime() const { return prftime; }
    quint32 Type() const { return type; }

private:
    void initUI();
    void initConnect();

    private slots:
        void slotOk();

private:
    QPushButton *m_btnOk, *m_btnCancel;
    QComboBox *m_comboBox;
    QSpinBox *m_sbPRFTime, *m_sbDataNum, *m_sbPRF, *m_sbCPI;

    quint32 type, prftime, datanum, prf, cpi;
};

#endif // DLGFILEPLAYBLACK_H
