/**
 * @file app_ble_manager.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-11-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>

/**
 * @brief 派生 App
 *
 */
class AppBleManager : public mooncake::AppAbility {
public:
    AppBleManager();

    // 重写生命周期回调
    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;

private:
    uint32_t _time_count = 0;

    void handle_ble_message();
};
