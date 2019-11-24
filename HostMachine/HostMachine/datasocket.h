#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>
#include <QFile>

class DataSocket : public QTcpSocket
{
    Q_OBJECT

public:
    DataSocket(QObject *parent);
    ~DataSocket();

private:
    void respondExport(QByteArray buf);

signals:
    void updateProcess(QString, float, float);
    void importCompleted();
    void exportCompleted();

public slots:
    void slotImport();
    void readyRead();

public:
    QFile   m_file;             // �ļ�
    bool    m_bStart;           // �Ƿ�ʼ
    float   m_fileSize, m_bufferSize;    // �ļ���С�������С

    // �������
    qint32 areano;              // �����ļ����ڵķ���
    QStringList importFileList; // �����ļ�
    QString sIPAddr;            // IP

    // ��������
    QString exportFilePath;     // �������ı���·��
};

#endif // DATASOCKET_H
