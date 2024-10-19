/**
 * @file page_widgets.cpp
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

static const char* _tag = "PageWidgets";

void LauncherPageWidgets::onShow()
{
    mclog::tagInfo(_tag, "on show");
}

void LauncherPageWidgets::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }
}

void LauncherPageWidgets::onBackground() {}

void LauncherPageWidgets::onHide()
{
    mclog::tagInfo(_tag, "on hide");
}
