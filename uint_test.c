#include<stdio.h>
#include "client_list.h"

int main()
{
	char pList[1024] = {0};
	pClient client1 = (pClient)malloc(sizeof(Client));
	pClient client2 = (pClient)malloc(sizeof(Client));
	char *pIP = "10.25.15.235";
	char *pName = "nobody";
	pClient pClientx = NULL;

	memset(client1, 0, sizeof(Client));
	memcpy(client1->userName, "alcht", 5);
	memcpy(client1->IP, "10.25.15.235", 12);

	memset(client2, 0, sizeof(Client));
	memcpy(client2->userName, "nobody", 6);
	memcpy(client2->IP, "10.25.15.23", 11);

	CL_clientListInit();
	CL_addClient(client1);
	CL_addClient(client2);
	CL_listClients(pList);
	printf("Clients list: \n%s\n", pList);

	CL_getClientbyUserName(pName, pClientx);
	if(pClientx == NULL)
	{
		printf("NULL \n");
	}
	else
	{
		printf("get Client: \n%s : %s\n", pClientx->userName, pClientx->IP);
	}
	/*delete client by item */
	memset(pList, 0, sizeof(pList));
	printf("Clients delete: %s\n", pIP);
	CL_deleteClientbyItem(CLINET_ITEM_IP_TYPE, pIP);
	CL_listClients(pList);

	memset(pList, 0, sizeof(pList));
	printf("Clients delete: %s\n", pName);
	CL_deleteClientbyItem(CLINET_ITEM_USERNAME_TYPE, pName);
	CL_listClients(pList);

	return 0;
}