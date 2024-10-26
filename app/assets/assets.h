/**
 * @file assets.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <lvgl.h>
#include <string>
#include <cstdint>

/**
 * @brief 资产池层，用于管理字体、图片等静态资源，提供全局懒加载单例，方便 App 的静态资源访问
 *
 */
namespace AssetPool {

/**
 * @brief 资产池定义，静态资源都可以放在这里
 *
 */
struct AssetPool_t {
    struct Font_t {
        const lv_font_t* RajdhaniBold16 = nullptr;
        const lv_font_t* RajdhaniBold24 = nullptr;
        const lv_font_t* RajdhaniBold36 = nullptr;
        const lv_font_t* RajdhaniBold48 = nullptr;
        const lv_font_t* RajdhaniBold64 = nullptr;
        const lv_font_t* RajdhaniBold72 = nullptr;
        const lv_font_t* RajdhaniBold96 = nullptr;
        const lv_font_t* RajdhaniBold144 = nullptr;
        const lv_font_t* zpix12 = nullptr;
    };
    Font_t Font;
};

/**
 * @brief 资产池初始化回调，可以在这里面赋值你的图片指针等
 *
 * @param assetPool
 */
void on_asset_pool_init(AssetPool_t& assetPool);

/* -------------------------------------------------------------------------- */
/*                                  Singleton                                 */
/* -------------------------------------------------------------------------- */
// 全局单例

/**
 * @brief 获取资产池
 *
 * @return AssetPool_t&
 */
AssetPool_t& Get();

/**
 * @brief 销毁当前资产池实例
 *
 */
void Destroy();

// 封装一下不然长的一
inline const AssetPool_t::Font_t& Font()
{
    return Get().Font;
}

} // namespace AssetPool
