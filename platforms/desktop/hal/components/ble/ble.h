/**
 * @file ble.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-11-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class BlePython : public hal_components::BleBase {
public:
    void init() override;
};
