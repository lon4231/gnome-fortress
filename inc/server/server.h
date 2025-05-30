#ifndef _SERVER_DEFINED_
#define _SERVER_DEFINED_

#include <headers.h>
#include <server/gstate.h>
#include <server/net_routines.h>

#define MAX_CLIENTS 32

struct client_handle_t
{
    IPaddress client_addr;
    TCPsocket client_socket;
};

struct server_state_t
{
    IPaddress server_addr;
    TCPsocket server_socket;
    uint32_t client_count;
    client_handle_t clients[MAX_CLIENTS];
};

struct server_state_packet_t
{
};

extern server_state_t srv_state;

void init_server(uint16_t port);
void handle_server();

#endif