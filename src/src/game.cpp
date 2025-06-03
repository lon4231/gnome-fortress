#include <game.h>
#include <main.h>
#include <rndr_routines.h>
#include <keyboard.h>
#include <ui.h>
#include <assets.h>

#include <server.h>

struct ui_layer_t
{

    SDL_Rect ready_button_trect;
    ui_button_t ready_button;
};

game_state_t game_state;
ui_layer_t ui_layer;

static SDL_Rect *buttons_rect_ptr;
void game_buttons_hover() { buttons_rect_ptr->y = 64; }
void game_buttons_press() { buttons_rect_ptr->y = 32; }
void game_buttons_default() { buttons_rect_ptr->y = 0; }

void game_buttons_ready()
{
}

void draw_board()
{
    SDL_SetRenderTarget(window_hnd.renderer, game_state.board_texture);

    SDL_Rect trect = {0, 0, 8, 8};
    SDL_Rect upper_trect = {0, 0, 8, 8};
    SDL_Rect rect = {0, 0, 8, 8};

    for (uint32_t i = 0; i < BOARD_W * BOARD_H; ++i)
    {
        trect.x = game_state.remote_state.board[i] * 8;
        trect.y = game_state.remote_state.disp_board[i] * 8;

        upper_trect.x = game_state.remote_state.upper_board[i] * 8;
        upper_trect.y = game_state.remote_state.upper_disp_board[i] * 8;

        rect.x = (i % BOARD_W) * 8;
        rect.y = (i / BOARD_W) * 8;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (((game_state.remote_state.disp_board[i] ^ i) & 1) == 1)
        {
            flip = SDL_FLIP_HORIZONTAL;
        }

        SDL_RenderCopyEx(window_hnd.renderer, runtime_assets.board_tiles, &trect, &rect, 0, NULL, flip);
        SDL_RenderCopyEx(window_hnd.renderer, runtime_assets.board_tiles, &upper_trect, &rect, 0, NULL, flip);
    }

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);
}

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

void game_init()
{
    init_game_state(&game_state.remote_state, 8);

    game_state.board_texture = SDL_CreateTexture(window_hnd.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BOARD_W * 8, BOARD_H * 8);
    game_state.board_rect = {0, 0, BOARD_W * 16, BOARD_H * 16};

    ui_layer.ready_button_trect = {192, 0, 64, 32};
    ui_layer.ready_button =
        {
            .rect = {RENDER_TEXTURE_W - 256, RENDER_TEXTURE_H - 128, 256, 128},
            .onclick = game_buttons_press,
            .onrelease = game_buttons_ready,
            .onhover = game_buttons_hover,
            .noton = game_buttons_default,

        };

    Mix_HaltMusic();
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(runtime_assets.songloop1, -1);
}

void game_update()
{
    handle_events();

    if ((keyboard_hnd.kmap[SDL_SCANCODE_F11] == 1) && (keyboard_hnd.last_kmap[SDL_SCANCODE_F11] == 0))
    {
        window_hnd.fullscreen ^= 1;
        SDL_SetWindowFullscreen(window_hnd.window, window_hnd.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

    buttons_rect_ptr = &ui_layer.ready_button_trect;
    handle_ui_button(&ui_layer.ready_button);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    draw_board();

    SDL_RenderCopy(window_hnd.renderer, runtime_assets.game_bg, NULL, NULL);

    SDL_RenderCopy(window_hnd.renderer, game_state.board_texture, NULL, &game_state.board_rect);

    SDL_RenderCopy(window_hnd.renderer, runtime_assets.buttons_texture, &ui_layer.ready_button_trect, &ui_layer.ready_button.rect);

    SDL_SetRenderTarget(window_hnd.renderer, NULL);
    routines_draw_window();
}