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
class tagAreaFileInfos;
class CMWFileList : public QMainWindow
{
    Q_OBJECT

public:
    CMWFileList(QWidget *parent = 0);
    ~CMWFileList();

    void readDelete(quint32 area, quint32 state);
    void readRecord(quint32 area, quint32 state);
    void readPlayBack(quint32 area, quint32 state);
    void readExport(quint32 area, quint32 state);
    void readTaskStop(quint32 tasktype, quint32 state);
    void readRefresh(tagAreaFileInfos* pFileInfos);
    void readImport(quint32 state);

    void updateProcess(QString fileName, qint64 buffer, qint64 total);

signals:
    void siglogRecord(QString);

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
    QAction                 *m_pActTaskQueryStart;   // 任务查询
};

#endif // MWFILELIST_H
