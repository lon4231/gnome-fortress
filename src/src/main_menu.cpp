#include <main_menu.h>
#include <window.h>
#include <ui.h>
#include <main.h>
#include <rndr_routines.h>
#include <keyboard.h>
#include <assets.h>
#include <game.h>
#include <server.h>
#include <client.h>

struct menu_data_t
{
    SDL_Rect p_button_trect;
    ui_button_t p_button;

    ui_text_input_t ip_input;
    ui_text_input_t name_input;

    SDL_Rect join_button_trect;
    ui_button_t join_button;
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
    handle_keyboard();
}

void play_button_action()
{
    scene_fn_handle = play_menu_update;
}

void join_button_action()
{
    init_client(menu_data.ip_input.buffer);
    game_init();
    scene_fn_handle = game_update;
}

SDL_Texture **current_text_input_texture_handle;
ui_text_input_t *current_text_input;
void text_input_texture_update()
{
    if (current_text_input_texture_handle != NULL)
    {
        SDL_DestroyTexture(*current_text_input_texture_handle);
    }
    *current_text_input_texture_handle = routines_render_text_texture(current_text_input->buffer, {255, 255, 255, 255});
}

static SDL_Rect *buttons_rect_ptr;
void buttons_hover() { buttons_rect_ptr->y = 64; }
void buttons_press() { buttons_rect_ptr->y = 32; }
void buttons_default() { buttons_rect_ptr->y = 0; }

void draw_text_input(ui_text_input_t *text_input, SDL_Texture *text_texture)
{
    text_input->rect.w = mmax(strlen(text_input->buffer), 1) * 32;
    if (text_input->selected)
    {
        SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(window_hnd.renderer, &text_input->rect);
        SDL_RenderCopy(window_hnd.renderer, text_texture, NULL, &text_input->rect);
    }
    else
    {
        SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(window_hnd.renderer, &text_input->rect);
        SDL_RenderCopy(window_hnd.renderer, text_texture, NULL, &text_input->rect);
    }
}

void main_menu_init()
{

    menu_data.p_button_trect = {0, 0, 64, 32};
    menu_data.p_button =
        {
            .rect = {RENDER_TEXTURE_HW - 128, RENDER_TEXTURE_HH - 64, 256, 128},
            .onclick = buttons_hover,
            .onrelease = play_button_action,
            .onhold = buttons_press,
            .onhover = buttons_hover,
            .noton = buttons_default,
        };

    menu_data.ip_input = {
        .rect = {0, 0, 32, 32},
        .buffer = (char *)malloc(16 + 1),
        .buffer_index = 0,
        .buffer_size = 16,
        .oninput = text_input_texture_update,
    };
    memset(menu_data.ip_input.buffer, 0, 16 + 1);

    menu_data.name_input = {
        .rect = {0, 64, 32, 32},
        .buffer = (char *)malloc(8 + 1),
        .buffer_index = 0,
        .buffer_size = 8,
        .oninput = text_input_texture_update,
    };
    memset(menu_data.name_input.buffer, 0, 8 + 1);

    menu_data.join_button =
        {
            .rect = {800 - 256, RENDER_TEXTURE_HH, 256, 128},
            .onclick = buttons_hover,
            .onrelease = join_button_action,
            .onhold = buttons_press,
            .onhover = buttons_hover,
            .noton = buttons_default,
        };

    menu_data.join_button_trect = {128, 0, 64, 32};
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

        SDL_SetTextureColorMod(runtime_assets.title_texture, 128, 128, 128);
        SDL_RenderCopy(window_hnd.renderer, runtime_assets.title_texture, &temp_texture_rect, &temp_rect);

        temp_rect.x -= 4;
        temp_rect.y -= 4;

        SDL_SetTextureColorMod(runtime_assets.title_texture, 255, 255, 255);
        SDL_RenderCopy(window_hnd.renderer, runtime_assets.title_texture, &temp_texture_rect, &temp_rect);
    }
}

void main_menu_update()
{
    handle_events();

    if ((keyboard_hnd.kmap[SDL_SCANCODE_F11] == 1) && (keyboard_hnd.last_kmap[SDL_SCANCODE_F11] == 0))
    {
        window_hnd.fullscreen ^= 1;
        SDL_SetWindowFullscreen(window_hnd.window, window_hnd.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

    buttons_rect_ptr = &menu_data.p_button_trect;
    handle_ui_button(&menu_data.p_button);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);
    SDL_RenderCopy(window_hnd.renderer, runtime_assets.menu_bg, NULL, NULL);
    SDL_RenderCopy(window_hnd.renderer, runtime_assets.buttons_texture, &menu_data.p_button_trect, &menu_data.p_button.rect);

    draw_title();

    SDL_SetRenderTarget(window_hnd.renderer, NULL);

    routines_draw_window();
}

void play_menu_update()
{
    handle_events();

    if ((keyboard_hnd.kmap[SDL_SCANCODE_F11] == 1) && (keyboard_hnd.last_kmap[SDL_SCANCODE_F11] == 0))
    {
        window_hnd.fullscreen ^= 1;
        SDL_SetWindowFullscreen(window_hnd.window, window_hnd.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

    current_text_input = &menu_data.ip_input;
    current_text_input_texture_handle = &runtime_assets.ip_text_input_texture;
    handle_ui_text_input(&menu_data.ip_input);
    current_text_input = &menu_data.name_input;
    current_text_input_texture_handle = &runtime_assets.name_text_input_texture;
    handle_ui_text_input(&menu_data.name_input);

    buttons_rect_ptr = &menu_data.join_button_trect;
    handle_ui_button(&menu_data.join_button);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_RenderCopy(window_hnd.renderer, runtime_assets.menu_bg, NULL, NULL);

    draw_text_input(&menu_data.ip_input, runtime_assets.ip_text_input_texture);
    draw_text_input(&menu_data.name_input, runtime_assets.name_text_input_texture);

    SDL_RenderCopy(window_hnd.renderer, runtime_assets.buttons_texture, &menu_data.join_button_trect, &menu_data.join_button.rect);

    SDL_SetRenderTarget(window_hnd.renderer, NULL);

    routines_draw_window();
}