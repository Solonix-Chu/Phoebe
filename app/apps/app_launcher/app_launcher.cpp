/**
 * @file app_launcher.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_launcher.h"
#include "apps/app_launcher/view/page.h"
#include <memory>
#include <mooncake_log.h>
#include <hal/hal.h>
#include <lvgl.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/core/lv_obj_tree.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_color.h>
#include <src/themes/lv_theme.h>
#include <src/themes/simple/lv_theme_simple.h>

using namespace mooncake;

#define _tag (getAppInfo().name)

AppLauncher::AppLauncher()
{
    setAppInfo().name = "AppLauncher";
}

void AppLauncher::onCreate()
{
    mclog::tagInfo(_tag, "on create");
    open();
}

void AppLauncher::onOpen()
{
    mclog::tagInfo(_tag, "on open");
    reset_lv_screen();
    create_page_list();
}

void AppLauncher::onRunning()
{
    // 刷新按钮状态
    HAL::BtnUpdate();
    handle_page_change();
    update_page_list();
}

void AppLauncher::onClose()
{
    mclog::tagInfo(_tag, "on close");
}

// page_list 实例顺序：
// 0：消息
// 1：表盘
// 2：小组件
// 3：应用列表
void AppLauncher::handle_page_change()
{
    if (_page_list[_current_page_index]->isOnSubPage()) {
        return;
    }

    _new_page_index = _current_page_index;

    // Go up
    if (HAL::BtnUp().wasClicked()) {
        _new_page_index--;
        if (_new_page_index < 0) {
            _new_page_index = 0;
            // TODO feedback
        }
    }

    // Go down
    else if (HAL::BtnDown().wasClicked()) {
        _new_page_index++;
        if (_new_page_index >= _page_list.size()) {
            _new_page_index = _page_list.size() - 1;
            // TODO feedback
        }
    }

    // Go sub page
    else if (HAL::BtnOk().wasClicked()) {
        _page_list[_current_page_index]->enterSubPage();
    }

    // If page change
    if (_new_page_index != _current_page_index) {
        // mclog::info("{}", _new_page_index);

        // Hide current
        _page_list[_current_page_index]->hide();
        // Show new
        _page_list[_new_page_index]->show();
        // Update index
        _current_page_index = _new_page_index;
    }
}

void AppLauncher::create_page_list()
{
    // Create page instances
    _page_list.resize(4);
    _page_list[0] = std::make_unique<LauncherPageNotification>();
    _page_list[1] = std::make_unique<LauncherPageWatchFace>();
    _page_list[2] = std::make_unique<LauncherPageWidgets>();
    _page_list[3] = std::make_unique<LauncherPageAppList>();

    for (auto& page : _page_list) {
        static_cast<AbilityBase*>(page.get())->baseCreate();
    }

    _page_list[1]->show();
}

void AppLauncher::update_page_list()
{
    for (auto& page : _page_list) {
        static_cast<AbilityBase*>(page.get())->baseUpdate();
    }
}

void AppLauncher::destory_page_list()
{
    for (auto& page : _page_list) {
        static_cast<AbilityBase*>(page.get())->baseDestroy();
    }
    _page_list.clear();
}

void AppLauncher::reset_lv_screen()
{
    lv_obj_clean(lv_screen_active());
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xAFAFAC), 0);
    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);
}
