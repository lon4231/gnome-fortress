#include <server/server.h>

static bool srv_initialized=false;
server_state_t srv_state;

void init_server(uint16_t port)
{
if(srv_initialized==false)
{
if(SDLNet_ResolveHost(&srv_state.server_addr,NULL,port)==-1)
{
printf("UNABLE TO RESOLVE HOST, FUCKER!: %s\r\n",SDLNet_GetError());
return;
}

srv_state.server_socket=SDLNet_TCP_Open(&srv_state.server_addr);
if(srv_state.server_socket==nullptr)
{
printf("COULDN'T OPEN TCP SERVER, IDIOT!: %s\r\n",SDLNet_GetError());
return;
}

srv_initialized=true;
}
else
{
printf("SEVER ALREADY OPEN, DUMBASS!\r\n");
}
}