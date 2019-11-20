#pragma once



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
    // CS_Stop = 0x61,         // ֹͣ
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
    // SC_Stop = 0x1061,           // ֹͣ
    SC_Delete = 0x1071,         // ɾ��
    SC_Refresh = 0x1081,        // ˢ��
    SC_TaskQuery = 0x1091,      // �����ѯ
    SC_TaskStop = 0x10C1,       // ����ֹͣ
};