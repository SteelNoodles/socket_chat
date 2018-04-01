#include "uility.h"
#include "client_socket.h"


uint8 snd_msg_buffer[MAX_SND_BUFFER_SIZE];
uint8 rec_msg_buffer[MAX_REC_BUFFER_SIZE];
int  sfd;
struct sockaddr_in saddr;
struct sockaddr_in caddr;
struct sockaddr_in dAddr;
pthread_t sendPthread;
pthread_t recPthread;

// typedef struct{
// `	
// };

int main(int argc, char *arg[])
{
	int  result = 0;
	char *msg;

	result = socketClientInit();
	if(result != 0)
	{
		printf ("Fail to init socket\n");
		return -1;
	}

	pthread_create(&recPthread, NULL, (void*)(clientRecMessage), NULL);
	if(recPthread < 0)
	{
		printf ("Fail to create clientRecMessage\n");
		return -1;
	}

	pthread_create(&sendPthread, NULL, (void*)(clientGetMessage), NULL);
	if(sendPthread < 0)
	{
		printf ("Fail to create clientGetMessage\n");
		return -1;
	}

	while(1)
	{

	}
	
}

int socketClientInit()
{
	uint8 localAddr[MAX_IP_ADDRESS_LENGTH+1] ={0};
	uint8 result = 0;

	/*Init local socket */
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family = AF_INET; 
	saddr.sin_port   = htons(_INT_PORT);

	getLocalIPByIoctl(localAddr);
	saddr.sin_addr.s_addr   = inet_addr(localAddr);

	sfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(!sfd)
	{
		printf("Fail to create socket \n");
		return -1;
	}

	result = bind(sfd, (struct sockaddr*)(&saddr), sizeof(struct sockaddr_in));
	if(result != 0)
	{	
		printf("Fail to bind socket\n");
		return 1;
	}

	/*destination Init*/
	memset(&dAddr, 0, sizeof(struct sockaddr_in));
	dAddr.sin_family = AF_INET; 
	dAddr.sin_port   = htons(_INT_PORT);
	dAddr.sin_addr.s_addr   = inet_addr("10.25.15.174");

	/*recieve socket Init*/
	memset(&caddr, 0, sizeof(struct sockaddr_in));
	
	return 0;
}

int clientGetMessage()
{
	int 	result;
	char*   buff = snd_msg_buffer;
	unsigned int length = 0;
	uint8*	destAddr = inet_ntoa(dAddr.sin_addr);

	while(1)
	{
		length = 0;
		memset(snd_msg_buffer, 0, MAX_SND_BUFFER_SIZE);
		memset(rec_msg_buffer, 0, MAX_REC_BUFFER_SIZE);
		
		gets(rec_msg_buffer);
		if(strlen(rec_msg_buffer))
		{
			msgSet8bitVal(buff+length, MSG_TYPE_MESSAGE);
			length = length + 1;
			//printf("%s\n", snd_msg_buffer);
			msgSet16bitVal(buff+length, strlen(destAddr));
			length = length + 2;
			msgSetDataVal(buff+length, destAddr, strlen(destAddr));
			length = length + strlen(destAddr);
			msgSet16bitVal(buff+length, strlen(rec_msg_buffer));
			length = length + 2;
			msgSetDataVal(buff+length, rec_msg_buffer, strlen(rec_msg_buffer));
			length = length + strlen(rec_msg_buffer);

			result = sendto(sfd, snd_msg_buffer, length, 0, (struct sockaddr *)&dAddr, sizeof(dAddr));
			if(result == -1)
			{
				printf("Error: Fail to send message \n");
			}
		}
	}
}

uint8 clientRecMessage()
{
	uint8 reslut = 0;
	uint16 length = 0;
	uint16 clen = 0;

	memset(rec_msg_buffer, 0, MAX_REC_BUFFER_SIZE);
	while(1)
	{
		length = recvfrom(sfd, rec_msg_buffer, MAX_REC_BUFFER_SIZE, 0, (struct sockaddr *)(&caddr), &clen);
		if(length > 0)
		{
			clientMessageHandler();
		}
	}
}

uint8 clientMessageHandler()
{
	uint8 messageType = 0;
	uint8* message = rec_msg_buffer;

	msgGet8bitVal(message, &messageType);
	switch(messageType)
	{
		case MSG_TYPE_MESSAGE:
		{
			messagePrase(message);
			break;
		}
		default:
		{
			break;
		}
	}
}

uint8 messagePrase(uint8* message)
{
	uint16 IPLength = 0;
	uint8 addrString[MAX_IP_ADDRESS_LENGTH+1] = {0};
	uint16 msgLength = 0;
	uint8* msg = NULL;

	msgGet16bitVal(message, &IPLength);
	if(IPLength <= 0)
	{
		printf("Illegal param\n");
		return 1;
	}
	msgGetDataVal(message, addrString, IPLength);
	printf("Recieve message from: %s\n", addrString);

	msgGet16bitVal(message, &msgLength);
	if(msgLength <= 0)
	{
		printf("Illegal param\n");
		return 1;
	}
	msg = (uint8*)malloc(msgLength);
	if(msg == NULL)
	{
		printf("Fail to create messgae memory\n");
		return 1;
	}
	msgGetDataVal(message, msg, msgLength);
	printf("Message: %s\n", msg);

	return 0;

}