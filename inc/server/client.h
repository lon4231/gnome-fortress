#ifndef _CLIENT_FUCKSHITFUCK_DEFINED
#define _CLIENT_FUCKSHITFUCK_DEFINED

#include <game_server.h>
#include <server.h>

extern IPaddress client_ip;
extern TCPsocket client_socket;

extern uint32_t client_id;
extern char*client_name;

inline void client_send_request(TCPsocket sock, DATA_REQUEST_TYPE request_type, void *ret_buff)
{
    printf("sent request: %d\r\n",request_type);
    data_request_t request = {request_type};

    SDLNet_TCP_Send(sock, &request, sizeof(data_request_t));

    switch (request_type)
    {
    case DATA_REQUEST_STATE:
        SDLNet_TCP_Recv(sock, ret_buff, sizeof(game_server_state_t));
        break;

    case DATA_REQUEST_READY:
    
        break;

    default:
        break;
    }
}

void init_client(const char *host,const char*name);
void handle_client();

#endif