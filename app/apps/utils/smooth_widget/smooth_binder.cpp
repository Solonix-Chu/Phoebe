/**
 * @file smooth_binder.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_widget.h"
#include <hal/hal.h>

using namespace smooth_widget;
using namespace SmoothUIToolKit;

void SmoothBinder::bindSmoothTarget(lv_obj_t* target)
{
    _smooth_target = target;
}

void SmoothBinder::updateSmoothing()
{
    if (!_smooth_target) {
        return;
    }

    if (_transitions.position) {
        _transitions.position->update(HAL::SysCtrl().millis());
        lv_obj_set_pos(_smooth_target, _transitions.position->getValue().x, _transitions.position->getValue().y);
    }
    if (_transitions.size) {
        _transitions.size->update(HAL::SysCtrl().millis());
        lv_obj_set_size(_smooth_target, _transitions.size->getValue().x, _transitions.size->getValue().y);
    }
}

void SmoothBinder::freeSmoothBinding()
{
    _transitions.position->reset();
    _transitions.size->reset();
}

Transition2D& SmoothBinder::smoothPosition()
{
    if (!_transitions.position) {
        _transitions.position = std::make_unique<Transition2D>();
    }
    return *_transitions.position.get();
}

Transition2D& SmoothBinder::smoothSize()
{
    if (!_transitions.size) {
        _transitions.size = std::make_unique<Transition2D>();
    }
    return *_transitions.size.get();
}
