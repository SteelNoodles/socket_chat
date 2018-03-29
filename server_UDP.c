#include "server_UDP.h"

typedef struct 
{
	unsigned int param_len;
	unsigned int param_index;
	unsigned char *data;
}param_data;

/**error code define**/
#define OK 					 0
#define ERROR_PARAM_ILLEGAL  1
#define ERROR_STATUS_ILLEGAL 2
/**error code define end**/

int MSGServerHandler(param_data *param)
{
	unsigned int messageType = param->data[0];
	int result = 0;
	switch(messageType)
	{
		case MSG_TYPE_REGISTER_REQ:
		{
			userServerRegister(param);
		}
		case MSG_TYPE_SIGN_IN_REQ:
		{
			
		}
		case MSG_TYPE_ONLINE_MSG_REQ:
		{

		}
		case MSG_TYPE_MESSAGE:
		{

		}
		default:
		{
			return ERROR_PARAM_ILLEGAL;
		}
	}
}


int userServerRegister(param_data *param)
{

}