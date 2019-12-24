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
    DlgFileExport(qint32 filesize, QWidget *parent = 0);
    ~DlgFileExport();

    qint32 Exportsize() const { return exportsize; }
    qint32 Startpos() const { return startpos; }
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
    qint32 m_filesize, startpos, exportsize;
    QString m_sExportPath;
};

#endif // DLGFILEEXPORT_H
