/**
 * @file system_ctrl_sdl.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "system_ctrl_sdl.h"
#include <SDL2/SDL.h>
#include <SDL_timer.h>

std::uint32_t SystemControlSdl::millis()
{
    return SDL_GetTicks();
}

void SystemControlSdl::delay(std::uint32_t ms)
{
    SDL_Delay(ms);
}
