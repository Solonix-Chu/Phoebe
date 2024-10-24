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

  hal.imu.update();
  var imuData = hal.imu.getData();
  console.log(
    'IMU Data - accelX: ' + imuData.accelX.toFixed(1) + ', accelY: ' + imuData.accelY.toFixed(1) + ', accelZ: ' + imuData.accelZ.toFixed(1) + ', ' +
    'gyroX: ' + imuData.gyroX.toFixed(1) + ', gyroY: ' + imuData.gyroY.toFixed(1) + ', gyroZ: ' + imuData.gyroZ.toFixed(1)
  );
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

void AppTestShit::onOpen()
{
    mclog::tagInfo(_tag, "on open");

    _duktape_ctx = duk_create_heap_default();

    duk_console_init(_duktape_ctx, DUK_CONSOLE_STDOUT_ONLY);
    duk_hal_init(_duktape_ctx);

    duk_eval_string(_duktape_ctx, _script.c_str());

    _call_script_api(_duktape_ctx, _script_api_on_app_open);
}

void AppTestShit::onRunning()
{
    _call_script_api(_duktape_ctx, _script_api_on_app_update);
}

void AppTestShit::onClose()
{
    mclog::tagInfo(_tag, "on close");
    duk_destroy_heap(_duktape_ctx);
}
