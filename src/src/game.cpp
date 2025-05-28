#include <server/server.h>
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

}


}


void game_update()
{
handle_events();


}