/**
 * @file display.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "utils/lgfx/v1/LGFX_Sprite.hpp"
#include <lvgl.h>

namespace hal_components {

/**
 * @brief 显示屏基类，提供相对方便直接的绘图接口
 *
 * 这里直接继承 lgfx::LGFX_Sprite 的图形渲染方法，总不能自己写吧😊
 */
class DisplayBase : public lgfx::LGFX_Sprite {
public:
    ~DisplayBase() = default;

    /**
     * @brief 在这里要实现 LGFX_Sprite 的 buffer 创建、色深调整等，比如：createSprite(144, 168); setColorDepth(16);
     *
     */
    virtual void init() {}

    /**
     * @brief 重置屏幕内容
     *
     */
    void resetScreen()
    {
        lv_obj_clean(lv_screen_active());
        lv_obj_invalidate(lv_screen_active());
        lv_timer_handler();
    }

    /**
     * @brief 将改动推送到屏幕
     *
     */
    void pushToScreen()
    {
        push_buffer_to_display(getBuffer());
    }

protected:
    /**
     * @brief 这里要实现 LGFX_Sprite 的 buffer 对屏幕的推送
     *
     * @param buffer
     */
    virtual void push_buffer_to_display(void* buffer) {}
};

} // namespace hal_components
