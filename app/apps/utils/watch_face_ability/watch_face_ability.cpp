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
#include <mooncake_log.h>
#include <hal/hal.h>
#include <assets/assets.h>

using namespace mooncake;
using namespace widget;

static const char* _tag = "WatchFaceAbility";
static const char* _wf_callback_on_create = "wf_on_create";
static const char* _wf_callback_on_resume = "wf_on_resume";
static const char* _wf_callback_on_pause = "wf_on_pause";
static const char* _wf_callback_on_tick = "wf_on_tick";

static const std::string _default_watch_face_script = R"(
function wf_on_create() {
  console.log("on create")
}

function wf_on_resume() {
  console.log("on resume")
}

function wf_on_tick() {
  console.log("on tick")
}

function wf_on_pause() {
  console.log("on pause")
}
)";

void WatchFaceAbility::init(lv_obj_t* widgetParent)
{
    mclog::tagInfo(_tag, "init");
    _js_runtime.loadConsoleBinding();
    _js_runtime.loadWidgetBinding(widgetParent);

    // TODO
    // Load script from fs
    _js_runtime.evaluation(_default_watch_face_script);
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
