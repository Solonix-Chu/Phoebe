/**
 * @file watch_face_ability.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "watch_face_ability.h"
#include "../debug/debug.h"
#include <mooncake_log.h>
#include <hal/hal.h>
#include <assets/assets.h>

using namespace mooncake;
using namespace widget;
using namespace debug;

static const char* _tag = "WatchFaceAbility";
static const char* _wf_callback_on_create = "wf_on_create";
static const char* _wf_callback_on_resume = "wf_on_resume";
static const char* _wf_callback_on_pause = "wf_on_pause";
static const char* _wf_callback_on_tick = "wf_on_tick";
#include "default.js"

void WatchFaceAbility::init(lv_obj_t* widgetParent)
{
    mclog::tagInfo(_tag, "init");
    log_heap_usage();
    _js_runtime.loadConsoleBinding();
    log_heap_usage();
    _js_runtime.loadHalBinding();
    log_heap_usage();
    _js_runtime.loadWidgetBinding(widgetParent);
    log_heap_usage();

    // TODO
    // Load script from fs
    _js_runtime.evaluate(_default_watch_face_script);
    log_heap_usage();
}

void WatchFaceAbility::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    _js_runtime.callScriptFunction(_wf_callback_on_create);
}

void WatchFaceAbility::onResume()
{
    mclog::tagInfo(_tag, "on resume");
    _js_runtime.callScriptFunction(_wf_callback_on_resume);
}

void WatchFaceAbility::onRunning()
{
    // Tick every 1s
    if (HAL::SysCtrl().millis() - _tick_time_count > 1000) {
        _js_runtime.callScriptFunction(_wf_callback_on_tick);
        log_heap_usage();
        _tick_time_count = HAL::SysCtrl().millis();
    }
}

void WatchFaceAbility::onPause()
{
    mclog::tagInfo(_tag, "on pause");
    _js_runtime.callScriptFunction(_wf_callback_on_pause);
}

void WatchFaceAbility::onDestroy()
{
    mclog::tagInfo(_tag, "on destroy");
}
