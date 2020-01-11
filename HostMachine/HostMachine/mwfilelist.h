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
    QAction                 *m_pActImport;      // ����
    QAction                 *m_pActExport;      // ����
    QAction                 *m_pActRecord;      // ��¼
    QAction                 *m_pActDelete;      // ɾ��
    QAction                 *m_pActRefresh;     // ˢ��
    QAction                 *m_pActPlayBack;    // �ط�
    QAction                 *m_pActStop;        // ֹͣ
    QAction                 *m_pActTaskQueryStart;   // �����ѯ
};

#endif // MWFILELIST_H
