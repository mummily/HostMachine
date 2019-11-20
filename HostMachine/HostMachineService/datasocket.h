#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QTcpSocket>

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
    quint32 m_blockSize;
    float   m_fileSize;
    QFile   *m_file;
};

#endif // DATASOCKET_H
