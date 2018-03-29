#include<uility.h>

int paramGetDataVal(param* data, uint8* val, uint16 length)
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