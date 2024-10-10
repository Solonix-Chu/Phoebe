/**
 * @file hal_desktop.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class HalDesktop : public hal::HalBase {
public:
    std::string type() override
    {
        return "Desktop";
    }

    void init() override;

private:
    void lvgl_init();
};
