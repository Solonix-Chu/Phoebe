/**
 * @file assets.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "assets.h"
#include <mooncake_log.h>
#include <string>

using namespace mooncake;

static asset_pool::AssetPool_t* _asset_pool = nullptr;
static const std::string _tag = "Asset";

asset_pool::AssetPool_t& asset_pool::Get()
{
    // 如果没有注入过，则创建实例，并触发初始化回调
    if (!_asset_pool) {
        _asset_pool = new asset_pool::AssetPool_t;
        mclog::tagInfo(_tag, "create and init asset pool");
        on_asset_pool_init(*_asset_pool);
    }
    return *_asset_pool;
}

void asset_pool::Destroy()
{
    mclog::tagInfo(_tag, "destroy asset pool");
    if (_asset_pool) {
        delete _asset_pool;
        _asset_pool = nullptr;
    }
}

void asset_pool::Inject(AssetPool_t* assetPool)
{
    if (assetPool) {
        mclog::tagInfo(_tag, "inject asset pool");
        Destroy();
        _asset_pool = assetPool;
    } else {
        mclog::tagError(_tag, "inject with null");
    }
}
