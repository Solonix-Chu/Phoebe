/**
 * @file battery_monitor.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <functional>

namespace hal_components {

/**
 * @brief 电池监视基类
 *
 */
class BatteryMonitorBase {
public:
    virtual bool init()
    {
        return false;
    }

    virtual float voltage()
    {
        return 0.0f;
    }

    virtual float percent()
    {
        return 0.0f;
    }

    virtual bool isCharging()
    {
        return false;
    }

    virtual void onChargingStart(std::function<void()> callback) {}

    virtual void onChargingComplete(std::function<void()> callback) {}

    virtual void onLowBattery(std::function<void()> callback) {}
};

} // namespace hal_components
