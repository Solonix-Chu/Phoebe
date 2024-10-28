/**
 * @file smooth_widget.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../widget/widget.h"
#include <smooth_ui_toolkit.h>
#include <lvgl.h>

namespace smooth_widget {

class SmoothBinder {
public:
    void bindSmoothTarget(lv_obj_t* target);
    void updateSmoothing();
    void freeSmoothBinding();
    bool isAllSmoothingFinish();

    SmoothUIToolKit::Transition2D& smoothPosition();
    SmoothUIToolKit::Transition2D& smoothSize();

private:
    struct Transitions_t {
        std::unique_ptr<SmoothUIToolKit::Transition2D> position;
        std::unique_ptr<SmoothUIToolKit::Transition2D> size;
    };
    Transitions_t _transitions;

    lv_obj_t* _smooth_target = NULL;
};

class SmoothWidgetBase : public widget::WidgetBase, public SmoothBinder {
public:
    SmoothWidgetBase() = default;
    SmoothWidgetBase(lv_obj_t* parent) : WidgetBase(parent)
    {
        bindSmoothTarget(_lv_obj);
    }
};

class SmoothWidgetLabel : public widget::WidgetLabel, public SmoothBinder {
public:
    SmoothWidgetLabel() = default;
    SmoothWidgetLabel(lv_obj_t* parent) : WidgetLabel(parent)
    {
        bindSmoothTarget(_lv_obj);
    }
};

class SmoothWidgetImg : public widget::WidgetImg, public SmoothBinder {
public:
    SmoothWidgetImg() = default;
    SmoothWidgetImg(lv_obj_t* parent) : WidgetImg(parent)
    {
        bindSmoothTarget(_lv_obj);
    }
};

} // namespace smooth_widget
