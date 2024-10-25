/**
 * @file duk_helper.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "duktape.h"

namespace duk_helper {
void call_script_function(duk_context* ctx, const char* functionName, bool logOnFailed = true);
}
