/**
 * @file button_sdl.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "button_sdl.h"
#include "hal/components/button.h"
#include <SDL2/SDL.h>
#include <SDL_scancode.h>
#include <SDL_timer.h>

bool ButtonSDL::getButton(ButtonId::ButtonId_t id)
{
    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
    switch (id) {
        case ButtonId::Power:
            return current_key_states[SDL_SCANCODE_Q] != 0;
        case ButtonId::Up:
            return current_key_states[SDL_SCANCODE_W] != 0;
        case ButtonId::Ok:
            return current_key_states[SDL_SCANCODE_D] != 0;
        case ButtonId::Down:
            return current_key_states[SDL_SCANCODE_E] != 0;
        default:
            return false;
    }
    return false;
}

std::uint32_t ButtonSDL::millis()
{
    return SDL_GetTicks();
}
