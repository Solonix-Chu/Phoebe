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
    // 菜单选项类型
    enum OptionType {
        TYPE_TOGGLE,   // 开关类型
        TYPE_VALUE,    // 数值类型
        TYPE_ACTION    // 动作类型（如返回）
    };

    // 菜单选项数据结构
    struct MenuOption {
        std::string name;
        OptionType type;
        bool toggleState;     // 开关状态
        int value;            // 数值
        int minValue;         // 最小值
        int maxValue;         // 最大值
        int step;             // 步长
    };

    // 存储每个应用的选项配置
    std::vector<std::vector<MenuOption>> appMenuOptions;
    
    // 编辑状态
    bool isEditingValue = false;
    uint32_t blinkTimer = 0;
    bool blinkState = true;
    
    // UI变量
    std::vector<lv_obj_t*> appIcons;     // 应用图标
    std::vector<lv_obj_t*> menuItems;    // 菜单项
    lv_obj_t* selector = nullptr;        // 选择器
    std::vector<lv_obj_t*> stateLabels;  // 状态标签
    
    // 布局常量
    const int MENU_ITEM_HEIGHT = 28;     // 选项高度
    const int MENU_ITEM_SPACING = 3;     // 选项间距
    const int MENU_START_Y = 40;         // 起始Y坐标
    const int MENU_LEFT_MARGIN = 5;      // 左侧边距

    // 菜单变量
    SmoothUIToolKit::SelectMenu::SmoothOptions horizontalMenu;  // 横向菜单
    SmoothUIToolKit::SelectMenu::SmoothSelector verticalMenu;   // 竖向菜单
    
    // 状态控制
    enum MenuState {
        HORIZONTAL_MENU,
        VERTICAL_MENU
    };
    MenuState currentState = HORIZONTAL_MENU;
    int currentAppIndex = 0;             // 当前选中的应用索引
    uint32_t currentTime = 0;           // 当前时间，用于动画更新
    
    // 初始化默认选项配置
    void initMenuOptions();
    
    // 切换开关状态
    void toggleOptionState(int index);
    
    // 调整数值
    void adjustValue(int index, bool increment);
    
    // 获取状态文本
    std::string getOptionStateText(const MenuOption& option);
    
    // 菜单初始化
    void initHorizontalMenu();
    void initVerticalMenu(int appIndex);
    void switchToHorizontalMenu();
    void switchToVerticalMenu(int appIndex);
    
    // 清理资源
    void clearMenus();
};
