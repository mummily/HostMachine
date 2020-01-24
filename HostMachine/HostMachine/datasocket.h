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
    void importStart(qint32, QString, qint64, qint64);
    void importUpdate(qint32, QString, qint64, qint64);
    void importStop(qint32, QString, qint64, qint64);
    void importCompleted(qint32, QString, qint64, qint64);
    // 导出
    void exportStart(qint32, QString, qint64, qint64);
    void exportUpdate(qint32, QString, qint64, qint64);
    void exportStop(qint32, QString, qint64, qint64);
    void exportCompleted(qint32, QString, qint64, qint64);
    // 日志
    void siglogRecord(QString);

public slots:
    void slotImport();
    void readyRead();

private:
    void respondExport(QByteArray buf);
public:
    bool    m_bImportStop, m_bExportStop;

    QFile   m_file;             // 文件
    bool    m_bStart;           // 是否开始
    qint64  m_fileSize, m_bufferSize;    // 文件大小，缓存大小

    // 导入参数
    qint32 areano;              // 导入文件所在的分区
    QString sIPAddr;            // IP
};

#endif // DATASOCKET_H
