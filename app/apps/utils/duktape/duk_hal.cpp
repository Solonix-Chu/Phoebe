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
static duk_ret_t _hal_sysCtrl_delay(duk_context* ctx)
{
    std::uint32_t ms = (std::uint32_t)duk_to_uint(ctx, 0);
    HAL::SysCtrl().delay(ms);
    return 0;
}

static duk_ret_t _hal_sysCtrl_millis(duk_context* ctx)
{
    std::uint32_t ms = HAL::SysCtrl().millis();
    duk_push_uint(ctx, ms);
    return 1;
}

static duk_ret_t _hal_sysCtrl_reboot(duk_context* ctx)
{
    HAL::SysCtrl().reboot();
    return 0;
}

static duk_ret_t _hal_sysCtrl_powerOff(duk_context* ctx)
{
    HAL::SysCtrl().powerOff();
    return 0;
}

static duk_ret_t _hal_sysCtrl_feedTheDog(duk_context* ctx)
{
    HAL::SysCtrl().feedTheDog();
    return 0;
}

static duk_ret_t _hal_sysCtrl_freeHeapSize(duk_context* ctx)
{
    size_t size = HAL::SysCtrl().freeHeapSize();
    duk_push_uint(ctx, (duk_uint_t)size);
    return 1;
}

static void _duk_hal_sysCtrl_init(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _hal_sysCtrl_delay, 1);
    duk_put_prop_string(ctx, -2, "delay");
    duk_push_c_function(ctx, _hal_sysCtrl_millis, 0);
    duk_put_prop_string(ctx, -2, "millis");
    duk_push_c_function(ctx, _hal_sysCtrl_reboot, 0);
    duk_put_prop_string(ctx, -2, "reboot");
    duk_push_c_function(ctx, _hal_sysCtrl_powerOff, 0);
    duk_put_prop_string(ctx, -2, "powerOff");
    duk_push_c_function(ctx, _hal_sysCtrl_feedTheDog, 0);
    duk_put_prop_string(ctx, -2, "feedTheDog");
    duk_push_c_function(ctx, _hal_sysCtrl_freeHeapSize, 0);
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

/* -------------------------------------------------------------------------- */
/*                                   Buzzer                                   */
/* -------------------------------------------------------------------------- */
static duk_ret_t _hal_buzzer_beep(duk_context* ctx)
{
    float frequency = (float)duk_to_number(ctx, 0);
    std::uint32_t duration = (std::uint32_t)duk_opt_uint(ctx, 1, 0xFFFFFFFF);
    HAL::Buzzer().beep(frequency, duration);
    return 0;
}

static duk_ret_t _hal_buzzer_stop(duk_context* ctx)
{
    HAL::Buzzer().stop();
    return 0;
}

static duk_ret_t _hal_buzzer_playRtttlMusic(duk_context* ctx)
{
    const char* rtttlMusic = duk_to_string(ctx, 0);
    HAL::Buzzer().playRtttlMusic(rtttlMusic);
    return 0;
}

static duk_ret_t _hal_buzzer_isPlaying(duk_context* ctx)
{
    bool isPlaying = HAL::Buzzer().isPlaying();
    duk_push_boolean(ctx, isPlaying);
    return 1;
}

static void _duk_hal_buzzer_init(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _hal_buzzer_beep, 2);
    duk_put_prop_string(ctx, -2, "beep");
    duk_push_c_function(ctx, _hal_buzzer_stop, 0);
    duk_put_prop_string(ctx, -2, "stop");
    duk_push_c_function(ctx, _hal_buzzer_playRtttlMusic, 1);
    duk_put_prop_string(ctx, -2, "playRtttlMusic");
    duk_push_c_function(ctx, _hal_buzzer_isPlaying, 0);
    duk_put_prop_string(ctx, -2, "isPlaying");
    duk_put_prop_string(ctx, -2, "buzzer");
}

/* -------------------------------------------------------------------------- */
/*                                Haptic Engine                               */
/* -------------------------------------------------------------------------- */
static duk_ret_t _hal_haptic_enable(duk_context* ctx)
{
    HAL::HapticEngine().enable();
    return 0;
}

static duk_ret_t _hal_haptic_disable(duk_context* ctx)
{
    HAL::HapticEngine().disable();
    return 0;
}

static duk_ret_t _hal_haptic_playEffect(duk_context* ctx)
{
    HAL::HapticEngine().playEffect(static_cast<HapticEffect::HapticEffect_t>(duk_to_uint(ctx, 0)));
    return 0;
}

static duk_ret_t _hal_haptic_playEffects(duk_context* ctx)
{
    duk_require_object_coercible(ctx, 0);
    std::vector<HapticEffect::HapticEffect_t> effectSequence;
    duk_enum(ctx, 0, DUK_ENUM_ARRAY_INDICES_ONLY);

    while (duk_next(ctx, -1, 1)) {
        effectSequence.push_back(static_cast<HapticEffect::HapticEffect_t>(duk_to_uint(ctx, -1)));
        duk_pop_2(ctx); // pop key and value
    }
    HAL::HapticEngine().playEffects(effectSequence);
    return 0;
}

static void _duk_hal_haptic_init(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _hal_haptic_enable, 0);
    duk_put_prop_string(ctx, -2, "enable");
    duk_push_c_function(ctx, _hal_haptic_disable, 0);
    duk_put_prop_string(ctx, -2, "disable");
    duk_push_c_function(ctx, _hal_haptic_playEffect, 1);
    duk_put_prop_string(ctx, -2, "playEffect");
    duk_push_c_function(ctx, _hal_haptic_playEffects, 1);
    duk_put_prop_string(ctx, -2, "playEffects");
    duk_put_prop_string(ctx, -2, "haptic");
}

/* -------------------------------------------------------------------------- */
/*                               Battery Monitor                              */
/* -------------------------------------------------------------------------- */
static duk_ret_t _hal_battery_voltage(duk_context* ctx)
{
    float voltage = HAL::BatteryMonitor().voltage();
    duk_push_number(ctx, voltage);
    return 1;
}

static duk_ret_t _hal_battery_percent(duk_context* ctx)
{
    float percent = HAL::BatteryMonitor().percent();
    duk_push_number(ctx, percent);
    return 1;
}

static void _duk_hal_battery_init(duk_context* ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _hal_battery_voltage, 0);
    duk_put_prop_string(ctx, -2, "voltage");
    duk_push_c_function(ctx, _hal_battery_percent, 0);
    duk_put_prop_string(ctx, -2, "percent");
    duk_put_prop_string(ctx, -2, "batteryMonitor");
}

void duk_hal_init(duk_context* ctx)
{
    mclog::tagInfo(_tag, "init");
    duk_push_object(ctx);
    _duk_hal_sysCtrl_init(ctx);
    _duk_hal_imu_init(ctx);
    _duk_hal_buzzer_init(ctx);
    _duk_hal_haptic_init(ctx);
    _duk_hal_battery_init(ctx);
    duk_put_global_string(ctx, "hal");

    // HAL::BtnUpdate();
    // HAL::BtnUp().wasClicked();
    // HAL::BtnUp().wasDoubleClicked();
    // HAL::BtnUp().wasHold();
    // HAL::BtnUp().isPressed();
    // HAL::BtnUp().isHolding();
    // HAL::BtnPower()...
    // HAL::BtnOk()...
    // HAL::BtnDown()...
}
