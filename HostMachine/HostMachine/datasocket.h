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
    void slotExport();
    void slotBatchExport();

public:
    qint32 areano;
    QStringList importFileList;
    QString sIPAddr;

    QString exportFilePath;
};

#endif // DATASOCKET_H
