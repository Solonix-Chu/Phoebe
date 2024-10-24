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
#include "../utils/duktape/duktape.h"
#include "../utils/duktape/duk_console.h"
#include "../utils/duktape/duk_hal.h"
#include "lgfx/v1/misc/enum.hpp"

using namespace mooncake;

#define _tag (getAppInfo().name)

duk_context* _duktape_ctx;

std::string _script = R"(
var app_name = "app sb";

function onAppOpen() {
  console.log(app_name + " on open");
}

function onAppUpdate() {
  // console.log(app_name + " on update " + hal.sysCtrl.millis() + " " + hal.sysCtrl.freeHeapSize());
  // hal.sysCtrl.delay(200)

  // while (1) {
  //   console.log(app_name + " on update " + hal.sysCtrl.millis() + " " + hal.sysCtrl.freeHeapSize());
  //   hal.sysCtrl.delay(200)
  //   hal.sysCtrl.feedTheDog()
  // }

  // hal.imu.update();
  // var imuData = hal.imu.getData();
  // console.log(
  //   'IMU Data - accelX: ' + imuData.accelX.toFixed(1) + ', accelY: ' + imuData.accelY.toFixed(1) + ', accelZ: ' + imuData.accelZ.toFixed(1) + ', ' +
  //   'gyroX: ' + imuData.gyroX.toFixed(1) + ', gyroY: ' + imuData.gyroY.toFixed(1) + ', gyroZ: ' + imuData.gyroZ.toFixed(1)
  // );

  // console.log("bat: " + hal.batteryMonitor.voltage().toFixed(1) + "v " + hal.batteryMonitor.percent().toFixed(1) + "%")

  // hal.haptic.playEffects([1, 2, 3, 4]);
  // hal.sysCtrl.delay(800)

  hal.btnUpdate()

  if (hal.btnPower.wasClicked()) {
    console.log("ppp cc");
  } else if (hal.btnPower.wasDoubleClicked()) {
    console.log("ppp ddcc");
  } else if (hal.btnPower.wasHold()) {
    console.log("ppp hhh");
    hal.sysCtrl.powerOff()
  }

  if (hal.btnUp.wasClicked()) {
    console.log("up cc");
  }

  if (hal.btnOk.wasClicked()) {
    console.log("ok cc");
  }

  if (hal.btnDown.wasClicked()) {
    console.log("down cc");
  }
}

function onAppClose() {
  console.log(app_name + " on close");
}
)";

static const char* _script_api_on_app_open = "onAppOpen";
static const char* _script_api_on_app_update = "onAppUpdate";
static const char* _script_api_on_app_close = "onAppClose";

void _call_script_api(duk_context* ctx, const char* api)
{
    duk_get_global_string(ctx, api);
    if (duk_pcall(ctx, 0) != 0) {
        // printf("Error: %s\n", duk_safe_to_string(ctx, -1));
        mclog::error("call script api: {} error: {}", api, duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx); /* ignore result */
}

AppTestShit::AppTestShit()
{
    setAppInfo().name = "AppTestShit";
}

void AppTestShit::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    open();
}

void _log_free_heap_shit()
{
    static auto current_free_heap = HAL::SysCtrl().freeHeapSize();
    mclog::info("free heap: {}, {} used", HAL::SysCtrl().freeHeapSize(),
                current_free_heap - HAL::SysCtrl().freeHeapSize());
    current_free_heap = HAL::SysCtrl().freeHeapSize();
}

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");

    _log_free_heap_shit();

    mclog::info("create duk heap..");
    _duktape_ctx = duk_create_heap_default();
    _log_free_heap_shit();

    mclog::info("load console api..");
    duk_console_init(_duktape_ctx, DUK_CONSOLE_STDOUT_ONLY);
    _log_free_heap_shit();

    mclog::info("load hal api..");
    duk_hal_init(_duktape_ctx);
    _log_free_heap_shit();

    mclog::info("laod script..");
    duk_eval_string(_duktape_ctx, _script.c_str());
    _log_free_heap_shit();

    _call_script_api(_duktape_ctx, _script_api_on_app_open);

    HAL::Display().resetScreen();

    HAL::Display().fillScreen(TFT_BLACK);
    // HAL::Display().fillSmoothRoundRect(50, 70, 25, 88, 12, TFT_RED);
    HAL::Display().fillRoundRect(50, 70, 25, 88, 12, TFT_WHITE);
    HAL::Display().drawCircle(30, 40, 50, TFT_WHITE);
    HAL::Display().setTextSize(2);
    HAL::Display().drawString("????niafsfjiJIJ", 5, 100);
    HAL::Display().pushToScreen();

    // HAL::Display().resetScreen();

    // while (1) {
    // }
}

void AppTestShit::onRunning()
{
    _call_script_api(_duktape_ctx, _script_api_on_app_update);

    // HAL::Display().fillScreen(TFT_BLACK);
    // // HAL::Display().fillSmoothRoundRect(50, 70, 25, 88, 12, TFT_RED);
    // HAL::Display().fillRoundRect(50, 70, 25, 88, 12, TFT_WHITE);
    // HAL::Display().drawCircle(30, 40, 50, TFT_WHITE);
    // HAL::Display().setTextSize(2);
    // HAL::Display().drawString("????niafsfjiJIJ", 5, 100);
    // HAL::Display().pushToScreen();
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
    duk_destroy_heap(_duktape_ctx);
}
