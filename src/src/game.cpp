#include <server/server.h>
#include <server/client.h>
#include <game.h>
#include <main_menu.h>


bool is_hosting_flag;

inline void handle_events()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        handle_window(&event);
    };
}


void init_game()
{
if(is_hosting_flag==true)
{
init_server(atoi(game_init_data.port));
}
else
{
init_client(game_init_data.ip,atoi(game_init_data.port));
}


}


void game_update()
{
handle_events();

if(is_hosting_flag==true)
{
handle_server();
}

handle_client();

}