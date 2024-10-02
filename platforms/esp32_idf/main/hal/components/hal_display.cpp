/**
 * @file hal_display.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_esp32.h"
#include "../hal_config.h"
#include <mooncake_log.h>
#include <memory>
#include "utils/sharpe_mlcd/sharpe_mlcd.h"

using namespace mooncake;

static SharpeMlcd* _sharp_mlcd = nullptr;

SharpeMlcd* __get_sharpe_lcd()
{
    return _sharp_mlcd;
}

/**
 * @brief 派生组件
 *
 */
class DisplayEsp32 : public hal_components::DisplayBase {
public:
private:
};

void HalEsp32::display_init()
{
    mclog::info("display init");

    initArduino();

    // lgfx::pinMode(HAL_PIN_PWR_HOLD, lgfx::pin_mode_t::output);
    // lgfx::gpio_hi(HAL_PIN_PWR_HOLD);
    // lgfx::delay(100);

    tone(HAL_PIN_BUZZ_CTRL, 400, 300);

    // // 创建组件实例
    // _components.display = std::make_unique<DisplayEsp32>();

    _sharp_mlcd = new SharpeMlcd;
    _sharp_mlcd->setConfig().screen_width = HAL_SCREEN_WIDTH;
    _sharp_mlcd->setConfig().screen_height = HAL_SCREEN_HEIGHT;
    _sharp_mlcd->setConfig().pin_scs = HAL_PIN_MLCD_SCS;
    _sharp_mlcd->setConfig().pin_sclk = HAL_PIN_MLCD_SCLK;
    _sharp_mlcd->setConfig().pin_si = HAL_PIN_MLCD_SI;
    _sharp_mlcd->setConfig().spi_clk_freq = 4000000;
    _sharp_mlcd->setConfig().rotation = 2;
    _sharp_mlcd->init();

    _sharp_mlcd->clearScreen();
}
