#ifndef CMDSOCKET_H
#define CMDSOCKET_H

#include <QTcpSocket>

class CmdSocket : public QTcpSocket
{
    Q_OBJECT

public:
    CmdSocket(QObject *parent);
    ~CmdSocket();

    void respondCheckSelf();
    void respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4);
    void respondPlayBack(quint32 data1, quint32 data2, quint32 data3, quint32 data4, quint32 data5, quint32 data6, quint32 data7);
    void respondSystemConfig(quint32 choice, quint32 setting);
    void respondRecord(quint32 areano, quint64 time, QString filename);
    void respondTaskStop(quint32 areano, quint32 tasktype);
    void respondDelete(quint32 areano, float fileno);
    void respondRefresh(quint32 areano, quint32 fileno, quint32 filenum);
    void respondImport(quint32 areano, float filesize, QDateTime time, char* filename);
private slots:
    void readClient();
};

#endif // CMDSOCKET_H
