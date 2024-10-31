/**
 * @file shared.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

/**
 * @brief 共享数据层，提供一个 App 间共享的数据单例
 *
 */
namespace SharedData {

/**
 * @brief 共享数据定义
 *
 */
struct SharedData_t {
    struct Notification_t {
    };
    Notification_t Notification;

    struct Weather_t {
        std::string weather = "SUNNY";
        int temperature = 26;
    };
    Weather_t Weather;
};

/**
 * @brief 获取共享数据单例
 *
 * @return SharedData_t&
 */
SharedData_t& Get();

/**
 * @brief 销毁共享数据单例
 *
 */
void Destroy();

// 封装一下不然长的一
inline SharedData_t::Notification_t& Notification()
{
    return Get().Notification;
}
inline SharedData_t::Weather_t& Weather()
{
    return Get().Weather;
}

} // namespace SharedData
