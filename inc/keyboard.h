#ifndef _INPUT_MANAGER_DEFINED_
#define _INPUT_MANAGER_DEFINED_

#include <headers.h>

struct keyboard_hnd_t
{
    uint8_t *kmap;
    uint8_t *last_kmap;
};

extern keyboard_hnd_t keyboard_hnd;

void init_keyboard();
void handle_keyboard();

#endif