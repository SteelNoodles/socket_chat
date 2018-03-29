#ifndef 	_SERVER_TASK_H_
#define    	_SERVER_TASK_H_
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "uility.h"


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

int msgServerRegister(param_data *param);
int msgServerSignIN(param_data *param);

#endif