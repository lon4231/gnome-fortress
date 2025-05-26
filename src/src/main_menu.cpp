#include <main_menu.h>
#include <window.h>
#include <ui.h>
#include <main.h>
#include <rndr_routines.h>
#include <keyboard.h>

struct menu_data_t
{
    SDL_Texture *menu_bg;
    SDL_Texture *title_texture;
    SDL_Texture *p_button_texture;
    SDL_Rect p_button_trect;
    ui_button_t p_button;

    SDL_Texture *demo_text;

    ui_text_input_t ip_input;
    ui_text_input_t port_input;

    SDL_Rect join_button_trect;
    ui_button_t join_button;
    SDL_Rect host_button_trect;
    ui_button_t host_button;
};

menu_data_t menu_data;

inline void handle_events()
{
    ui_frame();
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        handle_window(&event);
        handle_ui(&event);
    };
}

void play_button_action()
{
    play_menu_init();
    scene_fn_handle = play_menu_update;
}

void play_button_hover() { menu_data.p_button_trect.y = 64; }
void play_button_press() { menu_data.p_button_trect.y = 32; }
void play_button_default() { menu_data.p_button_trect.y = 0; }

void draw_text_input(ui_text_input_t *text_input)
{
    if (text_input->selected)
    {
        SDL_SetRenderDrawColor(window_hnd.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(window_hnd.renderer, &text_input->rect);
    }
    else
    {
        SDL_SetRenderDrawColor(window_hnd.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(window_hnd.renderer, &text_input->rect);
    }
}

void main_menu_init()
{
    menu_data.menu_bg = routines_load_texture("assets/sprites/absolutegnome.png");
    menu_data.title_texture = routines_load_texture("assets/sprites/main_title.png");

    menu_data.p_button_texture = routines_load_texture("assets/sprites/button.png");
    menu_data.p_button =
        {
            .rect = {RENDER_TEXTURE_HW - 128, RENDER_TEXTURE_HH - 64, 256, 128},
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
        SDL_Rect temp_rect = {
            (RENDER_TEXTURE_HW - 14 * 16) + (i * 32) + (int)(cosf(((i * 16) + SDL_GetTicks() * 0.1) * DEG_TO_RAD) * 4),
            64 + (int)(sinf(((i * 16) + SDL_GetTicks() * 0.1) * DEG_TO_RAD) * 8),
            32,
            32};

        SDL_SetTextureColorMod(menu_data.title_texture, 128, 128, 128);
        SDL_RenderCopy(window_hnd.renderer, menu_data.title_texture, &temp_texture_rect, &temp_rect);

        temp_rect.x -= 4;
        temp_rect.y -= 4;

        SDL_SetTextureColorMod(menu_data.title_texture, 255, 255, 255);
        SDL_RenderCopy(window_hnd.renderer, menu_data.title_texture, &temp_texture_rect, &temp_rect);
    }
}

void main_menu_update()
{
    handle_events();

    handle_ui_button(&menu_data.p_button);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);
    SDL_RenderCopy(window_hnd.renderer, menu_data.menu_bg, NULL, NULL);
    SDL_RenderCopy(window_hnd.renderer, menu_data.p_button_texture, &menu_data.p_button_trect, &menu_data.p_button.rect);

    draw_title();

    SDL_SetRenderTarget(window_hnd.renderer, NULL);

    routines_draw_window();
}

void play_menu_init()
{
    menu_data.ip_input.rect = {0, 0, 128, 64};
    menu_data.ip_input.buffer = (char *)malloc(32 + 1);
    memset(menu_data.ip_input.buffer, 0, 32 + 1);
    menu_data.ip_input.buffer_index = 0;
    menu_data.ip_input.buffer_size = 32;

    menu_data.port_input.rect = {0, 64, 128, 64};
    menu_data.port_input.buffer = (char *)malloc(32 + 1);
    memset(menu_data.port_input.buffer, 0, 32 + 1);
    menu_data.port_input.buffer_index = 0;
    menu_data.port_input.buffer_size = 32;

    menu_data.host_button.rect={800-256,0,256,128};
    menu_data.join_button.rect={800-256,128,256,128};
    
    menu_data.host_button_trect={64,0,64,32};
    menu_data.join_button_trect={128,0,64,32};
}

void play_menu_update()
{
    handle_events();

    handle_ui_text_input(&menu_data.ip_input);
    handle_ui_text_input(&menu_data.port_input);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_RenderCopy(window_hnd.renderer, menu_data.menu_bg, NULL, NULL);

    draw_text_input(&menu_data.ip_input);
    draw_text_input(&menu_data.port_input);

    SDL_RenderCopy(window_hnd.renderer, menu_data.p_button_texture, &menu_data.host_button_trect, &menu_data.host_button.rect);
    SDL_RenderCopy(window_hnd.renderer, menu_data.p_button_texture, &menu_data.join_button_trect, &menu_data.join_button.rect);


    SDL_RenderCopy(window_hnd.renderer, menu_data.demo_text, NULL, NULL);

    SDL_SetRenderTarget(window_hnd.renderer, NULL);

    routines_draw_window();
}