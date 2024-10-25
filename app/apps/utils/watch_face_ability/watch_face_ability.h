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
#include <src/misc/lv_types.h>

class WatchFaceAbility : public mooncake::WorkerAbility {
public:
    WatchFaceAbility();
    ~WatchFaceAbility();

    void pushScript(const char* scriptContent);

    void setRenderCanvas(lv_obj_t* canvas)
    {
        _render_canvas = canvas;
    }

    void onCreate() override;
    void onResume() override;
    void onRunning() override;
    void onPause() override;
    void onDestroy() override;

private:
    duk_context* _duktape_ctx = NULL;
    lv_obj_t* _render_canvas = NULL;
    uint32_t _tick_time_count = 0;
};
