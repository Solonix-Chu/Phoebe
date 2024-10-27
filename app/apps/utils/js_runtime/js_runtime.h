/**
 * @file js_runtime.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "engine/duktape.h"
#include "../widgets/widget.h"
#include <memory>
#include <string>

namespace js_runtime {

class JsRuntime {
public:
    JsRuntime();
    ~JsRuntime();

    void loadConsoleBinding();
    void loadHalBinding();
    void loadWidgetBinding(lv_obj_t* widgetParent);

    void evaluate(const std::string& script);
    bool callScriptFunction(const char* functionName, bool logErrorOnFailed = true);
    void reset();

private:
    duk_context* _duktape_ctx = NULL;
    std::unique_ptr<widget::WidgetFactory> _widget_factory;
};

} // namespace js_runtime
