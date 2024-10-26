/**
 * @file widget.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <lvgl.h>

namespace widget {

class WidgetBase {
public:
    WidgetBase() = default;
    WidgetBase(lv_obj_t* parent);
    virtual ~WidgetBase();

    void setAlign(const char* alignment);
    void setBgColor(const char* hexColor);
    void setPos(int32_t x, int32_t y);
    void setSize(int32_t w, int32_t h);
    void setScrollbarMode(lv_scrollbar_mode_t mode);
    void setRadius(int32_t value);
    void setBorderWidth(int32_t value);
    void setBorderColor(const char* hexColor);

    lv_obj_t* get()
    {
        return _lv_obj;
    }

    void set(lv_obj_t* lvObj)
    {
        _lv_obj = lvObj;
    }

protected:
    lv_obj_t* _lv_obj = NULL;
};

class WidgetLabel : public WidgetBase {
public:
    WidgetLabel() = default;
    WidgetLabel(lv_obj_t* parent);

    void setTextColor(const char* hexColor);
    void setText(const char* text);
    void setFont(const char* fontName);
};

class Img : public WidgetBase {
public:
    Img(lv_obj_t* parent);

    void setSrc(const char* imageSrc);
};

} // namespace widget

namespace widget_helper {

lv_align_t get_lv_align_by_string(const char* align);
lv_color_t get_lv_color_by_string(const char* hexColor);
const lv_font_t* get_lv_font_by_string(const char* fontName);

} // namespace widget_helper
