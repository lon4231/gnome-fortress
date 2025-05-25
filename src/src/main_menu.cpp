#include <main_menu.h>
#include <window.h>
#include <ui.h>
#include <main.h>
#include <rndr_routines.h>

static SDL_Texture *menu_bg;
static SDL_Texture *title;

static SDL_Texture *p_button_texture;
static SDL_Rect p_button_trect;
static sbutton_t p_button;

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

void play_button_action()
{
}

void play_button_hover()
{
    p_button_trect = {0, 64, 64, 32};
}

void play_button_press()
{
    p_button_trect = {0, 32, 64, 32};
}

void play_button_default()
{
    p_button_trect = {0, 0, 64, 32};
}

void main_menu_init()
{
    p_button_texture = routines_load_texture("assets/sprites/button.png");
    menu_bg = routines_load_texture("assets/sprites/absolutegnome.png");
    title = routines_load_texture("assets/sprites/main_title.png");

    p_button =
        {
            .rect = {400 - 64, 300 - 32, 128, 64},
            .onclick = play_button_press,
            .onrelease = play_button_action,
            .onhold = play_button_press,
            .onhover = play_button_hover,
            .noton = play_button_default,
        };
}

void draw_title()
{

    for (uint8_t i = 0; i < 14; ++i)
    {
        SDL_Rect temp_texture_rect = {i * 8, 0, 8, 8};
        SDL_Rect temp_rect = {(400-14*16) + i * 32,64+ sinf(((i*16)+SDL_GetTicks()*0.1)*DEG_TO_RAD)*8, 32, 32};
        
        SDL_SetTextureColorMod(title,128,128,128);
        SDL_RenderCopy(window_hnd.renderer, title, &temp_texture_rect, &temp_rect);

        temp_rect.x-=4;
        temp_rect.y-=4;

        SDL_SetTextureColorMod(title,255,255,255);
        SDL_RenderCopy(window_hnd.renderer, title, &temp_texture_rect, &temp_rect);
    }
}

void main_menu_update()
{
    handle_events();

    handle_sbutton(&p_button);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);
    SDL_RenderCopy(window_hnd.renderer, menu_bg, NULL, NULL);
    SDL_RenderCopy(window_hnd.renderer, p_button_texture, &p_button_trect, &p_button.rect);

    draw_title();

    SDL_SetRenderTarget(window_hnd.renderer, NULL);

    routines_draw_window();
}
