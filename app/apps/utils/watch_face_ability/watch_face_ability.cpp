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
#include "../duktape/duktape.h"
#include "../duktape/duk_console.h"
#include "../duktape/duk_helper.h"
#include "../widgets/widget.h"
#include <mooncake_log.h>
#include <hal/hal.h>
#include <assets/assets.h>
#include <src/core/lv_obj_style_gen.h>

using namespace mooncake;
using namespace widget;

static const char* _tag = "WatchFaceAbility";
static const char* _wf_callback_on_create = "wf_on_create";
static const char* _wf_callback_on_resume = "wf_on_resume";
static const char* _wf_callback_on_pause = "wf_on_pause";
static const char* _wf_callback_on_tick = "wf_on_tick";
// static const char* _wf_callback_on_destroy = "wf_on_destroy";

WatchFaceAbility::WatchFaceAbility()
{
    // Create duktape heap and load api binging
    _duktape_ctx = duk_create_heap_default();
    duk_console_init(_duktape_ctx, DUK_CONSOLE_STDOUT_ONLY);
}

WatchFaceAbility::~WatchFaceAbility()
{
    duk_destroy_heap(_duktape_ctx);
}

void WatchFaceAbility::pushScript(const char* scriptContent)
{
    duk_eval_string(_duktape_ctx, scriptContent);
}

void WatchFaceAbility::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    duk_helper::call_script_function(_duktape_ctx, _wf_callback_on_create);

    // Test shit
    // lv_obj_create(lv_obj_t *parent)
    auto shit = new WidgetBase(_render_canvas);
    shit->setBgColor("#000000");
    shit->setSize(15, 15);
    shit->setPos(130, 0);

    // delete shit;

    auto shit2 = new WidgetLabel(_render_canvas);
    shit2->setText("10.21 FRI. 啊？！，。\n默抱緊你もあ\nなた的人。");
    // shit2->setText("10.21 FRI. ??@");
    shit2->setPos(5, 5);
    shit2->setTextColor("#000000");

    lv_obj_set_style_text_font(shit2->get(), AssetPool::Font().zpix12, LV_PART_MAIN);
    // lv_obj_set_style_text_font(shit2->get(), AssetPool::Font().RajdhaniBold144, LV_PART_MAIN);
}

void WatchFaceAbility::onResume()
{
    mclog::tagInfo(_tag, "on resume");
    duk_helper::call_script_function(_duktape_ctx, _wf_callback_on_resume);
}

void WatchFaceAbility::onRunning()
{
    // Call on tick every 1s
    if (HAL::SysCtrl().millis() - _tick_time_count > 1000) {
        duk_helper::call_script_function(_duktape_ctx, _wf_callback_on_tick);
        _tick_time_count = HAL::SysCtrl().millis();
    }
}

void WatchFaceAbility::onPause()
{
    mclog::tagInfo(_tag, "on pause");
    duk_helper::call_script_function(_duktape_ctx, _wf_callback_on_pause);
}

void WatchFaceAbility::onDestroy()
{
    mclog::tagInfo(_tag, "on destroy");
}
