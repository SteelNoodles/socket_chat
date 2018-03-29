#include "server_task.h"



/**error code define**/
#define OK 					 0
#define ERROR_PARAM_ILLEGAL  1
#define ERROR_STATUS_ILLEGAL 2
/**error code define end**/

int msgServerHandler(param_data *param)
{
	uint8 messageType = 0;
	int result = 0;

	paramGet8bitVal(param, &messageType);
	switch(messageType)
	{
		case MSG_TYPE_REGISTER_REQ:
		{
			msgServerRegister(param);
			break;
		}
		case MSG_TYPE_SIGN_IN_REQ:
		{
			msgServerSignIN(param);
			break;
		}
		case MSG_TYPE_ONLINE_MSG_REQ:
		{

		}
		case MSG_TYPE_MESSAGE:
		{
			msgServerSendMessage(param);
		}
		default:
		{
			return ERROR_PARAM_ILLEGAL;
		}
	}
}


int msgServerRegister(param_data *param)
{
	return 0;
}

int msgServerSignIN(param_data *param)
{
	pClient newClient = (pClient)malloc(sizeof(Client));

	memset(newClient, 0, sizeof(Client));
	paramGetDataVal(param, newClient->userName, 20);
	paramGetDataVal(param, newClient->IP, 20);

	CL_addClient(newClient);
	return 0;
}

int msgServerSendMessage(param_data *param)
{
	uint16	IPLength = 0;
	uint16	msgLength = 0;
	uint8	destIP[20] = {0};
	uint8*	pMessage = NULL;

	paramGet16bitVal(param, &IPLength);
	paramGetDataVal(param, &destIP[0], IPLength);
	paramGet16bitVal(param, &msgLength);

	if(msgLength > 0)
	{
		pMessage = (uint8*)malloc(msgLength+1);
	}
	if(pMessage != NULL)
	{
		paramGetDataVal(param, pMessage);
	}

	if(1 == addrIsInvalid(destIP, IPLength))
	{
		return 1;
	}

	sendMessageToDest(destIP, IPLength, pMessage, msgLength);

	free(pMessage);
	pMessage = NULL;
	return 0;
}

uint8 addrIsInvalid(uint8* address, uint8 length)
{
	uint8 result = 0;
	uint8 invalidAddr[MAX_IP_ADDRESS_LENGTH+1] = {0};

	if(address == NULL)
	{
		return 1;
	}
	if(0 == memcmp(invalidAddr, address, length))
	{
		return 1;
	}
	return 0;
}

uint8 sendMessageToDest(uiint8* addr, uint16 addrLength, uint8* message, uint16 msgLength)
{
	param_data param = {0};
	uint16	length = msgLength + sizeof(uint16);
	uiint8	result = 0;

	param->data = (uint8*)malloc(length);
	paramSet16bitVal(param, msgLength);
	paramSetDataVal(param, message, msgLength);

	result = socketSendMsg2Client(addr, addrLength, &param);
	return 0;
}