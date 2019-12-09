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
    // 导入
    void importStart(qint32, QString, float, float);
    void importUpdate(qint32, QString, float, float);
    void importCompleted(qint32, QString, float, float);
    // 导出
    void exportStart(qint32, QString, float, float);
    void exportUpdate(qint32, QString, float, float);
    void exportCompleted(qint32, QString, float, float);
    // 日志
    void siglogRecord(QString);

public slots:
    void slotImport();
    void readyRead();

private:
    void respondExport(QByteArray buf);
public:
    QFile   m_file;             // 文件
    bool    m_bStart;           // 是否开始
    float   m_fileSize, m_bufferSize;    // 文件大小，缓存大小

    // 导入参数
    qint32 areano;              // 导入文件所在的分区
    QString sIPAddr;            // IP
};

#endif // DATASOCKET_H
