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

    void respondImport(QByteArray buf);
    void respondExport(QByteArray buf);
private slots:
    void readClient();
private:
    qint64  m_fileSize;
    qint64  m_blockSize;
    QFile   m_file;
    bool    m_bStart;
};

#endif // DATASOCKET_H
