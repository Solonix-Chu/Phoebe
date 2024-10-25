/**
 * @file duk_helper.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "duk_helper.h"
#include <mooncake_log.h>

using namespace mooncake;

static const char* _tag = "DukHelper";

void duk_helper::call_script_function(duk_context* ctx, const char* functionName, bool logOnFailed)
{
    duk_get_global_string(ctx, functionName);
    if (duk_pcall(ctx, 0) != 0) {
        if (logOnFailed) {
            mclog::tagError(_tag, "call script function: {} error: {}", functionName, duk_safe_to_string(ctx, -1));
        }
    }
    duk_pop(ctx); /* ignore result */
}
