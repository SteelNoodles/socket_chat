#ifndef	_CLIENT_SOCKET_H_
#define	_CLIENT_SOCKET_H_

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>


int clientSendMessage();
uint8 clientMessageHandler();
uint8 messagePrase(uint8* message);
uint8 clientRecMessage();
int clientGetMessage();
int socketClientInit();


#endif