/**
 * @file smooth_lv_obj.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_lv_obj.h"
#include <memory>
#include <smooth_ui_toolkit.h>
#include <lvgl.h>
#include <hal/hal.h>
#include <src/core/lv_obj_pos.h>

using namespace SmoothUIToolKit;

SmoothLvObj::SmoothLvObj(lv_obj_t* lvObj)
{
    _lv_obj = lvObj;
    lv_obj_null_on_delete(&_lv_obj);
}

SmoothLvObj::~SmoothLvObj()
{
    if (_lv_obj != NULL) {
        lv_obj_delete_async(_lv_obj);
    }
}

void SmoothLvObj::update()
{
    if (_transitions.position) {
        _transitions.position->update(HAL::SysCtrl().millis());
        lv_obj_set_pos(_lv_obj, _transitions.position->getValue().x, _transitions.position->getValue().y);
        if (_transitions.position->isFinish()) {
            _transitions.position.reset();
        }
    }
    if (_transitions.size) {
        _transitions.size->update(HAL::SysCtrl().millis());
        lv_obj_set_size(_lv_obj, _transitions.size->getValue().x, _transitions.size->getValue().y);
        if (_transitions.size->isFinish()) {
            _transitions.size.reset();
        }
    }
}

Transition2D& SmoothLvObj::Postion()
{
    if (!_transitions.position) {
        _transitions.position = std::make_unique<Transition2D>();
    }
    return *_transitions.position.get();
}

Transition2D& SmoothLvObj::Size()
{
    if (!_transitions.size) {
        _transitions.size = std::make_unique<Transition2D>();
    }
    return *_transitions.size.get();
}
