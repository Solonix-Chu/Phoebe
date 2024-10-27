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
#include <cstdint>
#include <lvgl.h>
#include <memory>
#include <vector>

namespace widget_helper {

lv_align_t get_lv_align_by_string(const char* align);
lv_color_t get_lv_color_by_string(const char* hexColor);
const lv_font_t* get_lv_font_by_string(const char* fontName);

} // namespace widget_helper

namespace widget {

/**
 * @brief 组件类型
 *
 */
namespace WidgetType {
enum Type_t {
    Base = 0,
    Label,
    Img,
    Clock,
};
}

/**
 * @brief 基础组件
 *
 */
class WidgetBase {
public:
    WidgetBase() = default;
    WidgetBase(lv_obj_t* parent);
    virtual ~WidgetBase();

    // "lv_align_default" | "lv_align_top_left" | "lv_align_top_mid" | "lv_align_top_right"
    // "lv_align_bottom_left" | "lv_align_bottom_mid" | "lv_align_bottom_right"
    // "lv_align_left_mid" | "lv_align_right_mid" | "lv_align_center"
    void setAlign(const char* alignment);
    void setBgColor(const char* hexColor);
    void setPos(int32_t x, int32_t y);
    void setSize(int32_t w, int32_t h);
    void setScrollbarMode(lv_scrollbar_mode_t mode);
    void setRadius(int32_t value);
    void setBorderWidth(int32_t value);
    void setBorderColor(const char* hexColor);
    void setRotation(int32_t value);

    lv_obj_t* getLvObj()
    {
        return _lv_obj;
    }

    void set(lv_obj_t* lvObj)
    {
        _lv_obj = lvObj;
    }

    virtual WidgetType::Type_t type()
    {
        return WidgetType::Base;
    }

protected:
    lv_obj_t* _lv_obj = NULL;
};

/**
 * @brief 标签组件
 *
 */
class WidgetLabel : public WidgetBase {
public:
    WidgetLabel() = default;
    WidgetLabel(lv_obj_t* parent);

    // "RajdhaniBold16" | "RajdhaniBold24" | "RajdhaniBold36" | "RajdhaniBold48"
    // "RajdhaniBold64" | "RajdhaniBold72" | "RajdhaniBold96" | "RajdhaniBold144"
    // "Zpix12"
    void setFont(const char* fontName);
    void setTextColor(const char* hexColor);
    void setText(const char* text);

    WidgetType::Type_t type() override
    {
        return WidgetType::Label;
    }
};

/**
 * @brief 图片组件
 *
 */
class WidgetImg : public WidgetBase {
public:
    WidgetImg() = default;
    WidgetImg(lv_obj_t* parent) {}

    void setSrc(const char* imageSrc);

    WidgetType::Type_t type() override
    {
        return WidgetType::Img;
    }
};

/**
 * @brief 时钟组件
 *
 */
class WidgetClock : public WidgetBase {
public:
    WidgetClock() = default;
    WidgetClock(lv_obj_t* parent);
    ~WidgetClock();

    int centerX = 50;
    int centerY = 50;
    int hourHandWidth = 5;
    int hourHandLength = 26;
    int minHandWidth = 4;
    int minHandLength = 40;
    int secHandWidth = 2;
    int secHandLength = 60;
    lv_color_t handColor = lv_color_black();

    // {
    //   "centerX": 50,
    //   "centerY": 50,
    //   "hourHandWidth": 5,
    //   "hourHandLength": 26,
    //   "minHandWidth": 4,
    //   "minHandLength": 40,
    //   "secHandWidth": 2,
    //   "secHandLength": 60,
    //   "handColor": "#000000"
    // }
    bool setStyle(const char* styleJson);
    void update();

    WidgetType::Type_t type() override
    {
        return WidgetType::Clock;
    }

private:
    lv_obj_t* _hour_hand = NULL;
    lv_obj_t* _minute_hand = NULL;
    lv_obj_t* _second_hand = NULL;
    lv_point_precise_t _hour_points[2];
    lv_point_precise_t _minute_points[2];
    lv_point_precise_t _second_points[2];
};

/**
 * @brief 组件工厂
 *
 */
class WidgetFactory {
public:
    /**
     * @brief 创建组件，返回组件 ID
     *
     * @param widgetType "base" | "label" | "img" | "clock"
     * @return int
     */
    int create(const char* widgetType);

    /**
     * @brief 销毁组件
     *
     * @param widgetId 组件 ID
     */
    void destory(int widgetId);

    // 获取组件实例，如果没有对应 ID 或类型不对，返回 nullptr
    WidgetBase* getBase(int widgetId);
    WidgetLabel* getLabel(int widgetId);
    WidgetImg* getImg(int widgetId);
    WidgetClock* getClock(int widgetId);

    /**
     * @brief 设置组件父对象
     *
     * @param widgetParent
     */
    void setWidgetParent(lv_obj_t* widgetParent)
    {
        _widget_parent = widgetParent;
    }

private:
    struct WidgetInfo_t {
        int id = -114514;
        std::unique_ptr<WidgetBase> widget;
    };

    std::vector<WidgetInfo_t> _widget_list;
    std::vector<int> _available_widget_id_list;
    int _next_widget_id = 0;
    lv_obj_t* _widget_parent = NULL;

    int get_next_widget_id();
};

} // namespace widget
