#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>


// ��������
enum RequestType
{
    CS_CheckSelf = 0x11,    // �Լ�
    CS_Format = 0xA1,       // ��ʽ��
    CS_SystemConfig = 0xB1, // ϵͳ����
    CS_Record = 0x21,       // ��¼
    CS_PlayBack = 0x31,     // �ط�
    CS_Import = 0x41,       // ����
    CS_Export = 0x51,       // ����
    CS_Stop = 0x61,         // ֹͣ
    CS_Delete = 0x71,       // ɾ��
    CS_Refresh = 0x81,      // ˢ��
    CS_TaskQuery = 0x91,    // �����ѯ
    CS_TaskStop = 0xC1,     // ����ֹͣ
};

// Ӧ������
enum RespondType
{
    SC_CheckSelf = 0x1011,      // �Լ�
    SC_Format = 0x10A1,         // ��ʽ��
    SC_SystemConfig = 0x10B1,   // ϵͳ����
    SC_Record = 0x1021,         // ��¼
    SC_PlayBack = 0x1031,       // �ط�
    SC_Import = 0x1041,         // ����
    SC_Export = 0x1051,         // ����
    SC_Stop = 0x1061,           // ֹͣ
    SC_Delete = 0x1071,         // ɾ��
    SC_Refresh = 0x1081,        // ˢ��
    SC_TaskQuery = 0x1091,      // �����ѯ
    SC_TaskStop = 0x10C1,       // ����ֹͣ
};

class ClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    ClientSocket(QObject *parent);
    ~ClientSocket();

    void respondCheckSelf();
    void respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4);
    void respondPlayBack(quint32 data1, quint32 data2, quint32 data3, quint32 data4, quint32 data5, quint32 data6, quint32 data7);
    void respondSystemConfig(quint32 choice, quint32 setting);
    void respondRecord(quint32 areano, quint64 time, QString filename);
    void respondImport(quint32 areano, float filesize, QDateTime time, QString filename);
    void respondExport(quint32 areano, float fileno, float startpos, float exportsize);
    void respondStop(quint32 areano);
    void respondDelete(quint32 areano, float fileno);
    void respondRefresh(quint32 areano, quint32 fileno, quint32 filenum);
private slots:
    void readClient();
};

#endif // CLIENTSOCKET_H
