#include <ui.h>
#include <window.h>

uint32_t mouse_x;
uint32_t mouse_y;
uint8_t l_click;
uint8_t r_click;

uint8_t l_click_set;
uint8_t r_click_set;

void ui_frame()
{
    l_click <<= 1;
    r_click <<= 1;
    l_click = l_click | l_click_set;
    r_click = r_click | r_click_set;
}

void handle_ui(SDL_Event *event)
{

    switch (event->type)
    {

    case SDL_MOUSEMOTION:
        SDL_GetMouseState((int *)&mouse_x, (int *)&mouse_y);
        break;
    case SDL_MOUSEBUTTONDOWN:
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            l_click_set=1;
            break;
        case SDL_BUTTON_RIGHT:
            r_click_set=1;
            break;
        default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            l_click_set=0;
            break;
        case SDL_BUTTON_RIGHT:
            r_click_set=0;
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
            mouse_y < (button->rect.y + button->rect.h)))
    {
        switch (l_click & 0b11)
        {
        case 0b01:
            if (button->onclick != nullptr)
            {
                button->onclick();
            }
            break;

        case 0b10:
            if (button->onrelease != nullptr)
            {
                button->onrelease();
            }
            break;

        case 0b11:
            if (button->onhold != nullptr)
            {
                button->onhold();
            }
            break;
        }
    }
}