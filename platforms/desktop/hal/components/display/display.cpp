/**
 * @file display.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "display.h"
#include "../../hal_config.h"
#include <SDL.h>
#include <cstdint>
#include <lvgl.h>
#include <src/display/lv_display.h>
#include <src/drivers/sdl/lv_sdl_window.h>

void render_from_uint8(SDL_Renderer* renderer, uint8_t* pixel_data, int width, int height)
{
    // Create an SDL surface for monochrome display
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (!surface) {
        SDL_Log("Unable to create surface: %s", SDL_GetError());
        return;
    }

    // Convert monochrome data to 32-bit RGBA
    uint32_t* pixels = (uint32_t*)surface->pixels;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int byte_index = (y * width + x) / 8;
            int bit_index = 7 - ((y * width + x) % 8); // MSB first
            
            bool pixel_is_set = (pixel_data[byte_index] & (1 << bit_index)) != 0;
            
            // Monochrome: White on Black (OLED style)
            uint32_t color = pixel_is_set ? 0xFFFFFFFF : 0x000000FF; // White if set, Black if not
            
            pixels[y * width + x] = color;
        }
    }

    // Convert the SDL_Surface to an SDL_Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Unable to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Present the updated renderer
    SDL_RenderPresent(renderer);

    // Cleanup
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void DisplaySdl::init()
{
    // Setting monochrome (1-bit) color depth
    setColorDepth(lgfx::color_depth_t::palette_1bit);
    createSprite(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    
    // Set black background color for LVGL
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
}

void DisplaySdl::push_buffer_to_display(void* buffer)
{
    // From lvgl, get sdl renderer instance
    auto sdl_render = (SDL_Renderer*)lv_sdl_window_get_renderer(lv_display_get_default());
    render_from_uint8(sdl_render, (uint8_t*)buffer, width(), height());
}
