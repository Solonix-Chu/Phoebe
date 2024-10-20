/**
 * @file smooth_lv_obj.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include <smooth_ui_toolkit.h>
#include <lvgl.h>
#include <memory>

namespace smooth_lv_widgets {

class LvObj {
public:
    LvObj(lv_obj_t* lvObj);
    ~LvObj();

    lv_obj_t* get()
    {
        return _lv_obj;
    }

    virtual void update();

    SmoothUIToolKit::Transition2D& Position();
    SmoothUIToolKit::Transition2D& Size();

    void autoDestroyPosition(bool autoDestroy)
    {
        _transitions.auto_destroy_position = autoDestroy;
    }

    void autoDestroySize(bool autoDestroy)
    {
        _transitions.auto_destroy_size = autoDestroy;
    }

    void align(lv_align_t align, int32_t x_ofs, int32_t y_ofs);
    void alignTo(const lv_obj_t* base, lv_align_t align, int32_t x_ofs, int32_t y_ofs);
    void setAlign(lv_align_t align);
    void setScrollbarMode(lv_scrollbar_mode_t mode);
    void setRadius(int32_t value, lv_style_selector_t selector = LV_PART_MAIN);
    void setBgColor(lv_color_t value, lv_style_selector_t selector = LV_PART_MAIN);
    void setBorderWidth(int32_t value, lv_style_selector_t selector = LV_PART_MAIN);
    void setBorderColor(lv_color_t value, lv_style_selector_t selector = LV_PART_MAIN);
    void setPos(int32_t x, int32_t y);
    void setSize(int32_t w, int32_t h);

private:
    lv_obj_t* _lv_obj = NULL;

    struct Transitions_t {
        std::unique_ptr<SmoothUIToolKit::Transition2D> position;
        std::unique_ptr<SmoothUIToolKit::Transition2D> size;
        bool auto_destroy_position = false;
        bool auto_destroy_size = false;
    };
    Transitions_t _transitions;
};

} // namespace smooth_lv_widgets
