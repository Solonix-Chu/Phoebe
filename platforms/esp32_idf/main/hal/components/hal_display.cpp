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
#include <Arduino.h>
#include <SPI.h>
#include "utils/m5gfx_panel_sharpe_mlcd/panel_sharpe_mlcd.h"
#include "utils/sharpe_mlcd/sharpe_mlcd.h"
// https://github.com/adafruit/Adafruit_SHARP_Memory_Display/blob/master/Adafruit_SharpMem.h

using namespace mooncake;

class LGFX_Phoebe : public lgfx::LGFX_Device {
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

    void updateCanvas() override
    {
        _canvas->pushSprite(0, 0);
    }

private:
    std::unique_ptr<LGFX_Device> _display;
    std::unique_ptr<LGFX_Sprite> _canvas;
};

void HalEsp32::_display_init()
{
    mclog::info("displat init");

    initArduino();

    // lgfx::pinMode(HAL_PIN_PWR_HOLD, lgfx::pin_mode_t::output);
    // lgfx::gpio_hi(HAL_PIN_PWR_HOLD);
    // lgfx::delay(100);

    tone(HAL_PIN_BUZZ_CTRL, 400, 300);

    // // 创建组件实例
    // _components.display_m5gfx = std::make_unique<DisplayEsp32>();
    // _components.display_m5gfx->init();

    // auto mcld = new SharpMem;
    // mcld->init();
    // mcld->clear();
    // mcld->clearBuffer();
    // mcld->refresh();

    // lgfx::PanelSharpMlcd panel_mlcd(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT, HAL_PIN_MLCD_SCS, HAL_PIN_MLCD_SCLK,
    //                                 HAL_PIN_MLCD_SI);

    SharpeMlcd mlcd;

    mlcd.setConfig().screen_width = HAL_SCREEN_WIDTH;
    mlcd.setConfig().screen_height = HAL_SCREEN_HEIGHT;
    mlcd.setConfig().pin_scs = HAL_PIN_MLCD_SCS;
    mlcd.setConfig().pin_sclk = HAL_PIN_MLCD_SCLK;
    mlcd.setConfig().pin_si = HAL_PIN_MLCD_SI;
    mlcd.setConfig().spi_clk_freq = 2000000;

    mlcd.init();

    LGFX_Phoebe lgfx_phoebe(&mlcd);
    lgfx_phoebe.init();
    lgfx_phoebe.setRotation(2);

    LGFX_Sprite canvas(&lgfx_phoebe);
    canvas.createSprite(144, 168);

    /* -------------------------------------------------------------------------- */
    /*                                    Test                                    */
    /* -------------------------------------------------------------------------- */
    while (1) {
        mlcd.fillBufferBlack();
        int y = 0;
        for (int x = 0; x < HAL_SCREEN_WIDTH; x++) {
            mlcd.drawPixel(x, y, 1);
            y++;
        }
        mlcd.refreshScreen();
        lgfx::delay(1000);

        mlcd.clearBuffer();
        y = 0;
        for (int x = 0; x < HAL_SCREEN_WIDTH; x++) {
            mlcd.drawPixel(x, y, 0);
            y++;
        }
        mlcd.refreshScreen();
        lgfx::delay(1000);

        // mclog::info("canvas shit");
        // canvas.fillScreen(TFT_WHITE);
        // canvas.pushSprite(0, 0);
        // lgfx::delay(100);

        // mclog::info("device shit {} {}", lgfx_phoebe.width(), lgfx_phoebe.height());
        // lgfx_phoebe.fillScreen(TFT_WHITE);
        // lgfx::delay(1000);

        mclog::info("canvas shit");
        canvas.fillScreen(TFT_WHITE);
        canvas.fillRect(10, 30, 66, 99, TFT_BLACK);
        canvas.setTextColor(TFT_BLACK);
        canvas.setCursor(0, 0);
        canvas.print("asdasdasd\n66666\n???&&*&^%\nddd");
        canvas.pushSprite(0, 0);
        lgfx::delay(1000);
    }
}
