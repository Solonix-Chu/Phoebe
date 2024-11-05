/**
 * @file page.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-11-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "../widget/widget.h"
#include "../smooth_widget/smooth_widget.h"

namespace page {

class PageSelectMenu {
public:
    void create();
    void show();
    void hide();
    void update();

    std::vector<std::string> optionList;

private:
    std::unique_ptr<smooth_widget::SmoothWidgetBase> _menu_base;
    std::unique_ptr<smooth_widget::SmoothWidgetMouse> _mouse;
    std::vector<std::unique_ptr<widget::WidgetLabel>> _option_widget_list;
};

} // namespace page
