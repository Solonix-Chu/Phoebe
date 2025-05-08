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

void AppMenuTest::initHorizontalMenu() {
    // 清理当前屏幕上的所有元素 
    lv_obj_clean(lv_screen_active());
    
    // 初始化横向菜单
    horizontalMenu.init(lv_screen_active());
    
    // 确保选中框可见
    horizontalMenu.setSelectionFrameVisible(true);
    
    // 使用白色图标 - 适合OLED屏幕上的高对比度
    lv_color_t iconColor = lv_color_hex(0xFFFFFF); // 纯白色
    
    // 添加应用 - 全部使用白色图标，交替使用圆形和方形
    horizontalMenu.addApp("App 1", iconColor, true);   // 白色圆形
    horizontalMenu.addApp("App 2", iconColor, false);  // 白色方形
    horizontalMenu.addApp("App 3", iconColor, true);   // 白色圆形
    horizontalMenu.addApp("App 4", iconColor, false);  // 白色方形
    horizontalMenu.addApp("App 5", iconColor, true);   // 白色圆形
    horizontalMenu.addApp("App 6", iconColor, false);  // 白色方形
    horizontalMenu.addApp("App 7", iconColor, true);   // 白色圆形
    horizontalMenu.addApp("App 8", iconColor, false);  // 白色方形
    horizontalMenu.addApp("App 9", iconColor, true);   // 白色圆形
    
    // 设置按钮回调
    horizontalMenu.setSelectCallback([this](int appIndex) {
        onHorizontalMenuSelect(appIndex);
        if (HAL::BtnOk().wasReleased()) {
            switchToVerticalMenu(appIndex);
        }
    });
    
    // 更新状态
    currentState = HORIZONTAL_MENU;
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

void AppMenuTest::completeVerticalMenuTransition(int appIndex) {
    // 清理横向菜单资源
    horizontalMenu.clear();
    
    // 初始化垂直菜单
    try {
        initVerticalMenu(appIndex);
        
        // 为垂直菜单添加淡入效果
        lv_obj_t* menuSelector = verticalMenu.getSelector();
        if (menuSelector) {
            // 初始设置为不可见
            lv_obj_set_style_opa(menuSelector, 0, 0);
            
            // 创建淡入动画
            lv_anim_t menuFadeIn;
            lv_anim_init(&menuFadeIn);
            lv_anim_set_var(&menuFadeIn, menuSelector);
            lv_anim_set_values(&menuFadeIn, 0, 255);
            lv_anim_set_time(&menuFadeIn, 300);
            lv_anim_set_path_cb(&menuFadeIn, lv_anim_path_ease_out);
            
            // 设置不透明度动画回调
            lv_anim_set_exec_cb(&menuFadeIn, [](void* target, int32_t value) {
                lv_obj_set_style_opa((lv_obj_t*)target, value, 0);
            });
            
            lv_anim_start(&menuFadeIn);
        }
        
        // 重置过渡状态
        isTransitioning = false;
        transitionTargetAppIndex = -1;
        
    } catch (const std::exception& e) {
        mclog::tagError(_tag, "初始化垂直菜单时异常: %s", e.what());
        initHorizontalMenu();
    } catch (...) {
        mclog::tagError(_tag, "初始化垂直菜单时未知异常");
        initHorizontalMenu();
    }
}

void AppMenuTest::switchToVerticalMenu(int appIndex) {
    // 安全检查 appIndex
    if (appIndex < 0 || appIndex >= appMenuOptions.size()) {
        mclog::tagError(_tag, "无效的应用索引: %d", appIndex);
        initHorizontalMenu();
        return;
    }
    
    // 保存当前选中的应用索引
    currentAppIndex = appIndex;
    
    // 设置过渡状态
    isTransitioning = true;
    transitionTargetAppIndex = appIndex;
    
    // 隐藏选中框
    horizontalMenu.setSelectionFrameVisible(false);
    
    // 获取当前应用图标的位置信息，用于动画起始点
    lv_obj_t* selectedIcon = nullptr;
    lv_coord_t icon_x = 0;
    lv_coord_t icon_y = 0;
    lv_coord_t icon_width = 0;
    lv_coord_t icon_height = 0;
    
    // 确保存在应用图标
    int selectedIndex = horizontalMenu.getSelectedIndex();
    if (selectedIndex >= 0 && selectedIndex < horizontalMenu.getAppIconCount()) {
        selectedIcon = horizontalMenu.getAppIcon(selectedIndex);
        if (selectedIcon) {
            icon_x = lv_obj_get_x(selectedIcon);
            icon_y = lv_obj_get_y(selectedIcon);
            icon_width = lv_obj_get_width(selectedIcon);
            icon_height = lv_obj_get_height(selectedIcon);
        }
    }
    
    // 创建一个临时容器用于过渡动画
    lv_obj_t* transitionCont = lv_obj_create(lv_screen_active());
    lv_obj_set_size(transitionCont, HAL::Display().width(), HAL::Display().height());
    lv_obj_set_pos(transitionCont, 0, 0);
    lv_obj_set_style_radius(transitionCont, 0, 0);
    lv_obj_set_style_border_width(transitionCont, 0, 0);
    lv_obj_set_style_bg_color(transitionCont, lv_color_hex(0x000000), 0); // 黑色背景
    
    // 创建一个临时标签显示应用名称
    lv_obj_t* titleLabel = lv_label_create(transitionCont);
    std::string appTitle = "App " + std::to_string(appIndex + 1);
    lv_label_set_text(titleLabel, appTitle.c_str());
    lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_10, 0);
    lv_obj_set_style_text_color(titleLabel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(titleLabel, LV_ALIGN_TOP_MID, 0, 5);
    
    // 初始设置为透明
    lv_obj_set_style_opa(transitionCont, 0, 0);
    
    // 创建用户数据结构
    struct UserData {
        AppMenuTest* app;
        int appIndex;
        lv_obj_t* container;
    };
    
    UserData* userData = new UserData{this, appIndex, transitionCont};
    
    // 1. 定义动画 - 容器淡入
    lv_anim_t fadeIn;
    lv_anim_init(&fadeIn);
    lv_anim_set_var(&fadeIn, transitionCont);
    lv_anim_set_values(&fadeIn, 0, 255);
    lv_anim_set_time(&fadeIn, 300);
    lv_anim_set_path_cb(&fadeIn, lv_anim_path_ease_out);
    
    // 设置不透明度动画回调
    lv_anim_set_exec_cb(&fadeIn, [](void* target, int32_t value) {
        lv_obj_set_style_opa((lv_obj_t*)target, value, 0);
    });
    
    // 设置完成回调
    lv_anim_set_ready_cb(&fadeIn, [](lv_anim_t* a) {
        // 获取用户数据
        UserData* data = static_cast<UserData*>(lv_anim_get_user_data(a));
        if (!data) return;
        
        // 清理当前屏幕上的所有元素 - 包括临时过渡容器
        lv_obj_clean(lv_screen_active());
        
        // 完成垂直菜单初始化
        data->app->completeVerticalMenuTransition(data->appIndex);
        
        // 清理用户数据
        delete data;
    });
    
    // 设置用户数据
    lv_anim_set_user_data(&fadeIn, userData);
    
    // 开始动画
    lv_anim_start(&fadeIn);
}

void AppMenuTest::switchToHorizontalMenu() {
    // 保存当前应用索引
    int lastAppIndex = currentAppIndex;
    
    // 更改菜单状态，防止在过渡过程中访问已清理的垂直菜单
    currentState = HORIZONTAL_MENU;
    
    // 创建一个临时过渡容器
    lv_obj_t* transitionCont = lv_obj_create(lv_screen_active());
    lv_obj_set_size(transitionCont, HAL::Display().width(), HAL::Display().height());
    lv_obj_set_pos(transitionCont, 0, 0);
    lv_obj_set_style_radius(transitionCont, 0, 0);
    lv_obj_set_style_border_width(transitionCont, 0, 0);
    lv_obj_set_style_bg_color(transitionCont, lv_color_hex(0x000000), 0); // 黑色背景
    
    // 淡入过渡容器
    lv_obj_set_style_opa(transitionCont, 0, 0);
    lv_anim_t fadeIn;
    lv_anim_init(&fadeIn);
    lv_anim_set_var(&fadeIn, transitionCont);
    lv_anim_set_values(&fadeIn, 0, 255);
    lv_anim_set_time(&fadeIn, 200);
    lv_anim_set_path_cb(&fadeIn, lv_anim_path_ease_out);
    
    // 设置不透明度动画回调
    lv_anim_set_exec_cb(&fadeIn, [](void* target, int32_t value) {
        lv_obj_set_style_opa((lv_obj_t*)target, value, 0);
    });
    
    // 创建用户数据，包含this指针和lastAppIndex
    struct UserData {
        AppMenuTest* app;
        int appIndex;
        lv_obj_t* container;
    };
    
    UserData* userData = new UserData{this, lastAppIndex, transitionCont};
    
    // 先清理垂直菜单资源，但保留屏幕
    // 在开始动画前清理，防止在过渡过程中访问已清理的资源
    verticalMenu.clear();
    
    // 淡入完成后，淡出并初始化横向菜单
    lv_anim_set_ready_cb(&fadeIn, [](lv_anim_t* a) {
        // 获取用户数据
        UserData* data = static_cast<UserData*>(lv_anim_get_user_data(a));
        if (!data) return;
        
        // 创建淡出动画
        lv_anim_t fadeOut;
        lv_anim_init(&fadeOut);
        lv_anim_set_var(&fadeOut, data->container);
        lv_anim_set_values(&fadeOut, 255, 0);
        lv_anim_set_time(&fadeOut, 200);
        lv_anim_set_path_cb(&fadeOut, lv_anim_path_ease_in);
        
        // 设置不透明度动画回调
        lv_anim_set_exec_cb(&fadeOut, [](void* target, int32_t value) {
            lv_obj_set_style_opa((lv_obj_t*)target, value, 0);
        });
        
        // 淡出完成后，清理屏幕并初始化横向菜单
        lv_anim_set_ready_cb(&fadeOut, [](lv_anim_t* anim) {
            // 获取用户数据
            UserData* userData = static_cast<UserData*>(lv_anim_get_user_data(anim));
            if (!userData) return;
            
            // 清理屏幕
            lv_obj_clean(lv_screen_active());
            
            // 初始化横向菜单
            userData->app->initHorizontalMenu();
            
            // 如果之前有选择有效的应用索引，则将横向菜单设置到该位置
            if (userData->appIndex >= 0 && userData->appIndex < 9) {
                // 移动到保存的位置
                int currentPos = userData->app->horizontalMenu.getSelectedIndex();
                int stepsToMove = userData->appIndex - currentPos;
                
                // 根据方向移动
                if (stepsToMove > 0) {
                    // 向右移动
                    for (int i = 0; i < stepsToMove; i++) {
                        userData->app->horizontalMenu.goNext();
                        userData->app->horizontalMenu.update(userData->app->currentTime); // 更新布局
                    }
                } else if (stepsToMove < 0) {
                    // 向左移动
                    for (int i = 0; i < -stepsToMove; i++) {
                        userData->app->horizontalMenu.goLast();
                        userData->app->horizontalMenu.update(userData->app->currentTime); // 更新布局
                    }
                }
                // 强制更新一次
                userData->app->horizontalMenu.update(userData->app->currentTime);
            }
            
            // 为横向菜单添加淡入效果
            lv_obj_t* menuItems[9] = {nullptr};
            for (int i = 0; i < userData->app->horizontalMenu.getAppIconCount() && i < 9; i++) {
                menuItems[i] = userData->app->horizontalMenu.getAppIcon(i);
                if (menuItems[i]) {
                    lv_obj_set_style_opa(menuItems[i], 0, 0);
                }
            }
            
            // 依次淡入每个菜单项
            for (int i = 0; i < userData->app->horizontalMenu.getAppIconCount() && i < 9; i++) {
                if (menuItems[i]) {
                    lv_anim_t itemFadeIn;
                    lv_anim_init(&itemFadeIn);
                    lv_anim_set_var(&itemFadeIn, menuItems[i]);
                    lv_anim_set_values(&itemFadeIn, 0, 255);
                    lv_anim_set_time(&itemFadeIn, 200);
                    lv_anim_set_delay(&itemFadeIn, i * 30); // 错开每个图标的淡入时间
                    lv_anim_set_path_cb(&itemFadeIn, lv_anim_path_ease_out);
                    
                    // 设置不透明度动画回调
                    lv_anim_set_exec_cb(&itemFadeIn, [](void* target, int32_t value) {
                        lv_obj_set_style_opa((lv_obj_t*)target, value, 0);
                    });
                    
                    lv_anim_start(&itemFadeIn);
                }
            }
            
            // 释放用户数据
            delete userData;
        });
        
        // 使用与fadeIn相同的用户数据
        lv_anim_set_user_data(&fadeOut, data);
        
        // 开始淡出动画
        lv_anim_start(&fadeOut);
    });
    
    // 设置用户数据
    lv_anim_set_user_data(&fadeIn, userData);
    
    // 开始淡入动画
    lv_anim_start(&fadeIn);
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
                // 移除底部的应用名称标签
                lv_obj_t* children = lv_screen_active();
                int childCount = lv_obj_get_child_cnt(children);
                if (childCount > 0) {
                    lv_obj_t* lastChild = lv_obj_get_child(children, childCount - 1);
                    if (lv_obj_check_type(lastChild, &lv_label_class)) {
                        lv_obj_del(lastChild);
                    }
                }
                
                // 切换到垂直菜单
                switchToVerticalMenu(selectedIndex);
            } else {
                mclog::tagError(_tag, "无效的应用索引");
            }
            
            // 在状态变更后直接返回，避免处理其他逻辑
            return;
        }
        
        // 更新横向菜单 - 确保动画更新
        horizontalMenu.update(currentTime);
        
        // 在底部显示当前选中的应用名称（仅在非过渡状态显示）
        if (!isTransitioning) {
            int selectedAppIndex = horizontalMenu.getSelectedIndex();
            if (selectedAppIndex >= 0 && selectedAppIndex < 9) {
                // 检查是否已有标签，如果没有则创建
                lv_obj_t* nameLabel = nullptr;
                lv_obj_t* children = lv_screen_active();
                
                // 先删除之前的标签以防止重叠
                int childCount = lv_obj_get_child_cnt(children);
                for (int i = 0; i < childCount; i++) {
                    lv_obj_t* child = lv_obj_get_child(children, i);
                    if (lv_obj_check_type(child, &lv_label_class) && 
                        lv_obj_get_y(child) > lv_obj_get_height(children) - 20) { // 只删除底部区域的标签
                        lv_obj_del(child);
                        break; // 只需要删除一个标签
                    }
                }
                
                // 创建新标签
                nameLabel = lv_label_create(lv_screen_active());
                lv_obj_set_style_text_font(nameLabel, &lv_font_montserrat_10, 0);
                lv_obj_set_style_text_color(nameLabel, lv_color_hex(0xFFFFFF), 0);
                lv_obj_align(nameLabel, LV_ALIGN_BOTTOM_MID, 0, -2);
                
                // 设置标签文本为应用名
                std::string appName = "App " + std::to_string(selectedAppIndex + 1);
                lv_label_set_text(nameLabel, appName.c_str());
            }
        }
    } 
    else if (currentState == VERTICAL_MENU) {
        // 确保垂直菜单已初始化并且不在过渡状态
        if (verticalMenu.getSelector() == nullptr) {
            // 垂直菜单可能已被清理，但状态未及时更新
            // 不处理垂直菜单逻辑
            return;
        }
        
        // 获取当前选中的选项
        int selectedIndex = verticalMenu.getSelectedIndex();
        
        // 安全检查索引和数组访问
        if (selectedIndex < 0 || 
            currentAppIndex < 0 || 
            currentAppIndex >= appMenuOptions.size() || 
            selectedIndex >= appMenuOptions[currentAppIndex].size()) {
            
            // 不记录日志，避免大量错误输出
            // 在下一帧会自动恢复
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
