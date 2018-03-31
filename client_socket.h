#ifndef	_CLIENT_SOCKET_H_
#define	_CLIENT_SOCKET_H_

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

typedef enum
{
	MSG_TYPE_REGISTER_REQ,
	MSG_TYPE_SIGN_IN_REQ,
	MSG_TYPE_ONLINE_MSG_REQ,
	MSG_TYPE_MESSAGE
}MSG_type;

int clientSendMessage();

#endif