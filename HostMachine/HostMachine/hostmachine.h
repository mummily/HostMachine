#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

class QTableWidget;
class QTabWidget;
class QSplitter;
class QtTreePropertyBrowser;
class QFrame;
class HostMachine : public QMainWindow
{
    Q_OBJECT

public:
    HostMachine(QWidget *parent = 0);
    ~HostMachine();

private:
    void initUI();
    void initLayout();
    void initConnect();

    void initLDDataWgt();
    void initGDDataWgt();
    void initHHDataWgt();
    void initTaskWgt();
    void initLogWgt();
    void initPropertyWgt1();
    void initPropertyWgt2();

private:
    QTableWidget    *m_pLDDataWgt1; // 雷达数据_1
    QTableWidget    *m_pLDDataWgt2; // 雷达数据_2
    QTableWidget    *m_pGDDataWgt1; // 光电数据_1
    QTableWidget    *m_pGDDataWgt2; // 光电数据_2
    QTableWidget    *m_pHHDataWgt;  // 混合数据

    QTableWidget    *m_pTaskWgt;    // 任务列表框
    QTableWidget    *m_pLogWgt;     // 日志输出框

    QtTreePropertyBrowser   *m_pPropertyWgt1; // 磁盘控制面板
    QFrame                  *m_pPropertyWgt2; // 基本参数

    QSplitter       *m_splitter1;
    QSplitter       *m_splitter2;
    QSplitter       *m_splitter3;
};

#endif // HOSTMACHINE_H
