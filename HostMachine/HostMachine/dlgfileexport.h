#ifndef DLGFILEEXPORT_H
#define DLGFILEEXPORT_H

#include <QDialog>
class QDoubleSpinBox;
class QPushButton;
class QLineEdit;
class DlgFileExport : public QDialog
{
    Q_OBJECT

public:
    DlgFileExport(float filesize, QWidget *parent = 0);
    ~DlgFileExport();

    float Exportsize() const { return exportsize; }
    float Startpos() const { return startpos; }
    QString ExportPath() const { return m_sExportPath; }

private:
    void initUI();
    void initConnect();

    private slots:
        void slotBrowser();
        void slotOk();
        void slotSpinBoxValueChanged(double value);

private:
    QLineEdit *m_lineEdit;
    QPushButton *m_btnOk, *m_btnCancel, *m_btnBrowser;
    QDoubleSpinBox *m_spinBox1, *m_spinBox2;
    float m_filesize, startpos, exportsize;
    QString m_sExportPath;
};

#endif // DLGFILEEXPORT_H
