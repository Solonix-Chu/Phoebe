/**
 * @file base.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "core/types/types.h"
#include "smooth_widget.h"

using namespace smooth_widget;
using namespace SmoothUIToolKit;

int32_t SmoothWidgetBase::getX()
{
    if (_transitions.position) {
        return _transitions.position->getTargetPoint().x;
    }
    return WidgetBase::getX();
}

int32_t SmoothWidgetBase::getX2()
{
    return getX() + getWidth();
}

int32_t SmoothWidgetBase::getY()
{
    if (_transitions.position) {
        return _transitions.position->getTargetPoint().y;
    }
    return WidgetBase::getY();
}

int32_t SmoothWidgetBase::getY2()
{
    return getY() + getHeight();
}

int32_t SmoothWidgetBase::getWidth()
{
    if (_transitions.size) {
        return _transitions.size->getTargetPoint().width;
    }
    return WidgetBase::getWidth();
}

int32_t SmoothWidgetBase::getHeight()
{
    if (_transitions.size) {
        return _transitions.size->getTargetPoint().height;
    }
    return WidgetBase::getHeight();
}
