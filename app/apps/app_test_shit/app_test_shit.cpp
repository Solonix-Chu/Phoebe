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

using namespace mooncake;
using namespace widget;

#define _tag (getAppInfo().name)

AppTestShit::AppTestShit()
{
    setAppInfo().name = "AppTestShit";
}

static WidgetMouse* _selector;

static WidgetBase* _shit1;
static WidgetBase* _shit2;
static WidgetBase* _shit3;

void handle_input_event_111(InputEvent_t event)
{
    mclog::info("shit111 {}", (int)event.type);
}

void handle_input_event_222(InputEvent_t event)
{
    mclog::info("shit222: {}", (int)event.type);
}

void handle_input_event_333(InputEvent_t event)
{
    mclog::info("shit333: {}", (int)event.type);
}

void AppTestShit::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    open();

    _shit1 = new WidgetBase(lv_screen_active());
    _shit1->setPos(20, 20);
    _shit1->setSize(100, 32);
    _shit1->onHover = handle_input_event_111;
    _shit1->onClick = handle_input_event_111;
    _shit1->onMouseLeave = handle_input_event_111;
    _shit2 = new WidgetBase(lv_screen_active());
    _shit2->setPos(20, 20 + 40);
    _shit2->setSize(100, 32);
    _shit2->onHover = handle_input_event_222;
    _shit2->onClick = handle_input_event_222;
    _shit2->onMouseLeave = handle_input_event_222;
    _shit3 = new WidgetBase(lv_screen_active());
    _shit3->setPos(20, 20 + 40 + 40);
    _shit3->setSize(100, 32);
    _shit3->onHover = handle_input_event_333;
    _shit3->onClick = handle_input_event_333;
    _shit3->onMouseLeave = handle_input_event_333;

    _selector = new WidgetMouse(lv_screen_active());
    _selector->addTargetWidget(_shit1);
    _selector->addTargetWidget(_shit2);
    _selector->addTargetWidget(_shit3);
    // _selector->goInLoop = false;
    mclog::info("shit1 {} {}", _shit1->getX(), _shit1->getY());
    _selector->goTo(_shit1);
}

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");
}

void AppTestShit::onRunning()
{
    HAL::BtnUpdate();
    if (HAL::BtnUp().wasClicked()) {
        _selector->goLast();
        mclog::info("?? go last {}", _selector->getCurrentTargetIndex());
    }
    if (HAL::BtnDown().wasClicked()) {
        _selector->goNext();
        mclog::info("?? go next {}", _selector->getCurrentTargetIndex());
    }
    if (HAL::BtnOk().wasClicked()) {
        _selector->click();
    }
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
}
