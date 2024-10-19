/**
 * @file page_watch_face.cpp
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

static const char* _tag = "PageWatchFace";

void LauncherPageWatchFace::onShow()
{
    mclog::tagInfo(_tag, "on show");
}

void LauncherPageWatchFace::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }
}

void LauncherPageWatchFace::onBackground() {}

void LauncherPageWatchFace::onHide()
{
    mclog::tagInfo(_tag, "on hide");
}
