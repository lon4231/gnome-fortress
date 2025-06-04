#include <client.h>

IPaddress client_ip;
TCPsocket client_socket;



void init_client(const char*host)
{
SDLNet_ResolveHost(&client_ip,host,0xB00B);
client_socket=SDLNet_TCP_Open(&client_ip);



}

void handle_client()
{

}
