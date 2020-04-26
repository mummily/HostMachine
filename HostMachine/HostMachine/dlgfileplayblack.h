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
    DlgFilePlayblack(quint32 type, quint32 prftime, quint32 datanum, quint32 prf, quint32 cpi, QWidget *parent = 0);
    ~DlgFilePlayblack();

public:
    quint32 Cpi() const { return m_cpi; }
    quint32 Prf() const { return m_prf; }
    quint32 Datanum() const { return m_datanum; }
    quint32 Prftime() const { return m_prftime; }
    quint32 Type() const { return m_type; }

private:
    void initUI();
    void initData();
    void initConnect();

    private slots:
        void slotOk();

private:
    QPushButton *m_btnOk, *m_btnCancel;
    QComboBox *m_comboBox;
    QSpinBox *m_sbPRFTime, *m_sbDataNum, *m_sbPRF, *m_sbCPI;

    quint32 m_type, m_prftime, m_datanum, m_prf, m_cpi;
};

#endif // DLGFILEPLAYBLACK_H
