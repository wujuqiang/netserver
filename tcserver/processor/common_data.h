/******************************************************************************
** Copyright (C) 2017 Sony Corporation

******************************************************************************/
#ifndef __NET_SERVER_COMMON_DATA_H__
#define __NET_SERVER_COMMON_DATA_H__

#include <stdint.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

namespace NetServer{

static const uint8_t REQ_TYPE_SYNC_TC = 0x01;	
static const uint8_t REQ_TYPE_GET_TC = 0x02;	
static const uint8_t REQ_TYPE_SET_TC = 0x03;


static const uint8_t RES_TYPE_GET_TC = 0x11;
static const uint8_t RES_TYPE_SET_TC = 0x20;
static const uint8_t RES_TYPE_SET_UB = 0x21;
static const uint8_t RES_TYPE_SYNC_TC = 0x22;
static const uint8_t RES_TYPE_FOR_TEST = 0x02;

static const uint8_t MILLISCONDS_MAX_LEN = 13;

static const uint8_t TRANSFER_DATA_DECIMAL = 10;
static const uint8_t TRANSFER_DATA_HEXADECIMAL = 16;
static const uint8_t TRANSFER_DATA_OCTONARY = 8;
static const uint8_t TRANSFER_DATA_BINARY = 2;

static const uint8_t BUFF_READ_MAX_LEN = 255;
static const uint8_t BUFF_IP_MAX_LEN = 16;

typedef enum{
    SYNC_DATA_PARSE_MILLSECONDS = 0,
    SYNC_DATA_PARSE_TC_P,
    SYNC_DATA_PARSE_TC_S,
    SYNC_DATA_PARSE_TC_M,
    SYNC_DATA_PARSE_TC_H,
    SYNC_DATA_PARSE_AUTO_FLAG,
    SYNC_DATA_PARSE_MAX,
}SYNC_DATA_PARSE;

typedef struct{
    uint64_t   milli_seconds;
    uint8_t     tc_p;
    uint8_t     tc_s;
    uint8_t     tc_m;
    uint8_t     tc_h;
//    uint8_t     rate; //drop
    uint8_t     auto_flag;
}Sync_Data_Parse;

typedef struct{
    int64_t offset;
}Get_Data_Parse;

typedef struct{
    uint8_t type;          //type = 0x01(SyncTc); 0x02(getTc)
    union {
        Sync_Data_Parse sync_data;
        Get_Data_Parse get_data;
    } param;
}Data_Parse;

typedef enum{
    ERROR_CODE_OK = 0,
    ERROR_CODE_NG,
    ERROR_CODE_OTHER
}Error_Code;

typedef struct {
    int len;          //data length
    uint8_t type; //data type
    int port;
    char ip[BUFF_IP_MAX_LEN];
    char data[BUFF_READ_MAX_LEN]; //real data
}Data_Transfer;

// debug print
#define TC_LOG_DBG(fmt, ...)   printf("[TCSYNC][DBG]  %s:%d, %s(): "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
#define TC_LOG_ERR(fmt, ...)   printf("[TCSYNC][ERR]  %s:%d, %s(): "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)

}

#endif

