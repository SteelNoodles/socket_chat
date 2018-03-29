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

#include "server_socket.h"

#define MAX_REC_BUFF_SIZE	1024
uint8	recMsgBuff[MAX_REC_BUFF_SIZE];
struct 	sockaddr_in serverAddr;
struct  sockaddr_in clientAddr;
int 	sfd;
pthread_t spthread;	


uint8 socketServerInit()
{
	int result = 0;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port	  = htons(8088);


	sfd = socket(PF_INET, SOCKDGRAM, IPPROTOL_UDP);
	if(sfd < 0)
	{
		printf("Fail to create socket\n");
		return 1;
	}

	result = bind(sfd, (struct sockaddr*)serverAddr, sizeof(struct sockaddr_in));
	if(result < 0)
	{
		printf("Fail to bind socket\n");
		closesocket(sfd);
		return 1;
	}

	result = pthread_create(&sin_port, NULL, (void*)recMessageHandler, NULL):
	if()
	{
		printf("Fail to create thread\n");
		closesocket(sfd);
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
		memset(recMsgBuff, 0, MAX_REC_BUFF_SIZE);
		length = recvfrom(sfd, recMsgBuff, 0, &clientAddr, &addrlen);
		if(length > 0)
		{
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
	messageType = 
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