/**
 * @file label.cpp
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

using namespace widget;
using namespace widget_helper;

WidgetLabel::WidgetLabel(lv_obj_t* parent)
{
    _lv_obj = lv_label_create(parent);
    lv_obj_null_on_delete(&_lv_obj);
    setTextColor("#000000");
    setScrollbarMode(LV_SCROLLBAR_MODE_OFF);
}

void WidgetLabel::setTextColor(const char* hexColor)
{
    lv_obj_set_style_text_color(_lv_obj, get_lv_color_by_string(hexColor), LV_PART_MAIN);
}

void WidgetLabel::setText(const char* text)
{
    lv_label_set_text(_lv_obj, text);
}

void WidgetLabel::setFont(const char* fontName)
{
    lv_obj_set_style_text_font(_lv_obj, get_lv_font_by_string(fontName), LV_PART_MAIN);
}
