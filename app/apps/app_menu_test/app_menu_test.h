/**
 * @file app_menu_test.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>
#include "dependencies/smooth_ui_toolkit/src/select_menu/smooth_options/smooth_options.h"
#include "dependencies/smooth_ui_toolkit/src/select_menu/smooth_selector/smooth_selector.h"
#include <lvgl.h>
#include <memory>
#include <vector>
#include <string>

/**
 * @brief 派生 App
 *
 */
class AppMenuTest : public mooncake::AppAbility {
public:
    AppMenuTest();

    // 重写生命周期回调
    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;

private:
    // 菜单状态
    enum MenuState {
        HORIZONTAL_MENU,
        VERTICAL_MENU
    };
    MenuState currentState = HORIZONTAL_MENU;
    
    // 横向循环菜单
    SmoothUIToolKit::SelectMenu::SmoothOptions horizontalMenu;
    std::vector<lv_obj_t*> appIcons;
    std::vector<lv_color_t> appColors; // 存储应用图标颜色
    std::vector<std::string> appNames; // 存储应用名称
    
    // 竖向设置菜单
    SmoothUIToolKit::SelectMenu::SmoothSelector verticalMenu;
    lv_obj_t* selector = nullptr;
    std::vector<lv_obj_t*> menuItems;
    
    // 时间计数
    uint32_t currentTime = 0;
    
    // 初始化菜单
    void initHorizontalMenu();
    void initVerticalMenu();
    void switchToVerticalMenu();
    void switchToHorizontalMenu();
    
    // 清理资源
    void clearMenus();
};
