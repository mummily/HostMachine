#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>

class DataSocket : public QTcpSocket
{
    Q_OBJECT

public:
    DataSocket(QObject *parent);
    ~DataSocket();

signals:
    void updateProcess(QString, float, float);
    void importCompleted();

public slots:
    void slotImport();

public:
    qint32 areano;
    QStringList importFileList;
    QString sIPAddr;
};

#endif // DATASOCKET_H
