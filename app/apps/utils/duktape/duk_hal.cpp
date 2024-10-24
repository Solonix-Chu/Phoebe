/**
 * @file duk_hal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "duk_hal.h"
#include <mooncake_log.h>
#include <hal/hal.h>

using namespace mooncake;

static const char* _tag = "DukHal";

/* -------------------------------------------------------------------------- */
/*                               System control                               */
/* -------------------------------------------------------------------------- */
static duk_ret_t _hal_sys_ctrl_delay(duk_context* ctx)
{
    std::uint32_t ms = (std::uint32_t)duk_to_uint(ctx, 0);
    HAL::SysCtrl().delay(ms);
    return 0;
}

static duk_ret_t _hal_sys_ctrl_millis(duk_context* ctx)
{
    std::uint32_t ms = HAL::SysCtrl().millis();
    duk_push_uint(ctx, ms);
    return 1;
}

static duk_ret_t _hal_sys_ctrl_reboot(duk_context* ctx)
{
    HAL::SysCtrl().reboot();
    return 0;
}

static duk_ret_t _hal_sys_ctrl_powerOff(duk_context* ctx)
{
    HAL::SysCtrl().powerOff();
    return 0;
}

static duk_ret_t _hal_sys_ctrl_feedTheDog(duk_context* ctx)
{
    HAL::SysCtrl().feedTheDog();
    return 0;
}

static duk_ret_t _hal_sys_ctrl_freeHeapSize(duk_context* ctx)
{
    size_t size = HAL::SysCtrl().freeHeapSize();
    duk_push_uint(ctx, (duk_uint_t)size);
    return 1;
}

static void _duk_hal_sys_ctrl_init(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _hal_sys_ctrl_delay, 1);
    duk_put_prop_string(ctx, -2, "delay");
    duk_push_c_function(ctx, _hal_sys_ctrl_millis, 0);
    duk_put_prop_string(ctx, -2, "millis");
    duk_push_c_function(ctx, _hal_sys_ctrl_reboot, 0);
    duk_put_prop_string(ctx, -2, "reboot");
    duk_push_c_function(ctx, _hal_sys_ctrl_powerOff, 0);
    duk_put_prop_string(ctx, -2, "powerOff");
    duk_push_c_function(ctx, _hal_sys_ctrl_feedTheDog, 0);
    duk_put_prop_string(ctx, -2, "feedTheDog");
    duk_push_c_function(ctx, _hal_sys_ctrl_freeHeapSize, 0);
    duk_put_prop_string(ctx, -2, "freeHeapSize");
    duk_put_prop_string(ctx, -2, "sysCtrl");
}

/* -------------------------------------------------------------------------- */
/*                                     IMU                                    */
/* -------------------------------------------------------------------------- */
static duk_ret_t _hal_imu_update(duk_context* ctx)
{
    HAL::Imu().update();
    return 0;
}

static duk_ret_t _hal_imu_getData(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_number(ctx, HAL::Imu().getData().accelX);
    duk_put_prop_string(ctx, -2, "accelX");
    duk_push_number(ctx, HAL::Imu().getData().accelY);
    duk_put_prop_string(ctx, -2, "accelY");
    duk_push_number(ctx, HAL::Imu().getData().accelZ);
    duk_put_prop_string(ctx, -2, "accelZ");
    duk_push_number(ctx, HAL::Imu().getData().gyroX);
    duk_put_prop_string(ctx, -2, "gyroX");
    duk_push_number(ctx, HAL::Imu().getData().gyroY);
    duk_put_prop_string(ctx, -2, "gyroY");
    duk_push_number(ctx, HAL::Imu().getData().gyroZ);
    duk_put_prop_string(ctx, -2, "gyroZ");

    return 1;
}

static void _duk_hal_imu_init(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _hal_imu_update, 0);
    duk_put_prop_string(ctx, -2, "update");
    duk_push_c_function(ctx, _hal_imu_getData, 0);
    duk_put_prop_string(ctx, -2, "getData");
    duk_put_prop_string(ctx, -2, "imu");
}

void duk_hal_init(duk_context* ctx)
{
    mclog::tagInfo(_tag, "init");
    duk_push_object(ctx);
    _duk_hal_sys_ctrl_init(ctx);
    _duk_hal_imu_init(ctx);
    duk_put_global_string(ctx, "hal");
}
