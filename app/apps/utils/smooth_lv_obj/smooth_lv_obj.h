/**
 * @file smooth_lv_obj.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <smooth_ui_toolkit.h>
#include <lvgl.h>
#include <memory>

class SmoothLvObj {
public:
    SmoothLvObj(lv_obj_t* lvObj);
    ~SmoothLvObj();

    lv_obj_t* get()
    {
        return _lv_obj;
    }

    void update();

    SmoothUIToolKit::Transition2D& Postion();
    SmoothUIToolKit::Transition2D& Size();

private:
    lv_obj_t* _lv_obj = NULL;

    struct Transitions_t {
        std::unique_ptr<SmoothUIToolKit::Transition2D> position;
        std::unique_ptr<SmoothUIToolKit::Transition2D> size;
    };
    Transitions_t _transitions;
};
