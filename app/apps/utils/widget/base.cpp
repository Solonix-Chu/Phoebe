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
#include <src/core/lv_obj_style_gen.h>
#include <src/lv_api_map_v8.h>

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
    setPadding(0, 0, 0, 0);
}

WidgetBase::~WidgetBase()
{
    if (_lv_obj != NULL) {
        lv_obj_delete(_lv_obj);
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

void WidgetBase::setRotation(int32_t value)
{
    lv_obj_set_style_transform_rotation(_lv_obj, value, LV_PART_MAIN);
}

void WidgetBase::setPadding(int32_t top, int32_t bottom, int32_t left, int32_t right)
{
    lv_obj_set_style_pad_top(_lv_obj, top, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(_lv_obj, bottom, LV_PART_MAIN);
    lv_obj_set_style_pad_left(_lv_obj, left, LV_PART_MAIN);
    lv_obj_set_style_pad_right(_lv_obj, right, LV_PART_MAIN);
}

void WidgetBase::setOutlineWidth(int32_t value)
{
    lv_obj_set_style_outline_width(_lv_obj, value, LV_PART_MAIN);
}

void WidgetBase::setOutlineColor(const char* hexColor)
{
    lv_obj_set_style_outline_color(_lv_obj, get_lv_color_by_string(hexColor), LV_PART_MAIN);
}

void WidgetBase::moveBackground()
{
    lv_obj_move_background(_lv_obj);
}

void WidgetBase::moveForeground()
{
    lv_obj_move_foreground(_lv_obj);
}

void WidgetBase::setHidden(bool hidden)
{
    if (hidden) {
        lv_obj_add_flag(_lv_obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_remove_flag(_lv_obj, LV_OBJ_FLAG_HIDDEN);
    }
}

int32_t WidgetBase::getX()
{
    lv_obj_update_layout(_lv_obj);
    return lv_obj_get_x(_lv_obj);
}

int32_t WidgetBase::getX2()
{
    lv_obj_update_layout(_lv_obj);
    return lv_obj_get_x2(_lv_obj);
}

int32_t WidgetBase::getY()
{
    lv_obj_update_layout(_lv_obj);
    return lv_obj_get_y(_lv_obj);
}

int32_t WidgetBase::getY2()
{
    lv_obj_update_layout(_lv_obj);
    return lv_obj_get_y2(_lv_obj);
}

int32_t WidgetBase::getWidth()
{
    lv_obj_update_layout(_lv_obj);
    return lv_obj_get_width(_lv_obj);
}

int32_t WidgetBase::getHeight()
{
    lv_obj_update_layout(_lv_obj);
    return lv_obj_get_height(_lv_obj);
}

void WidgetBase::triggerInputEvent(InputEventType::Type_t type)
{
    InputEvent_t event;
    event.type = type;
    event.target = this;

    switch (type) {
        case InputEventType::None:
            break;
        case InputEventType::Hover: {
            if (onHover) {
                onHover(event);
            }
            break;
        }
        case InputEventType::MouseLeave: {
            if (onMouseLeave) {
                onMouseLeave(event);
            }
            break;
        }
        case InputEventType::Click: {
            if (onClick) {
                onClick(event);
            }
            break;
        }
    }
}
