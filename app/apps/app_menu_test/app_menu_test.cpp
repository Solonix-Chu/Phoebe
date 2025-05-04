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
#include <algorithm> // 添加algorithm头文件以使用std::max

// Add font declarations
LV_FONT_DECLARE(lv_font_montserrat_10);
LV_FONT_DECLARE(lv_font_montserrat_14);
LV_FONT_DECLARE(lv_font_montserrat_16);

using namespace mooncake;
using namespace SmoothUIToolKit;
using namespace SmoothUIToolKit::SelectMenu;

#define _tag (getAppInfo().name)

AppMenuTest::AppMenuTest()
{
    // 配置 App 信息
    setAppInfo().name = "AppMenuTest";
}

void AppMenuTest::onCreate()
{
    mclog::tagInfo(_tag, "on create");

    // 清除屏幕
    lv_obj_clean(lv_screen_active());
    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);
    
    // 初始化菜单选项数据
    initMenuOptions();
    
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

void AppMenuTest::toggleOptionState(int index)
{
    if (currentAppIndex >= 0 && currentAppIndex < appMenuOptions.size() &&
        index >= 0 && index < appMenuOptions[currentAppIndex].size()) {
        
        MenuOption& option = appMenuOptions[currentAppIndex][index];
        if (option.type == TYPE_TOGGLE) {
            // 切换开关状态
            option.toggleState = !option.toggleState;
            
            // 更新UI
            if (index < stateLabels.size()) {
                lv_label_set_text(stateLabels[index], getOptionStateText(option).c_str());
            }
        }
    }
}

void AppMenuTest::adjustValue(int index, bool increment)
{
    if (currentAppIndex >= 0 && currentAppIndex < appMenuOptions.size() &&
        index >= 0 && index < appMenuOptions[currentAppIndex].size()) {
        
        MenuOption& option = appMenuOptions[currentAppIndex][index];
        if (option.type == TYPE_VALUE) {
            // 调整值
            if (increment) {
                option.value += option.step;
                if (option.value > option.maxValue) {
                    option.value = option.maxValue;
                }
            } else {
                option.value -= option.step;
                if (option.value < option.minValue) {
                    option.value = option.minValue;
                }
            }
            
            // 更新UI
            if (index < stateLabels.size()) {
                lv_label_set_text(stateLabels[index], getOptionStateText(option).c_str());
            }
        }
    }
}

std::string AppMenuTest::getOptionStateText(const MenuOption& option)
{
    switch (option.type) {
        case TYPE_TOGGLE:
            return option.toggleState ? "ON" : "OFF";
        case TYPE_VALUE:
            return std::to_string(option.value);
        case TYPE_ACTION:
        default:
            return "";
    }
}

void AppMenuTest::clearMenus() 
{
    // 清理横向菜单资源
    for (auto icon : appIcons) {
        if (icon != nullptr) {
            lv_obj_del(icon);
        }
    }
    appIcons.clear();
    
    // 清理竖向菜单资源
    for (auto item : menuItems) {
        if (item != nullptr) {
            lv_obj_del(item);
        }
    }
    menuItems.clear();
    
    // 清理状态标签
    for (auto label : stateLabels) {
        if (label != nullptr) {
            lv_obj_del(label);
        }
    }
    stateLabels.clear();
    
    if (selector != nullptr) {
        lv_obj_del(selector);
        selector = nullptr;
    }
    
    // 重置编辑状态
    isEditingValue = false;
    
    // 不需要调用reset方法，在初始化函数中会重新创建菜单对象
}

