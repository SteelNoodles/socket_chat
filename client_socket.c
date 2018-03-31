#include "uility.h"
#include "client_socket.h"

#define _INT_PORT (8088)
#define MAX_SND_BUFFER_SIZE (1024)
#define MAX_MSG_BUFFER_SIZE (1020)

char snd_udp_buffer[MAX_SND_BUFFER_SIZE];
char message_buffer[MAX_MSG_BUFFER_SIZE];
int  sfd;
struct sockaddr_in saddr;
pthread_t sendPthread;
pthread_t recPthread;

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
		printf ("Fail to create clientRecMessage\n");
		return -1;
	}
	
}

int socketClientInit()
{
	saddr.sin_family = AF_INET; 
	saddr.sin_port   = htons(_INT_PORT);
	saddr.sin_addr.s_addr   = inet_addr("10.25.15.174");

	sfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(!sfd)
	{
		printf("Fail to create socket \n");
		return -1;
	}
	return 0;
}

int clientGetMessage()
{
	int 	result;
	char*   buff = snd_udp_buffer;
	unsigned int length = 0;

	memset(snd_udp_buffer, 0, MAX_SND_BUFFER_SIZE);
	memset(message_buffer, 0, MAX_MSG_BUFFER_SIZE);
	
	gets(message_buffer);
	if(strlen(message_buffer))
	{
		msgSet8bitVal(buff, MSG_TYPE_MESSAGE);
		length = length + 1;
		msgSet16bitVal(buff, strlen(message_buffer));
		length = length + 2;
		msgSet16bitVal(buff, message_buffer);
		length = length + strlen(message_buffer);

		printf("Message length: %d", strlen(message_buffer));
		result = sendto(sfd, snd_udp_buffer, length, 0, (struct sockaddr *)&saddr, sizeof(saddr));
		if(result == -1)
		{
			printf("Error: Fail to send message \n");
		}
		else
		{
			printf("send message: %s\n", snd_udp_buffer);
			printf("result %d\n", result);
		}
	}
	
}

int clientRecMessage()
{

}