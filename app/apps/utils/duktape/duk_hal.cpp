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
    duk_put_prop_string(ctx, -2, "sysCtrl");
}

void duk_hal_init(duk_context* ctx)
{
    mclog::tagInfo(_tag, "init");

    duk_push_object(ctx);

    _duk_hal_sys_ctrl_init(ctx);

    duk_put_global_string(ctx, "hal");
}
