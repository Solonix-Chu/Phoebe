/**
 * @file binding.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../engine/duktape.h"

void duk_console_init(duk_context* ctx);
void duk_hal_init(duk_context* ctx);
