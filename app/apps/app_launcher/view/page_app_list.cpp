/**
 * @file page_app_list.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "page.h"
#include <hal/hal.h>
#include <mooncake_log.h>

using namespace mooncake;

static const char* _tag = "PageAppList";

void LauncherPageAppList::onShow()
{
    mclog::tagInfo(_tag, "on show");
}

void LauncherPageAppList::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }
}

void LauncherPageAppList::onBackground() {}

void LauncherPageAppList::onHide()
{
    mclog::tagInfo(_tag, "on hide");
}
