#ifndef _CLIENT_FUCKSHITFUCK_DEFINED
#define _CLIENT_FUCKSHITFUCK_DEFINED

#include <game_server.h>
#include <net_routines.h>

struct client_hnd_t
{
    SDLNet_SocketSet set;
    TCPsocket socket;
    IPaddress addr;
};

extern client_hnd_t client_handle;

#endif