#ifndef _NET_ROUTINES_DEFINED_
#define _NET_ROUTINES_DEFINED_

#include <headers.h>

struct request_header_t
{
    void *ptr;
    uint32_t size;
};

inline void request_data_from_ptr(TCPsocket socket, void *ptr, void *buffer, uint32_t size)
{
    request_header_t request = {ptr, size};

    SDLNet_TCP_Send(socket, &request, sizeof(request_header_t));

    uint32_t recieved=0;

    while (recieved!=size)
    {
        recieved+=SDLNet_TCP_Recv(socket,buffer,1);
    }
    

}

inline void handle_data_request(TCPsocket socket)
{
    request_header_t request;
    SDLNet_TCP_Recv(socket, &request, sizeof(request_header_t));
    SDLNet_TCP_Send(socket, request.ptr, request.size);
}

#endif
