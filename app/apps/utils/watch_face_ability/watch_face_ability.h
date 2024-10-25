/**
 * @file watch_face_ability.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "ability/ability.h"
#include "../duktape/duktape.h"
#include <cstdint>
#include <functional>
#include <mooncake.h>

class WatchFaceAbility : public mooncake::WorkerAbility {
public:
    WatchFaceAbility();
    ~WatchFaceAbility();

    void pushScript(const char* scriptContent);

    void onCreate() override;
    void onResume() override;
    void onRunning() override;
    void onPause() override;
    void onDestroy() override;

private:
    struct Data_t {
        duk_context* duktape_ctx = NULL;
        uint32_t tick_time_count = 0;
    };
    Data_t _data;
};
