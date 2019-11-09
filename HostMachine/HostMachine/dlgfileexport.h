#ifndef DLGFILEEXPORT_H
#define DLGFILEEXPORT_H

#include <QDialog>
class QDoubleSpinBox;
class QPushButton;
class DlgFileExport : public QDialog
{
    Q_OBJECT

public:
    DlgFileExport(float filesize, QWidget *parent = 0);
    ~DlgFileExport();

    float Exportsize() const { return exportsize; }
    float Startpos() const { return startpos; }

private:
    void initUI();
    void initConnect();

    private slots:
        void slotOk();
        void slotSpinBoxValueChanged(double value);

private:
    QPushButton *m_btnOk, *m_btnCancel;
    QDoubleSpinBox *m_spinBox1, *m_spinBox2;
    float m_filesize, startpos, exportsize;
};

#endif // DLGFILEEXPORT_H
