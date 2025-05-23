#include <main_menu.h>
#include <window.h>
#include <ui.h>

static sbutton_t play_b;

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

void aaaaaA()
{
printf("AAAAAAAAAAA\n");
}

void main_menu_init()
{
    play_b.onrelease = aaaaaA;
    play_b.rect={40,40,256,128};
}

void main_menu_update()
{
    handle_events();

    handle_sbutton(&play_b);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_SetRenderDrawColor(window_hnd.renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(window_hnd.renderer,&play_b.rect);

    SDL_RenderPresent(window_hnd.renderer);
}
