#include <ui.h>
#include <window.h>
#include <keyboard.h>

uint32_t mouse_x;
uint32_t mouse_y;
uint8_t l_click;
uint8_t r_click;

uint8_t l_click_set;
uint8_t r_click_set;

char text_input_char;
bool text_input_enabled;

bool text_input_input_enabled;

void ui_frame()
{
    text_input_enabled = false;
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
        mouse_x -= window_hnd.render_texture_rect.x;
        mouse_y -= window_hnd.render_texture_rect.y;
        mouse_x = mouse_x * RENDER_TEXTURE_W / window_hnd.render_texture_rect.w;
        mouse_y = mouse_y * RENDER_TEXTURE_H / window_hnd.render_texture_rect.h;

        break;
    case SDL_MOUSEBUTTONDOWN:
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            l_click_set = 1;
            break;
        case SDL_BUTTON_RIGHT:
            r_click_set = 1;
            break;
        default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            l_click_set = 0;
            break;
        case SDL_BUTTON_RIGHT:
            r_click_set = 0;
            break;
        default:
            break;
        }
        break;
    case SDL_TEXTINPUT:
        text_input_char = (char)event->text.text[0];
        text_input_enabled = true;

    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_BACKSPACE:
            text_input_char = '\b';
            text_input_enabled = true;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void handle_ui_button(ui_button_t *button)
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
        case 0b00:
            if (button->onhover != nullptr)
            {
                button->onhover();
            }
            break;
        }
    }
    else
    {
        if (button->noton != nullptr)
        {
            button->noton();
        }
    }
}

void handle_ui_text_input(ui_text_input_t *text_input)
{
    if ((l_click & 0b11) == 0b01)
    {
        if ((
                mouse_x > text_input->rect.x &&
                mouse_x < (text_input->rect.x + text_input->rect.w) &&
                mouse_y > text_input->rect.y &&
                mouse_y < (text_input->rect.y + text_input->rect.h)))
        {
            text_input->selected = true;
        }
        else
        {
            text_input->selected = false;
        }
    }

    if (text_input->selected && text_input_enabled)
    {
        if (isascii(text_input_char))
        {
            if(text_input->oninput!=nullptr){text_input->oninput();}
            if (isprint(text_input_char))
            {
                text_input->buffer[text_input->buffer_index] = text_input_char;
                text_input->buffer_index = mmin(text_input->buffer_index + 1, text_input->buffer_size);
            }
            else
            {
                switch (text_input_char)
                {
                case '\b':
                    text_input->buffer[text_input->buffer_index] = '\0';
                    text_input->buffer_index = mmax((int)text_input->buffer_index - 1, 0);
                    break;

                default:
                    break;
                }
            }
        }
    }
}