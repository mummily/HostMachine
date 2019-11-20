#pragma once



// 请求类型
enum RequestType
{
    CS_CheckSelf = 0x11,    // 自检
    CS_Format = 0xA1,       // 格式化
    CS_SystemConfig = 0xB1, // 系统配置
    CS_Record = 0x21,       // 记录
    CS_PlayBack = 0x31,     // 回放
    CS_Import = 0x41,       // 导入
    CS_Export = 0x51,       // 导出
    // CS_Stop = 0x61,         // 停止
    CS_Delete = 0x71,       // 删除
    CS_Refresh = 0x81,      // 刷新
    CS_TaskQuery = 0x91,    // 任务查询
    CS_TaskStop = 0xC1,     // 任务停止
};

// 应答类型
enum RespondType
{
    SC_CheckSelf = 0x1011,      // 自检
    SC_Format = 0x10A1,         // 格式化
    SC_SystemConfig = 0x10B1,   // 系统配置
    SC_Record = 0x1021,         // 记录
    SC_PlayBack = 0x1031,       // 回放
    SC_Import = 0x1041,         // 导入
    SC_Export = 0x1051,         // 导出
    // SC_Stop = 0x1061,           // 停止
    SC_Delete = 0x1071,         // 删除
    SC_Refresh = 0x1081,        // 刷新
    SC_TaskQuery = 0x1091,      // 任务查询
    SC_TaskStop = 0x10C1,       // 任务停止
};