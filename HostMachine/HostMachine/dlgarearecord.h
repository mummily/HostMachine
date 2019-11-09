#ifndef DLGAREARECORD_H
#define DLGAREARECORD_H

#include <QDialog>
class QPushButton;
class QComboBox;
class QLineEdit;
class DlgAreaRecord : public QDialog
{
    Q_OBJECT

public:
    DlgAreaRecord(QWidget *parent = 0);
    ~DlgAreaRecord();

public:
    quint32 Area() const { return area; }
    QString Filename() const { return filename; }

private:
    void initUI();
    void initConnect();

    private slots:
        void slotOk();

private:
    QPushButton     *m_btnOk, *m_btnCancel;
    QComboBox *m_comboBox;
    QLineEdit *m_lineEdit;

    quint32 area;
    QString filename;
};

#endif // DLGAREARECORD_H
