#ifndef _SCR_UI_DEFINED_
#define _SCR_UI_DEFINED_

#include <headers.h>

typedef void (*ui_action_t)();

struct ui_button_t
{
    SDL_Rect rect;
    ui_action_t onclick;
    ui_action_t onrelease;
    ui_action_t onhold;
    ui_action_t onhover;
    ui_action_t noton;
};

struct ui_text_input_t
{
    SDL_Rect rect;
    bool selected;
    char *buffer;
    uint32_t buffer_index;
    uint32_t buffer_size;
};

void handle_ui(SDL_Event *event);
void handle_ui_button(ui_button_t *button);
void handle_ui_text_input(ui_text_input_t *text_input);
void ui_frame();

#endif