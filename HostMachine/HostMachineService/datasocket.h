#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>
#include <QFile>

enum operatetype
{
    ot_none = 0,    // 初始化
    ot_import,      // 导入
    ot_export       // 导出
};

class QFile;
class DataSocket : public QTcpSocket
{
    Q_OBJECT

public:
    DataSocket(QObject *parent);
    ~DataSocket();

public:
    void initData();

private slots:
    void readClient();
    void slotExport();

private:
    void respondImport(QByteArray buf);

public:
    qint32 areaNo;
    QString sFileName;
    qint64 startPos, fileSize;

private:
    qint64  m_fileSize;
    qint64  m_blockSize;
    QFile   m_file;
    bool    m_bStart;
};

#endif // DATASOCKET_H
