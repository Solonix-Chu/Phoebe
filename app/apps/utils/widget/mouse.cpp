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
#include "widget.h"

using namespace widget;

WidgetMouse::WidgetMouse(lv_obj_t* parent) : WidgetBase(parent)
{
    setSize(18, 18);
    setRadius(18);
    setBorderWidth(0);
    setBgColor("#000000");
}

void WidgetMouse::clearAllTargets()
{
    _target_widget_list.clear();
    _current_target_index = -1;
}

void WidgetMouse::addTarget(WidgetBase* targetWidget)
{
    _target_widget_list.push_back(targetWidget);
    // If add target from none, set default to 0
    if (_current_target_index < 0) {
        _current_target_index = 0;
    }
}

void WidgetMouse::show()
{
    onShow();
}

void WidgetMouse::hide()
{
    onHide();
}

void WidgetMouse::goNext()
{
    if (_target_widget_list.empty()) {
        return;
    }

    // Get new target index
    auto new_target_index = _current_target_index;
    new_target_index++;
    if (new_target_index >= _target_widget_list.size()) {
        if (goInLoop) {
            new_target_index = 0;
        } else {
            new_target_index = _target_widget_list.size() - 1;
        }
    }

    goTo(_target_widget_list[new_target_index]);
}

void WidgetMouse::goLast()
{
    if (_target_widget_list.empty()) {
        return;
    }

    // Get new target index
    auto new_target_index = _current_target_index;
    new_target_index--;
    if (new_target_index < 0) {
        if (goInLoop) {
            new_target_index = _target_widget_list.size() - 1;
        } else {
            new_target_index = 0;
        }
    }

    goTo(_target_widget_list[new_target_index]);
}

void WidgetMouse::goTo(WidgetBase* targetWidget)
{
    if (_target_widget_list.empty()) {
        return;
    }

    // Trigger current widget on leave
    if (_current_target_index >= 0 && _current_target_index < _target_widget_list.size()) {
        _target_widget_list[_current_target_index]->triggerInputEvent(InputEventType::MouseLeave);
    }

    // Find new widget
    for (int i = 0; i < _target_widget_list.size(); i++) {
        if (_target_widget_list[i] == targetWidget) {
            // Trigger option on hover and selector on go to
            targetWidget->triggerInputEvent(InputEventType::Hover);
            onGoTo(targetWidget);
            // Update current and go
            _current_target_index = i;
            break;
        }
    }
}

void WidgetMouse::click()
{
    if (_target_widget_list.empty()) {
        return;
    }

    _target_widget_list[_current_target_index]->triggerInputEvent(InputEventType::Click);
}

int WidgetMouse::getCurrentTargetIndex()
{
    return _current_target_index;
}

WidgetBase* WidgetMouse::getCurrentTargetWidget()
{
    if (_current_target_index >= 0 && _current_target_index < _target_widget_list.size()) {
        return _target_widget_list[_current_target_index];
    }
    return nullptr;
}

void WidgetMouse::onShow()
{
    setHidden(false);
}

void WidgetMouse::onHide()
{
    setHidden(true);
}

void WidgetMouse::onGoTo(WidgetBase* targetWidget)
{
    setPos(targetWidget->getX2() - 13, targetWidget->getY2() - 13);
}
