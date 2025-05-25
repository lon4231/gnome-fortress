#ifndef _SCR_UI_DEFINED_
#define _SCR_UI_DEFINED_

#include <headers.h>

typedef void (*sbutton_action_t)();

struct sbutton_t
{
    SDL_Rect rect;
    sbutton_action_t   onclick;
    sbutton_action_t   onrelease;
    sbutton_action_t   onhold;
    sbutton_action_t   onhover;
    sbutton_action_t   noton;
};

void handle_ui(SDL_Event *event);
void handle_sbutton(sbutton_t *button);
void ui_frame();

#endif