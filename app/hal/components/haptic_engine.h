/**
 * @file haptic_engine.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-11
 *
 * @copyright Copyright (c) 2024
 *
 */
// https://www.ti.com/cn/lit/ds/symlink/drv2605l.pdf
#pragma once
#include <vector>

namespace hal_components {

/**
 * @brief 触觉反馈（线性马达）
 *
 */
class HapticEngine {
public:
    enum HapticEffect_t {
        STRONG_CLICK_100 = 1,                 // 强力点击 - 100%
        STRONG_CLICK_60,                      // 强力点击 - 60%
        STRONG_CLICK_30,                      // 强力点击 - 30%
        SHARP_CLICK_100,                      // 猛击 - 100%
        SHARP_CLICK_60,                       // 猛击 - 60%
        SHARP_CLICK_30,                       // 猛击 - 30%
        SOFT_BUMP_100,                        // 软冲击 - 100%
        SOFT_BUMP_60,                         // 软冲击 - 60%
        SOFT_BUMP_30,                         // 软冲击 - 30%
        DOUBLE_CLICK_100,                     // 双次点击 - 100%
        DOUBLE_CLICK_60,                      // 双次点击 - 60%
        TRIPLE_CLICK_100,                     // 三次点击 - 100%
        SOFT_FUZZ_60,                         // 小毛刺 - 60%
        STRONG_BUZZ_100,                      // 剧烈蜂鸣 - 100%
        ALERT_750MS_100,                      // 750ms 报警 - 100%
        ALERT_1000MS_100,                     // 1000ms 报警 - 100%
        STRONG_CLICK_1_100,                   // 强力点击 1 - 100%
        STRONG_CLICK_2_80,                    // 强力点击 2 - 80%
        STRONG_CLICK_3_60,                    // 强力点击 3 - 60%
        STRONG_CLICK_4_30,                    // 强力点击 4 - 30%
        MEDIUM_CLICK_1_100,                   // 中等力度点击 1 - 100%
        MEDIUM_CLICK_2_80,                    // 中等力度点击 2 - 80%
        MEDIUM_CLICK_3_60,                    // 中等力度点击 3 - 60%
        SHARP_TICK_1_100,                     // 猛击节拍 1 - 100%
        SHARP_TICK_2_80,                      // 猛击节拍 2 - 80%
        SHARP_TICK_3_60,                      // 猛击节拍 3 - 60%
        SHORT_DOUBLE_CLICK_STRONG_1_100,      // 短时间强力双击 1 - 100%
        SHORT_DOUBLE_CLICK_STRONG_2_80,       // 短时间强力双击 2 - 80%
        SHORT_DOUBLE_CLICK_STRONG_3_60,       // 短时间强力双击 3 - 60%
        SHORT_DOUBLE_CLICK_STRONG_4_30,       // 短时间强力双击 4 - 30%
        SHORT_DOUBLE_CLICK_MEDIUM_1_100,      // 短时间中等强度双击 1 - 100%
        SHORT_DOUBLE_CLICK_MEDIUM_2_80,       // 短时间中等强度双击 2 - 80%
        SHORT_DOUBLE_CLICK_MEDIUM_3_60,       // 短时间中等强度双击 3 - 60%
        SHORT_SHARP_TICK_1_100,               // 短时间猛击节拍 1 - 100%
        SHORT_SHARP_TICK_2_80,                // 短时间猛击节拍 2 - 80%
        SHORT_SHARP_TICK_3_60,                // 短时间猛击节拍 3 - 60%
        LONG_DOUBLE_SHARP_CLICK_STRONG_1_100, // 长时间双次强力猛击 1 - 100%
        LONG_DOUBLE_SHARP_CLICK_STRONG_2_80,  // 长时间双次强力猛击 2 - 80%
        LONG_DOUBLE_SHARP_CLICK_STRONG_3_60,  // 长时间双次强力猛击 3 - 60%
        LONG_DOUBLE_SHARP_CLICK_STRONG_4_30,  // 长时间双次强力猛击 4 - 30%
        LONG_DOUBLE_SHARP_CLICK_MEDIUM_1_100, // 长时间双次中度猛击 1 - 100%
        LONG_DOUBLE_SHARP_CLICK_MEDIUM_2_80,  // 长时间双次中度猛击 2 - 80%
        LONG_DOUBLE_SHARP_CLICK_MEDIUM_3_60,  // 长时间双次中度猛击 3 - 60%
        LONG_DOUBLE_SHARP_CLICK_MEDIUM_4_40,  // 长时间双次中度猛击 4 - 40%
        BUZZ_1_100,                           // 蜂鸣 1 - 100%
        BUZZ_2_80,                            // 蜂鸣 2 - 80%
        BUZZ_3_60,                            // 蜂鸣 3 - 60%
        BUZZ_4_40,                            // 蜂鸣 4 - 40%
        BUZZ_5_20,                            // 蜂鸣 5 - 20%
        STRONG_PULSE_1_100,                   // 强脉冲 1 - 100%
        STRONG_PULSE_2_60,                    // 强脉冲 2 - 60%
        MEDIUM_PULSE_1_100,                   // 中等脉冲 1 - 100%
        MEDIUM_PULSE_2_60,                    // 中等脉冲 2 - 60%
        SHARP_PULSE_1_100,                    // 剧烈脉冲 1 - 100%
        SHARP_PULSE_2_60,                     // 剧烈脉冲 2 - 60%
        TRANSITION_CLICK_1_100,               // 转换点击 1 - 100%
        TRANSITION_CLICK_2_80,                // 转换点击 2 - 80%
        TRANSITION_CLICK_3_60,                // 转换点击 3 - 60%
        TRANSITION_CLICK_4_40,                // 转换点击 4 - 40%
        TRANSITION_CLICK_5_20,                // 转换点击 5 - 20%
        TRANSITION_CLICK_6_10,                // 转换点击 6 - 10%
        TRANSITION_HUM_1_100,                 // 转换噪声 1 - 100%
        TRANSITION_HUM_2_80,                  // 转换噪声 2 - 80%
        TRANSITION_HUM_3_60,                  // 转换噪声 3 - 60%
        TRANSITION_HUM_4_40,                  // 转换噪声 4 - 40%
        TRANSITION_HUM_5_20,                  // 转换噪声 5 - 20%
        TRANSITION_HUM_6_10,                  // 转换噪声 6 - 10%
        LONG_RAMP_DOWN_1_100_TO_0,            // 长时间平缓斜降转换 1 - 100 至 0%
        LONG_RAMP_DOWN_2_100_TO_0,            // 长时间平缓斜降转换 2 - 100 至 0%
        MEDIUM_RAMP_DOWN_1_100_TO_0,          // 中等时间平缓斜降转换 1 - 100 至 0%
        MEDIUM_RAMP_DOWN_2_100_TO_0,          // 中等时间平缓斜降转换 2 - 100 至 0%
        SHORT_RAMP_DOWN_1_100_TO_0,           // 短时间平缓斜降转换 1 - 100 至 0%
        SHORT_RAMP_DOWN_2_100_TO_0,           // 短时间平缓斜降转换 2 - 100 至 0%
        LONG_RAMP_DOWN_STRONG_1_100_TO_0,     // 长时间剧烈斜降转换 1 - 100 至 0%
        LONG_RAMP_DOWN_STRONG_2_100_TO_0,     // 长时间剧烈斜降转换 2 - 100 至 0%
        MEDIUM_RAMP_DOWN_STRONG_1_100_TO_0,   // 中等时间剧烈斜降转换 1 - 100 至 0%
        MEDIUM_RAMP_DOWN_STRONG_2_100_TO_0,   // 中等时间剧烈斜降转换 2 - 100 至 0%
        SHORT_RAMP_DOWN_STRONG_1_100_TO_0,    // 短时间剧烈斜降转换 1 - 100 至 0%
        SHORT_RAMP_DOWN_STRONG_2_100_TO_0,    // 短时间剧烈斜降转换 2 - 100 至 0%
        LONG_RAMP_UP_1_0_TO_100,              // 长时间平缓斜升转换 1 - 0 至 100%
        LONG_RAMP_UP_2_0_TO_100,              // 长时间平缓斜升转换 2 - 0 至 100%
        MEDIUM_RAMP_UP_1_0_TO_100,            // 中等时间平缓斜升转换 1 - 0 至 100%
        MEDIUM_RAMP_UP_2_0_TO_100,            // 中等时间平缓斜升转换 2 - 0 至 100%
        SHORT_RAMP_UP_1_0_TO_100,             // 短时间平缓斜升转换 1 - 0 至 100%
        SHORT_RAMP_UP_2_0_TO_100,             // 短时间平缓斜升转换 2 - 0 至 100%
        LONG_RAMP_UP_STRONG_1_0_TO_100,       // 长时间剧烈斜升转换 1 - 0 至 100%
        LONG_RAMP_UP_STRONG_2_0_TO_100,       // 长时间剧烈斜升转换 2 - 0 至 100%
        MEDIUM_RAMP_UP_STRONG_1_0_TO_100,     // 中等时间剧烈斜升转换 1 - 0 至 100%
        MEDIUM_RAMP_UP_STRONG_2_0_TO_100,     // 中等时间剧烈斜升转换 2 - 0 至 100%
        SHORT_RAMP_UP_STRONG_1_0_TO_100,      // 短时间剧烈斜升转换 1 - 0 至 100%
        SHORT_RAMP_UP_STRONG_2_0_TO_100,      // 短时间剧烈斜升转换 2 - 0 至 100%
        LONG_RAMP_DOWN_1_50_TO_0,             // 长时间平缓斜降转换 1 - 50 至 0%
        LONG_RAMP_DOWN_2_50_TO_0,             // 长时间平缓斜降转换 2 - 50 至 0%
        MEDIUM_RAMP_DOWN_1_50_TO_0,           // 中等时间平缓斜降转换 1 - 50 至 0%
        MEDIUM_RAMP_DOWN_2_50_TO_0,           // 中等时间平缓斜降转换 2 - 50 至 0%
        SHORT_RAMP_DOWN_1_50_TO_0,            // 短时间平缓斜降转换 1 - 50 至 0%
        SHORT_RAMP_DOWN_2_50_TO_0,            // 短时间平缓斜降转换 2 - 50 至 0%
        LONG_RAMP_DOWN_STRONG_1_50_TO_0,      // 长时间剧烈斜降转换 1 - 50 至 0%
        LONG_RAMP_DOWN_STRONG_2_50_TO_0,      // 长时间剧烈斜降转换 2 - 50 至 0%
        MEDIUM_RAMP_DOWN_STRONG_1_50_TO_0,    // 中等时间剧烈斜降转换 1 - 50 至 0%
        MEDIUM_RAMP_DOWN_STRONG_2_50_TO_0,    // 中等时间剧烈斜降转换 2 - 50 至 0%
        SHORT_RAMP_DOWN_STRONG_1_50_TO_0,     // 短时间剧烈斜降转换 1 - 50 至 0%
        SHORT_RAMP_DOWN_STRONG_2_50_TO_0,     // 短时间剧烈斜降转换 2 - 50 至 0%
        LONG_RAMP_UP_1_0_TO_50,               // 长时间平缓斜升转换 1 - 0 至 50%
        LONG_RAMP_UP_2_0_TO_50,               // 长时间平缓斜升转换 2 - 0 至 50%
        MEDIUM_RAMP_UP_1_0_TO_50,             // 中等时间平缓斜升转换 1 - 0 至 50%
        MEDIUM_RAMP_UP_2_0_TO_50,             // 中等时间平缓斜升转换 2 - 0 至 50%
        SHORT_RAMP_UP_1_0_TO_50,              // 短时间平缓斜升转换 1 - 0 至 50%
        SHORT_RAMP_UP_2_0_TO_50,              // 短时间平缓斜升转换 2 - 0 至 50%
        LONG_RAMP_UP_STRONG_1_0_TO_50,        // 长时间剧烈斜升转换 1 - 0 至 50%
        LONG_RAMP_UP_STRONG_2_0_TO_50,        // 长时间剧烈斜升转换 2 - 0 至 50%
        MEDIUM_RAMP_UP_STRONG_1_0_TO_50,      // 中等时间剧烈斜升转换 1 - 0 至 50%
        MEDIUM_RAMP_UP_STRONG_2_0_TO_50,      // 中等时间剧烈斜升转换 2 - 0 至 50%
        SHORT_RAMP_UP_STRONG_1_0_TO_50,       // 短时间剧烈斜升转换 1 - 0 至 50%
        SHORT_RAMP_UP_STRONG_2_0_TO_50,       // 短时间剧烈斜升转换 2 - 0 至 50%
        PROGRAM_STOP_CAUSED_LONG_BUZZ_100,    // 程序停止引发长蜂鸣 - 100%
        SMOOTH_HUM_1_NO_BRAKE_50,             // 平滑噪声 1 - 无刹车 - 50%
        SMOOTH_HUM_2_NO_BRAKE_40,             // 平滑噪声 2 - 无刹车 - 40%
        SMOOTH_HUM_3_NO_BRAKE_30,             // 平滑噪声 3 - 无刹车 - 30%
        SMOOTH_HUM_4_NO_BRAKE_20,             // 平滑噪声 4 - 无刹车 - 20%
        SMOOTH_HUM_5_NO_BRAKE_10              // 平滑噪声 5 - 无刹车 - 10%
    };

    virtual bool init()
    {
        return false;
    }

    virtual void enable() {}

    virtual void disable() {}

    /**
     * @brief 播放反馈效果
     *
     * @param effectSequence 效果序列，最多8个
     */
    virtual void playEffect(const std::vector<HapticEffect_t>& effectSequence) {}

    virtual void stop() {}

    virtual bool isPlaying()
    {
        return false;
    }
};

} // namespace hal_components
