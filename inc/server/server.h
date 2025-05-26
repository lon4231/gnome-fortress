#ifndef _SERVER_DEFINED_
#define _SERVER_DEFINED_

#include <headers.h>
#include <server/gstate.h>

#define MAX_CLIENTS 32

struct client_handle_t
{

};

struct server_state_t
{
IPaddress server_addr;
TCPsocket server_socket;

client_handle_t clients[MAX_CLIENTS];

};

extern server_state_t srv_state;

void init_server(uint16_t port);
void handle_server();

#endif