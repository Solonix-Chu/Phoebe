/**
 * @file hal_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "esp32-hal.h"
#include "hal_esp32.h"
#include <mooncake_log.h>
#include <Arduino.h>

using namespace mooncake;

void HalEsp32::hal_test()
{
    /* ---------------------------------- Test ---------------------------------- */
    // imu_test();
    // buzzer_test();
}

void HalEsp32::imu_test()
{
    while (1) {
        GetHAL().Imu().update();
        mclog::info("{:0.2f}\t{:0.2f}\t{:0.2f}\t|\t{:0.2f}\t{:0.2f}\t{:0.2f}", GetHAL().Imu().getData().accelX,
                    GetHAL().Imu().getData().accelY, GetHAL().Imu().getData().accelZ, GetHAL().Imu().getData().gyroX,
                    GetHAL().Imu().getData().gyroY, GetHAL().Imu().getData().gyroZ);

        delay(50);
        GetHAL().SystemControl().feedTheDog();
    }
}

void HalEsp32::buzzer_test()
{
    while (1) {
        mclog::info("is playing: {}", GetHAL().Buzzer().isPlaying());
        GetHAL().Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

        while (GetHAL().Buzzer().isPlaying()) {
            mclog::info("is playing: {}", GetHAL().Buzzer().isPlaying());
            GetHAL().SystemControl().feedTheDog();
            delay(1000);
        }

        // 打断测试
        int interval = 2000;
        while (interval >= 500) {
            GetHAL().Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

            mclog::info("delay {}", interval);
            delay(interval);
            interval -= 500;
            GetHAL().SystemControl().feedTheDog();
        }

        interval = 500;
        while (interval >= 20) {
            GetHAL().Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

            mclog::info("delay {}", interval);
            delay(interval);
            interval -= 20;
            GetHAL().SystemControl().feedTheDog();
        }
    }
}
