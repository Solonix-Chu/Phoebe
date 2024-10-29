/**
 * @file selector.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widget.h"

using namespace widget;

void WidgetSelector::addOption(WidgetBase* optionWidget)
{
    _option_widget_list.push_back(optionWidget);
}

void WidgetSelector::show()
{
    onShow();
}

void WidgetSelector::hide()
{
    onHide();
}

void WidgetSelector::goNext()
{
    if (_option_widget_list.empty()) {
        return;
    }

    _current_option_index++;
    if (_current_option_index >= _option_widget_list.size()) {
        if (goInLoop) {
            _current_option_index = 0;
        } else {
            _current_option_index = _option_widget_list.size() - 1;
        }
        goTo(_option_widget_list[_current_option_index]);
    }
}

void WidgetSelector::goLast()
{
    if (_option_widget_list.empty()) {
        return;
    }

    _current_option_index--;
    if (_current_option_index < 0) {
        if (goInLoop) {
            _current_option_index = _option_widget_list.size() - 1;
        } else {
            _current_option_index = 0;
        }
        goTo(_option_widget_list[_current_option_index]);
    }
}

void WidgetSelector::goTo(WidgetBase* optionWidget) {}

void WidgetSelector::onShow() {}

void WidgetSelector::onHide() {}

void WidgetSelector::onGoTo(WidgetBase* optionWidget) {}
