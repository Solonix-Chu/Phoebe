/**
 * @file mouse.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "core/easing_path/easing_path.h"
#include "smooth_widget.h"

using namespace smooth_widget;
using namespace SmoothUIToolKit;

static constexpr int _mouse_start_up_x = 150;
static constexpr int _mouse_start_up_y = 69;
static constexpr int _mouse_start_up_w = 12;
static constexpr int _mouse_start_up_h = 30;
static constexpr int _mouse_w = 18;
static constexpr int _mouse_h = 18;

SmoothWidgetMouse::SmoothWidgetMouse(lv_obj_t* parent) : WidgetMouse(parent)
{
    bindSmoothTarget(_lv_obj);
    smoothPosition().setTransitionPath(EasingPath::easeOutBack);
    smoothSize().setTransitionPath(EasingPath::easeOutBack);
    smoothPosition().jumpTo(_mouse_start_up_x, _mouse_start_up_y);
    smoothSize().jumpTo(_mouse_start_up_w, _mouse_start_up_h);
}

void SmoothWidgetMouse::onShow()
{
    auto current_target = getCurrentTargetWidget();
    if (current_target) {
        goTo(current_target);
    }
}

void SmoothWidgetMouse::onHide()
{
    smoothPosition().setDuration(400);
    smoothPosition().getXTransition().setDelay(100);

    smoothPosition().moveTo(_mouse_start_up_x, _mouse_start_up_y);
    smoothSize().moveTo(_mouse_start_up_w, _mouse_start_up_h);
}

void SmoothWidgetMouse::onGoTo(WidgetBase* targetWidget)
{
    moveForeground();
    smoothPosition().moveTo(targetWidget->getX2() - 13, targetWidget->getY2() - 13);
    smoothSize().moveTo(_mouse_w, _mouse_h);
    smoothPosition().setDuration(300);
}

void SmoothWidgetMouse::press()
{
    auto target_widget = getCurrentTargetWidget();
    if (!target_widget) {
        return;
    }

    Vector4D_t squeeze_shape;
    squeeze_shape.w = _mouse_w * 2 / 3;
    squeeze_shape.h = _mouse_h * 2 / 3;
    squeeze_shape.x = target_widget->getX2() - 13 + _mouse_w / 6;
    squeeze_shape.y = target_widget->getY2() - 13 + _mouse_h / 6;
    smoothPosition().moveTo(squeeze_shape.x, squeeze_shape.y);
    smoothSize().moveTo(squeeze_shape.w, squeeze_shape.h);

    smoothPosition().setDuration(400);
    smoothSize().setDuration(400);
}

void SmoothWidgetMouse::release()
{
    auto target_widget = getCurrentTargetWidget();
    if (!target_widget) {
        return;
    }

    Vector4D_t release_shape;
    release_shape.w = _mouse_w;
    release_shape.h = _mouse_h;
    release_shape.x = target_widget->getX2() - 13;
    release_shape.y = target_widget->getY2() - 13;
    smoothPosition().moveTo(release_shape.x, release_shape.y);
    smoothSize().moveTo(release_shape.w, release_shape.h);

    smoothPosition().setDuration(300);
    smoothSize().setDuration(600);
}
