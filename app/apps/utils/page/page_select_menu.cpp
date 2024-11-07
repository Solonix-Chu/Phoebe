/**
 * @file page_select_menu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-11-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "apps/utils/widget/widget.h"
#include "page.h"
#include <lvgl.h>
#include <hal/hal.h>
#include <mooncake_log.h>
#include <src/core/lv_obj.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_style.h>
#include <src/widgets/label/lv_label.h>

using namespace page;
using namespace widget;
using namespace smooth_widget;
using namespace mooncake;
using namespace SmoothUIToolKit;

void PageSelectMenu::create()
{
    _menu_base = std::make_unique<SmoothWidgetBase>(lv_screen_active());
    _mouse = std::make_unique<SmoothWidgetMouse>(_menu_base->get());

    _menu_base->setSize(HAL::Display().width(), HAL::Display().height());
    _menu_base->smoothPosition().jumpTo(0, HAL::Display().height());

    for (int i = 0; i < optionList.size(); i++) {
        _option_widget_list.push_back(std::make_unique<WidgetLabel>(_menu_base->get()));
        _option_widget_list[i]->setFont("RajdhaniBold16");
        _option_widget_list[i]->setText(optionList[i].c_str());
        _option_widget_list[i]->setPos(10, (16 + 10) * i + 10);

        // Limit long text width and enable scrolling
        if (_option_widget_list[i]->getWidth() > HAL::Display().width() - 22) {
            _option_widget_list[i]->setSize(HAL::Display().width() - 22, _option_widget_list[i]->getHeight());
            lv_label_set_long_mode(_option_widget_list[i]->get(), LV_LABEL_LONG_SCROLL_CIRCULAR);
        } else {
            _option_widget_list[i]->setSize(_option_widget_list[i]->getWidth(), _option_widget_list[i]->getHeight());
        }

        _option_widget_list[i]->onHover = [](InputEvent_t e) {
            static_cast<WidgetLabel*>(e.target)->setTextColor("#FFFFFF");
        };
        _option_widget_list[i]->onMouseLeave = [](InputEvent_t e) {
            static_cast<WidgetLabel*>(e.target)->setTextColor("#000000");
        };

        _mouse->addTarget(_option_widget_list[i].get());
    }

    _mouse->mouseType = SmoothWidgetMouse::BackgroundBrick;
    _mouse->show();
}

void PageSelectMenu::show()
{
    _menu_base->smoothPosition().setTransitionPath(EasingPath::easeOutBack);
    _menu_base->smoothPosition().setDuration(800);
    _menu_base->smoothPosition().moveTo(0, 0);
}

void PageSelectMenu::hide() {}

void PageSelectMenu::update()
{
    HAL::BtnUpdate();

    if (HAL::BtnUp().wasClicked()) {
        _mouse->goLast();
    }

    if (HAL::BtnDown().wasClicked()) {
        _mouse->goNext();
    }

    if (HAL::BtnOk().wasPressed()) {
        _mouse->press();
    }

    if (HAL::BtnOk().wasReleased()) {
        _mouse->release();
    }

    _menu_base->updateSmoothing();
    _mouse->updateSmoothing();
}
