#include <server.h>

server_hnd_t server_hnd;

void server_init(uint8_t p_count, uint16_t port)
{

}

void server_handle()
{
//update_game_state(&server_hnd.state);

for(uint8_t i=0;i<server_hnd.client_count;++i)
{
SDLNet_SocketReady(server_hnd.client_handles[i].socket);

}
}
