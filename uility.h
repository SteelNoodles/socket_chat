#ifndef _UILITY_H_
#define _UILITY_H_

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "public_type.h"


typedef struct 
{
	uint16 len;
	uint16 index;
	uint8* data;
}paramData;



int paramGetDataVal(paramData* data, uint8* val, uint16 length);
int paramGet8bitVal(paramData* data, uint8* val);
int paramGet16bitVal(paramData* data, uint16* val);
int paramSetDataVal(paramData* data, const uint8* val, uint16 length);
int paramSet8bitVal(paramData* data, uint8 val);
int paramSet16bitVal(paramData* data, uint16 val);
int msgGet8bitVal(uint8* msg, uint8 * val);
int msgGetDataVal(uint8* msg, uint8* val, uint16 len);
int msgGet16bitVal(uint8* msg, uint8* val);
int msgSet8bitVal(uint8* msg, uint8 val);
int msgSet16bitVal(uint8* msg, uint16 val);
int msgSetDataVal(uint8* msg, uint8* val, uint16 len);
unsigned char* findDevice(unsigned char* device);
int getLocalIPByIoctl(unsigned char* pDeviceIP);

#endif 