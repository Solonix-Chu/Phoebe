/**
 * @file display.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class DisplaySDL : public hal_components::DisplayBase {
public:
    void init() override;
    void push_buffer_to_display(void* buffer) override;
};
