#include <server/server.h>

server_hnd_t server_hnd;

void server_init(uint8_t p_count, uint16_t port)
{

}

void server_handle()
{
update_game_state(&server_hnd.state);

for(uint8_t i=0;i<server_hnd.client_count;++i)
{
routines_send_tcp(server_hnd.client_handles[i].socket,&server_hnd.state,sizeof(game_server_state_t));
}
}
