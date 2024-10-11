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
    StrongClick100 = 1,             // 强力点击 - 100%
    StrongClick60,                  // 强力点击 - 60%
    StrongClick30,                  // 强力点击 - 30%
    SharpClick100,                  // 猛击 - 100%
    SharpClick60,                   // 猛击 - 60%
    SharpClick30,                   // 猛击 - 30%
    SoftBump100,                    // 软冲击 - 100%
    SoftBump60,                     // 软冲击 - 60%
    SoftBump30,                     // 软冲击 - 30%
    DoubleClick100,                 // 双次点击 - 100%
    DoubleClick60,                  // 双次点击 - 60%
    TripleClick100,                 // 三次点击 - 100%
    SoftFuzz60,                     // 小毛刺 - 60%
    StrongBuzz100,                  // 剧烈蜂鸣 - 100%
    Alert750Ms100,                  // 750ms 报警 - 100%
    Alert1000Ms100,                 // 1000ms 报警 - 100%
    StrongClick1100,                // 强力点击 1 - 100%
    StrongClick280,                 // 强力点击 2 - 80%
    StrongClick360,                 // 强力点击 3 - 60%
    StrongClick430,                 // 强力点击 4 - 30%
    MediumClick1100,                // 中等力度点击 1 - 100%
    MediumClick280,                 // 中等力度点击 2 - 80%
    MediumClick360,                 // 中等力度点击 3 - 60%
    SharpTick1100,                  // 猛击节拍 1 - 100%
    SharpTick280,                   // 猛击节拍 2 - 80%
    SharpTick360,                   // 猛击节拍 3 - 60%
    ShortDoubleClickStrong1100,     // 短时间强力双击 1 - 100%
    ShortDoubleClickStrong280,      // 短时间强力双击 2 - 80%
    ShortDoubleClickStrong360,      // 短时间强力双击 3 - 60%
    ShortDoubleClickStrong430,      // 短时间强力双击 4 - 30%
    ShortDoubleClickMedium1100,     // 短时间中等强度双击 1 - 100%
    ShortDoubleClickMedium280,      // 短时间中等强度双击 2 - 80%
    ShortDoubleClickMedium360,      // 短时间中等强度双击 3 - 60%
    ShortSharpTick1100,             // 短时间猛击节拍 1 - 100%
    ShortSharpTick280,              // 短时间猛击节拍 2 - 80%
    ShortSharpTick360,              // 短时间猛击节拍 3 - 60%
    LongDoubleSharpClickStrong1100, // 长时间双次强力猛击 1 - 100%
    LongDoubleSharpClickStrong280,  // 长时间双次强力猛击 2 - 80%
    LongDoubleSharpClickStrong360,  // 长时间双次强力猛击 3 - 60%
    LongDoubleSharpClickStrong430,  // 长时间双次强力猛击 4 - 30%
    LongDoubleSharpClickMedium1100, // 长时间双次中度猛击 1 - 100%
    LongDoubleSharpClickMedium280,  // 长时间双次中度猛击 2 - 80%
    LongDoubleSharpClickMedium360,  // 长时间双次中度猛击 3 - 60%
    LongDoubleSharpClickMedium440,  // 长时间双次中度猛击 4 - 40%
    Buzz1100,                       // 蜂鸣 1 - 100%
    Buzz280,                        // 蜂鸣 2 - 80%
    Buzz360,                        // 蜂鸣 3 - 60%
    Buzz440,                        // 蜂鸣 4 - 40%
    Buzz520,                        // 蜂鸣 5 - 20%
    StrongPulse1100,                // 强脉冲 1 - 100%
    StrongPulse260,                 // 强脉冲 2 - 60%
    MediumPulse1100,                // 中等脉冲 1 - 100%
    MediumPulse260,                 // 中等脉冲 2 - 60%
    SharpPulse1100,                 // 剧烈脉冲 1 - 100%
    SharpPulse260,                  // 剧烈脉冲 2 - 60%
    TransitionClick1100,            // 转换点击 1 - 100%
    TransitionClick280,             // 转换点击 2 - 80%
    TransitionClick360,             // 转换点击 3 - 60%
    TransitionClick440,             // 转换点击 4 - 40%
    TransitionClick520,             // 转换点击 5 - 20%
    TransitionClick610,             // 转换点击 6 - 10%
    TransitionHum1100,              // 转换噪声 1 - 100%
    TransitionHum280,               // 转换噪声 2 - 80%
    TransitionHum360,               // 转换噪声 3 - 60%
    TransitionHum440,               // 转换噪声 4 - 40%
    TransitionHum520,               // 转换噪声 5 - 20%
    TransitionHum610,               // 转换噪声 6 - 10%
    LongRampDown1100To0,            // 长时间平缓斜降转换 1 - 100 至 0%
    LongRampDown2100To0,            // 长时间平缓斜降转换 2 - 100 至 0%
    MediumRampDown1100To0,          // 中等时间平缓斜降转换 1 - 100 至 0%
    MediumRampDown2100To0,          // 中等时间平缓斜降转换 2 - 100 至 0%
    ShortRampDown1100To0,           // 短时间平缓斜降转换 1 - 100 至 0%
    ShortRampDown2100To0,           // 短时间平缓斜降转换 2 - 100 至 0%
    LongRampDownStrong1100To0,      // 长时间剧烈斜降转换 1 - 100 至 0%
    LongRampDownStrong2100To0,      // 长时间剧烈斜降转换 2 - 100 至 0%
    MediumRampDownStrong1100To0,    // 中等时间剧烈斜降转换 1 - 100 至 0%
    MediumRampDownStrong2100To0,    // 中等时间剧烈斜降转换 2 - 100 至 0%
    ShortRampDownStrong1100To0,     // 短时间剧烈斜降转换 1 - 100 至 0%
    ShortRampDownStrong2100To0,     // 短时间剧烈斜降转换 2 - 100 至 0%
    LongRampUp10To100,              // 长时间平缓斜升转换 1 - 0 至 100%
    LongRampUp20To100,              // 长时间平缓斜升转换 2 - 0 至 100%
    MediumRampUp10To100,            // 中等时间平缓斜升转换 1 - 0 至 100%
    MediumRampUp20To100,            // 中等时间平缓斜升转换 2 - 0 至 100%
    ShortRampUp10To100,             // 短时间平缓斜升转换 1 - 0 至 100%
    ShortRampUp20To100,             // 短时间平缓斜升转换 2 - 0 至 100%
    LongRampUpStrong10To100,        // 长时间剧烈斜升转换 1 - 0 至 100%
    LongRampUpStrong20To100,        // 长时间剧烈斜升转换 2 - 0 至 100%
    MediumRampUpStrong10To100,      // 中等时间剧烈斜升转换 1 - 0 至 100%
    MediumRampUpStrong20To100,      // 中等时间剧烈斜升转换 2 - 0 至 100%
    ShortRampUpStrong10To100,       // 短时间剧烈斜升转换 1 - 0 至 100%
    ShortRampUpStrong20To100,       // 短时间剧烈斜升转换 2 - 0 至 100%
    LongRampDown150To0,             // 长时间平缓斜降转换 1 - 50 至 0%
    LongRampDown250To0,             // 长时间平缓斜降转换 2 - 50 至 0%
    MediumRampDown150To0,           // 中等时间平缓斜降转换 1 - 50 至 0%
    MediumRampDown250To0,           // 中等时间平缓斜降转换 2 - 50 至 0%
    ShortRampDown150To0,            // 短时间平缓斜降转换 1 - 50 至 0%
    ShortRampDown250To0,            // 短时间平缓斜降转换 2 - 50 至 0%
    LongRampUp50To100,              // 长时间平缓斜升转换 1 - 50 至 100%
    LongRampUp250To100,             // 长时间平缓斜升转换 2 - 50 至 100%
    MediumRampUp50To100,            // 中等时间平缓斜升转换 1 - 50 至 100%
    MediumRampUp250To100,           // 中等时间平缓斜升转换 2 - 50 至 100%
    ShortRampUp50To100,             // 短时间平缓斜升转换 1 - 50 至 100%
    ShortRampUp250To100             // 短时间平缓斜升转换 2 - 50 至 100%
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
