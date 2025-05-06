/**
 * @file app_menu_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <mooncake.h>
#include "app_menu_test.h"
#include <lvgl.h>
#include <hal/hal.h>
#include <mooncake_log.h>
#include <string>
#include <cstring>
#include <src/misc/lv_timer.h>
#include <algorithm>
#include <sstream>

// Add font declarations
LV_FONT_DECLARE(lv_font_montserrat_10);
LV_FONT_DECLARE(lv_font_montserrat_14);
LV_FONT_DECLARE(lv_font_montserrat_16);

using namespace mooncake;
using namespace MenuModules;

#define _tag (getAppInfo().name)

AppMenuTest::AppMenuTest()
{
    // 配置 App 信息
    setAppInfo().name = "AppMenuTest";
}

void AppMenuTest::onCreate()
{
    mclog::tagInfo(_tag, "on create");

    // 添加测试日志
    mclog::tagInfo(_tag, "日志系统测试 - 普通文本");
    mclog::tagInfo(_tag, "日志系统测试 - 整数: %d", 123);
    mclog::tagInfo(_tag, "日志系统测试 - 字符串: %s", "测试文本");
    
    // 添加标准日志
    mclog::info("标准日志测试 - 普通文本");
    mclog::info("标准日志测试 - 整数: %d", 456);
    mclog::info("标准日志测试 - 字符串: %s", "测试文本");

    // 清除屏幕
    lv_obj_clean(lv_screen_active());
    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);
    
    // 设置屏幕为黑色背景 - OLED显示
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
    
    // 为小屏幕设置全局字体
    LV_FONT_DECLARE(lv_font_montserrat_10);
    lv_obj_set_style_text_font(lv_screen_active(), &lv_font_montserrat_10, 0);
    
    // 初始化菜单选项数据
    initMenuOptions();
    
    // 添加数据初始化完成日志
    mclog::tagInfo(_tag, "菜单选项初始化完成, 数组大小: %d", (int)appMenuOptions.size());
    
    // 初始化横向菜单
    initHorizontalMenu();

    // 打开自己
    open();
}

void AppMenuTest::onOpen()
{
    mclog::tagInfo(_tag, "on open");
}

void AppMenuTest::initMenuOptions()
{
    // 初始化菜单选项数据
    appMenuOptions.resize(9); // 9个应用
    
    // App 1 选项
    appMenuOptions[0] = {
        {"WiFi", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Brightness", TYPE_VALUE, false, 50, 0, 100, 5},
        {"Volume", TYPE_VALUE, false, 75, 0, 100, 5},
        {"Back", TYPE_ACTION, false, 0, 0, 0, 0}
    };
    
    // App 2 选项
    appMenuOptions[1] = {
        {"Bluetooth", TYPE_TOGGLE, false, 0, 0, 0, 0},
        {"Sleep Timer", TYPE_VALUE, false, 30, 5, 60, 5},
        {"Dark Mode", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Rotation", TYPE_TOGGLE, false, 0, 0, 0, 0},
        {"Back", TYPE_ACTION, false, 0, 0, 0, 0}
    };
    
    // App 3 选项
    appMenuOptions[2] = {
        {"Auto Update", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Sensitivity", TYPE_VALUE, false, 5, 1, 10, 1},
        {"Back", TYPE_ACTION, false, 0, 0, 0, 0}
    };
    
    // App 4 选项
    appMenuOptions[3] = {
        {"Power Save", TYPE_TOGGLE, false, 0, 0, 0, 0},
        {"Mic Volume", TYPE_VALUE, false, 80, 0, 100, 5},
        {"Speaker", TYPE_VALUE, false, 60, 0, 100, 10},
        {"Night Mode", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Vibration", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Back", TYPE_ACTION, false, 0, 0, 0, 0}
    };
    
    // App 5 选项
    appMenuOptions[4] = {
        {"GPS", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Contrast", TYPE_VALUE, false, 40, 10, 90, 5},
        {"Notifications", TYPE_TOGGLE, true, 0, 0, 0, 0},
        {"Back", TYPE_ACTION, false, 0, 0, 0, 0}
    };
    
    // App 6-9 简化设置
    for (int i = 5; i < 9; i++) {
        appMenuOptions[i] = {
            {"Option 1", TYPE_TOGGLE, (i % 2 == 0), 0, 0, 0, 0},
            {"Option 2", TYPE_VALUE, false, 50, 0, 100, 10},
            {"Option 3", TYPE_TOGGLE, (i % 2 == 1), 0, 0, 0, 0},
            {"Back", TYPE_ACTION, false, 0, 0, 0, 0}
        };
    }
}

void AppMenuTest::initHorizontalMenu() 
{
    // 清理屏幕
    lv_obj_clean(lv_screen_active());
    
    // 设置屏幕为黑色背景 - OLED显示
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
    
    // 初始化横向菜单
    horizontalMenu.init(lv_screen_active());
    
    // 设置选择回调
    horizontalMenu.setSelectCallback([this](int appIndex) {
        this->onHorizontalMenuSelect(appIndex);
    });
    
    // 应用颜色列表 - 更鲜明的颜色对比，适合OLED
    lv_color_t APP_COLORS[9] = {
        lv_color_hex(0xFF0000), // 纯红色
        lv_color_hex(0x00FF00), // 纯绿色
        lv_color_hex(0x0000FF), // 纯蓝色
        lv_color_hex(0xFFFF00), // 纯黄色
        lv_color_hex(0xFF00FF), // 纯紫色
        lv_color_hex(0x00FFFF), // 纯青色
        lv_color_hex(0xFF8000), // 纯橙色
        lv_color_hex(0x8000FF), // 亮紫色
        lv_color_hex(0x0080FF)  // 亮蓝色
    };
    
    // 添加所有应用图标
    for (int i = 0; i < 9; i++) {
        // 添加应用，交替使用方形和圆形图标
        horizontalMenu.addApp(("App " + std::to_string(i + 1)).c_str(), APP_COLORS[i], i % 2 != 0);
    }
    
    // 初始状态
    currentState = HORIZONTAL_MENU;
    mclog::tagInfo(_tag, "横向菜单已初始化，共9个应用");
}

void AppMenuTest::initVerticalMenu(int appIndex) 
{
    // 确保应用索引有效
    if (appIndex < 0 || appIndex >= appMenuOptions.size()) {
        mclog::tagError(_tag, "Invalid app index: %d", appIndex);
        // 失败时回到横向菜单
        initHorizontalMenu();
        return;
    }
    
    // 清理屏幕
    lv_obj_clean(lv_screen_active());
    
    // 设置屏幕为黑色背景
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
    
    // 获取当前应用的菜单选项
    const auto& menuOptions = appMenuOptions[appIndex];
    
    if (menuOptions.empty()) {
        mclog::tagError(_tag, "No menu options for app index: %d", appIndex);
        // 失败时回到横向菜单
        initHorizontalMenu();
        return;
    }
    
    // 保存当前应用索引
    currentAppIndex = appIndex;
    
    // 初始化竖向菜单 - 直接传入活动屏幕，不添加标题
    verticalMenu.init(lv_screen_active());
    
    try {
        // 设置选项
        verticalMenu.setOptions(menuOptions);
        
        // 设置选择回调
        verticalMenu.setSelectCallback([this](int optionIndex, OptionType type) {
            this->onVerticalMenuSelect(optionIndex, type);
        });
        
        // 切换当前状态
        currentState = VERTICAL_MENU;
        
        std::string appTitle = "App " + std::to_string(appIndex + 1);
        mclog::tagInfo(_tag, "%s settings menu initialized", appTitle.c_str());
    } catch (const std::exception& e) {
        // 捕获可能的异常
        mclog::tagError(_tag, "Exception initializing vertical menu: %s", e.what());
        // 失败时回到横向菜单
        initHorizontalMenu();
    } catch (...) {
        mclog::tagError(_tag, "Unknown exception initializing vertical menu");
        // 失败时回到横向菜单
        initHorizontalMenu();
    }
}

void AppMenuTest::onHorizontalMenuSelect(int appIndex) {
    // 仅记录选择事件，状态切换由其他函数处理
    mclog::info("处理应用选择事件: %d", appIndex);
    // 这里可以添加其他与选择相关的业务逻辑
}

void AppMenuTest::onVerticalMenuSelect(int optionIndex, OptionType type) {
    // 仅记录选择事件，状态切换由其他函数处理
    mclog::info("处理选项选择事件: %d, 类型: %d", optionIndex, (int)type);
    // 这里可以添加其他与选择相关的业务逻辑
}

void AppMenuTest::onToggleStateChanged(int optionIndex, bool newState) {
    // 处理开关状态变化
    mclog::info("切换开关状态为: %s", newState ? "ON" : "OFF");
}

void AppMenuTest::onValueAdjusted(int optionIndex, int newValue) {
    // 处理数值调整
    mclog::info("数值已调整: %d", newValue);
}

void AppMenuTest::switchToVerticalMenu(int appIndex) {
    // 安全检查 appIndex
    if (appIndex < 0 || appIndex >= appMenuOptions.size()) {
        mclog::tagError(_tag, "无效的应用索引: %d", appIndex);
        initHorizontalMenu();
        return;
    }
    
    // 1. 先清理横向菜单资源
    horizontalMenu.clear();
    
    // 2. 清理屏幕 - 确保没有残留的UI元素
    lv_obj_clean(lv_screen_active());
    
    // 3. 初始化垂直菜单
    try {
        initVerticalMenu(appIndex);
    } catch (const std::exception& e) {
        mclog::tagError(_tag, "初始化垂直菜单时异常: %s", e.what());
        initHorizontalMenu();
    } catch (...) {
        mclog::tagError(_tag, "初始化垂直菜单时未知异常");
        initHorizontalMenu();
    }
}

void AppMenuTest::switchToHorizontalMenu() {
    // 保存当前应用索引
    int lastAppIndex = currentAppIndex;
    
    // 无论当前状态如何，都确保垂直菜单资源被清理
    verticalMenu.clear();
    
    // 初始化横向菜单
    initHorizontalMenu();
    
    // 如果之前有选择有效的应用索引，则将横向菜单设置到该位置
    if (lastAppIndex >= 0 && lastAppIndex < 9) {
        // 移动到保存的位置
        int currentPos = horizontalMenu.getSelectedIndex();
        int stepsToMove = lastAppIndex - currentPos;
        
        // 根据方向移动
        if (stepsToMove > 0) {
            // 向右移动
            for (int i = 0; i < stepsToMove; i++) {
                horizontalMenu.goNext();
                horizontalMenu.update(currentTime); // 更新布局
            }
        } else if (stepsToMove < 0) {
            // 向左移动
            for (int i = 0; i < -stepsToMove; i++) {
                horizontalMenu.goLast();
                horizontalMenu.update(currentTime); // 更新布局
            }
        }
        // 强制更新一次
        horizontalMenu.update(currentTime);
    }
}

void AppMenuTest::onRunning()
{
    // 更新时间，增加增量确保动画有足够的更新帧
    currentTime += 40; // 增加每帧的时间增量，确保动画能够更流畅地进行
    
    // 更新按钮状态
    HAL::BtnUpdate();
    
    // 处理按钮输入
    if (currentState == HORIZONTAL_MENU) {
        // 横向菜单的控制
        if (HAL::BtnUp().wasClicked()) {
            horizontalMenu.goLast();
        }
        
        if (HAL::BtnDown().wasClicked()) {
            horizontalMenu.goNext();
        }
        
        if (HAL::BtnOk().wasClicked()) {
            // 选择当前应用，切换到竖向菜单
            int selectedIndex = horizontalMenu.getSelectedIndex();
            
            // 安全检查
            if (selectedIndex >= 0 && selectedIndex < appMenuOptions.size()) {
                switchToVerticalMenu(selectedIndex);
            } else {
                mclog::tagError(_tag, "无效的应用索引");
            }
            
            // 在状态变更后直接返回，避免处理其他逻辑
            return;
        }
        
        // 更新横向菜单 - 确保动画更新
        horizontalMenu.update(currentTime);
        
        // 在底部显示当前选中的应用名称
        int selectedAppIndex = horizontalMenu.getSelectedIndex();
        if (selectedAppIndex >= 0 && selectedAppIndex < 9) {
            // 检查是否已有标签，如果没有则创建
            lv_obj_t* nameLabel = nullptr;
            lv_obj_t* children = lv_screen_active();
            
            // 获取最后一个对象作为可能的标签
            int childCount = lv_obj_get_child_cnt(children);
            if (childCount > 0) { // 至少有一个子对象
                // 尝试获取最后一个子对象
                nameLabel = lv_obj_get_child(children, childCount - 1);
                if (!lv_obj_check_type(nameLabel, &lv_label_class)) { // 确保是标签
                    nameLabel = nullptr;
                }
            }
            
            if (nameLabel == nullptr) {
                // 创建底部标签
                nameLabel = lv_label_create(lv_screen_active());
                lv_obj_set_style_text_font(nameLabel, &lv_font_montserrat_10, 0);
                lv_obj_set_style_text_color(nameLabel, lv_color_hex(0xFFFFFF), 0);
                lv_obj_align(nameLabel, LV_ALIGN_BOTTOM_MID, 0, -2);
            }
            
            // 设置标签文本为应用名
            std::string appName = "App " + std::to_string(selectedAppIndex + 1);
            lv_label_set_text(nameLabel, appName.c_str());
        }
    } 
    else if (currentState == VERTICAL_MENU) {
        // 获取当前选中的选项
        int selectedIndex = verticalMenu.getSelectedIndex();
        
        if (selectedIndex < 0 || selectedIndex >= appMenuOptions[currentAppIndex].size()) {
            mclog::tagError(_tag, "无效的选项索引: %d", selectedIndex);
            switchToHorizontalMenu();
            return;
        }
        
        // 获取当前选中的选项
        MenuOption& currentOption = appMenuOptions[currentAppIndex][selectedIndex];
        
        // 检查是否是最后一项（返回选项）
        bool isLastOption = (selectedIndex == appMenuOptions[currentAppIndex].size() - 1);
        
        // 检查是否在编辑模式
        bool isEditing = verticalMenu.isInEditMode();
        int editingIndex = verticalMenu.getEditingIndex();
        
        // 在编辑模式下处理数值调整
        if (isEditing && editingIndex >= 0) {
            // 使用简单的时间控制来限制调整频率
            static uint32_t lastAdjustTime = 0;
            uint32_t currentTime = HAL::SysCtrl().millis();
            uint32_t minTimeInterval = 100; // 最小调整间隔 (ms)
            
            // 使用上下按键调整数值 - 带时间间隔控制
            if ((HAL::BtnUp().wasClicked() || (HAL::BtnUp().isPressed() && currentTime - lastAdjustTime > minTimeInterval))) {
                // 向上增加数值
                int newValue = verticalMenu.adjustValue(editingIndex, true);
                onValueAdjusted(editingIndex, newValue);
                lastAdjustTime = currentTime;
            }
            
            if ((HAL::BtnDown().wasClicked() || (HAL::BtnDown().isPressed() && currentTime - lastAdjustTime > minTimeInterval))) {
                // 向下减少数值
                int newValue = verticalMenu.adjustValue(editingIndex, false);
                onValueAdjusted(editingIndex, newValue);
                lastAdjustTime = currentTime;
            }
            
            // 确认键退出编辑模式
            if (HAL::BtnOk().wasClicked()) {
                // 退出编辑模式
                verticalMenu.toggleEditMode(editingIndex);
                mclog::info("退出数值编辑模式，最终值: %d", currentOption.value);
            }
        }
        // 非编辑模式下处理菜单导航
        else {
            // 通常的菜单上下移动
            if (HAL::BtnUp().wasClicked()) {
                verticalMenu.goLast();
            }
            
            if (HAL::BtnDown().wasClicked()) {
                verticalMenu.goNext();
            }
            
            if (HAL::BtnOk().wasClicked()) {
                // 根据选项类型进行不同处理
                if (isLastOption) {
                    // 返回选项
                    switchToHorizontalMenu();
                    return; // 在状态变更后直接返回
                } 
                else if (currentOption.type == TYPE_TOGGLE) {
                    // 切换开关状态
                    bool newState = verticalMenu.toggleOption(selectedIndex);
                    onToggleStateChanged(selectedIndex, newState);
                } 
                else if (currentOption.type == TYPE_VALUE) {
                    // 进入数值编辑模式，而不是直接调整数值
                    bool isEditingNow = verticalMenu.toggleEditMode(selectedIndex);
                    if (isEditingNow) {
                        mclog::info("进入数值编辑模式，当前值: %d", currentOption.value);
                    }
                }
            }
        }
        
        if (HAL::BtnPower().wasClicked()) {
            // 如果在编辑模式，先退出编辑模式
            if (isEditing) {
                verticalMenu.toggleEditMode(editingIndex);
                mclog::info("退出数值编辑模式");
            }
            // 否则返回横向菜单
            else {
                switchToHorizontalMenu();
                return; // 在状态变更后直接返回
            }
        }
        
        // 更新竖向菜单 - 确保动画更新
        verticalMenu.update(currentTime);
    }
    
    // 电源按钮长按退出应用
    if (HAL::BtnPower().wasDoubleClicked()) {
        close();
        return;
    }
    
    // 处理LVGL任务
    lv_timer_handler();
    
    // 添加一个小延迟，给动画留出更多更新时间
    HAL::SysCtrl().delay(10);
}

void AppMenuTest::onClose()
{
    mclog::tagInfo(_tag, "on close");
    
    // 清理资源
    horizontalMenu.clear();
    verticalMenu.clear();
    lv_obj_clean(lv_screen_active());
}
