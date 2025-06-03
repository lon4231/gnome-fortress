#include <headers.h>
#include <window.h>

#include <keyboard.h>
#include <main.h>
#include <main_menu.h>
#include <assets.h>

scene_fn_handle_t scene_fn_handle;

inline void init_libs()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    SDLNet_Init();
    TTF_Init();
}

int main(int argc,char*argv[])
{
    init_libs();
    init_window_hnd();
    init_keyboard();
    load_assets();
    
    main_menu_init();

    scene_fn_handle = main_menu_update;

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(runtime_assets.songloop0,-1);

    while (window_hnd.running)
    {
        if (scene_fn_handle != nullptr)
        {
            scene_fn_handle();
        }
    }
    return 0;
}