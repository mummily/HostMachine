#ifndef DLGAREAFORMAT_H
#define DLGAREAFORMAT_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QSplitter;
class QLabel;
class DlgAreaFormat : public QDialog
{
    Q_OBJECT

public:
    DlgAreaFormat(int nTotalSize, int nSize1, int nSize2, int nSize3, int nSize4, int nSize5, QWidget *parent = 0);
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
    void slotSplitterMoved(int pos, int index);

private:
    int             m_nTotalSize, m_nSize1, m_nSize2, m_nSize3, m_nSize4, m_nSize5;

private:
    QLineEdit       *m_pLineEdit1, *m_pLineEdit2, *m_pLineEdit3, *m_pLineEdit4, *m_pLineEdit5;
    QLabel          *m_pLabel1, *m_pLabel2, *m_pLabel3, *m_pLabel4, *m_pLabel5;
    QPushButton     *m_btnOk, *m_btnCancel;
    QSplitter       *m_pSplitter;
};

#endif // DLGAREAFORMAT_H
