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

int msgServerHandler(uint8* message);

#endif