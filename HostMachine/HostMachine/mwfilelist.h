#ifndef MWFILELIST_H
#define MWFILELIST_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <list>
#include <memory>
#include "QNetworkReply"
using namespace std;

class QTableWidget;
class QTabWidget;
class QSplitter;
class QFrame;
class QLabel;
class QFile;
class QNetworkReply;

const int c_bSizeMax = 1024;
const int c_kSizeMax = c_bSizeMax * 1024;
const int c_mSizeMax = c_kSizeMax * 1024;
const qint64 c_gSizeMax = c_mSizeMax * 1024;
const int c_bufferSize = 4 * c_bSizeMax;

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

    void readRecord(quint32 area, quint32 state);
    void readPlayBack(quint32 area, quint32 state);
    void readImport(quint32 area, char* filename, quint32 state);
    void readExport(quint32 area, quint32 state);
    void readTaskStop(quint32 area, quint32 tasktype, quint32 state);
    void readDelete(quint32 area, quint32 state);
    void readRefresh(tagAreaFileInfos &fileInfos);

private:
    void initUI();
    void initConnect();
    void initFileListWgt();
    void logRecord(QString sText);

signals:
    void sigDelete(QList<quint32>);
    void sigPlayBack(quint32, quint32, quint32, quint32, quint32, quint32);

    private slots:
         // 日志记录
         void slotLogRecord();
         void slotDelete();
         void slotPlayBack();
         void loadProgress(qint64 bytesSent,qint64 bytesTotal);
         void replyFinished(QNetworkReply* pNetworkReply);
         void loadError(QNetworkReply::NetworkError code);
public:
    QTableWidget            *m_pFileListWgt;

private:
    QFile                   *m_pFile;

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
