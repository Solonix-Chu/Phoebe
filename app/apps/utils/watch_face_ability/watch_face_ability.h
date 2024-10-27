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
#include "../js_runtime/js_runtime.h"
#include "../widget/widget.h"
#include <cstdint>
#include <mooncake.h>

class WatchFaceAbility : public mooncake::WorkerAbility {
public:
    void init(lv_obj_t* widgetParent);

    void onCreate() override;
    void onResume() override;
    void onRunning() override;
    void onPause() override;
    void onDestroy() override;

private:
    js_runtime::JsRuntime _js_runtime;
    uint32_t _tick_time_count = 0;
};
