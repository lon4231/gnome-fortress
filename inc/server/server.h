#ifndef _SERVER_DEFINED_FUCK_
#define _SERVER_DEFINED_FUCK_

#include <headers.h>
#include <game_server.h>

struct client_hnd_t
{
    SDLNet_SocketSet set;
    TCPsocket socket;
    IPaddress addr;
};

struct server_hnd_t
{
    SDLNet_SocketSet server_set;
    TCPsocket server_socket;
    IPaddress server_addr;

    game_server_state_t state;

    uint8_t client_count;
    client_hnd_t client_handles[MAX_CLIENTS];
};

extern server_hnd_t server_hnd;

void server_init(uint8_t p_count, uint16_t port);
void server_handle();

#endif