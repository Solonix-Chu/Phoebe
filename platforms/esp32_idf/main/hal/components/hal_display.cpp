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
#include <M5GFX.h>
#include "utils/m5gfx_panel_sharpe_mlcd/panel_sharpe_mlcd.h"
#include "utils/sharpe_mlcd/sharpe_mlcd.h"

using namespace mooncake;

class LGFX_Phoebe : public LGFX_Device {
public:
    lgfx::PanelSharpMlcd _panel_instance;

    LGFX_Phoebe(SharpeMlcd* sharpMlcd)
    {
        _panel_instance.setSharpMlcdInstance(sharpMlcd);
        auto cfg = _panel_instance.config();
        cfg.panel_width = sharpMlcd->getConfig().screen_width;
        cfg.panel_height = sharpMlcd->getConfig().screen_height;
        _panel_instance.config(cfg);

        setPanel(&_panel_instance);
    }
};

/**
 * @brief 派生组件
 *
 */
class DisplayEsp32 : public hal_components::DisplayM5GFXBase {
public:
    bool init() override
    {
        _sharp_mlcd = new SharpeMlcd;
        _sharp_mlcd->setConfig().screen_width = HAL_SCREEN_WIDTH;
        _sharp_mlcd->setConfig().screen_height = HAL_SCREEN_HEIGHT;
        _sharp_mlcd->setConfig().pin_scs = HAL_PIN_MLCD_SCS;
        _sharp_mlcd->setConfig().pin_sclk = HAL_PIN_MLCD_SCLK;
        _sharp_mlcd->setConfig().pin_si = HAL_PIN_MLCD_SI;
        _sharp_mlcd->setConfig().spi_clk_freq = 2000000;
        _sharp_mlcd->init();

        _display = new LGFX_Phoebe(_sharp_mlcd);
        _display->init();
        _display->setRotation(2);

        _canvas = new LGFX_Sprite(_display);
        _canvas->createSprite(144, 168);

        // while (1) {
        mclog::info("bbb");
        _sharp_mlcd->clearScreen();
        lgfx::delay(1000);
        // }

        return true;
    }

    LGFX_Device& display() override
    {
        return *_display;
    }

    LGFX_Sprite& canvas() override
    {
        return *_canvas;
    }

    void pushCanvas() override
    {
        _canvas->pushSprite(0, 0);
    }

private:
    SharpeMlcd* _sharp_mlcd;
    LGFX_Device* _display;
    LGFX_Sprite* _canvas;
};

void HalEsp32::_display_init()
{
    mclog::info("display init");

    initArduino();

    // lgfx::pinMode(HAL_PIN_PWR_HOLD, lgfx::pin_mode_t::output);
    // lgfx::gpio_hi(HAL_PIN_PWR_HOLD);
    // lgfx::delay(100);

    // tone(HAL_PIN_BUZZ_CTRL, 400, 300);

    // 创建组件实例
    _components.display_m5gfx = std::make_unique<DisplayEsp32>();
    _components.display_m5gfx->init();

    /* -------------------------------------------------------------------------- */
    /*                                    Test                                    */
    /* -------------------------------------------------------------------------- */
    while (1) {
        mclog::info("www");
        // HalGetCanvas().fillScreen(TFT_WHITE);
        // HalPushCanvas();
        _components.display_m5gfx->display().fillScreen(TFT_WHITE);
        // _components.display_m5gfx->pushCanvas();
        // lgfx::delay(1000);

        mclog::info("bbb");
        // HalGetCanvas().fillScreen(TFT_BLACK);
        // HalPushCanvas();
        _components.display_m5gfx->display().fillScreen(TFT_BLACK);
        // _components.display_m5gfx->pushCanvas();
        lgfx::delay(1000);
    }
}
