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
#include "lv_obj.h"
#include <memory>
#include <smooth_ui_toolkit.h>
#include <lvgl.h>
#include <hal/hal.h>

using namespace SmoothUIToolKit;
using namespace smooth_lv_widgets;

LvObj::LvObj(lv_obj_t* lvObj)
{
    _lv_obj = lvObj;
    lv_obj_null_on_delete(&_lv_obj);
}

LvObj::~LvObj()
{
    if (_lv_obj != NULL) {
        lv_obj_delete_async(_lv_obj);
    }
}

void LvObj::update()
{
    if (_transitions.position) {
        _transitions.position->update(HAL::SysCtrl().millis());
        lv_obj_set_pos(_lv_obj, _transitions.position->getValue().x, _transitions.position->getValue().y);
        if (_transitions.auto_destroy_position && _transitions.position->isFinish()) {
            _transitions.position.reset();
        }
    }
    if (_transitions.size) {
        _transitions.size->update(HAL::SysCtrl().millis());
        lv_obj_set_size(_lv_obj, _transitions.size->getValue().x, _transitions.size->getValue().y);
        if (_transitions.auto_destroy_size && _transitions.size->isFinish()) {
            _transitions.size.reset();
        }
    }
}

Transition2D& LvObj::Position()
{
    if (!_transitions.position) {
        _transitions.position = std::make_unique<Transition2D>();
    }
    return *_transitions.position.get();
}

Transition2D& LvObj::Size()
{
    if (!_transitions.size) {
        _transitions.size = std::make_unique<Transition2D>();
    }
    return *_transitions.size.get();
}
