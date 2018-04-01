#include "server_socket.h"
#include "client_list.h"


#define MAX_BUFF_SIZE	1024
uint8	recMsgBuff[MAX_BUFF_SIZE];
uint8   sendMsgBuff[MAX_BUFF_SIZE];
struct 	sockaddr_in serverAddr;
struct  sockaddr_in clientAddr;
int 	sfd;
pthread_t spthread;	


uint8 socketServerInit()
{
	int result = 0;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port	  = htons(8088);


	sfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sfd < 0)
	{
		printf("Fail to create socket\n");
		return 1;
	}

	result = bind(sfd, (struct sockaddr*)(&serverAddr), sizeof(struct sockaddr_in));
	if(result < 0)
	{
		printf("Fail to bind socket\n");
		//closesocket(sfd);
		return 1;
	}

	result = pthread_create(&spthread, NULL, (void*)recMessageHandler, NULL);
	if(result < 0)
	{
		printf("Fail to create thread\n");
		//closesocket(sfd);
		return 1;
	}
	return 0;
}
// int sendto(int sockfd, void *msg, int len, unsigned int flags, const struct sockaddr *to, int tolen);
uint8 socketServerMsgSend2Client(uint8* addr, uint16 addrLength)
{
	uint16 length = 0;
	struct sockaddr_in clAddr;

	memset(&clAddr, 0, sizeof(struct sockaddr_in));
	clAddr.sin_family = AF_INET;
	clAddr.sin_port = htons(8808);
	clAddr.sin_addr.s_addr = inet_addr(addr); 

	length = sendto(sfd, sendMsgBuff, strlen(sendMsgBuff), 0, (struct sockaddr*)(&clAddr), sizeof(struct sockaddr_in));
	if(length < 0)
	{
		printf("Fail to send message to: %s\n", addr);
		return 1;
	}
	return 0;
}
// int recfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);

void recMessageHandler()
{
	uint16 length = 0;
	uint16 addrLen = 0;

	
	while(1)
	{
		memset(recMsgBuff, 0, MAX_BUFF_SIZE);
		length = recvfrom(sfd, recMsgBuff, MAX_BUFF_SIZE, 0, &clientAddr, &addrLen);
		if(length > 0)
		{
			printf("get message from: %s\n", inet_ntoa(clientAddr.sin_addr));
			msgServerHandler(recMsgBuff);
		}
	}
}

int msgServerHandler(uint8* message)
{
	uint8 messageType = 0;
	uint8 *msg = message;
	int result = 0;

	//paramGet8bitVal(param, &messageType);
	if((msgGet8bitVal(msg, &messageType)) == 0)
	{
		printf("message type: %d\n", messageType);
		switch(messageType)
		{
			case MSG_TYPE_REGISTER_REQ:
			{
				result = msgServerRegister(msg);
				break;
			}
			case MSG_TYPE_SIGN_IN_REQ:
			{
				result = msgServerSignIN(msg);
				break;
			}
			case MSG_TYPE_ONLINE_MSG_REQ:
			{
				break;
			}
			case MSG_TYPE_MESSAGE:
			{
				result = msgServerSendMessage(msg);
				break;
			}
			default:
			{
				result = ERROR_PARAM_ILLEGAL;
				break;
			}
		}
	}
	return result;
}

int msgServerRegister(uint8* message)
{
	return 0;
}

int msgServerSignIN(uint8* message)
{
	uint16 nameLength = 0;
	uint16 IPLength = 0;
	pClient newClient = (pClient)malloc(sizeof(Client));

	memset(newClient, 0, sizeof(Client));
	msgGet16bitVal(message, &nameLength);
	msgGetDataVal(message, newClient->userName, nameLength);
	msgGet16bitVal(message, &IPLength);
	msgGetDataVal(message, newClient->IP, IPLength);

	CL_addClient(newClient);
	return 0;
}

int msgServerSendMessage(uint8* message)
{
	uint16	IPLength = 0;
	uint16	msgLength = 0;
	uint8	destIP[20] = {0};
	uint8*	pMessage = NULL;
	uint16	index = 1;

	msgGet16bitVal(message+index, &IPLength);
	index = index + 2;
	msgGetDataVal(message+index, &destIP[0], IPLength);
	index = index + IPLength;
	msgGet16bitVal(message+index, &msgLength);
	index = index + 2;

	printf("IPLength :%d\n", IPLength);
	printf("IP: %s\n",destIP );
	printf("msgLength :%d\n", msgLength);

	if(msgLength > 0)
	{
		pMessage = (uint8*)malloc(msgLength+1);
	}
	if(pMessage != NULL)
	{
		memset(pMessage, 0, msgLength+1);
		msgGetDataVal(message+index, pMessage, msgLength);
	}

	if(1 == addrIsInvalid(destIP, IPLength))
	{
		return 1;
	}
	printf("Message :%s\n", pMessage);
	sendMessageToDest(destIP, IPLength, pMessage, msgLength);

	free(pMessage);
	pMessage = NULL;
	return 0;
}

uint8 addrIsInvalid(uint8* address, uint16 length)
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

uint8 sendMessageToDest(uint8* addr, uint16 addrLength, uint8* message, uint16 msgLength)
{
	uint8* buff = sendMsgBuff;
	uint16 index = 0;
	if((addr != NULL) && (message != NULL))
	{
		uint8* fromAddr = inet_ntoa(clientAddr.sin_addr);

		msgSet8bitVal(buff+index, MSG_TYPE_MESSAGE);
		index = index + 1;
		/*set Msg From addr*/
		msgSet16bitVal(buff, strlen(fromAddr));
		index = index + 2;
		msgSetDataVal(buff, fromAddr, strlen(fromAddr));
		index = index + strlen(fromAddr);

		msgSet16bitVal(buff, msgLength);
		index = index + 2;
		msgSetDataVal(buff, message, msgLength);
		index = index + msgLength;
		socketServerMsgSend2Client(addr, addrLength);
	}
	return 1;
}


int main()
{
	socketServerInit();
	while(1)
	{

	}
	return 0;
}

// struct sockaddr
// {
// 	unsigned short sa_family;
// 	char sa_data[14];
// };

// struct sockaddr_in
// {
// 	short int 			sin_family;
// 	unsigned short int  sin_port;	
// 	struct in_addr		sin_addr;
// 	unsigned char 		sin_zero[8];
// };

// struct in_addr
// {
// 	unsigned long s_addr;
// };

// related socket functions  
// int socket(int domain, int type, int protocol);
// int bind(int sockfd, struct sockaddr * my_addr, int addrlen);
// int connect(int sockfd, struct sockaddr serv_addr, int addrlen);
// int listen(int sockfd, int backlog);
// int accept(int sockfd, void *addr, int *addrlen);
// int send(int sockfd, void *msg, int len, int flags);
// int recv(int sockfd, void *buf, int len, unsigned int flags);
// int sendto(int sockfd, void *msg, int len, unsigned int flags, const struct sockaddr *to, int tolen);
// int recfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);
