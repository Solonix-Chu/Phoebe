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

namespace smooth_lv_widgets {

class LvObj {
public:
    LvObj(lv_obj_t* lvObj);
    ~LvObj();

    lv_obj_t* get()
    {
        return _lv_obj;
    }

    virtual void update();

    SmoothUIToolKit::Transition2D& Position();
    SmoothUIToolKit::Transition2D& Size();

    void autoDestroyPosition(bool autoDestroy)
    {
        _transitions.auto_destroy_position = autoDestroy;
    }

    void autoDestroySize(bool autoDestroy)
    {
        _transitions.auto_destroy_size = autoDestroy;
    }

private:
    lv_obj_t* _lv_obj = NULL;

    struct Transitions_t {
        std::unique_ptr<SmoothUIToolKit::Transition2D> position;
        std::unique_ptr<SmoothUIToolKit::Transition2D> size;
        bool auto_destroy_position = false;
        bool auto_destroy_size = false;
    };
    Transitions_t _transitions;
};

} // namespace smooth_lv_widgets
