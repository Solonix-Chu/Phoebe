/**
 * @file label.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widget.h"
#include <lvgl.h>
#include <src/widgets/label/lv_label.h>

using namespace widget;

Label::Label(lv_obj_t* parent)
{
    _lv_obj = lv_label_create(parent);
}
