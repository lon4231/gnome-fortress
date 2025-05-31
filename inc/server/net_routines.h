#ifndef _NET_ROUTINES_DEFINED_
#define _NET_ROUTINES_DEFINED_

#include <headers.h>

inline void routines_send_tcp(TCPsocket socket, void *buffer, uint32_t size)
{
    uint32_t net_size = SDL_SwapBE32(size);
    SDLNet_TCP_Send(socket, &net_size, 4);
    SDLNet_TCP_Send(socket, buffer, size);
}

inline void routines_recv_tcp(TCPsocket socket, void *buffer, uint32_t *size)
{
    uint32_t net_size;
    SDLNet_TCP_Recv(socket, &net_size, 4);
    *size = SDL_SwapBE32(net_size);
    SDLNet_TCP_Recv(socket, buffer, *size);
}

#endif
