#include "keyboard.h"

keyboard_hnd_t keyboard_hnd;

void init_keyboard()
{
    keyboard_hnd.kmap = (uint8_t *)malloc(SDL_NUM_SCANCODES);
    keyboard_hnd.last_kmap = (uint8_t *)malloc(SDL_NUM_SCANCODES);
}

void handle_keyboard()
{
    const uint8_t *sdl_keys = SDL_GetKeyboardState(NULL);

    memcpy(keyboard_hnd.last_kmap, keyboard_hnd.kmap, SDL_NUM_SCANCODES);
    memcpy(keyboard_hnd.kmap, sdl_keys, SDL_NUM_SCANCODES);
}
