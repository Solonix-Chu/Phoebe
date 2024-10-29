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

SmoothWidgetMouse::SmoothWidgetMouse(lv_obj_t* parent) : WidgetMouse(parent)
{
    bindSmoothTarget(_lv_obj);
    smoothPosition().setDuration(300);
    smoothPosition().setTransitionPath(EasingPath::easeOutBack);
    smoothPosition().jumpTo(150, 84);
}

void SmoothWidgetMouse::onShow() {}

void SmoothWidgetMouse::onHide()
{
    smoothPosition().moveTo(150, 84);
}

void SmoothWidgetMouse::onGoTo(WidgetBase* optionWidget)
{
    moveForeground();
    smoothPosition().moveTo(optionWidget->getX2() - 12, optionWidget->getY2() - 14);
}
