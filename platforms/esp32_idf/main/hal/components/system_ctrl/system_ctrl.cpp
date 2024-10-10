/**
 * @file system_ctrl.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "system_ctrl.h"
#include "../../hal_config.h"
#include <Arduino.h>
#include <mooncake_log.h>
#include <mutex>

using namespace mooncake;

// 看门狗线程
static uint8_t _dog = 0;
static std::mutex _feed_mutex;
static void _daemon_watch_dog(void* param)
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        _feed_mutex.lock();
        _dog++;
        if (_dog > HAL_WATCH_DOG_TIMEOUT_S) {
            mclog::error(":(");
            mclog::error("watch dog timeout");
            mclog::error("rebooting..");
            vTaskDelay(pdMS_TO_TICKS(100));
            esp_restart();
        }
        _feed_mutex.unlock();
    }
    vTaskDelete(NULL);
}

void SystemControlArduino::init()
{
    mclog::info("system control init");

    // 锁定电源 MOS 管
    mclog::info("lock power mos");
    pinMode(HAL_PIN_PWR_HOLD, OUTPUT);
    digitalWrite(HAL_PIN_PWR_HOLD, 1);

    // 创建看门狗线程
    mclog::info("create watch dog deamon");
    xTaskCreate(_daemon_watch_dog, "wd", 2000, NULL, configMAX_PRIORITIES - 1, NULL);
}

std::uint32_t SystemControlArduino::millis()
{
    return ::millis();
}

void SystemControlArduino::delay(std::uint32_t ms)
{
    ::delay(ms);
}

void SystemControlArduino::reboot()
{
    mclog::info("reboot system..");
    esp_restart();
}

void SystemControlArduino::powerOff()
{
    mclog::info("power off..");
    delay(100);

    // 释放电源 mos 管
    digitalWrite(HAL_PIN_PWR_HOLD, 0);
    delay(114514);
}

void SystemControlArduino::feedTheDog()
{
    _feed_mutex.lock();
    _dog = 0;
    _feed_mutex.unlock();
}
