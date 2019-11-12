#ifndef MWFILELIST_H
#define MWFILELIST_H

#include <QtWidgets/QMainWindow>
#include <list>
using namespace std;

#include "constdef.h"
class QTableWidget;
class QTabWidget;
class QSplitter;
class QFrame;
class QLabel;
class MWFileList : public QMainWindow
{
    Q_OBJECT

public:
    MWFileList(QWidget *parent = 0);
    ~MWFileList();

    void readRecord(quint32 area, quint32 state);
    void readPlayBack(quint32 area, quint32 state);
    void readImport(quint32 area, quint32 state);
    void readExport(quint32 area, quint32 state);
    void readStop(quint32 area, quint32 state);
    void readDelete(quint32 area, quint32 state);
    void readRefresh(tagAreaFileInfos &fileInfos);

private:
    void initUI();
    void initConnect();
    void initFileListWgt();
    void logRecord(QString sText);

    private slots:
         // 日志记录
         void slotLogRecord();

private:
    QAction                 *m_pActImport;      // 导入
    QAction                 *m_pActExport;      // 导出
    QAction                 *m_pActRecord;      // 记录
    QAction                 *m_pActDelete;      // 删除
    QAction                 *m_pActRefresh;     // 刷新
    QAction                 *m_pActPlayBack;    // 回放
    QAction                 *m_pActStop;        // 停止

    QTableWidget            *m_pFileListWgt;
};

#endif // MWFILELIST_H
