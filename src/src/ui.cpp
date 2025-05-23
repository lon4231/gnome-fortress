#include <ui.h>
#include <window.h>

uint32_t mouse_x;
uint32_t mouse_y;
uint8_t l_click;
uint8_t r_click;

void handle_ui(SDL_Event *event)
{
    l_click = (l_click << 1) & 0xFE;
    r_click = (r_click << 1) & 0xFE;

    switch (event->type)
    {

    case SDL_MOUSEMOTION:
        SDL_GetMouseState((int *)&mouse_x, (int *)&mouse_y);
        break;
    case SDL_MOUSEBUTTONDOWN:
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            l_click = l_click | 1;
            break;
        case SDL_BUTTON_RIGHT:
            r_click = r_click | 1;
            break;
        default:
            break;
        }
        break;

    case SDL_MOUSEBUTTONUP:
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            l_click &= ~1;
            break;
        case SDL_BUTTON_RIGHT:
            r_click &= ~1;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void handle_sbutton(sbutton_t *button)
{
    if (
        (
            mouse_x > button->rect.x &&
            mouse_x < (button->rect.x + button->rect.w) &&
            mouse_y > button->rect.y &&
            mouse_y < (button->rect.y + button->rect.h)) &&
        ((l_click & 0b11) == 0b10))
    {
        button->onclick();
    }
}