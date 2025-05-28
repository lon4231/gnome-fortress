#include <server/client.h>

client_data_t client_data;

void init_client(const char*addr,uint16_t port)
{
if(SDLNet_ResolveHost(&client_data.server_addr,addr,port)==-1)
{
printf("CLIENT COULD NOT RESOLVE HOST, HOMELESS GUY!\r\n");
}

//client_data.server_socket

client_data.server_socket=SDLNet_TCP_Open(&client_data.server_addr);
if(!client_data.server_socket)
{
printf("CLIENT COULD NOT CONNECT TO SERVER\r\n");
}

}


void handle_client()
{

}