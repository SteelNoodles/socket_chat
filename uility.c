#include "uility.h"

#define DEVICE_NAME_LENGTH 5
#define DEVICE_IP_LENGTH   13

int paramGetDataVal(paramData* data, uint8* val, uint16 length)
{
	if((data->index+length)>data->len)
	{
		return -1;
	}
	memcpy(val, (uint8*)data->data[data->index], length);
	data->index = (uint16)(data->index + length);
	return 0;	
}

int paramGet8bitVal(paramData* data, uint8* val)
{
	if((data->index+1)>data->len)
	{
		return -1;
	}
	*val = data->data[data->index++];
	return 0;
}

int paramGet16bitVal(paramData* data, uint16* val)
{
	if((data->index+2)>data->len)
	{
		return -1;
	}
	*val = data->data[data->index++];
	*val = (uint16)(*val << 8);
	*val = (uint16)(*val | data->data[data->index++]);
	return 0;
}

int paramSetDataVal(paramData* data, const uint8* val, uint16 length)
{
	if(length > 0)
	{
		memcpy((&data->data[data->index]), val, length);
		data->index = (uint16)(data->index + length);
		data->len   = (uint16)(data->len + length);
		return 0;
	}
	return -1;
}

int paramSet8bitVal(paramData* data, uint8 val)
{
	data->data[data->index++] = val;
	data->len = (uint16)(data->len + 1);
	return 0;
}

int paramSet16bitVal(paramData* data, uint16 val)
{
	data->data[data->index++] = (uint8)(val >> 8);
	data->data[data->index++] = (uint8)(val & 0xFF);
	data->len = (uint16)(data->len + 2);
	return 0;
}

int msgGet8bitVal(uint8* msg, uint8 * val)
{
	uint16 index = 0;
	if(msg == NULL)
	{
		return -1;
	}
	*val = msg[index++];
	msg = msg+index;
	return 0;
}

int msgGetDataVal(uint8* msg, uint8* val, uint16 len)
{
	if(msg != NULL && val !=NULL)
	{
		if(len > 0)
		{
			memcpy(val, msg, len);
			msg = msg + len;
			return 0;	
		}
	}
	return -1;
}

int msgGet16bitVal(uint8* msg, uint8* val)
{
	if(msg != NULL && val != NULL)
	{
		*val = msg[0];
		*val = (uint16)((*val) << 8);
		*val = (uint16)((*val)|(msg[1]));
		msg = msg + 2;
		return 0;
	}
	return -1;
}

int msgSet8bitVal(uint8* msg, uint8 val)
{
	if(msg != NULL)
	{
		msg[0] = val;
		msg = msg + 1;
		return 0;
	}
	return -1;
}

int msgSet16bitVal(uint8* msg, uint16 val)
{
	if(msg != NULL)
	{
		msg[0] = (uint8)(val >> 8);
		msg[1] = (uint8)(val & 0xFF);
		msg = msg + 2;
	}
}

int msgSetDataVal(uint8* msg, uint8* val, uint16 len)
{
	if((msg != NULL)&&(val != NULL))
	{
		memcpy(msg, val, len);
		msg = msg + len;
	}
	return -1;
}


unsigned char* findDevice(unsigned char* device)
{
	
	int result = 0;
	FILE * fp = NULL;
	unsigned char* pDevice = device;

	result = system("ifconfig > /home/alcht/share/log.txt");
	if(result == 0)
	{
		fp = fopen("/home/alcht/share/log.txt", "r+");
		if(fp != NULL)
		{
			fgets(pDevice, DEVICE_NAME_LENGTH, fp);
			printf("Device: %s\n", pDevice);
		}
	}
	return pDevice;
}

int getLocalIPByIoctl(unsigned char* pDeviceIP)
{
	int inet_sock;
    struct ifreq ifr;
    unsigned char device[DEVICE_NAME_LENGTH] = {0};
    inet_sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(pDeviceIP == NULL)
    {
    	printf("Illegal param\n");
    	return -1;
    }
    /*get network device*/
    findDevice(device);
    strcpy(ifr.ifr_name, (unsigned char*)device);
    
    //SIOCGIFADDR标志代表获取接口地址
    if (ioctl(inet_sock, SIOCGIFADDR, &ifr) <  0)
    {
            perror("ioctl");
            return -1;
    }
    memcpy(pDeviceIP, inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr), DEVICE_IP_LENGTH);
    printf("%s\n", pDeviceIP);
    return 0;
}