void AppMenuTest::initHorizontalMenu() 
{
    // 清理之前的菜单资源
    clearMenus();
    
    // 重新初始化横向菜单对象，清除所有旧状态
    horizontalMenu = SmoothUIToolKit::SelectMenu::SmoothOptions();
    
    // 创建应用图标列表 - 增加图标数量
    const int NUM_APPS = 9;
    const char* APP_NAMES[NUM_APPS] = {"App 1", "App 2", "App 3", "App 4", "App 5", "App 6", "App 7", "App 8", "App 9"};
    lv_color_t APP_COLORS[NUM_APPS] = {
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
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    
    // 为每个应用添加一个选项并创建图标
    for (int i = 0; i < NUM_APPS; i++) {
        // 添加选项
        horizontalMenu.addOption();
        
        // 创建图标 - 使用矩形作为图标
        lv_obj_t* icon = lv_obj_create(lv_screen_active());
        lv_obj_set_style_bg_color(icon, APP_COLORS[i], 0);
        lv_obj_set_style_radius(icon, i % 2 == 0 ? 0 : LV_RADIUS_CIRCLE, 0); // 交替使用方形和圆形
        lv_obj_set_style_border_width(icon, 2, 0);
        lv_obj_set_style_border_color(icon, lv_color_hex(0xFFFFFF), 0);
        // 移除阴影效果
        lv_obj_set_style_shadow_width(icon, 0, 0);
        
        // 添加标签
        lv_obj_t* label = lv_label_create(icon);
        lv_label_set_text(label, APP_NAMES[i]);
        lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
        lv_obj_center(label);
        
        // 初始隐藏图标
        lv_obj_set_style_opa(icon, 0, 0);
        
        appIcons.push_back(icon);
    }
    
    // 设置横向循环菜单的关键帧
    for (int i = 0; i < NUM_APPS; i++) {
        // 计算循环位置，中心为选中项
        int offset = i - 2; // 以中间位置为基准
        
        // 设置关键帧位置，所有图标在同一水平线上，减小间距以显示更多图标
        Vector4D_t keyframe;
        keyframe.x = screenWidth/2 + offset * 75; // 减小横向间隔为75，使更多图标可见
        keyframe.y = screenHeight/2;              // 所有图标垂直居中在同一水平线
        
        // 更平衡的尺寸对比：选中项大，非选中项小一些但仍然清晰可见
        if (offset == 0) {
            keyframe.w = 70; // 选中项大小稍微减小
            keyframe.h = 70;
        } else {
            keyframe.w = 40;  // 非选中项大小
            keyframe.h = 40;
        }
        
        horizontalMenu.setKeyframe(i, keyframe);
    }
    
    // 设置动画效果，强化弹性效果和过渡
    
    // 位置过渡
    horizontalMenu.setPositionDuration(600);     // 增加持续时间，使动画更明显
    horizontalMenu.setPositionTransitionPath(EasingPath::easeOutElastic); // 使用easeOutElastic获得更强的弹性效果
    
    // 形状过渡
    horizontalMenu.setShapeDuration(800);        // 增加持续时间，使动画更明显
    horizontalMenu.setShapeTransitionPath(EasingPath::easeOutBack); // 使用easeOutBack获得弹性效果
    
    // 确保所有选项的动画统一设置
    horizontalMenu.setDuration(600); // 统一设置所有选项的过渡时间
    
    // 初始化动画，从中间开始
    horizontalMenu.jumpTo(2);
    
    // 初始状态
    currentState = HORIZONTAL_MENU;
    mclog::tagInfo(_tag, "横向菜单已初始化，共%d个应用", NUM_APPS);
}

void AppMenuTest::initVerticalMenu(int appIndex) 
{
    // 清理之前的菜单资源
    clearMenus();
    
    // 重新初始化垂直菜单对象，清除所有旧状态
    verticalMenu = SmoothUIToolKit::SelectMenu::SmoothSelector();
    
    // 确保应用索引有效
    if (appIndex < 0 || appIndex >= appMenuOptions.size()) {
        mclog::tagError(_tag, "Invalid app index: %d", appIndex);
        return;
    }
    
    // 获取当前应用的菜单选项
    const auto& menuOptions = appMenuOptions[appIndex];
    if (menuOptions.empty()) {
        mclog::tagError(_tag, "No menu options for app index: %d", appIndex);
        return;
    }
    
    // 保存当前应用索引
    currentAppIndex = appIndex;
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    
    // 创建一个透明背景覆盖整个屏幕
    lv_obj_t* fullBg = lv_obj_create(lv_screen_active());
    lv_obj_set_size(fullBg, screenWidth, screenHeight);
    lv_obj_set_pos(fullBg, 0, 0);
    lv_obj_set_style_bg_opa(fullBg, 0, 0); // 完全透明，移除背景
    lv_obj_set_style_border_width(fullBg, 0, 0);
    menuItems.push_back(fullBg);
    
    // 创建选择器UI元素
    selector = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_color(selector, lv_color_hex(0x3399FF), 0);
    lv_obj_set_style_bg_opa(selector, 80, 0);  // 降低背景透明度
    lv_obj_set_style_border_width(selector, 2, 0);
    lv_obj_set_style_border_color(selector, lv_color_hex(0x66AAFF), 0);
    lv_obj_set_style_radius(selector, 6, 0);
    
    // 设置菜单配置，包括摄像机设置
    verticalMenu.setConfig({
        .moveInLoop = true,      // 循环模式
        .cameraSize = {screenWidth, screenHeight},
        .readInputInterval = 20,
        .renderInterval = 15
    });
    
    // 设置摄像机动画效果
    verticalMenu.getCamera().setDuration(300);
    verticalMenu.getCamera().setTransitionPath(EasingPath::easeOutQuad);
    
    // 初始化摄像机位置为零
    verticalMenu.getCamera().jumpTo(0, 0);
    
    // 记录初始摄像机位置
    mclog::info("摄像机初始位置设置为 (0,0)");
    
    // 添加菜单选项
    const int SPACING = this->MENU_ITEM_SPACING;
    // 修改起始Y坐标，使其完全从左上角开始
    const int START_Y = 0; // 从屏幕顶部开始
    const int LEFT_MARGIN = 0; // 从屏幕最左侧开始
    
    int numOptions = menuOptions.size();
    
    for (int i = 0; i < numOptions; i++) {
        // 计算项目Y坐标，从顶部开始
        int itemY = START_Y + i * (this->MENU_ITEM_HEIGHT + SPACING);
        
        // 移除选项背景
        lv_obj_t* placeholder = lv_obj_create(lv_screen_active());
        lv_obj_set_size(placeholder, screenWidth, this->MENU_ITEM_HEIGHT);
        lv_obj_set_style_bg_opa(placeholder, 0, 0);  // 完全透明
        lv_obj_set_style_border_width(placeholder, 0, 0);
        lv_obj_set_pos(placeholder, LEFT_MARGIN, itemY);
        menuItems.push_back(placeholder);
        
        // 创建选项标签 - 左对齐
        lv_obj_t* label = lv_label_create(lv_screen_active());
        lv_label_set_text(label, menuOptions[i].name.c_str());
        lv_obj_set_style_text_color(label, lv_color_hex(0x000000), 0);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_10, 0);
        lv_obj_set_pos(label, LEFT_MARGIN + 5, itemY + (this->MENU_ITEM_HEIGHT - 10) / 2 - 2);
        menuItems.push_back(label);
        
        // 为非Back选项添加状态标签 (ON/OFF 或 数值)
        if (menuOptions[i].type != TYPE_ACTION) {
            lv_obj_t* stateLabel = lv_label_create(lv_screen_active());
            lv_label_set_text(stateLabel, getOptionStateText(menuOptions[i]).c_str());
            lv_obj_set_style_text_color(stateLabel, lv_color_hex(0x000000), 0);
            lv_obj_set_style_text_font(stateLabel, &lv_font_montserrat_10, 0);
            
            // 设置文本右对齐
            lv_obj_set_style_text_align(stateLabel, LV_TEXT_ALIGN_RIGHT, 0);
            int valueWidth = 40;
            lv_obj_set_width(stateLabel, valueWidth);
            
            int rightMargin = 10;
            int xPosition = screenWidth - rightMargin - valueWidth;
            
            lv_obj_set_pos(stateLabel, xPosition, itemY + (this->MENU_ITEM_HEIGHT - 10) / 2 - 2);
            
            menuItems.push_back(stateLabel);
            stateLabels.push_back(stateLabel);
        } else {
            // 为保持索引对应，添加一个空的占位符
            stateLabels.push_back(nullptr);
        }
        
        // 添加选项到菜单
        SmoothSelector::OptionProps_t option;
        option.keyframe = {
            LEFT_MARGIN,
            itemY,
            screenWidth,
            this->MENU_ITEM_HEIGHT
        };
        verticalMenu.addOption(option);
    }
    
    // 设置选择器样式和动画
    verticalMenu.setPositionDuration(300);
    verticalMenu.setShapeDuration(300);
    verticalMenu.setPositionTransitionPath(EasingPath::easeOutQuad);
    verticalMenu.setShapeTransitionPath(EasingPath::easeOutQuad);
    
    // 初始化动画
    verticalMenu.jumpTo(0);
    
    // 切换当前状态
    currentState = VERTICAL_MENU;
    mclog::tagInfo(_tag, "%s settings menu initialized", ("App " + std::to_string(appIndex + 1)).c_str());
}

