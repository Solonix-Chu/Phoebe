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
#include "app_menu_test.h"
#include <mooncake_log.h>
#include <hal/hal.h>
#include <lvgl.h>
#include <mooncake.h>
#include <src/misc/lv_timer.h>

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
    
    // 初始化横向菜单
    initHorizontalMenu();

    // 打开自己
    open();
}

void AppMenuTest::onOpen()
{
    mclog::tagInfo(_tag, "on open");
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
    
    if (selector != nullptr) {
        lv_obj_del(selector);
        selector = nullptr;
    }
}

void AppMenuTest::initHorizontalMenu() 
{
    // 清理之前的菜单资源
    clearMenus();
    
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
    
    // 不再创建选中框
    
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

void AppMenuTest::initVerticalMenu() 
{
    // 清理之前的菜单资源
    clearMenus();
    
    // 创建设置菜单选项
    const int NUM_SETTINGS = 6;
    const char* SETTING_NAMES[NUM_SETTINGS] = {
        "WiFi", "Bluetooth", "Display", 
        "Sound", "Battery", "About"
    };
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    
    // 创建选择器UI元素
    selector = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_color(selector, lv_color_hex(0x3399FF), 0);
    lv_obj_set_style_radius(selector, 10, 0);
    lv_obj_set_style_opa(selector, 150, 0);
    
    // 设置菜单配置
    verticalMenu.setConfig({
        .moveInLoop = true,              // 循环移动
        .cameraSize = {screenWidth, screenHeight},  // 相机尺寸
        .readInputInterval = 20,
        .renderInterval = 15
    });
    
    // 创建一个容器作为背景
    lv_obj_t* menuBg = lv_obj_create(lv_screen_active());
    lv_obj_set_size(menuBg, screenWidth - 40, screenHeight - 80);
    lv_obj_set_pos(menuBg, 20, 40);
    lv_obj_set_style_bg_color(menuBg, lv_color_hex(0x222222), 0);
    lv_obj_set_style_radius(menuBg, 15, 0);
    lv_obj_set_style_border_width(menuBg, 2, 0);
    lv_obj_set_style_border_color(menuBg, lv_color_hex(0x666666), 0);
    
    // 添加标题
    lv_obj_t* title = lv_label_create(lv_screen_active());
    lv_label_set_text(title, "设置菜单");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
    menuItems.push_back(title);
    
    // 添加菜单选项
    const int ITEM_HEIGHT = 50;
    const int SPACING = 10;
    for (int i = 0; i < NUM_SETTINGS; i++) {
        // 创建图标 (简单的形状)
        lv_obj_t* icon = lv_obj_create(lv_screen_active());
        lv_obj_set_size(icon, 30, 30);
        lv_obj_set_style_radius(icon, i % 3 == 0 ? 0 : (i % 3 == 1 ? 5 : LV_RADIUS_CIRCLE), 0); // 方形/圆角/圆形
        lv_obj_set_style_bg_color(icon, lv_color_hex(0x3399FF), 0);
        lv_obj_set_pos(icon, 30, 50 + i * (ITEM_HEIGHT + SPACING));
        
        // 创建文本标签
        lv_obj_t* label = lv_label_create(lv_screen_active());
        lv_label_set_text(label, SETTING_NAMES[i]);
        lv_obj_set_style_text_color(label, lv_color_hex(0xCCCCCC), 0);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
        lv_obj_set_pos(label, 70, 55 + i * (ITEM_HEIGHT + SPACING));
        
        menuItems.push_back(icon);
        menuItems.push_back(label);
        
        // 添加选项到菜单
        SmoothSelector::OptionProps_t option;
        option.keyframe = {
            30,                          // x位置
            50 + i * (ITEM_HEIGHT + SPACING),  // y位置 
            screenWidth - 60,            // 宽度
            ITEM_HEIGHT                  // 高度
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
    mclog::tagInfo(_tag, "竖向菜单已初始化");
}

void AppMenuTest::switchToVerticalMenu() {
    if (currentState == HORIZONTAL_MENU) {
        initVerticalMenu();
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
            switchToVerticalMenu();
        }
        
        // 更新横向菜单 - 确保动画更新
        horizontalMenu.update(currentTime);
        
        // 强制更新LVGL UI，确保动画显示
        lv_timer_handler();
        
        // 更新UI元素位置和大小
        for (int i = 0; i < appIcons.size() && i < horizontalMenu.getOptionList().size(); i++) {
            int matchingIndex = horizontalMenu.getMatchingOptionIndex(i);
            if (matchingIndex >= 0 && matchingIndex < appIcons.size()) {
                auto pos = horizontalMenu.getOption(matchingIndex).position.getValue();
                auto shape = horizontalMenu.getOption(matchingIndex).shape.getValue();
                
                // 更新图标位置和大小
                lv_obj_set_pos(appIcons[matchingIndex], pos.x - shape.width/2, pos.y - shape.height/2);
                lv_obj_set_size(appIcons[matchingIndex], shape.width, shape.height);
                
                // 设置所有图标为不透明
                lv_obj_set_style_opa(appIcons[matchingIndex], 255, 0);
                
                // 只为中心项添加特殊效果
                int center = 2;
                int distance = abs(i - center);
                if (distance == 0) {
                    // 选中项加强效果 - 更粗的边框
                    lv_obj_set_style_border_width(appIcons[matchingIndex], 4, 0);
                    lv_obj_set_style_border_color(appIcons[matchingIndex], lv_color_hex(0xFFFFFF), 0);
                } else {
                    // 设置非选中项的普通效果
                    lv_obj_set_style_border_width(appIcons[matchingIndex], 1, 0);
                    lv_obj_set_style_border_color(appIcons[matchingIndex], lv_color_hex(0xAAAAAA), 0);
                }
            }
        }
    } 
    else if (currentState == VERTICAL_MENU) {
        // 获取当前选中的索引
        int selectedIndex = verticalMenu.getSelectedOptionIndex();
        static int lastSelectedIndex = -1;  // 用于跟踪选择变化
        
        // 只在选中项改变时输出日志
        if (selectedIndex != lastSelectedIndex) {
            mclog::info("当前选中设置项索引: %d", selectedIndex);
            lastSelectedIndex = selectedIndex;
        }
        
        // 竖向菜单的控制
        if (HAL::BtnUp().wasClicked()) {
            verticalMenu.goLast();
        }
        
        if (HAL::BtnDown().wasClicked()) {
            verticalMenu.goNext();
        }
        
        if (HAL::BtnOk().wasClicked()) {
            // 选择当前设置项
            mclog::info("选中设置项: %d", selectedIndex);
            
            // 动画效果：选择时压缩选择器
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
        
        if (HAL::BtnPower().wasClicked()) {
            // 返回横向菜单
            mclog::info("返回应用菜单");
            switchToHorizontalMenu();
            
            // 重置横向菜单的lastSelectedIndex，确保切换回横向菜单时会输出当前选中项
            static_cast<void>(lastSelectedIndex = -1);
        }
        
        // 更新竖向菜单
        verticalMenu.update(currentTime);
        
        // 更新选择器位置
        if (selector != nullptr) {
            auto selectorFrame = verticalMenu.getSelectorCurrentFrame();
            lv_obj_set_pos(selector, selectorFrame.x, selectorFrame.y);
            lv_obj_set_size(selector, selectorFrame.w, selectorFrame.h);
        }
        
        // 更新选中项的颜色
        for (int i = 0; i < menuItems.size() / 2 - 1; i++) { // 第一项是标题，不包括在选项中
            int labelIndex = i * 2 + 3; // 每个选项有两个UI元素：图标和标签
            if (labelIndex < menuItems.size()) {
                lv_obj_set_style_text_color(menuItems[labelIndex], 
                    (i == selectedIndex) ? lv_color_hex(0xFFFFFF) : lv_color_hex(0xCCCCCC), 0);
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
