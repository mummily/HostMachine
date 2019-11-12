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
    DlgAreaRecord(QWidget *parent = 0);
    ~DlgAreaRecord();

public:
    QList<quint32> Areas() const { return lstArea; }
    QString Filename() const { return filename; }

private:
    void initUI();
    void initConnect();

    private slots:
        void slotOk();

private:
    QPushButton     *m_btnOk, *m_btnCancel;
    QLineEdit *m_lineEdit;
    QCheckBox* m_checkBox1;
    QCheckBox* m_checkBox2;
    QCheckBox* m_checkBox3;
    QCheckBox* m_checkBox4;
    QCheckBox* m_checkBox5;

    QList<quint32> lstArea;
    QString filename;
};

#endif // DLGAREARECORD_H
