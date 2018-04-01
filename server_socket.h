#ifndef		_SERVER_SOCKET_H_
#define		_SERVER_SOCKET_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "uility.h"




typedef struct _USER_INFO_
{
	unsigned int userID;
	char userName[20];
	char passWord[20];
	unsigned long addr;
}USER_INFO;

/**error code define**/
#define OK 					 0
#define ERROR_PARAM_ILLEGAL  1
#define ERROR_STATUS_ILLEGAL 2
/**error code define end**/

void recMessageHandler();
int msgServerHandler(uint8* message);
int msgServerRegister(uint8* message);
int msgServerSignIN(uint8* message);
uint8 addrIsInvalid(uint8* address, uint16 length);
uint8 sendMessageToDest(uint8* addr, uint16 addrLength, uint8* message, uint16 msgLength);

#endif