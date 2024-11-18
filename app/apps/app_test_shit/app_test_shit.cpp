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
}

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");
}

void AppTestShit::onRunning()
{
    auto ret = CreateSelecMenuPageAndWaitResult(
        [](std::vector<std::string>& optionList, size_t& startupIndex) {
            optionList.push_back("1111");
            optionList.push_back("23525");
            optionList.push_back("asf af dd");
            optionList.push_back("??? &(**&)vdssdvsdvdvdsv");
            optionList.push_back("6666..");
            optionList.push_back("*** fasf??? dsd");
            optionList.push_back("*** fasf??? dsd");
            optionList.push_back("1111");
            optionList.push_back("23525");
            optionList.push_back("asf af dd");
            optionList.push_back("??? &(**&)vdssdvsdvdvdsv");
            optionList.push_back("6666..");
            optionList.push_back("*** fasf??? dsd");
            optionList.push_back("*** fasf??? dsd");

            // startupIndex = 2;
        },
        [](int selectIndex, std::string& option) { mclog::info("on select {} {}", selectIndex, option); });
    mclog::info("ret: {}", ret);
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
}
