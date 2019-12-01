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
    // ����
    void importStart(qint32, QString, float, float);
    void importUpdate(qint32, QString, float, float);
    void importCompleted(qint32, QString, float, float);
    // ����
    void exportStart(qint32, QString, float, float);
    void exportUpdate(qint32, QString, float, float);
    void exportCompleted(qint32, QString, float, float);
    // ��־
    void siglogRecord(QString);

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
