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
#include <memory>
#include <mooncake_log.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/lv_api_map_v8.h>
#include <src/misc/lv_color.h>
#include <src/misc/lv_style.h>

using namespace mooncake;
using namespace SmoothUIToolKit;

static const char* _tag = "PageWatchFace";

static std::string _temp_wf_script = R"(
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

static constexpr int _canvas_start_up_x = 150;
static constexpr int _canvas_start_up_y = 32;
static constexpr int _canvas_start_up_w = 20;
static constexpr int _canvas_start_up_h = 40;
static constexpr int _canvas_x = 0;
static constexpr int _canvas_y = 0;
static constexpr int _canvas_w = 144;
static constexpr int _canvas_h = 168;

void LauncherPageWatchFace::onCreate()
{
    mclog::tagInfo(_tag, "on create");

    _canvas = std::make_unique<smooth_lv_widgets::LvObj>(lv_obj_create(lv_screen_active()));
    _canvas->setBorderWidth(0);
    _canvas->setRadius(5);
    lv_obj_set_style_outline_width(_canvas->get(), 2, LV_PART_MAIN);
    lv_obj_set_style_outline_color(_canvas->get(), lv_color_black(), LV_PART_MAIN);
    _canvas->Position().setTransitionPath(EasingPath::easeOutBack);
    _canvas->Size().setTransitionPath(EasingPath::easeOutBack);
    _canvas->Position().jumpTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->Size().jumpTo(_canvas_start_up_w, _canvas_start_up_h);

    // Create watch face ability
    _watch_face_ability = std::make_unique<WatchFaceAbility>();
    _watch_face_ability->setRenderCanvas(_canvas->get());
    // Load watch face script
    _watch_face_ability->pushScript(_temp_wf_script.c_str());
    // Trigger ability on create
    _watch_face_ability->baseCreate();
}

void LauncherPageWatchFace::onShow()
{
    mclog::tagInfo(_tag, "on show");

    _canvas->Position().setDuration(800);
    _canvas->Position().setDelay(0);
    _canvas->Size().setDuration(800);
    _canvas->Size().setDelay(100);
    _canvas->Position().moveTo(_canvas_x, _canvas_y);
    _canvas->Size().moveTo(_canvas_w, _canvas_h);
    lv_obj_move_foreground(_canvas->get());

    _watch_face_ability->resume();
}

void LauncherPageWatchFace::onForeground()
{
    if (isOnSubPage() && HAL::BtnPower().wasClicked()) {
        quitSubPage();
    }

    _canvas->update();
    _watch_face_ability->baseUpdate();
}

void LauncherPageWatchFace::onBackground()
{
    _canvas->update();
    _watch_face_ability->baseUpdate();
}

void LauncherPageWatchFace::onHide()
{
    mclog::tagInfo(_tag, "on hide");

    _canvas->Position().setDuration(800);
    _canvas->Position().setDelay(100);
    _canvas->Size().setDuration(800);
    _canvas->Size().setDelay(0);
    _canvas->Position().moveTo(_canvas_start_up_x, _canvas_start_up_y);
    _canvas->Size().moveTo(_canvas_start_up_w, _canvas_start_up_h);
    lv_obj_move_background(_canvas->get());

    _watch_face_ability->pause();
}
