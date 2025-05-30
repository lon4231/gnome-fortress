#ifndef _CLIENT_DEFINED_
#define _CLIENT_DEFINED_

#include <headers.h>
#include <server/gstate.h>

enum SERVER_RECV_TYPE
{
    RECV_TYPE_INIT_DATA,
    RECV_TYPE_GLOBAL_STATE,
};

enum SERVER_SEND_TYPE
{
    SEND_TYPE_POST,
    SEND_TYPE_STATUS_UPDATE,
};

struct server_recv_t
{
    uint32_t data_type;
    uint32_t data_size;
};

struct client_data_t
{
    IPaddress server_addr;
    TCPsocket server_socket;
};

extern client_data_t client_data;

void init_client(const char *addr, uint16_t port);
void handle_client();

#endif