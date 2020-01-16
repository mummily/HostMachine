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
    DlgFileExport(double filesize, QString sPath, QWidget *parent = 0);
    ~DlgFileExport();

    qint32 Exportsize() const { return exportsize * 1024; /* MB->LBA */ }
    qint32 Startpos() const { return startpos * 1024; /* MB->LBA */ }
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
    double m_filesize, startpos, exportsize;
    QString m_sDefExportPath, m_sExportPath;
};

#endif // DLGFILEEXPORT_H
