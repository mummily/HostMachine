#ifndef DLGSYSTEMCONFIG_H
#define DLGSYSTEMCONFIG_H

#include <QDialog>

class QPushButton;
class QComboBox;
class DlgSystemConfig : public QDialog
{
    Q_OBJECT

public:
    DlgSystemConfig(QWidget *parent = 0);
    ~DlgSystemConfig();

    quint32 Choice() const { return choice; }
    quint32 Bandwidth() const { return bandwidth; }

private:
    void initUI();
    void initConnect();

    private slots:
        void slotOk();

private:
    QPushButton *m_btnOk, *m_btnCancel;
    QComboBox *m_comboBox1, *m_comboBox2;
private:
    quint32 choice, bandwidth;
};

#endif // DLGSYSTEMCONFIG_H
