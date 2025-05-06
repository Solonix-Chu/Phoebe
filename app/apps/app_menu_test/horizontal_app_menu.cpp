/**
 * @file horizontal_app_menu.cpp
 * @brief 横向应用菜单模块实现
 */
#include "horizontal_app_menu.h"
#include <hal/hal.h>
#include <lvgl.h>

namespace MenuModules {

void HorizontalAppMenu::init(lv_obj_t* screen) {
    // 清理之前的菜单资源
    clear();
    
    // 保存目标屏幕
    targetScreen = screen;
    
    // 设置黑色背景 - OLED显示屏默认背景为黑色
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), LV_PART_MAIN);
    
    // 重新初始化横向菜单对象
    horizontalMenu = SmoothUIToolKit::SelectMenu::SmoothOptions();
}

int HorizontalAppMenu::addApp(const char* name, lv_color_t color, bool isCircle) {
    if (targetScreen == nullptr) return -1;
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    
    // 添加选项到菜单
    horizontalMenu.addOption();
    int appIndex = appIcons.size();
    
    // 创建图标 - 使用矩形或圆形作为图标
    lv_obj_t* icon = lv_obj_create(targetScreen);
    lv_obj_set_style_bg_color(icon, color, 0);
    lv_obj_set_style_radius(icon, isCircle ? LV_RADIUS_CIRCLE : 0, 0);
    lv_obj_set_style_border_width(icon, 1, 0);  // 减小边框厚度以适应小屏幕
    lv_obj_set_style_border_color(icon, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_shadow_width(icon, 0, 0);  // 移除阴影
    
    // 添加标签 - 使用更小的字体
    lv_obj_t* label = lv_label_create(icon);
    lv_label_set_text(label, name);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
    // 设置更小的字体
    lv_obj_set_style_text_font(label, &lv_font_montserrat_10, 0);
    lv_obj_center(label);
    
    // 初始隐藏图标
    lv_obj_set_style_opa(icon, 0, 0);
    
    // 保存图标
    appIcons.push_back(icon);
    
    // 设置关键帧
    updateKeyframes();
    
    // 设置菜单动画效果 - 减少动画持续时间以适应较小的屏幕
    horizontalMenu.setPositionDuration(400);
    horizontalMenu.setShapeDuration(600);
    horizontalMenu.setPositionTransitionPath(SmoothUIToolKit::EasingPath::easeOutElastic);
    horizontalMenu.setShapeTransitionPath(SmoothUIToolKit::EasingPath::easeOutBack);
    horizontalMenu.setDuration(400);
    
    return appIndex;
}

void HorizontalAppMenu::updateKeyframes() {
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    
    // 设置横向循环菜单的关键帧 - 为小屏幕调整大小和位置
    for (int i = 0; i < appIcons.size(); i++) {
        // 计算循环位置，中心为选中项
        int offset = i - 2; // 以中间位置为基准
        
        // 设置关键帧位置，所有图标在同一水平线上
        SmoothUIToolKit::Vector4D_t keyframe;
        keyframe.x = screenWidth/2 + offset * 32; // 减小横向间隔为32，适应128px宽度
        keyframe.y = screenHeight/2 - 12;         // 上移更多，为底部的应用名称留出空间
        
        // 更平衡的尺寸对比：适应较小的屏幕
        if (offset == 0) {
            keyframe.w = 30; // 选中项大小
            keyframe.h = 30;
        } else {
            keyframe.w = 20; // 非选中项大小
            keyframe.h = 20;
        }
        
        horizontalMenu.setKeyframe(i, keyframe);
    }
}

void HorizontalAppMenu::update(uint32_t currentTime) {
    if (appIcons.empty()) return;
    
    // 更新横向菜单
    horizontalMenu.update(currentTime);
    
    // 更新UI元素位置和大小
    int selectedIndex = horizontalMenu.getSelectedOptionIndex();
    
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

void HorizontalAppMenu::goNext() {
    // 确保每次移动都重新设置动画参数
    horizontalMenu.setPositionDuration(400);
    horizontalMenu.setShapeDuration(600);
    horizontalMenu.setPositionTransitionPath(SmoothUIToolKit::EasingPath::easeOutElastic);
    
    // 调用移动方法
    horizontalMenu.goNext();
}

void HorizontalAppMenu::goLast() {
    // 确保每次移动都重新设置动画参数
    horizontalMenu.setPositionDuration(400);
    horizontalMenu.setShapeDuration(600);
    horizontalMenu.setPositionTransitionPath(SmoothUIToolKit::EasingPath::easeOutElastic);
    
    // 调用移动方法
    horizontalMenu.goLast();
}

int HorizontalAppMenu::getSelectedIndex() const {
    try {
        if (appIcons.empty()) {
            return -1; // 返回无效索引，表示没有应用
        }
        return horizontalMenu.getSelectedOptionIndex();
    } catch (const std::exception& e) {
        // 捕获可能的异常，返回安全的默认值
        return 0;
    }
}

void HorizontalAppMenu::setSelectCallback(std::function<void(int)> callback) {
    onSelectCallback = callback;
}

void HorizontalAppMenu::clear() {
    // 清理图标资源
    for (auto icon : appIcons) {
        if (icon != nullptr) {
            lv_obj_del(icon);
        }
    }
    appIcons.clear();
    
    // 重置菜单对象
    horizontalMenu = SmoothUIToolKit::SelectMenu::SmoothOptions();
    
    // 重置目标屏幕
    targetScreen = nullptr;
    
    // 重置callback
    onSelectCallback = nullptr;
}

} // namespace MenuModules 