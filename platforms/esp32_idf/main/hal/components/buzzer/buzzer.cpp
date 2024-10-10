/**
 * @file buzzer.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "buzzer.h"
#include "../../hal_config.h"
#include <Arduino.h>
#include <mooncake_log.h>
#include <mutex>

using namespace mooncake;

void BuzzerArduino::init() {}

void BuzzerArduino::beep(float frequency, std::uint32_t duration = 0xFFFFFFFF)
{
    stop();
    tone(HAL_PIN_BUZZ_CTRL, frequency, duration);
}

void BuzzerArduino::stop()
{
    if (isPlaying()) {
        // stop playing
    }
    noTone(HAL_PIN_BUZZ_CTRL);
}

static void _daemon_rtttl_music_player(void* param)
{
    
    vTaskDelete(NULL);
}

void BuzzerArduino::playRtttlMusic(const std::string& rtttlMusic) {}

bool BuzzerArduino::isPlaying()
{
    return false;
}
