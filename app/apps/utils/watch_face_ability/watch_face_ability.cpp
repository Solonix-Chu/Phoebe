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
#include <src/misc/lv_color.h>

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

// WidgetClock* _clock;
WidgetFactory* _factory;
int _clock_id;

void WatchFaceAbility::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    duk_helper::call_script_function(_duktape_ctx, _wf_callback_on_create);

    // // Test shit
    // // lv_obj_create(lv_obj_t *parent)
    // auto shit = new WidgetBase(_render_canvas);
    // shit->setBgColor("#000000");
    // shit->setSize(15, 15);
    // shit->setPos(130, 0);

    // delete shit;

    // auto shit2 = new WidgetLabel(_render_canvas);
    // // shit2->setText("10.21 FRI. 啊？！，。\n默抱緊你もあ\nなた的人。");
    // // shit2->setText("10.21 FRI. ??@");
    // shit2->setText(":)");
    // shit2->setPos(5, 5);
    // shit2->setTextColor("#000000");

    // // lv_obj_set_style_text_font(shit2->get(), AssetPool::Font().Zpix12, LV_PART_MAIN);
    // lv_obj_set_style_text_font(shit2->get(), AssetPool::Font().RajdhaniBold16, LV_PART_MAIN);

    // shit2->setFont("RajdhaniBold48");

    // {
    //     auto shit = new WidgetBase(_render_canvas);
    //     shit->setBgColor("#000000");
    //     shit->setAlign("lv_align_top_right");
    //     shit->setPos(0, 0);
    //     shit->setSize(128, 168);
    //     shit->setBorderWidth(0);
    //     shit->setRadius(5);
    // }

    // {
    //     auto shit = new WidgetLabel(_render_canvas);
    //     shit->setPos(-6, 90);
    //     shit->setAlign("lv_align_top_right");
    //     shit->setFont("RajdhaniBold48");
    //     shit->setTextColor("#FFFFFF");
    //     shit->setText("17:37");
    // }

    // {
    //     auto shit = new WidgetLabel(_render_canvas);
    //     shit->setPos(-6, 135);
    //     shit->setAlign("lv_align_top_right");
    //     shit->setFont("RajdhaniBold24");
    //     shit->setTextColor("#FFFFFF");
    //     shit->setText("10.26 SAT.");
    // }

    // {
    //     auto shit = new WidgetLabel(_render_canvas);
    //     shit->setPos(14, -3);
    //     shit->setFont("RajdhaniBold16");
    //     shit->setRotation(900);
    //     shit->setTextColor("#000000");
    //     shit->setText("DATE: 2024.10.26 BAT: 96%");
    // }

    // {
    //     auto shit = new WidgetLabel(_render_canvas);
    //     shit->setPos(32, -3);
    //     shit->setFont("RajdhaniBold16");
    //     shit->setRotation(900);
    //     shit->setTextColor("#FFFFFF");
    //     shit->setText("SETPS: 2333.");
    // }

    // _clock = new WidgetClock(_render_canvas);
    // _clock->centerX = 94;
    // _clock->centerY = 45;
    // _clock->handColor = lv_color_white();
    // _clock->update();

    auto factory = new WidgetFactory();
    factory->setWidgetParent(_render_canvas);

    {
        auto shit = factory->create("base");
        factory->getBase(shit)->setBgColor("#000000");
        factory->getBase(shit)->setAlign("lv_align_top_right");
        factory->getBase(shit)->setPos(0, 0);
        factory->getBase(shit)->setSize(128, 168);
        factory->getBase(shit)->setBorderWidth(0);
        factory->getBase(shit)->setRadius(5);
    }

    {
        auto shit = factory->create("label");
        factory->getLabel(shit)->setPos(-6, 90);
        factory->getLabel(shit)->setAlign("lv_align_top_right");
        factory->getLabel(shit)->setFont("RajdhaniBold48");
        factory->getLabel(shit)->setTextColor("#FFFFFF");
        factory->getLabel(shit)->setText("17:37");
    }

    {
        auto shit = factory->create("label");
        factory->getLabel(shit)->setPos(-6, 135);
        factory->getLabel(shit)->setAlign("lv_align_top_right");
        factory->getLabel(shit)->setFont("RajdhaniBold24");
        factory->getLabel(shit)->setTextColor("#FFFFFF");
        factory->getLabel(shit)->setText("10.26 SAT.");
    }

    {
        auto shit = factory->create("label");
        factory->getLabel(shit)->setPos(14, -3);
        factory->getLabel(shit)->setFont("RajdhaniBold16");
        factory->getLabel(shit)->setRotation(900);
        factory->getLabel(shit)->setTextColor("#000000");
        factory->getLabel(shit)->setText("DATE: 2024.10.26 BAT: 96%");
    }

    {
        auto shit = factory->create("label");
        factory->getLabel(shit)->setPos(32, -3);
        factory->getLabel(shit)->setFont("RajdhaniBold16");
        factory->getLabel(shit)->setRotation(900);
        factory->getLabel(shit)->setTextColor("#FFFFFF");
        factory->getLabel(shit)->setText("SETPS: 2333.");
    }

    {
        auto shit = factory->create("clock");
        factory->getClock(shit)->centerX = 94;
        factory->getClock(shit)->centerY = 45;
        factory->getClock(shit)->handColor = lv_color_white();
        factory->getClock(shit)->update();
        _clock_id = shit;
    }

    _factory = factory;

    // factory->destory(2);
    // factory->destory(4);

    // delete factory;
}

void _test_on_tick_update_shit()
{
    // _clock->update();
    _factory->getClock(_clock_id)->update();

    time_t now;
    struct tm* tm_info;
    time(&now);
    tm_info = localtime(&now);
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

        _test_on_tick_update_shit();

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
