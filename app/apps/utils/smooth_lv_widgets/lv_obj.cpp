/**
 * @file smooth_lv_obj.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "lv_obj.h"
#include <memory>
#include <lvgl.h>
#include <hal/hal.h>
#include <smooth_ui_toolkit.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/misc/lv_color.h>

using namespace SmoothUIToolKit;
using namespace smooth_lv_widgets;

LvObj::LvObj(lv_obj_t* lvObj)
{
    _lv_obj = lvObj;
    lv_obj_null_on_delete(&_lv_obj);

    // Commom presets
    setRadius(10);
    setBorderWidth(2);
    // setBorderColor(lv_color_hex(0xAFAFAC));
    setBorderColor(lv_color_black());
    // setBgColor(lv_color_hex(0xAFAFAC));
    // setBgColor(lv_color_black());
    setScrollbarMode(LV_SCROLLBAR_MODE_OFF);

    // lv_obj_set_style_outline_width(_lv_obj, 2, 0);
    // lv_obj_set_style_outline_color(_lv_obj, lv_color_black(), 0);
}

LvObj::~LvObj()
{
    if (_lv_obj != NULL) {
        lv_obj_delete_async(_lv_obj);
    }
}

void LvObj::update()
{
    if (_transitions.position) {
        _transitions.position->update(HAL::SysCtrl().millis());
        lv_obj_set_pos(_lv_obj, _transitions.position->getValue().x, _transitions.position->getValue().y);
        if (_transitions.auto_destroy_position && _transitions.position->isFinish()) {
            _transitions.position.reset();
        }
    }
    if (_transitions.size) {
        _transitions.size->update(HAL::SysCtrl().millis());
        lv_obj_set_size(_lv_obj, _transitions.size->getValue().x, _transitions.size->getValue().y);
        if (_transitions.auto_destroy_size && _transitions.size->isFinish()) {
            _transitions.size.reset();
        }
    }
}

Transition2D& LvObj::Position()
{
    if (!_transitions.position) {
        _transitions.position = std::make_unique<Transition2D>();
    }
    return *_transitions.position.get();
}

Transition2D& LvObj::Size()
{
    if (!_transitions.size) {
        _transitions.size = std::make_unique<Transition2D>();
    }
    return *_transitions.size.get();
}

void LvObj::align(lv_align_t align, int32_t x_ofs, int32_t y_ofs)
{
    lv_obj_align(_lv_obj, align, x_ofs, y_ofs);
}

void LvObj::alignTo(const lv_obj_t* base, lv_align_t align, int32_t x_ofs, int32_t y_ofs)
{
    lv_obj_align_to(_lv_obj, base, align, x_ofs, y_ofs);
}

void LvObj::setAlign(lv_align_t align)
{
    lv_obj_set_align(_lv_obj, align);
}

void LvObj::setScrollbarMode(lv_scrollbar_mode_t mode)
{
    lv_obj_set_scrollbar_mode(_lv_obj, mode);
}

void LvObj::setRadius(int32_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_radius(_lv_obj, value, selector);
}

void LvObj::setBgColor(lv_color_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_bg_color(_lv_obj, value, selector);
}

void LvObj::setBorderWidth(int32_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_border_width(_lv_obj, value, selector);
}

void LvObj::setBorderColor(lv_color_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_border_color(_lv_obj, value, selector);
}

void LvObj::setPos(int32_t x, int32_t y)
{
    lv_obj_set_pos(_lv_obj, x, y);
}

void LvObj::setSize(int32_t w, int32_t h)
{
    lv_obj_set_size(_lv_obj, w, h);
}
