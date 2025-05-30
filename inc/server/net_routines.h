#ifndef _NET_ROUTINES_DEFINED_
#define _NET_ROUTINES_DEFINED_

#include <headers.h>

inline void routines_send_tcp(TCPsocket socket, void *buffer, uint32_t size)
{
    SDLNet_TCP_Send(socket, &size, 4);
    SDLNet_TCP_Send(socket, buffer, size);
}

inline void routines_recv_tcp(TCPsocket socket, void *buffer, uint32_t size)
{
    SDLNet_TCP_Recv(socket, &size, 4);
    SDLNet_TCP_Recv(socket, buffer, mmin(size,size));
}

#endif
