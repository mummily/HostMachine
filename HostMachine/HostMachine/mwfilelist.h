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
        // ��¼
        void slotRecord();
        // �ط�
        void slotPlayBack();
        // ����
        void slotImport();
        // ����
        void slotExport();
        // ֹͣ
        void slotStop();
        // ɾ��
        void slotDelete();
        // ˢ��
        void slotRefresh();
        // ��־��¼
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
    QAction                 *m_pActImport;      // ����
    QAction                 *m_pActExport;      // ����
    QAction                 *m_pActRecord;      // ��¼
    QAction                 *m_pActDelete;      // ɾ��
    QAction                 *m_pActRefresh;     // ˢ��
    QAction                 *m_pActPlayBack;    // �ط�
    QAction                 *m_pActStop;        // ֹͣ

    QTableWidget            *m_pFileListWgt;
    QTcpSocket              *m_pCmdSocket;
    QTcpSocket              *m_pDataSocket;
};

#endif // MWFILELIST_H
