#ifndef MWFILELIST_H
#define MWFILELIST_H

#include <QtWidgets/QMainWindow>
#include <list>
#include <QDataStream>
#include <QDateTime>
using namespace std;

#include "constdef.h"

class QtProperty;

class QTableWidget;
class QTabWidget;
class QSplitter;
class QtTreePropertyBrowser;
class QFrame;
class QLabel;
class QTcpSocket;
class MWFileList : public QMainWindow
{
    Q_OBJECT

public:
    MWFileList(QTcpSocket *pCmdSocket, QTcpSocket *pDataSocket, QWidget *parent = 0);
    ~MWFileList();

private:
    void initUI();
    void initConnect();

    void initFileListWgt();

    private slots:
        void slotCmdReadyRead();
        void slotDataReadyRead();

        // Menu
        // 记录
        void slotRecord();
        // 回放
        void slotPlayBack();
        // 导入
        void slotImport();
        // 导出
        void slotExport();
        // 停止
        void slotStop();
        // 删除
        void slotDelete();
        // 刷新
        void slotRefresh();
        // 日志记录
        void slotLogRecord();

private:
    void readRecord(quint32 area, quint32 state);
    void readPlayBack(quint32 area, quint32 state);
    void readImport(quint32 area, quint32 state);
    void readExport(quint32 area, quint32 state);
    void readStop(quint32 area, quint32 state);
    void readDelete(quint32 area, quint32 state);
    void readRefresh(tagAreaFileInfos &fileInfos);

    void logRecord(QString sText);

private:
    QAction                 *m_pActImport;      // 导入
    QAction                 *m_pActExport;      // 导出
    QAction                 *m_pActRecord;      // 记录
    QAction                 *m_pActDelete;      // 删除
    QAction                 *m_pActRefresh;     // 刷新
    QAction                 *m_pActPlayBack;    // 回放
    QAction                 *m_pActStop;        // 停止

    QTableWidget            *m_pFileListWgt;
    QTcpSocket              *m_pCmdSocket;
    QTcpSocket              *m_pDataSocket;
};

#endif // MWFILELIST_H
