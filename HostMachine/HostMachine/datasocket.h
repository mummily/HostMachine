#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>
#include <QFile>

class CDataSocket : public QTcpSocket
{
    Q_OBJECT

public:
    CDataSocket(QObject *parent);
    ~CDataSocket();

public:
    void preExport(qint32 areaNo, QString filePath, qint64 fileSize);
    bool preImport(qint32 areaNo, QString filePath);

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

private:
    void respondExport(QByteArray buf);
public:
    QFile   m_file;             // �ļ�
    bool    m_bStart;           // �Ƿ�ʼ
    float   m_fileSize, m_bufferSize;    // �ļ���С�������С

    // �������
    qint32 areano;              // �����ļ����ڵķ���
    QString sIPAddr;            // IP
};

#endif // DATASOCKET_H
