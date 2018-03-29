#include "client_list.h"


pClient head = NULL;

void CL_clientListInit()
{
	head = (pClient)malloc(sizeof(Client));
	head->next = NULL;
}

int CL_addClient(pClient client)
{
	client->next = head->next;
	head->next = client;
	return 0;
}

int CL_deleteClientbyItem(Client_item_type type, char *item)
{
	pClient current = head->next;
	pClient previous = head;
	if(item == NULL)
	{
		printf("illegal param\n");
		return -1;
	}
	if(type == CLINET_ITEM_USERNAME_TYPE)
	{
		while(current != NULL)
		{
			if(0 == memcmp(current->userName, item, strlen(item)))
			{
				printf("match the client userName.\n");
				previous->next = current->next;
				free(current);
				current = NULL;
				return 0;
			}
			previous = current;
			current = current->next;
		}
		printf("Fail to match client userName\n");
		return -1;
	}
	else if(type == CLINET_ITEM_IP_TYPE)
	{
		while(current != NULL)
		{
			if(0 == memcmp(current->IP, item, strlen(item)))
			{
				printf("match the client IP.\n");
				previous->next = current->next;
				free(current);
				current = NULL;
				return 0;
			}
			previous = current;
			current = current->next;
		}
		printf("Fail to match client IP\n");
		return -1;
	}
	printf("Fail to match client\n");
	return -1;
}

int CL_getClientbyUserName(char *userName, pClient client)
{
	pClient current = head->next;
	pClient previous = head;

	// if(client == NULL ||userName == NULL)
	// {
	// 	printf("Illegal param\n");
	// 	return -1;
	// }

	while(current != NULL)
	{
		if(0 == memcmp(current->userName, userName, strlen(userName)))
		{
			printf("match the client userName.\n");
			client = current;
			printf("get Client: \n%s : %s\n", client->userName, client->IP);
			if(client == NULL)
			{
				printf("11111 NULL \n");
			}
			return 0;
		}
		current = current->next;
	}
	printf("Fail to find client\n");
	return -1;
}

int CL_getClientbyIP(char *ip, pClient client)
{
	pClient current = head->next;
	pClient previous = head;

	if(client == NULL ||ip == NULL)
	{
		printf("Illegal param\n");
		return -1;
	}

	while(current != NULL)
	{
		if(0 != memcmp(current->IP, ip, strlen(ip)))
		{
			printf("match the client userName.\n");
			client = current;
			return 0;
		}
		current = current->next;
	}
	printf("Fail to find client\n");
	return -1;
}


int CL_listClients(char * clientList)
{
	char* clinetInfo = NULL;
	pClient pstr = head->next;
	unsigned int index = 0;

	if(clientList == NULL)
	{
		printf("Illegal param\n");
		return -1;
	}

	clinetInfo = clientList;

	while((pstr != NULL))
	{
		unsigned int length = strlen(pstr->userName)+strlen(pstr->IP)+2;
		if(index + length < 1023)
		{
			//printf("userName: %s\n", pstr->userName);
			strcat(clinetInfo + index, pstr->userName);
			index = index + strlen(pstr->userName);
			strcat(clinetInfo, ":");
			index = index + 1;
			//printf("userName: %s\n", pstr->IP);
			strcat(clinetInfo + index, pstr->IP);
			index = index + strlen(pstr->IP);
			strcat(clinetInfo, "\n");
			index = index + 1;
			pstr = pstr->next;
		}
		else
		{
			printf("max length of Clinet INFO\n");
			return -1;
		}
	}
	return 0;
}