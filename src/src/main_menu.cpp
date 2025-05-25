#include <main_menu.h>
#include <window.h>
#include <ui.h>

static SDL_Texture*p_button_texture;
static SDL_Rect    p_button_trect;
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
printf("aaaaa\r\n");
}

void play_button_hover()
{
p_button_trect={0,64,64,32};
}

void play_button_press()
{
p_button_trect={0,32,64,32};
}

void play_button_default()
{
p_button_trect={0,0,64,32};
}

void main_menu_init()
{
SDL_Surface*p_button_surface=IMG_Load("assets/sprites/button.png");

p_button_texture=SDL_CreateTextureFromSurface(window_hnd.renderer,p_button_surface);

SDL_FreeSurface(p_button_surface);

p_button=
{
.rect={336,300,128,64},
.onclick=play_button_press,
.onrelease=play_button_action,
.onhold=play_button_press,
.onhover=play_button_hover,
.noton=play_button_default,
};
}

void main_menu_update()
{
    handle_events();


    handle_sbutton(&p_button);    

    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_SetRenderTarget(window_hnd.renderer,window_hnd.render_texture);
    SDL_SetRenderDrawColor(window_hnd.renderer, 255, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);

    SDL_RenderCopy(window_hnd.renderer,p_button_texture,&p_button_trect,&p_button.rect);
    
    SDL_SetRenderTarget(window_hnd.renderer,NULL);
    SDL_RenderCopy(window_hnd.renderer,window_hnd.render_texture,NULL,&window_hnd.render_texture_rect);
    SDL_RenderPresent(window_hnd.renderer);
}
