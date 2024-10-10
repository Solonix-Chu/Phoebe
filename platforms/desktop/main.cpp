/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <app.h>
#include <memory>
#include <hal/hal.h>
#include "hal/hal_desktop.h"

int main()
{
    // 应用层初始化回调
    app::InitCallback_t callback;

    callback.onHalInjection = []() {
        // 注入桌面平台的硬件抽象
        hal::Inject(std::make_unique<HalDesktop>());
    };

    // 应用层启动
    app::Init(callback);
    while (!app::IsDone()) {
        app::Update();
    }
    app::Destroy();

    return 0;
}
