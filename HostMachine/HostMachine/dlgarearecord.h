#ifndef DLGAREARECORD_H
#define DLGAREARECORD_H

#include <QDialog>
#include <QList>
class QPushButton;
class QComboBox;
class QLineEdit;
class QCheckBox;
class DlgAreaRecord : public QDialog
{
    Q_OBJECT

public:
    DlgAreaRecord(quint32 areano, QWidget *parent = 0);
    ~DlgAreaRecord();

public:
    QList<quint32> Areas() const { return lstArea; }
    QString Filename() const { return filename; }

private:
    void initUI();
    void initConnect();
    void initData();

    private slots:
        void slotOk();

private:
    QPushButton *m_btnOk, *m_btnCancel;
    QLineEdit   *m_lineEdit;
    QCheckBox   *m_checkBox1, *m_checkBox2, *m_checkBox3, *m_checkBox4, *m_checkBox5;

    QList<quint32> lstArea;
    QString filename;
    quint32 m_areno;
};

#endif // DLGAREARECORD_H
