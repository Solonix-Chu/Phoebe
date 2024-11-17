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
#include "core/types/types.h"
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
    smoothPosition().getXTransition().setDelay(0);

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
    if (mouseType == CornerBall) {
        setRadius(18);
        moveForeground();
        smoothPosition().setDuration(300);
    } else if (mouseType == BackgroundBrick) {
        setRadius(5);
        moveBackground();
        smoothPosition().setDuration(300);
    }
    smoothPosition().moveTo(getMousePosition(targetWidget));
    smoothSize().moveTo(getMouseSize(targetWidget));
}

void SmoothWidgetMouse::press()
{
    auto target_widget = getCurrentTargetWidget();
    if (!target_widget) {
        return;
    }

    Vector2D_t mouse_target_size = getMouseSize(target_widget);
    Vector2D_t mouse_target_position = getMousePosition(target_widget);
    Vector4D_t squeeze_shape;

    if (mouseType == CornerBall) {
        squeeze_shape.w = mouse_target_size.width * 2 / 3;
        squeeze_shape.h = mouse_target_size.height * 2 / 3;
        squeeze_shape.x = mouse_target_position.x + mouse_target_size.width / 6;
        squeeze_shape.y = mouse_target_position.y + mouse_target_size.height / 6;
    } else {
        squeeze_shape.w = mouse_target_size.width * 7 / 8;
        squeeze_shape.h = mouse_target_size.height * 2 / 3;
        squeeze_shape.x = mouse_target_position.x + mouse_target_size.width / 16;
        squeeze_shape.y = mouse_target_position.y + mouse_target_size.height / 6;
    }

    smoothPosition().moveTo(squeeze_shape.x, squeeze_shape.y);
    smoothSize().moveTo(squeeze_shape.w, squeeze_shape.h);

    smoothPosition().getXTransition().setDelay(0);
    smoothPosition().setDuration(400);
    smoothSize().setDuration(400);
}

void SmoothWidgetMouse::release()
{
    auto target_widget = getCurrentTargetWidget();
    if (!target_widget) {
        return;
    }

    smoothPosition().moveTo(getMousePosition(target_widget));
    smoothSize().moveTo(getMouseSize(target_widget));

    smoothPosition().getXTransition().setDelay(0);
    smoothPosition().setDuration(300);
    smoothSize().setDuration(600);
}

Vector2D_t SmoothWidgetMouse::getMouseSize(WidgetBase* targetWidget)
{
    Vector2D_t ret;
    if (mouseType == CornerBall) {
        ret.width = _mouse_w;
        ret.height = _mouse_h;
    } else {
        ret.width = targetWidget->getWidth() + 4;
        ret.height = targetWidget->getHeight() + 4;
    }
    return ret;
}

Vector2D_t SmoothWidgetMouse::getMousePosition(WidgetBase* targetWidget)
{
    Vector2D_t ret;
    if (mouseType == CornerBall) {
        ret.x = targetWidget->getX2() - 13;
        ret.y = targetWidget->getY2() - 13;
    } else {
        ret.x = targetWidget->getX() - 2;
        ret.y = targetWidget->getY() - 2;
    }
    return ret;
}

int32_t SmoothWidgetMouse::getX()
{
    if (_transitions.position) {
        return _transitions.position->getTargetPoint().x;
    }
    return WidgetBase::getX();
}

int32_t SmoothWidgetMouse::getX2()
{
    return getX() + getWidth();
}

int32_t SmoothWidgetMouse::getY()
{
    if (_transitions.position) {
        return _transitions.position->getTargetPoint().y;
    }
    return WidgetBase::getY();
}

int32_t SmoothWidgetMouse::getY2()
{
    return getY() + getHeight();
}

int32_t SmoothWidgetMouse::getWidth()
{
    if (_transitions.size) {
        return _transitions.size->getTargetPoint().width;
    }
    return WidgetBase::getWidth();
}

int32_t SmoothWidgetMouse::getHeight()
{
    if (_transitions.size) {
        return _transitions.size->getTargetPoint().height;
    }
    return WidgetBase::getHeight();
}
