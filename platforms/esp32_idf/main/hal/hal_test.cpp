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
#include "hal_esp32.h"
#include <mooncake_log.h>
#include <Arduino.h>

using namespace mooncake;

void HalEsp32::hal_test()
{
    /* ---------------------------------- Test ---------------------------------- */
    imu_test();
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
