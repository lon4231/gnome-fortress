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
SDL_SetRenderTarget(window_hnd.renderer,game_state.board_texture);

SDL_Rect trect={0,0,16,16};
SDL_Rect rect={0,0,16,16};
for(uint32_t i=0;i<BOARD_W*BOARD_H;++i)
{
trect.x=game_state.remote_state.board[i]*16;
rect.x=(i%BOARD_W)*16;
rect.y=(i/BOARD_W)*16;

SDL_RenderCopy(window_hnd.renderer,runtime_assets.board_tiles,&trect,&rect);

}

SDL_SetRenderTarget(window_hnd.renderer,window_hnd.render_texture);

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
}

void game_init()
{
    game_state.board_texture=SDL_CreateTexture(window_hnd.renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,BOARD_W*16,BOARD_H*16);
    game_state.board_rect={0,0,BOARD_W*16,BOARD_H*16};

    ui_layer.ready_button_trect = {192, 0, 64, 32};
    ui_layer.ready_button =
        {
            .rect = {RENDER_TEXTURE_HW - 128, RENDER_TEXTURE_HH - 64, 256, 128},
            .onclick=game_buttons_press,
            .onrelease=game_buttons_ready,
            .onhover=game_buttons_hover,
            .noton=game_buttons_default,

        };
}

void game_update()
{
    handle_events();

    buttons_rect_ptr=&ui_layer.ready_button_trect;
    handle_ui_button(&ui_layer.ready_button);

    SDL_SetRenderTarget(window_hnd.renderer, window_hnd.render_texture);

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);
    
    SDL_RenderCopy(window_hnd.renderer,game_state.board_texture,NULL,&game_state.board_rect);

    SDL_RenderCopy(window_hnd.renderer, runtime_assets.buttons_texture, &ui_layer.ready_button_trect, &ui_layer.ready_button.rect);

    SDL_SetRenderTarget(window_hnd.renderer, NULL);
    routines_draw_window();
}