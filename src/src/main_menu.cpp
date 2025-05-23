#include <main_menu.h>
#include <window.h>
#include <ui.h>

inline void handle_events()
{
    ui_frame();
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        handle_window(&event);
        handle_ui(&event);
    }
}


void main_menu_init()
{

}

void main_menu_update()
{
    handle_events();

    

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_RenderPresent(window_hnd.renderer);
}
