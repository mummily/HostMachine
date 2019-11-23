#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>
#include <QFile>

enum operatetype
{
    ot_none = 0,    // ��ʼ��
    ot_import,      // ����
    ot_export       // ����
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
