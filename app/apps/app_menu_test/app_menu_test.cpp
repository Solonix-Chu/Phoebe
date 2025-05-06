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
    
    // 初始化横向菜单
    horizontalMenu.init(lv_screen_active());
    
    // 设置选择回调
    horizontalMenu.setSelectCallback([this](int appIndex) {
        this->onHorizontalMenuSelect(appIndex);
    });
    
    // 应用颜色列表
    lv_color_t APP_COLORS[9] = {
        lv_color_hex(0xFF5555), // 红色
        lv_color_hex(0x55FF55), // 绿色
        lv_color_hex(0x5555FF), // 蓝色
        lv_color_hex(0xFFFF55), // 黄色
        lv_color_hex(0xFF55FF), // 紫色
        lv_color_hex(0x55FFFF), // 青色
        lv_color_hex(0xFFAA55), // 橙色
        lv_color_hex(0xAA55FF), // 浅紫色
        lv_color_hex(0x55AAFF)  // 浅蓝色
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
    
    printf("DEBUG: initVerticalMenu - 索引检查通过\n");
    
    // 清理屏幕
    lv_obj_clean(lv_screen_active());
    printf("DEBUG: initVerticalMenu - 屏幕已清理\n");
    
    // 获取当前应用的菜单选项
    const auto& menuOptions = appMenuOptions[appIndex];
    printf("DEBUG: initVerticalMenu - 获取选项成功, 选项数量: %d\n", (int)menuOptions.size());
    
    if (menuOptions.empty()) {
        mclog::tagError(_tag, "No menu options for app index: %d", appIndex);
        // 失败时回到横向菜单
        initHorizontalMenu();
        return;
    }
    
    // 保存当前应用索引
    currentAppIndex = appIndex;
    printf("DEBUG: initVerticalMenu - 应用索引已保存: %d\n", currentAppIndex);
    
    // 初始化竖向菜单 - 传入活动屏幕
    printf("DEBUG: initVerticalMenu - 开始初始化菜单对象\n");
    lv_obj_t* screen = lv_screen_active();
    printf("DEBUG: initVerticalMenu - 活动屏幕指针: %p\n", (void*)screen);
    verticalMenu.init(screen);
    printf("DEBUG: initVerticalMenu - 菜单对象初始化完成\n");
    
    try {
        // 设置选项
        printf("DEBUG: initVerticalMenu - 开始设置选项\n");
        verticalMenu.setOptions(menuOptions);
        printf("DEBUG: initVerticalMenu - 选项设置完成\n");
        
        // 设置选择回调
        printf("DEBUG: initVerticalMenu - 开始设置回调\n");
        verticalMenu.setSelectCallback([this](int optionIndex, OptionType type) {
            this->onVerticalMenuSelect(optionIndex, type);
        });
        printf("DEBUG: initVerticalMenu - 回调设置完成\n");
        
        // 切换当前状态
        currentState = VERTICAL_MENU;
        printf("DEBUG: initVerticalMenu - 状态已切换\n");
        
        std::string appName = "App " + std::to_string(appIndex + 1);
        mclog::tagInfo(_tag, "%s settings menu initialized", appName.c_str());
        printf("DEBUG: initVerticalMenu - 初始化完成\n");
    } catch (const std::exception& e) {
        // 捕获可能的异常
        printf("ERROR: initVerticalMenu - 异常: %s\n", e.what());
        mclog::tagError(_tag, "Exception initializing vertical menu: %s", e.what());
        // 失败时回到横向菜单
        initHorizontalMenu();
    } catch (...) {
        printf("ERROR: initVerticalMenu - 未知异常\n");
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
    printf("DEBUG: 进入 switchToVerticalMenu, 索引 = %d\n", appIndex);
    
    // 安全检查 appIndex
    if (appIndex < 0 || appIndex >= appMenuOptions.size()) {
        printf("ERROR: 应用索引无效: %d, 菜单选项大小: %d\n", appIndex, (int)appMenuOptions.size());
        mclog::tagError(_tag, "无效的应用索引: %d", appIndex);
        initHorizontalMenu();
        return;
    }
    
    // 1. 先清理横向菜单资源
    horizontalMenu.clear();
    printf("DEBUG: 横向菜单已清理\n");
    
    // 2. 清理屏幕
    lv_obj_clean(lv_screen_active());
    printf("DEBUG: 屏幕已清理\n");
    
    // 3. 初始化垂直菜单
    try {
        printf("DEBUG: 开始初始化垂直菜单\n");
        initVerticalMenu(appIndex);
        printf("DEBUG: 垂直菜单初始化完成\n");
    } catch (const std::exception& e) {
        printf("ERROR: 初始化垂直菜单时异常: %s\n", e.what());
        mclog::tagError(_tag, "初始化垂直菜单时异常: %s", e.what());
        initHorizontalMenu();
    } catch (...) {
        printf("ERROR: 初始化垂直菜单时未知异常\n");
        mclog::tagError(_tag, "初始化垂直菜单时未知异常");
        initHorizontalMenu();
    }
}

void AppMenuTest::switchToHorizontalMenu() {
    // 无论当前状态如何，都确保垂直菜单资源被清理
    verticalMenu.clear();
    
    // 初始化横向菜单
    initHorizontalMenu();
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
            mclog::info("向左移动菜单");
            horizontalMenu.goLast();
        }
        
        if (HAL::BtnDown().wasClicked()) {
            mclog::info("向右移动菜单");
            horizontalMenu.goNext();
        }
        
        if (HAL::BtnOk().wasClicked()) {
            // 选择当前应用，切换到竖向菜单
            int selectedIndex = horizontalMenu.getSelectedIndex();
            
            // 避免使用格式化字符串，改为字符串拼接
            std::string logMsg = "选中应用: " + std::to_string(selectedIndex);
            mclog::info(logMsg.c_str());
            
            // 直接使用 printf 进行调试输出
            printf("DEBUG: 选中应用索引 = %d\n", selectedIndex);
            printf("DEBUG: appMenuOptions 大小 = %d\n", (int)appMenuOptions.size());
            printf("DEBUG: 当前状态 = %d\n", (int)currentState);
            
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
    } 
    else if (currentState == VERTICAL_MENU) {
        // 检查当前所选项的有效性
        int selectedIndex = verticalMenu.getSelectedIndex();
        
        // 检查当前应用索引的有效性
        if (currentAppIndex < 0 || currentAppIndex >= appMenuOptions.size()) {
            mclog::tagError(_tag, "Invalid current app index: %d, switching to horizontal menu", currentAppIndex);
            switchToHorizontalMenu();
            return;
        }
        
        auto& options = appMenuOptions[currentAppIndex];
        
        // 检查选中索引的有效性
        if (selectedIndex < 0 || selectedIndex >= options.size()) {
            mclog::tagError(_tag, "Invalid selected index: %d, resetting menu", selectedIndex);
            // 重新初始化垂直菜单
            initVerticalMenu(currentAppIndex);
            return;
        }
        
        bool isLastOption = (selectedIndex == options.size() - 1);
        auto& currentOption = verticalMenu.getOption(selectedIndex);
        
        // 竖向菜单的控制
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
                mclog::info("返回应用菜单");
                switchToHorizontalMenu();
                
                // 在状态变更后直接返回，避免处理其他逻辑
                return;
            } 
            else if (currentOption.type == TYPE_TOGGLE) {
                // 切换开关状态
                bool newState = verticalMenu.toggleOption(selectedIndex);
                onToggleStateChanged(selectedIndex, newState);
            } 
            else if (currentOption.type == TYPE_VALUE) {
                // 进入数值编辑模式，由verticalMenu内部处理闪烁等效果
                int value = verticalMenu.adjustValue(selectedIndex, true); // 初始增加一次
                onValueAdjusted(selectedIndex, value);
            }
        }
        
        if (HAL::BtnPower().wasClicked()) {
            // 返回横向菜单
            mclog::info("返回应用菜单");
            switchToHorizontalMenu();
            
            // 在状态变更后直接返回，避免处理其他逻辑
            return;
        }
        
        // 更新竖向菜单 - 确保动画更新
        verticalMenu.update(currentTime);
    }
    
    // 电源按钮长按退出应用
    if (HAL::BtnPower().wasDoubleClicked()) {
        mclog::info("退出应用");
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
