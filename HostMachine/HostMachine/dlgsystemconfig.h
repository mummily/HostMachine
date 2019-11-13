#ifndef DLGSYSTEMCONFIG_H
#define DLGSYSTEMCONFIG_H

#include <QDialog>

class QPushButton;
class QComboBox;
class QCheckBox;
class DlgSystemConfig : public QDialog
{
    Q_OBJECT

public:
    DlgSystemConfig(QWidget *parent = 0);
    ~DlgSystemConfig();

    QList<quint32> ChannelChoice() const { return lstChannelChoice; }
    quint32 Bandwidth() const { return bandwidth; }

private:
    void initUI();
    void initConnect();
    void initData();

    private slots:
        void slotOk();
        void slotChannelChanged(int index);

private:
    QPushButton *m_btnOk, *m_btnCancel;
    QComboBox *m_comboBox1, *m_comboBox2;
    QCheckBox *m_checkBox1, *m_checkBox2, *m_checkBox3, *m_checkBox4,
        *m_checkBox5, *m_checkBox6, *m_checkBox7, *m_checkBox8;
private:
    QList<quint32> lstChannelChoice;
    quint32 bandwidth;
};

#endif // DLGSYSTEMCONFIG_H
