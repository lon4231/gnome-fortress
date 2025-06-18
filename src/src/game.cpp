#include <game.h>
#include <main.h>
#include <rndr_routines.h>
#include <keyboard.h>
#include <ui.h>
#include <rndr_routines.h>
#include <assets.h>

struct obstacle_t
{
    float x;
    float y;
    uint8_t type;
    obstacle_t *next;
};

static float deltatime;
static uint32_t delta_time_last;
static uint32_t delta_time_current;
obstacle_t *obstacle_head;

int player_lives;
uint32_t score;

game_state_t game_state;
static SDL_Rect player_rect;

inline void handle_events()
{
    delta_time_last = delta_time_current;
    delta_time_current = SDL_GetTicks();
    deltatime = (delta_time_current - delta_time_last) / 1000.0f;

    ui_frame();
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        handle_window(&event);
        handle_ui(&event);
    };
    handle_keyboard();
}

void draw_character()
{
    SDL_Rect trect = {0, 0, 8, 8};
    player_rect = {16, (int)game_state.player_y, 32, 32};

    SDL_RenderCopy(window_hnd.renderer, runtime_assets.board_tiles, &trect, &player_rect);
}

void character_phys_handler()
{
    if (game_state.player_y >= (RENDER_TEXTURE_HH + 128) - 32)
    {
        game_state.player_sy = 0;
        game_state.player_y = (RENDER_TEXTURE_HH + 128) - 32;
    }

    game_state.player_sy += 9.6f * 200 * deltatime;
    game_state.player_sy *= 0.999;

    if (
        (keyboard_hnd.kmap[SDL_SCANCODE_SPACE] == 1) &&
        (game_state.player_y >= ((RENDER_TEXTURE_HH + 128) - 32)))
    {
        game_state.player_sy -= 600.0f;
    }

    game_state.player_y += game_state.player_sy * deltatime;
}

void create_obstacle()
{
    obstacle_t *obstacle = (obstacle_t *)malloc(sizeof(obstacle_t));

    obstacle->x = RENDER_TEXTURE_W + 64;
    obstacle->y = (RENDER_TEXTURE_HH + 128) - 32;
    obstacle->type = (rand() >> 16) % 5;
    obstacle->next = nullptr;

    if (obstacle_head != nullptr)
    {
        obstacle->next = obstacle_head;
        obstacle_head = obstacle;
    }
    else
    {
        obstacle_head = obstacle;
    }
}

void draw_obstacles()
{
    obstacle_t *current = obstacle_head;
    obstacle_t *prev = nullptr;

    while (current != nullptr)
    {
        obstacle_t *next = current->next;
        current->x -= ((256.0f + mmax(((float)SDL_GetTicks() * 0.01f), 1024.0f)) * deltatime);
        if (current->x <= -32)
        {
            score += 10;

            if (prev == nullptr)
            {
                obstacle_head = next;
            }
            else
            {
                prev->next = next;
            }

            free(current);
        }
        else
        {
            SDL_Rect trect = {current->type * 8, 8, 8, 8};
            SDL_Rect rect = {(int)current->x, (int)current->y, 32, 32};

            player_rect.w -= 4;
            player_rect.x += 2;

            if (SDL_HasIntersection(&rect, &player_rect))
            {
                printf("STOP TOUCHING MY PEANITS\r\n");
                current->x = -1000;
                player_lives--;
                if (player_lives == 0)
                {
                    printf("SCORE: %d\n",score);
                    exit(0xDEAD);
                }
            }

            SDL_SetRenderDrawColor(window_hnd.renderer, 255, 255, 255, 255);
            SDL_RenderCopy(window_hnd.renderer, runtime_assets.board_tiles, &trect, &rect);
            prev = current;
        }

        current = next;
    }
}

void draw_sky()
{
    SDL_Rect rect = {(SDL_GetTicks() >> 2) % RENDER_TEXTURE_W, 0, 800, 600};
    SDL_RenderCopy(window_hnd.renderer, runtime_assets.game_bg, NULL, &rect);
    rect.x -= 800;
    SDL_RenderCopy(window_hnd.renderer, runtime_assets.game_bg, NULL, &rect);
}

void game_init()
{
    obstacle_head = nullptr;

    player_lives = 3;

    Mix_HaltMusic();
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(runtime_assets.songloop1, -1);
}

void draw_stat_text()
{
    char score_text[32];

    memset(score_text, 0, 32);
    sprintf(score_text, "score: %d", score);

    SDL_Texture *texture = routines_render_text_texture(score_text, {255, 255, 255, 255});
    SDL_Rect text_texture_rect = {0, 0, strlen(score_text) * 16, 16};

    SDL_RenderCopy(window_hnd.renderer, texture, NULL, &text_texture_rect);

    SDL_DestroyTexture(texture);

    memset(score_text, 0, 32);
    sprintf(score_text, "lives: %d", player_lives);

    texture = routines_render_text_texture(score_text, {255, 255, 255, 255});
    text_texture_rect = {0, 16, (int)strlen(score_text) * 16, 16};

    SDL_RenderCopy(window_hnd.renderer, texture, NULL, &text_texture_rect);

    SDL_DestroyTexture(texture);
}

void game_update()
{
    handle_events();

    character_phys_handler();

    if ((keyboard_hnd.kmap[SDL_SCANCODE_F11] == 1) && (keyboard_hnd.last_kmap[SDL_SCANCODE_F11] == 0))
    {
        window_hnd.fullscreen ^= 1;
        SDL_SetWindowFullscreen(window_hnd.window, window_hnd.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0x4f, 0xa4, 0xb8, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_Rect rect = {-32, RENDER_TEXTURE_HH, RENDER_TEXTURE_W + 32, RENDER_TEXTURE_H};
    SDL_SetRenderDrawColor(window_hnd.renderer, 0x28, 0x35, 0x40, 255);
    SDL_RenderFillRect(window_hnd.renderer, &rect);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0x14, 0x18, 0x2e, 255);
    for (uint8_t i = 0; i < 4; ++i)
    {
        rect.y++;
        SDL_RenderDrawRect(window_hnd.renderer, &rect);
    }

    draw_sky();

    draw_character();
    draw_obstacles();

    draw_stat_text();

    SDL_SetRenderTarget(window_hnd.renderer, NULL);
    routines_draw_window();

    static float ticker = 0;
    if (ticker > mmax(2.0f - ((float)SDL_GetTicks() * 0.0001f), 0.7))
    {
        create_obstacle();
        ticker = 0;
    }

    ticker += deltatime;
}