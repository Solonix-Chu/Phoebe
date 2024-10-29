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
#include <src/display/lv_display.h>

using namespace mooncake;
using namespace SmoothUIToolKit;

static const char* _tag = "PageWidgets";

static constexpr int _canvas_start_up_x = 150;
static constexpr int _canvas_start_up_y = 100;
static constexpr int _canvas_start_up_w = 20;
static constexpr int _canvas_start_up_h = 40;
static constexpr int _canvas_x = 10;
static constexpr int _canvas_y = 10;
static constexpr int _canvas_w = 124;
static constexpr int _canvas_h = 68;

static widget::WidgetMouse* _mouse;

void LauncherPageWidgets::onCreate()
{
    _canvas_list.resize(2);
    _mouse = new widget::WidgetMouse(lv_screen_active());
}

void LauncherPageWidgets::onShow()
{
    mclog::tagInfo(_tag, "on show");

    int i = 0;
    for (auto& canvas : _canvas_list) {
        if (!canvas) {
            canvas = std::make_unique<smooth_widget::SmoothWidgetBase>(lv_screen_active());
            canvas->setRadius(16);
            canvas->smoothPosition().setTransitionPath(EasingPath::easeOutQuad);
            canvas->smoothPosition().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
            canvas->smoothSize().setTransitionPath(EasingPath::easeOutBack);
            canvas->smoothSize().jumpTo(_canvas_start_up_w, _canvas_start_up_h);
        }

        canvas->smoothPosition().setDelay(i * 100);
        canvas->smoothPosition().setDuration(300);
        canvas->smoothPosition().moveTo(_canvas_x, _canvas_y + i * 80);
        canvas->smoothSize().setDelay(i * 100 + 100);
        canvas->smoothSize().setDuration(800);
        canvas->smoothSize().moveTo(_canvas_w, _canvas_h);

        i++;
    }

    _mouse->clearAllTargets();
    _mouse->addTarget(_canvas_list[0].get());
    _mouse->addTarget(_canvas_list[1].get());
    mclog::info("shit {} {}", _canvas_list[0]->getX2(), _canvas_list[0]->getY2());
    _mouse->goTo(_canvas_list[0].get());
    mclog::info("??????");
}

void LauncherPageWidgets::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    for (auto& canvas : _canvas_list) {
        if (canvas) {
            canvas->updateSmoothing();
        }
    }
}

void LauncherPageWidgets::onBackground()
{
    for (auto& canvas : _canvas_list) {
        if (canvas) {
            canvas->updateSmoothing();
            if (canvas->isAllSmoothingFinish()) {
                canvas.reset();
                // mclog::tagInfo(_tag, "free shit");
            }
        }
    }
}

void LauncherPageWidgets::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    int i = 0;
    for (auto& canvas : _canvas_list) {
        canvas->smoothPosition().setDelay((_canvas_list.size() - 1 - i) * 50 + 100);
        canvas->smoothPosition().setDuration(300);
        canvas->smoothPosition().moveTo(_canvas_start_up_x, _canvas_start_up_y);
        canvas->smoothSize().setDelay((_canvas_list.size() - 1 - i) * 100);
        canvas->smoothSize().setDuration(800);
        canvas->smoothSize().moveTo(_canvas_start_up_w, _canvas_start_up_h);

        i++;
    }
}
