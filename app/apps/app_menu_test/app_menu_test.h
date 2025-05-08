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
#include "horizontal_app_menu.h"
#include "vertical_options_menu.h"
#include <lvgl.h>
#include <memory>
#include <vector>
#include <string>

/**
 * @brief 派生 App
 *
 */
class AppMenuTest : public mooncake::AppAbility
{
public:
    AppMenuTest();

    // 重写生命周期回调
    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;

private:
    // 存储每个应用的选项配置
    std::vector<std::vector<MenuModules::MenuOption>> appMenuOptions;
    
    // 菜单模块
    MenuModules::HorizontalAppMenu horizontalMenu;
    MenuModules::VerticalOptionsMenu verticalMenu;
    
    // 状态控制
    enum MenuState {
        HORIZONTAL_MENU,
        VERTICAL_MENU
    };
    MenuState currentState = HORIZONTAL_MENU;
    int currentAppIndex = 0;             // 当前选中的应用索引
    uint32_t currentTime = 0;           // 当前时间，用于动画更新
    
    // 过渡动画状态
    bool isTransitioning = false;
    int transitionTargetAppIndex = -1;
    
    // 初始化默认选项配置
    void initMenuOptions();
    
    // 菜单初始化
    void initHorizontalMenu();
    void initVerticalMenu(int appIndex);
    void switchToHorizontalMenu();
    void switchToVerticalMenu(int appIndex);
    
    // 菜单事件处理
    void onHorizontalMenuSelect(int appIndex);
    void onVerticalMenuSelect(int optionIndex, MenuModules::OptionType type);
    void onValueAdjusted(int optionIndex, int newValue);
    void onToggleStateChanged(int optionIndex, bool newState);
    
    // 完成垂直菜单初始化
    void completeVerticalMenuTransition(int appIndex);
};
