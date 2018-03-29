#ifndef _CLIENT_LIST_H
#define _CLIENT_LIST_H
#include <stdio.h>
#include <string.h>


typedef struct _CLIENT_INFO
{
	char userName[20];
	char IP[20];
	struct _CLIENT_INFO *next;
}Client, *pClient;

typedef enum
{
	CLINET_ITEM_USERNAME_TYPE,
	CLINET_ITEM_IP_TYPE	
}Client_item_type;

void CL_clientListInit();

int CL_addClient(pClient client);

int CL_deleteClientbyItem(Client_item_type type, char *item);

int CL_getClientbyUserName(char *userName, pClient client);

int CL_listClients(char * clientList);




#endif