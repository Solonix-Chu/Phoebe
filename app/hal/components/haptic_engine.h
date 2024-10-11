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

// ToFix tmd gpt 怎么缺料了
namespace HapticEffect {
enum HapticEffect_t {
    STRONG_CLICK_100 = 1,                          // 强力点击 - 100%
    STRONG_CLICK_60,                               // 强力点击 - 60%
    STRONG_CLICK_30,                               // 强力点击 - 30%
    SHARP_CLICK_100,                               // 强力点击 - 30%
    SHARP_CLICK_60,                                // 猛击 - 60%
    SHARP_CLICK_30,                                // 猛击 - 30%
    SOFT_BUMP_100,                                 // 软冲击 - 100%
    SOFT_BUMP_60,                                  // 软冲击 - 60%
    SOFT_BUMP_30,                                  // 软冲击 - 30%
    DOUBLE_CLICK_100,                              // 双次点击 - 100%
    DOUBLE_CLICK_60,                               // 双次点击 - 60%
    TRIPLE_CLICK_100,                              // 三次点击 - 100%
    SOFT_FUZZ_60,                                  // 小毛刺 - 60%
    STRONG_BUZZ_100,                               // 剧烈蜂鸣 - 100%
    ALERT_750_MS_100,                              // 750ms 报警 100%
    ALERT_1000_MS_100,                             // 1000ms 报警 100%
    STRONG_CLICK_1_100,                            // 强力点击 1 - 100%
    STRONG_CLICK_2_80,                             // 强力点击 2 - 80%
    STRONG_CLICK_3_60,                             // 强力点击 3 - 60%
    STRONG_CLICK_4_30,                             // 强力点击 4 - 30%
    MEDIUM_CLICK_1_100,                            // 中等力度点击 1 - 100%
    MEDIUM_CLICK_2_80,                             // 中等力度点击 2 - 80%
    MEDIUM_CLICK_3_60,                             // 中等力度点击 3 - 60%
    SHARP_TICK_1_100,                              // 猛击节拍 1 - 100%
    SHARP_TICK_2_80,                               // 猛击节拍 2 - 80%
    SHARP_TICK_3_60,                               // 猛击节拍 3 - 60%
    SHORT_DOUBLE_CLICK_STRONG_1_100,               // 短时间强力双击 1 – 100%
    SHORT_DOUBLE_CLICK_STRONG_2_80,                // 短时间强力双击 2 – 80%
    SHORT_DOUBLE_CLICK_STRONG_3_60,                // 短时间强力双击 3 – 60%
    SHORT_DOUBLE_CLICK_STRONG_4_30,                // 短时间强力双击 4 – 30%
    SHORT_DOUBLE_CLICK_MEDIUM_1_100,               // 短时间中等强度双击 1 – 100%
    SHORT_DOUBLE_CLICK_MEDIUM_2_80,                // 短时间中等强度双击 2 – 80%
    SHORT_DOUBLE_CLICK_MEDIUM_3_60,                // 短时间中等强度双击 3 – 60%
    SHORT_DOUBLE_SHARP_TICK_1_100,                 // 短时间双次猛击节拍 1 – 100%
    SHORT_DOUBLE_SHARP_TICK_2_80,                  // 短时间双次猛击节拍 2 – 80%
    SHORT_DOUBLE_SHARP_TICK_3_60,                  // 短时间双次猛击节拍 3 – 60%
    LONG_DOUBLE_SHARP_CLICK_STRONG_1_100,          // 长时间双次强力猛击 1 – 100%
    LONG_DOUBLE_SHARP_CLICK_STRONG_2_80,           // 长时间双次强力猛击 2 – 80%
    LONG_DOUBLE_SHARP_CLICK_STRONG_3_60,           // 长时间双次强力猛击 3 – 60%
    LONG_DOUBLE_SHARP_CLICK_STRONG_4_30,           // 长时间双次强力猛击 4 – 30%
    LONG_DOUBLE_SHARP_CLICK_MEDIUM_1_100,          // 长时间双次中度猛击 1 – 100%
    LONG_DOUBLE_SHARP_CLICK_MEDIUM_2_80,           // 长时间双次中度猛击 2 – 80%
    LONG_DOUBLE_SHARP_CLICK_MEDIUM_3_60,           // 长时间双次中度猛击 3 – 60%
    LONG_DOUBLE_SHARP_TICK_1_100,                  // 长时间双次猛击节拍 1 – 100%
    LONG_DOUBLE_SHARP_TICK_2_80,                   // 长时间双次猛击节拍 2 – 80%
    LONG_DOUBLE_SHARP_TICK_3_60,                   // 长时间双次猛击节拍 3 – 60%
    BUZZ_1_100,                                    // 蜂鸣 1 – 100%
    BUZZ_2_80,                                     // 蜂鸣 2 – 80%
    BUZZ_3_60,                                     // 蜂鸣 3 – 60%
    BUZZ_4_40,                                     // 蜂鸣 4 – 40%
    BUZZ_5_20,                                     // 蜂鸣 5 – 20%
    PULSING_STRONG_1_100,                          // 强脉冲 1 – 100%
    PULSING_STRONG_2_60,                           // 强脉冲 2 – 60%
    PULSING_MEDIUM_1_100,                          // 中等脉冲 1 – 100%
    PULSING_MEDIUM_2_60,                           // 中等脉冲 2 – 60%
    PULSING_SHARP_1_100,                           // 剧烈脉冲 1 – 100%
    PULSING_SHARP_2_60,                            // 剧烈脉冲 2 – 60%
    TRANSITION_CLICK_1_100,                        // 转换点击 1 - 100%
    TRANSITION_CLICK_2_80,                         // 转换点击 1 - 100%
    TRANSITION_CLICK_3_60,                         // 转换点击 3 - 60%
    TRANSITION_CLICK_4_40,                         // 转换点击 4 - 40%
    TRANSITION_CLICK_5_20,                         // 转换点击 5 - 20%
    TRANSITION_CLICK_6_10,                         // 转换点击 6 - 10%
    TRANSITION_HUM_1_100,                          // 转换噪声 1 - 100%
    TRANSITION_HUM_2_80,                           // 转换噪声 2 - 80%
    TRANSITION_HUM_3_60,                           // 转换噪声 3 - 60%
    TRANSITION_HUM_4_40,                           // 转换噪声 4 - 40%
    TRANSITION_HUM_5_20,                           // 转换噪声 5 - 20%
    TRANSITION_HUM_6_10,                           // 转换噪声 6 - 10%
    TRANSITION_RAMP_DOWN_LONG_SMOOTH_1_100_TO_0,   // 长时间平缓斜降转换 1 – 100 至 0%
    TRANSITION_RAMP_DOWN_LONG_SMOOTH_2_100_TO_0,   // 长时间平缓斜降转换 2 – 100 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SMOOTH_1_100_TO_0, // 中等时间平缓斜降转换 1 – 100 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SMOOTH_2_100_TO_0, // 中等时间平缓斜降转换 2 – 100 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SMOOTH_1_100_TO_0,  // 短时间平缓斜降转换 1 – 100 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SMOOTH_2_100_TO_0,  // 短时间平缓斜降转换 2 – 100 至 0%
    TRANSITION_RAMP_DOWN_LONG_SHARP_1_100_TO_0,    // 长时间剧烈斜降转换 1 – 100 至 0%
    TRANSITION_RAMP_DOWN_LONG_SHARP_2_100_TO_0,    // 长时间剧烈斜降转换 2 – 100 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SHARP_1_100_TO_0,  // 中等时间剧烈斜降转换 1 – 100 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SHARP_2_100_TO_0,  // 中等时间剧烈斜降转换 2 – 100 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SHARP_1_100_TO_0,   // 短时间剧烈斜降转换 1 – 100 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SHARP_2_100_TO_0,   // 短时间剧烈斜降转换 2 – 100 至 0%
    TRANSITION_RAMP_UP_LONG_SMOOTH_1_0_TO_100,     // 长时间平缓斜升转换 1 – 0 至 100%
    TRANSITION_RAMP_UP_LONG_SMOOTH_2_0_TO_100,     // 长时间平缓斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_UP_MEDIUM_SMOOTH_1_0_TO_100,   // 中等时间平缓斜升转换 1 – 0 至 100%
    TRANSITION_RAMP_UP_MEDIUM_SMOOTH_2_0_TO_100,   // 中等时间平缓斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_UP_SHORT_SMOOTH_1_0_TO_100,    // 短时间平缓斜升转换 1 – 0 至 100%
    TRANSITION_RAMP_UP_SHORT_SMOOTH_2_0_TO_100,    // 短时间平缓斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_UP_LONG_SHARP_1_0_TO_100,      // 长时间剧烈斜升转换 1 – 0 至 100%
    TRANSITION_RAMP_UP_LONG_SHARP_2_0_TO_100,      // 长时间剧烈斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_UP_MEDIUM_SHARP_1_0_TO_100,    // 长时间剧烈斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_UP_MEDIUM_SHARP_2_0_TO_100,    // 中等时间剧烈斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_UP_SHORT_SHARP_1_0_TO_100,     // 短时间剧烈斜升转换 1 – 0 至 100%
    TRANSITION_RAMP_UP_SHORT_SHARP_2_0_TO_100,     // 短时间剧烈斜升转换 2 – 0 至 100%
    TRANSITION_RAMP_DOWN_LONG_SMOOTH_1_50_TO_0,    // 长时间平缓斜降转换 1 – 50 至 0%
    TRANSITION_RAMP_DOWN_LONG_SMOOTH_2_50_TO_0,    // 长时间平缓斜降转换 2 – 50 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SMOOTH_1_50_TO_0,  // 中等时间平缓斜降转换 1 – 50 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SMOOTH_2_50_TO_0,  // 中等时间平缓斜降转换 2 – 50 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SMOOTH_1_50_TO_0,   // 短时间平缓斜降转换 1 – 50 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SMOOTH_2_50_TO_0,   // 短时间平缓斜降转换 2 – 50 至 0%
    TRANSITION_RAMP_DOWN_LONG_SHARP_1_50_TO_0,     // 长时间剧烈斜降转换 1 – 50 至 0%
    TRANSITION_RAMP_DOWN_LONG_SHARP_2_50_TO_0,     // 长时间剧烈斜降转换 2 – 50 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SHARP_1_50_TO_0,   // 中等时间剧烈斜降转换 1 – 50 至 0%
    TRANSITION_RAMP_DOWN_MEDIUM_SHARP_2_50_TO_0,   // 中等时间剧烈斜降转换 2 – 50 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SHARP_1_50_TO_0,    // 短时间剧烈斜降转换 1 – 50 至 0%
    TRANSITION_RAMP_DOWN_SHORT_SHARP_2_50_TO_0,    // 短时间剧烈斜降转换 2 – 50 至 0%
    TRANSITION_RAMP_UP_LONG_SMOOTH_1_0_TO_50,      // 长时间平缓斜升转换 1 – 0 至 50%
    TRANSITION_RAMP_UP_LONG_SMOOTH_2_0_TO_50,      // 长时间平缓斜升转换 2 – 0 至 50%
    TRANSITION_RAMP_UP_MEDIUM_SMOOTH_1_0_TO_50,    // 中等时间平缓斜升转换 1 – 0 至 50%
    TRANSITION_RAMP_UP_MEDIUM_SMOOTH_2_0_TO_50,    // 中等时间平缓斜升转换 2 – 0 至 50%
    TRANSITION_RAMP_UP_SHORT_SMOOTH_1_0_TO_50,     // 短时间平缓斜升转换 1 – 0 至 50%
    TRANSITION_RAMP_UP_SHORT_SMOOTH_2_0_TO_50,     // 短时间平缓斜升转换 2 – 0 至 50%
    TRANSITION_RAMP_UP_LONG_SHARP_1_0_TO_50,       // 长时间剧烈斜升转换 1 – 0 至 50%
    TRANSITION_RAMP_UP_LONG_SHARP_2_0_TO_50,       // 长时间剧烈斜升转换 2 – 0 至 50%
    TRANSITION_RAMP_UP_MEDIUM_SHARP_1_0_TO_50,     // 中等时间剧烈斜升转换 1 – 0 至 50%
    TRANSITION_RAMP_UP_MEDIUM_SHARP_2_0_TO_50,     // 中等时间剧烈斜升转换 2 – 0 至 50%
    TRANSITION_RAMP_UP_SHORT_SHARP_1_0_TO_50,      // 短时间剧烈斜升转换 1 – 0 至 50%
    TRANSITION_RAMP_UP_SHORT_SHARP_2_0_TO_50,      // 短时间剧烈斜升转换 2 – 0 至 50%
    LONG_BUZZ_FOR_PROGRAMMATIC_STOPPING_100,       // 编程停止导致长时间蜂鸣 – 100%
    SMOOTH_HUM_1_NO_KICK_OR_BRAKE_50,              // 平缓噪声 1（无回弹或制动脉冲） – 50%
    SMOOTH_HUM_2_NO_KICK_OR_BRAKE_40,              // 平缓噪声 2（无回弹或制动脉冲） – 40%
    SMOOTH_HUM_3_NO_KICK_OR_BRAKE_30,              // 平缓噪声 3（无回弹或制动脉冲） – 30%
    SMOOTH_HUM_4_NO_KICK_OR_BRAKE_20,              // 平缓噪声 4（无回弹或制动脉冲） – 20%
    SMOOTH_HUM_5_NO_KICK_OR_BRAKE_10               // 平缓噪声 5（无回弹或制动脉冲） – 10%
};
}

namespace hal_components {

/**
 * @brief 触觉反馈（线性马达）组件基类
 *
 */
class HapticEngineBase {
public:
    virtual bool init()
    {
        return false;
    }

    virtual void enable() {}

    virtual void disable() {}

    /**
     * @brief 播放效果
     *
     * @param effect
     */
    virtual void playEffect(const HapticEffect::HapticEffect_t& effect) {}

    /**
     * @brief 播放效果序列
     *
     * @param effectSequence 效果序列，最多8个
     */
    virtual void playEffects(const std::vector<HapticEffect::HapticEffect_t>& effectSequence) {}

    virtual void stop() {}

    virtual bool isPlaying()
    {
        return false;
    }
};

} // namespace hal_components
