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

// ˢ�� - �ļ���Ϣ
struct tagAreaFileInfo
{
    quint32 fileno;     // �ļ����
    QString sFileName;  // �ļ�����
    float filesize;     // �ļ���С
    QDateTime datetime; // ����ʱ��
};

// ˢ�� - �ļ���Ϣ
struct tagAreaFileInfos
{
    quint32 areano;     // ������
    quint32 fileno;     // ��ʼ�ļ����
    quint32 filenum;    // �ļ���
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
    QAction                 *m_pActImport;      // ����
    QAction                 *m_pActExport;      // ����
    QAction                 *m_pActRecord;      // ��¼
    QAction                 *m_pActDelete;      // ɾ��
    QAction                 *m_pActRefresh;     // ˢ��
    QAction                 *m_pActPlayBack;    // �ط�
    QAction                 *m_pActStop;        // ֹͣ
};

#endif // MWFILELIST_H
