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
#include <cstdint>
#include <lgfx/v1/LGFX_Sprite.hpp>

namespace hal_components {

/**
 * @brief 显示屏基类，这里继承 lgfx::LGFX_Sprite 来获得图形渲染方法
 *
 */
class DisplayBase : public lgfx::LGFX_Sprite {
public:
    ~DisplayBase() = default;

    /**
     * @brief 在这里要实现 LGFX_Sprite 的 buffer 创建、色深调整等，比如：createSprite(144, 168); setColorDepth(16);
     *
     */
    virtual void init() {}

    void pushToScreen()
    {
        push_buffer_to_display(getBuffer());
    }

    /**
     * @brief Lvgl 刷新标志位，用来暂停/恢复 lvgl 的刷新渲染
     *
     */
    bool updateLvgl = true;
    void pauseLvgl()
    {
        updateLvgl = false;
    }
    void rusumeLvgl()
    {
        updateLvgl = true;
    }

protected:
    /**
     * @brief 这里要实现对 LGFX_Sprite 的 buffer 对屏幕的推送
     *
     * @param buffer
     */
    virtual void push_buffer_to_display(void* buffer) {}
};

} // namespace hal_components
