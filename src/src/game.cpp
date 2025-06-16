#include <game.h>
#include <main.h>
#include <rndr_routines.h>
#include <keyboard.h>
#include <ui.h>
#include <rndr_routines.h>
#include <assets.h>

#include <server.h>
#include <client.h>

game_state_t game_state;
ui_layer_t ui_layer;

static SDL_Rect *buttons_rect_ptr;
void game_buttons_hover() { buttons_rect_ptr->y = 64; }
void game_buttons_press() { buttons_rect_ptr->y = 32; }
void game_buttons_default() { buttons_rect_ptr->y = 0; }

void game_buttons_ready()
{
    if (ui_layer.button_active)
    {
        client_send_request(client_socket, DATA_REQUEST_READY, NULL);
        ui_layer.button_active = false;
    }
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

const char *tile_names[] =
    {
        "nothing",
        "fortress",
        "nothing",
        "tree",
        "rock"};

void draw_tile_data()
{
    static char str[128];
    SDL_Texture *text_texture = NULL;

    if ((mouse_x < 512) && (mouse_y < 512))
    {
        int tile_x = mouse_x / 16;
        int tile_y = mouse_y / 16;
        int index = tile_x + tile_y * BOARD_W;

        const char *tile_name = tile_names[0];
        uint8_t type = game_state.remote_state.upper_board[index];
        if (type < sizeof(tile_names) / sizeof(tile_names[0])) {
            tile_name = tile_names[type];
        }

        if (type == 1)
        {
            uint8_t disp = game_state.remote_state.upper_disp_board[index];
            const char* name = game_state.remote_state.clients[disp].name;
            sprintf(str, "type: %s\nplayer: %8s\nid: %d", tile_name, name, disp + 1);

            SDL_Surface *surface = TTF_RenderText_Solid_Wrapped(window_hnd.font, str, (SDL_Color){255,255,255,255}, 160);
            if (!surface) return;

            text_texture = SDL_CreateTextureFromSurface(window_hnd.renderer, surface);
            SDL_Rect text_rect = {mouse_x + 16, mouse_y, surface->w + 8, surface->h + 8};

            SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 200);
            SDL_RenderFillRect(window_hnd.renderer, &text_rect);

            SDL_Rect draw_rect = {text_rect.x + 4, text_rect.y + 4, surface->w, surface->h};
            SDL_RenderCopy(window_hnd.renderer, text_texture, NULL, &draw_rect);

            SDL_FreeSurface(surface);
        }
        else
        {
            sprintf(str, "type: %s", tile_name);
            text_texture = routines_render_text_texture(str, (SDL_Color){255,255,255,255});

            if (text_texture) {
                int texW, texH;
                SDL_QueryTexture(text_texture, NULL, NULL, &texW, &texH);
                SDL_Rect text_rect = {mouse_x + 16, mouse_y, texW + 8, texH + 8};

                SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 200);
                SDL_RenderFillRect(window_hnd.renderer, &text_rect);

                SDL_Rect draw_rect = {text_rect.x + 4, text_rect.y + 4, texW, texH};
                SDL_RenderCopy(window_hnd.renderer, text_texture, NULL, &draw_rect);
            }
        }

        if (text_texture) SDL_DestroyTexture(text_texture);
    }
}


void draw_text_wall()
{
    for (uint32_t i = 0; i < game_state.text_wall_size; ++i)
    {
        if ((game_state.text_wall[i] != nullptr) && (game_state.text_wall_texture[i] != nullptr))
        {
            SDL_Rect text_rect = {516, i * 16, strlen(game_state.text_wall[i]) * 16, 16};

            SDL_RenderCopy(window_hnd.renderer, game_state.text_wall_texture[i], NULL, &text_rect);
        }
    }
}

void update_text_wall()
{
    for (uint32_t i = 0; i < game_state.text_wall_size; ++i)
    {
        if ((game_state.text_wall[i] != nullptr))
        {
            if (game_state.text_wall_texture[i] != NULL)
            {
                SDL_DestroyTexture(game_state.text_wall_texture[i]);
                game_state.text_wall_texture[i] = NULL;
            }
            game_state.text_wall_texture[i] = routines_render_text_texture(game_state.text_wall[i], {255, 255, 255, 255});
        }
    }
}

void game_init()
{
    strcpy(game_state.remote_state.clients[0].name,client_name);
    client_send_request(client_socket, DATA_REQUEST_STATE, &game_state.remote_state);

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

    ui_layer.button_active = true;

    game_state.text_wall_size = 6;
    game_state.text_wall = (const char **)malloc(game_state.text_wall_size * sizeof(const char *));
    game_state.text_wall_texture = (SDL_Texture **)malloc(game_state.text_wall_size * sizeof(SDL_Texture *));
    memset(game_state.text_wall, 0, game_state.text_wall_size * sizeof(const char *));
    memset(game_state.text_wall_texture, 0, game_state.text_wall_size * sizeof(char *));

    game_state.text_wall[0] = (const char *)malloc(32 + 1);
    memset((void *)game_state.text_wall[0], 0, 33);

    sprintf((char *)game_state.text_wall[0], "poblation: % 4d", game_state.remote_state.clients[0].poblation);

    update_text_wall();

    Mix_HaltMusic();
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(runtime_assets.songloop1, -1);
}

void game_update()
{
    handle_events();
    handle_client();

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
    SDL_RenderCopy(window_hnd.renderer, runtime_assets.buttons_texture, &ui_layer.ready_button_trect, &ui_layer.ready_button.rect);

    SDL_RenderCopy(window_hnd.renderer, game_state.board_texture, NULL, &game_state.board_rect);

    draw_text_wall();
    draw_tile_data();

    SDL_SetRenderTarget(window_hnd.renderer, NULL);
    routines_draw_window();
}