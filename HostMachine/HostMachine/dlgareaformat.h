#ifndef DLGAREAFORMAT_H
#define DLGAREAFORMAT_H

#include <QDialog>

class QPushButton;
class QSpinBox;
class QSlider;
class DlgAreaFormat : public QDialog
{
    Q_OBJECT

public:
    DlgAreaFormat(int nSize1, int nSize2, int nSize3, int nSize4, int nSize5, QWidget *parent = 0);
    ~DlgAreaFormat();

public:
    int Size5() const { return m_nSize5; }
    int Size4() const { return m_nSize4; }
    int Size3() const { return m_nSize3; }
    int Size2() const { return m_nSize2; }
    int Size1() const { return m_nSize1; }

private:
    void initUI();
    void initConnect();
    void initData();

private slots:
    void slotOk();

private:
    QSpinBox        *m_spinbox1, *m_spinbox2, *m_spinbox3, *m_spinbox4, *m_spinbox5;
    QSlider         *m_slider1, *m_slider2, *m_slider3, *m_slider4, *m_slider5;
    QPushButton     *m_btnOk, *m_btnCancel;
    int             m_nSize1, m_nSize2, m_nSize3, m_nSize4, m_nSize5;
};

#endif // DLGAREAFORMAT_H
