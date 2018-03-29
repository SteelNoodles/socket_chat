#ifndef 	_SOCKET_SERVER_H
#define    	_SOCKET_SERVER_H
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>


typedef enum
{
	MSG_TYPE_REGISTER_REQ,
	MSG_TYPE_SIGN_IN_REQ,
	MSG_TYPE_ONLINE_MSG_REQ,
	MSG_TYPE_MESSAGE
}MSG_type;


typedef struct _USER_INFO_
{
	unsigned int userID;
	char userName[20];
	char passWord[20];
	unsigned long addr;
}USER_INFO;
#endif