void AppMenuTest::switchToVerticalMenu(int appIndex) {
    if (currentState == HORIZONTAL_MENU) {
        initVerticalMenu(appIndex);
    }
}

void AppMenuTest::switchToHorizontalMenu() {
    if (currentState == VERTICAL_MENU) {
        initHorizontalMenu();
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
        // 获取当前选中的索引
        int selectedIndex = horizontalMenu.getSelectedOptionIndex();
        static int lastSelectedIndex = -1;  // 用于跟踪选择变化
        
        // 只在选中项改变时输出日志
        if (selectedIndex != lastSelectedIndex) {
            mclog::info("当前选中应用索引: %d", selectedIndex);
            lastSelectedIndex = selectedIndex;
        }
        
        // 横向菜单的控制
        if (HAL::BtnUp().wasClicked()) {
            mclog::info("向左移动菜单");
            // 确保每次移动都重新设置动画参数
            horizontalMenu.setPositionDuration(600);
            horizontalMenu.setShapeDuration(800);
            horizontalMenu.setPositionTransitionPath(EasingPath::easeOutElastic);
            // 调用移动方法
            horizontalMenu.goLast();
        }
        
        if (HAL::BtnDown().wasClicked()) {
            mclog::info("向右移动菜单");
            // 确保每次移动都重新设置动画参数
            horizontalMenu.setPositionDuration(600);
            horizontalMenu.setShapeDuration(800);
            horizontalMenu.setPositionTransitionPath(EasingPath::easeOutElastic);
            // 调用移动方法
            horizontalMenu.goNext();
        }
        
        if (HAL::BtnOk().wasClicked()) {
            // 选择当前应用，切换到竖向菜单
            mclog::info("选中应用: %d", selectedIndex);
            switchToVerticalMenu(selectedIndex);
        }
        
        // 更新横向菜单 - 确保动画更新
        horizontalMenu.update(currentTime);
        
        // 强制更新LVGL UI，确保动画显示
        lv_timer_handler();
        
        // 更新UI元素位置和大小
        for (int i = 0; i < appIcons.size() && i < horizontalMenu.getOptionList().size(); i++) {
            // 获取当前选项的位置和形状
            auto& option = horizontalMenu.getOption(i);
            auto pos = option.position.getValue();
            auto shape = option.shape.getValue();
            
            // 注意：Transition2D::getValue() 返回 Vector2D_t，使用 width/height
            lv_obj_set_pos(appIcons[i], pos.x - shape.width/2, pos.y - shape.height/2);
            lv_obj_set_size(appIcons[i], shape.width, shape.height);
            
            // 设置所有图标为不透明
            lv_obj_set_style_opa(appIcons[i], 255, 0);
            
            // 只为中心项添加特殊效果
            if (i == selectedIndex) {
                // 选中项加强效果 - 更粗的边框
                lv_obj_set_style_border_width(appIcons[i], 4, 0);
                lv_obj_set_style_border_color(appIcons[i], lv_color_hex(0xFFFFFF), 0);
            } else {
                // 设置非选中项的普通效果
                lv_obj_set_style_border_width(appIcons[i], 1, 0);
                lv_obj_set_style_border_color(appIcons[i], lv_color_hex(0xAAAAAA), 0);
            }
        }
    } 
    else if (currentState == VERTICAL_MENU) {
        // 获取当前选中的索引
        int selectedIndex = verticalMenu.getSelectedOptionIndex();
        static int lastSelectedIndex = -1;  // 用于跟踪选择变化
        
        // 只在选中项改变时输出日志，并且不在编辑状态时
        if (selectedIndex != lastSelectedIndex && !isEditingValue) {
            mclog::info("当前选中设置项索引: %d", selectedIndex);
            lastSelectedIndex = selectedIndex;
        }
        
        // 检查当前所选项的类型
        auto& options = appMenuOptions[currentAppIndex];
        bool isLastOption = (selectedIndex == options.size() - 1);
        
        // 如果在编辑数值模式
        if (isEditingValue) {
            // 闪烁效果 - 每300毫秒切换一次
            if (HAL::SysCtrl().millis() - blinkTimer > 300) {
                blinkTimer = HAL::SysCtrl().millis();
                blinkState = !blinkState;
                
                // 切换闪烁状态
                if (selectedIndex < stateLabels.size() && stateLabels[selectedIndex] != nullptr) {
                    lv_obj_set_style_opa(stateLabels[selectedIndex], blinkState ? 255 : 0, 0);
                }
            }
            
            // 数值调整控制
            if (HAL::BtnUp().wasClicked()) {
                // 增加数值
                adjustValue(selectedIndex, true);
            }
            
            if (HAL::BtnDown().wasClicked()) {
                // 减少数值
                adjustValue(selectedIndex, false);
            }
            
            if (HAL::BtnOk().wasClicked()) {
                // 退出编辑模式
                isEditingValue = false;
                mclog::info("退出数值编辑模式, 新数值: %d", options[selectedIndex].value);
                
                // 确保显示
                if (selectedIndex < stateLabels.size() && stateLabels[selectedIndex] != nullptr) {
                    lv_obj_set_style_opa(stateLabels[selectedIndex], 255, 0);
                }
            }
        } 
        else {
            // 正常菜单导航模式
            // 竖向菜单的控制
            if (HAL::BtnUp().wasClicked()) {
                // 改进的摄像机移动逻辑
                int currentIndex = verticalMenu.getSelectedOptionIndex();
                int prevIndex = (currentIndex - 1 + verticalMenu.getOptionList().size()) % verticalMenu.getOptionList().size();
                
                // 检查是否从第一项到最后一项（循环向上）
                if (currentIndex == 0 && prevIndex == verticalMenu.getOptionList().size() - 1) {
                    // 获取屏幕高度
                    int screenHeight = HAL::Display().height();
                    
                    // 计算最后一项的位置
                    float lastItemY = 0 + prevIndex * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING);
                    
                    // 计算需要的摄像机偏移，使最后一项在底部可见区域内
                    float targetOffset = (lastItemY - (screenHeight - 40) > 0) ? lastItemY - (screenHeight - 40) : 0;
                    
                    // 设置摄像机位置
                    verticalMenu.getCamera().setDuration(300);
                    verticalMenu.getCamera().moveTo(0, targetOffset);
                    mclog::info("循环向上: 移动摄像机到 y=%.1f", targetOffset);
                }
                // 标准移动
                else {
                    // 检查当前项距离顶部的可见性
                    Vector2D_t cameraOffset = verticalMenu.getCameraOffset();
                    
                    // 计算上一项的位置
                    float prevItemY = 0 + prevIndex * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING);
                    float screenPrevY = prevItemY - cameraOffset.y;
                    
                    // 如果上一项会超出顶部可见区域
                    if (screenPrevY < 0) { // 顶部边界
                        // 计算新的摄像机偏移，使上一项保持在可见区域
                        float newOffset = (cameraOffset.y - (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING) > 0) ? 
                            cameraOffset.y - (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING) : 0;
                        
                        // 设置摄像机动画
                        verticalMenu.getCamera().setDuration(300);
                        verticalMenu.getCamera().moveTo(0, newOffset);
                        mclog::info("向上滚动: 调整摄像机偏移至 y=%.1f", newOffset);
                    }
                }
                
                // 移动选择器
                verticalMenu.goLast();
            }
            
            if (HAL::BtnDown().wasClicked()) {
                // 改进的摄像机移动逻辑
                int currentIndex = verticalMenu.getSelectedOptionIndex();
                int nextIndex = (currentIndex + 1) % verticalMenu.getOptionList().size();
                
                // 检查是否从最后一项到第一项（循环向下）
                if (currentIndex == verticalMenu.getOptionList().size() - 1 && nextIndex == 0) {
                    // 重置摄像机到顶部
                    verticalMenu.getCamera().setDuration(300);
                    verticalMenu.getCamera().moveTo(0, 0);
                    mclog::info("循环向下: 重置摄像机到顶部");
                }
                // 标准移动
                else {
                    // 检查下一项距离底部的可见性
                    Vector2D_t cameraOffset = verticalMenu.getCameraOffset();
                    
                    // 计算下一项的位置
                    float nextItemY = 0 + nextIndex * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING);
                    int screenHeight = HAL::Display().height();
                    float screenNextY = nextItemY - cameraOffset.y;
                    
                    // 如果下一项会超出底部可见区域
                    if (screenNextY + this->MENU_ITEM_HEIGHT > screenHeight) { // 底部边界
                        // 增加摄像机偏移，使下一项保持在可见区域
                        float additionalOffset = this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING;
                        
                        // 计算最大允许偏移量，防止超出列表总高度
                        int lastItemIndex = verticalMenu.getOptionList().size() - 1;
                        float lastItemY = 0 + lastItemIndex * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING);
                        float maxOffset = lastItemY + this->MENU_ITEM_HEIGHT - screenHeight;
                        
                        // 确保不超过最大偏移量
                        float newOffset = cameraOffset.y + additionalOffset;
                        if (newOffset > maxOffset && maxOffset > 0) {
                            newOffset = maxOffset;
                        }
                        
                        // 设置摄像机动画
                        verticalMenu.getCamera().setDuration(300);
                        verticalMenu.getCamera().moveTo(0, newOffset);
                        mclog::info("向下滚动: 增加摄像机偏移到 y=%.1f (最大:%.1f)", newOffset, maxOffset);
                    }
                }
                
                // 移动选择器
                verticalMenu.goNext();
            }
            
            if (HAL::BtnOk().wasClicked()) {
                // 根据选项类型进行不同处理
                if (isLastOption) {
                    // 返回选项
                    mclog::info("返回应用菜单");
                    switchToHorizontalMenu();
                    return; // 直接返回，不执行按下动画
                } 
                else if (options[selectedIndex].type == TYPE_TOGGLE) {
                    // 切换开关状态
                    toggleOptionState(selectedIndex);
                    mclog::info("切换开关状态为: %s", 
                               options[selectedIndex].toggleState ? "ON" : "OFF");
                    
                    // 动画效果
                    Vector4D_t pressedFrame = verticalMenu.getSelectedKeyframe();
                    pressedFrame.x += 5;
                    pressedFrame.w -= 10;
                    verticalMenu.press(pressedFrame);
                    
                    // 延迟释放
                    lv_timer_t* timer = lv_timer_create([](lv_timer_t* timer) {
                        AppMenuTest* app = static_cast<AppMenuTest*>(lv_timer_get_user_data(timer));
                        app->verticalMenu.release();
                        lv_timer_del(timer);
                    }, 200, this);
                } 
                else if (options[selectedIndex].type == TYPE_VALUE) {
                    // 进入数值编辑模式
                    isEditingValue = true;
                    blinkTimer = HAL::SysCtrl().millis();
                    blinkState = true;
                    mclog::info("进入数值编辑模式, 当前值: %d", options[selectedIndex].value);
                }
            }
        }
        
        if (HAL::BtnPower().wasClicked() && !isEditingValue) {
            // 返回横向菜单
            mclog::info("返回应用菜单");
            switchToHorizontalMenu();
            
            // 重置横向菜单的lastSelectedIndex，确保切换回横向菜单时会输出当前选中项
            static_cast<void>(lastSelectedIndex = -1);
        }
        
        // 更新竖向菜单
        verticalMenu.update(currentTime);
        
        // 获取摄像机当前偏移
        Vector2D_t cameraOffset = verticalMenu.getCameraOffset();
        
        // 定期输出摄像机状态，用于调试
        static uint32_t lastDebugTime = 0;
        if (HAL::SysCtrl().millis() - lastDebugTime > 3000) { // 每3秒输出一次
            lastDebugTime = HAL::SysCtrl().millis();
            mclog::info("摄像机状态: 偏移 (%.1f, %.1f)", cameraOffset.x, cameraOffset.y);
        }
        
        // 更新UI元素位置 - 使用简单的摄像机偏移
        for (int i = 0; i < menuItems.size(); i++) {
            if (menuItems[i] != nullptr) {
                // 跳过全屏背景
                if (i == 0) continue;
                
                // 获取原始位置，不依赖当前位置
                lv_coord_t x = lv_obj_get_x_aligned(menuItems[i]);
                
                // 计算原始Y坐标
                int itemIndex = (i - 1) / 3; // 计算对应的菜单项索引
                int elementType = (i - 1) % 3; // 计算元素类型 (0=背景, 1=标签, 2=状态)
                
                lv_coord_t baseY;
                if (elementType == 0) {
                    // placeholder
                    baseY = 0 + itemIndex * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING);
                } else if (elementType == 1 || elementType == 2) {
                    // label 或 stateLabel
                    baseY = 0 + itemIndex * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING) + 
                            (this->MENU_ITEM_HEIGHT - 10) / 2 - 2;
                } else {
                    // 默认情况，使用当前Y值加上摄像机偏移还原原始位置
                    baseY = lv_obj_get_y_aligned(menuItems[i]) + cameraOffset.y;
                }
                
                // 应用摄像机偏移
                float newY = baseY - cameraOffset.y;
                
                // 如果项目超出顶部，则隐藏它
                if (newY < -this->MENU_ITEM_HEIGHT) {
                    lv_obj_set_style_opa(menuItems[i], 0, 0); // 隐藏
                } else {
                    lv_obj_set_style_opa(menuItems[i], 255, 0); // 显示
                    lv_obj_set_y(menuItems[i], newY);
                }
            }
        }
        
        // 更新状态标签位置 - 使用计算的绝对位置而非相对位置
        for (int i = 0; i < stateLabels.size(); i++) {
            if (stateLabels[i] != nullptr) {
                // 获取X坐标 (保持不变)
                lv_coord_t x = lv_obj_get_x(stateLabels[i]);
                
                // 计算原始Y坐标
                lv_coord_t baseY = 0 + i * (this->MENU_ITEM_HEIGHT + this->MENU_ITEM_SPACING) +
                                   (this->MENU_ITEM_HEIGHT - 10) / 2 - 2;
                
                // 应用摄像机偏移
                float newY = baseY - cameraOffset.y;
                
                // 如果状态标签超出顶部，则隐藏它
                if (newY < -this->MENU_ITEM_HEIGHT) {
                    lv_obj_set_style_opa(stateLabels[i], 0, 0); // 隐藏
                    // 如果正在编辑状态且处于闪烁状态，保持一致性
                    if (isEditingValue && i == verticalMenu.getSelectedOptionIndex() && blinkState) {
                        lv_obj_set_style_opa(stateLabels[i], 0, 0);
                    }
                } else {
                    // 如果正在编辑此状态，根据闪烁状态决定是否显示
                    if (isEditingValue && i == verticalMenu.getSelectedOptionIndex()) {
                        lv_obj_set_style_opa(stateLabels[i], blinkState ? 255 : 0, 0);
                    } else {
                        lv_obj_set_style_opa(stateLabels[i], 255, 0); // 正常显示
                    }
                    lv_obj_set_y(stateLabels[i], newY);
                }
            }
        }
        
        // 更新选择器位置
        if (selector != nullptr) {
            auto selectorFrame = verticalMenu.getSelectorCurrentFrame();
            // 应用摄像机偏移
            lv_obj_set_pos(selector, selectorFrame.x, selectorFrame.y - cameraOffset.y);
            lv_obj_set_size(selector, selectorFrame.w, selectorFrame.h);
            // 确保边框样式正确
            lv_obj_set_style_border_width(selector, 2, 0);
            lv_obj_set_style_border_color(selector, lv_color_hex(0x66AAFF), 0);
        }
        
        // 安全检查：防止摄像机偏移过大导致菜单消失
        if (abs(cameraOffset.y) > HAL::Display().height() * 1.5) {
            mclog::info("摄像机偏移过大，强制重置: (%.1f, %.1f)", cameraOffset.x, cameraOffset.y);
            verticalMenu.getCamera().jumpTo(0, 0);
            return;
        }
        
        // 更新选中项的高亮状态
        int numOptions = verticalMenu.getOptionList().size();
        for (int i = 0; i < numOptions; i++) {
            // 获取背景对象和标签对象的索引 - 移除标题后索引计算需要调整
            int bgIndex = i * 3 + 1;      // 背景索引，移除标题后调整
            int labelIndex = i * 3 + 2;   // 标签索引，移除标题后调整
            
            if (bgIndex < menuItems.size() && labelIndex < menuItems.size()) {
                if (i == selectedIndex) {
                    // 选中项高亮 - 使用亮蓝色文本
                    lv_obj_set_style_text_color(menuItems[labelIndex], lv_color_hex(0x0066CC), 0);
                    // 为选中项添加淡蓝色背景
                    lv_obj_set_style_bg_opa(menuItems[bgIndex], 40, 0);
                    lv_obj_set_style_bg_color(menuItems[bgIndex], lv_color_hex(0x99CCFF), 0);
                    lv_obj_set_style_radius(menuItems[bgIndex], 4, 0);
                } else {
                    // 非选中项 - 黑色文本
                    lv_obj_set_style_text_color(menuItems[labelIndex], lv_color_hex(0x000000), 0);
                    lv_obj_set_style_bg_opa(menuItems[bgIndex], 0, 0);
                }
            }
        }
    }
    
    // 电源按钮长按退出应用
    if (HAL::BtnPower().wasDoubleClicked()) {
        mclog::info("退出应用");
        close();
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
    clearMenus();
    lv_obj_clean(lv_screen_active());
}
