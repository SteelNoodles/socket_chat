#ifndef _UILITY_H_
#define _UILITY_H_

#include <stdio.h>
#include "public_type.h"


typedef struct 
{
	uint16 len;
	uint16 index;
	uint8* data;
}param_data;

int paramGetDataVal(param* data, uint8* val, uint16 length);
int paramGet8bitVal(paramData* data, uint8* val);
int paramGet16bitVal(paramData* data, uint16* val);
int paramSetDataVal(paramData* data, const uint8* val, uint16 length);
int paramSet8bitVal(paramData* data, uint8 val);
int paramSet16bitVal(paramData* data, uint16 val);

#endif 