#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>
#include <QFile>

class QFile;
class DataSocket : public QTcpSocket
{
    Q_OBJECT

public:
    DataSocket(QObject *parent);
    ~DataSocket();

    void respondExport(quint32 areano, float fileno, float startpos, float exportsize);
private slots:
    void readClient();
private:
    qint64  m_fileSize;
    qint64  m_blockSize;
    QFile   m_file;
    bool    m_bStart;
};

#endif // DATASOCKET_H
