/**
 * @file app_test_shit.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_test_shit.h"
#include <mooncake_log.h>
#include <hal/hal.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_timer.h>
#include "../utils/widget/widget.h"
#include "../utils/page/page.h"

using namespace mooncake;
using namespace widget;
using namespace smooth_widget;
using namespace page;

static PageSelectMenu* _menu;

#define _tag (getAppInfo().name)

AppTestShit::AppTestShit()
{
    setAppInfo().name = "AppTestShit";
}

void AppTestShit::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    open();

    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);

    _menu = new PageSelectMenu;
}

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");

    _menu->optionList.push_back("1111");
    _menu->optionList.push_back("23525");
    _menu->optionList.push_back("asf af dd");
    _menu->optionList.push_back("??? &(**&)");
    _menu->optionList.push_back("6666..");

    _menu->create();
    _menu->show();
}

void AppTestShit::onRunning()
{
    _menu->update();
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
}
