/**
 * @file base.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widget.h"
#include <lvgl.h>
#include <src/core/lv_obj_pos.h>

using namespace widget;
using namespace widget_helper;

WidgetBase::WidgetBase(lv_obj_t* parent)
{
    // Create and setup basic props
    _lv_obj = lv_obj_create(parent);
    lv_obj_null_on_delete(&_lv_obj);
    setRadius(10);
    setBorderWidth(2);
    setBorderColor("#000000");
    setScrollbarMode(LV_SCROLLBAR_MODE_OFF);
}

WidgetBase::~WidgetBase()
{
    if (_lv_obj != NULL) {
        lv_obj_delete_async(_lv_obj);
    }
}

void WidgetBase::setAlign(const char* alignment)
{
    lv_obj_set_align(_lv_obj, get_lv_align_by_string(alignment));
}

void WidgetBase::setBgColor(const char* hexColor)
{
    lv_obj_set_style_bg_color(_lv_obj, get_lv_color_by_string(hexColor), LV_PART_MAIN);
}

void WidgetBase::setPos(int32_t x, int32_t y)
{
    lv_obj_set_pos(_lv_obj, x, y);
}

void WidgetBase::setSize(int32_t w, int32_t h)
{
    lv_obj_set_size(_lv_obj, w, h);
}

void WidgetBase::setScrollbarMode(lv_scrollbar_mode_t mode)
{
    lv_obj_set_scrollbar_mode(_lv_obj, mode);
}

void WidgetBase::setRadius(int32_t value)
{
    lv_obj_set_style_radius(_lv_obj, value, LV_PART_MAIN);
}

void WidgetBase::setBorderWidth(int32_t value)
{
    lv_obj_set_style_border_width(_lv_obj, value, LV_PART_MAIN);
}

void WidgetBase::setBorderColor(const char* hexColor)
{
    lv_obj_set_style_border_color(_lv_obj, get_lv_color_by_string(hexColor), LV_PART_MAIN);
}
