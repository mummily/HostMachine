#ifndef MWFILELIST_H
#define MWFILELIST_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <list>
#include <memory>
using namespace std;

class QTableWidget;
class QTabWidget;
class QSplitter;
class QFrame;
class QProgressBar;

// 刷新 - 文件信息
struct tagAreaFileInfo
{
    quint32 fileno;     // 文件编号
    QString sFileName;  // 文件名称
    float filesize;     // 文件大小
    QDateTime datetime; // 创建时间
};

// 刷新 - 文件信息
struct tagAreaFileInfos
{
    quint32 areano;     // 分区号
    quint32 fileno;     // 起始文件编号
    quint32 filenum;    // 文件数
    list<shared_ptr<tagAreaFileInfo>> lstFileInfo;
};

class MWFileList : public QMainWindow
{
    Q_OBJECT

public:
    MWFileList(QWidget *parent = 0);
    ~MWFileList();
    
    virtual void resizeEvent(QResizeEvent * event);

    void readRecord(quint32 area, quint32 state);
    void readPlayBack(quint32 area, quint32 state);
    void readExport(quint32 area, quint32 state);
    void readTaskStop(quint32 area, quint32 tasktype, quint32 state);
    void readDelete(quint32 area, quint32 state);
    void readRefresh(tagAreaFileInfos &fileInfos);

    void updateProcess(QString fileName, float buffer, float total);

private:
    void initUI();
    void initConnect();
    void initFileListWgt();

public:
    QTableWidget            *m_pFileListWgt;
    QProgressBar            *m_pProgressBar;

private:
    QAction                 *m_pActImport;      // 导入
    QAction                 *m_pActExport;      // 导出
    QAction                 *m_pActRecord;      // 记录
    QAction                 *m_pActDelete;      // 删除
    QAction                 *m_pActRefresh;     // 刷新
    QAction                 *m_pActPlayBack;    // 回放
    QAction                 *m_pActStop;        // 停止
};

#endif // MWFILELIST_H
