#ifndef DLGAREAFORMAT_H
#define DLGAREAFORMAT_H

#include <QDialog>

class QPushButton;
class QDoubleSpinBox;
class QSlider;
class QRadioButton;
class QLabel;
class DlgAreaFormat : public QDialog
{
    Q_OBJECT

public:
    DlgAreaFormat(qint64 nTotalSize, qint64 nSize1, qint64 nSize2, qint64 nSize3, qint64 nSize4, qint64 nSize5, QWidget *parent = 0);
    ~DlgAreaFormat();

public:
    qint64 Size5() const { return m_nSize5 * 1024 * 1024; } /* GB->LBA */
    qint64 Size4() const { return m_nSize4 * 1024 * 1024; }
    qint64 Size3() const { return m_nSize3 * 1024 * 1024; }
    qint64 Size2() const { return m_nSize2 * 1024 * 1024; }
    qint64 Size1() const { return m_nSize1 * 1024 * 1024; }

private:
    void initUI();
    void initConnect();
    void initData();

private slots:
    void slotSpinBoxValueChanged(double value);
    void slotRadioToggled(bool checked);
    void slotSliderValueChange(int value);

private:
    QRadioButton    *m_pRadio1, *m_pRadio2, *m_pRadio3, *m_pRadio4, *m_pRadio5;
    QDoubleSpinBox  *m_spinbox1, *m_spinbox2, *m_spinbox3, *m_spinbox4, *m_spinbox5;
    QSlider         *m_slider1, *m_slider2, *m_slider3, *m_slider4, *m_slider5;
    QPushButton     *m_btnOk, *m_btnCancel;
    QLabel          *m_pLabel;

private:
    double          m_nTotalSize, m_nSize1, m_nSize2, m_nSize3, m_nSize4, m_nSize5;
};

#endif // DLGAREAFORMAT_H
