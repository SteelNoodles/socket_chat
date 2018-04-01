#ifndef _PUBLIC_TYPE_
#define _PUBLIC_TYPE_

typedef signed short int		int16;
typedef signed char				int8;
typedef unsigned short int		uint16;
typedef unsigned char			uint8;
typedef unsigned char			u8;
typedef unsigned int			uint32;	//
typedef unsigned short  		u16;


#define MAX_IP_ADDRESS_LENGTH	15
#define MAX_NAME_STRING_LENGTH	32

#define _INT_PORT (8088)
#define MAX_SND_BUFFER_SIZE (1024)
#define MAX_REC_BUFFER_SIZE (1000)

typedef enum
{
	MSG_TYPE_REGISTER_REQ,
	MSG_TYPE_SIGN_IN_REQ,
	MSG_TYPE_ONLINE_MSG_REQ,
	MSG_TYPE_MESSAGE
}MSG_type;

#endif