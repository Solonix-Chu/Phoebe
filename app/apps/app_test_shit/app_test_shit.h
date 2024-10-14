/**
 * @file app_test_shit.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include <mooncake.h>

/**
 * @brief 派生 App
 *
 */
class AppTestShit : public mooncake::AppAbility {
public:
    AppTestShit();

    // 重写生命周期回调
    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;
};
