#ifndef _SCR_UI_DEFINED_
#define _SCR_UI_DEFINED_

#include <headers.h>

typedef void (*sbutton_action_onclick_t)();

struct sbutton_t
{
    SDL_Rect rect;
    sbutton_action_onclick_t onclick;
};

void handle_ui(SDL_Event *event);
void handle_sbutton(sbutton_t *button);

#endif