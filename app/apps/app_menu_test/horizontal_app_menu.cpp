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
    
    // 确保选中框默认可见
    showSelectionFrame = true;
    
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
    
    // 设置横向循环菜单的关键帧 - 调整间距以同时只显示3个图标
    for (int i = 0; i < appIcons.size(); i++) {
        // 计算循环位置，中心为选中项
        int offset = i - 2; // 以中间位置为基准
        
        // 设置关键帧位置，所有图标在同一水平线上
        // 增大间距，确保屏幕上同时只有3个图标可见
        SmoothUIToolKit::Vector4D_t keyframe;
        keyframe.x = screenWidth/2 + offset * 45; // 增大横向间隔为45
        keyframe.y = screenHeight/2 - 12;         // 调整垂直位置
        
        // 使用统一大小的图标，不再放大选中项
        keyframe.w = 24; // 所有图标使用相同大小
        keyframe.h = 24;
        
        horizontalMenu.setKeyframe(i, keyframe);
    }
    
    // 创建或更新分割线和滑块
    createOrUpdateDivider();
}

void HorizontalAppMenu::createOrUpdateDivider() {
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    
    // 创建或更新分割线
    if (dividerLine == nullptr) {
        dividerLine = lv_obj_create(targetScreen);
        lv_obj_set_size(dividerLine, screenWidth - 20, 3); // 加粗分割线
        lv_obj_align(dividerLine, LV_ALIGN_BOTTOM_MID, 0, -16);
        lv_obj_set_style_radius(dividerLine, 0, 0);
        lv_obj_set_style_bg_color(dividerLine, lv_color_hex(0x666666), 0); // 略微亮一点的颜色
        lv_obj_set_style_border_width(dividerLine, 0, 0);
    }
    
    // 创建或更新滑块
    if (sliderIndicator == nullptr) {
        sliderIndicator = lv_obj_create(targetScreen);
        lv_obj_set_size(sliderIndicator, 12, 6); // 稍微大一点的滑块
        lv_obj_set_style_radius(sliderIndicator, 2, 0);
        lv_obj_set_style_bg_color(sliderIndicator, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(sliderIndicator, 0, 0);
    }
    
    // 创建左上角标记
    if (topLeftCorner == nullptr) {
        topLeftCorner = lv_obj_create(targetScreen);
        lv_obj_set_style_bg_color(topLeftCorner, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(topLeftCorner, 0, 0);
    }
    
    // 创建右上角标记
    if (topRightCorner == nullptr) {
        topRightCorner = lv_obj_create(targetScreen);
        lv_obj_set_style_bg_color(topRightCorner, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(topRightCorner, 0, 0);
    }
    
    // 创建左下角标记
    if (bottomLeftCorner == nullptr) {
        bottomLeftCorner = lv_obj_create(targetScreen);
        lv_obj_set_style_bg_color(bottomLeftCorner, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(bottomLeftCorner, 0, 0);
    }
    
    // 创建右下角标记
    if (bottomRightCorner == nullptr) {
        bottomRightCorner = lv_obj_create(targetScreen);
        lv_obj_set_style_bg_color(bottomRightCorner, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(bottomRightCorner, 0, 0);
    }
}

void HorizontalAppMenu::setSelectionFrameVisible(bool show) {
    showSelectionFrame = show;
    
    // 立即应用可见性变化到角标记
    if (!show) {
        // 隐藏所有角标记
        if (topLeftCorner != nullptr) lv_obj_set_style_opa(topLeftCorner, 0, 0);
        if (topRightCorner != nullptr) lv_obj_set_style_opa(topRightCorner, 0, 0);
        if (bottomLeftCorner != nullptr) lv_obj_set_style_opa(bottomLeftCorner, 0, 0);
        if (bottomRightCorner != nullptr) lv_obj_set_style_opa(bottomRightCorner, 0, 0);
        
        // 隐藏所有竖直标记
        for (auto corner : cornerVerticals) {
            if (corner != nullptr) {
                lv_obj_set_style_opa(corner, 0, 0);
            }
        }
    }
}

void HorizontalAppMenu::update(uint32_t currentTime) {
    if (appIcons.empty()) return;
    
    // 清理之前创建的临时竖直标记
    for (auto corner : cornerVerticals) {
        if (corner != nullptr) {
            lv_obj_del(corner);
        }
    }
    cornerVerticals.clear();
    
    // 更新横向菜单
    horizontalMenu.update(currentTime);
    
    // 获取屏幕中心位置
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2 - 12; // 与图标位置保持一致
    
    // 更新UI元素位置和大小
    int selectedIndex = horizontalMenu.getSelectedOptionIndex();
    
    for (int i = 0; i < appIcons.size() && i < horizontalMenu.getOptionList().size(); i++) {
        // 获取当前选项的位置和形状
        auto& option = horizontalMenu.getOption(i);
        auto pos = option.position.getValue();
        auto shape = option.shape.getValue();
        
        // 设置图标位置和大小
        lv_obj_set_pos(appIcons[i], pos.x - shape.width/2, pos.y - shape.height/2);
        lv_obj_set_size(appIcons[i], shape.width, shape.height);
        
        // 设置所有图标为不透明
        lv_obj_set_style_opa(appIcons[i], 255, 0);
        
        // 只为中心项添加特殊效果
        if (i == selectedIndex) {
            // 突出显示选中项 - 使用白色边框
            lv_obj_set_style_border_width(appIcons[i], 1, 0);
            lv_obj_set_style_border_color(appIcons[i], lv_color_hex(0xFFFFFF), 0);
        } else {
            // 设置非选中项的普通效果
            lv_obj_set_style_border_width(appIcons[i], 0, 0);
        }
    }
    
    // 如果选中框不应显示，则直接返回
    if (!showSelectionFrame) {
        return;
    }
    
    // 选中框的尺寸和位置 - 直接在屏幕中心位置创建选中框
    // 基于屏幕中心位置创建
    int iconSize = 24; // 图标统一大小
    int margin = 8;   // 选中框与图标的间距
    int lineLength = 12; // 角标记的线长度
    int lineWidth = 3;  // 角标记的线宽度
    
    // 计算选中框位置和大小
    int leftX = centerX - iconSize/2 - margin;
    int rightX = centerX + iconSize/2 + margin;
    int topY = centerY - iconSize/2 - margin;
    int bottomY = centerY + iconSize/2 + margin;
    
    // 绘制左上角标记
    lv_obj_set_pos(topLeftCorner, leftX, topY);
    lv_obj_set_size(topLeftCorner, lineLength, lineWidth);
    lv_obj_set_style_opa(topLeftCorner, 255, 0);
    
    // 左上L形竖线
    lv_obj_t* topLeftVertical = lv_obj_create(targetScreen);
    lv_obj_set_pos(topLeftVertical, leftX, topY);
    lv_obj_set_size(topLeftVertical, lineWidth, lineLength);
    lv_obj_set_style_bg_color(topLeftVertical, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(topLeftVertical, 0, 0);
    
    // 右上角标记
    lv_obj_set_pos(topRightCorner, rightX - lineLength, topY);
    lv_obj_set_size(topRightCorner, lineLength, lineWidth);
    lv_obj_set_style_opa(topRightCorner, 255, 0);
    
    // 右上L形竖线
    lv_obj_t* topRightVertical = lv_obj_create(targetScreen);
    lv_obj_set_pos(topRightVertical, rightX - lineWidth, topY);
    lv_obj_set_size(topRightVertical, lineWidth, lineLength);
    lv_obj_set_style_bg_color(topRightVertical, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(topRightVertical, 0, 0);
    
    // 左下角标记
    lv_obj_set_pos(bottomLeftCorner, leftX, bottomY - lineWidth);
    lv_obj_set_size(bottomLeftCorner, lineLength, lineWidth);
    lv_obj_set_style_opa(bottomLeftCorner, 255, 0);
    
    // 左下L形竖线
    lv_obj_t* bottomLeftVertical = lv_obj_create(targetScreen);
    lv_obj_set_pos(bottomLeftVertical, leftX, bottomY - lineLength);
    lv_obj_set_size(bottomLeftVertical, lineWidth, lineLength);
    lv_obj_set_style_bg_color(bottomLeftVertical, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(bottomLeftVertical, 0, 0);
    
    // 右下角标记
    lv_obj_set_pos(bottomRightCorner, rightX - lineLength, bottomY - lineWidth);
    lv_obj_set_size(bottomRightCorner, lineLength, lineWidth);
    lv_obj_set_style_opa(bottomRightCorner, 255, 0);
    
    // 右下L形竖线
    lv_obj_t* bottomRightVertical = lv_obj_create(targetScreen);
    lv_obj_set_pos(bottomRightVertical, rightX - lineWidth, bottomY - lineLength);
    lv_obj_set_size(bottomRightVertical, lineWidth, lineLength);
    lv_obj_set_style_bg_color(bottomRightVertical, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(bottomRightVertical, 0, 0);
    
    // 将所有竖直标记保存到向量中，以便后续清理
    cornerVerticals.push_back(topLeftVertical);
    cornerVerticals.push_back(topRightVertical);
    cornerVerticals.push_back(bottomLeftVertical);
    cornerVerticals.push_back(bottomRightVertical);
    
    // 确保角标记在最前面显示
    lv_obj_move_foreground(topLeftCorner);
    lv_obj_move_foreground(topRightCorner);
    lv_obj_move_foreground(bottomLeftCorner);
    lv_obj_move_foreground(bottomRightCorner);
    for (auto vertical : cornerVerticals) {
        lv_obj_move_foreground(vertical);
    }
    
    // 更新滑块位置
    if (sliderIndicator != nullptr && dividerLine != nullptr) {
        // 计算滑块位置
        float progress = (float)selectedIndex / (appIcons.size() - 1);
        int dividerWidth = lv_obj_get_width(dividerLine);
        int sliderWidth = lv_obj_get_width(sliderIndicator);
        
        // 计算滑块的x坐标，确保不会超出分割线范围
        int maxX = dividerWidth - sliderWidth;
        int sliderX = (int)(progress * maxX);
        
        // 获取分割线位置
        lv_coord_t dividerX = lv_obj_get_x(dividerLine);
        lv_coord_t dividerY = lv_obj_get_y(dividerLine);
        
        // 设置滑块位置 - 在分割线上居中
        lv_obj_set_pos(sliderIndicator, dividerX + sliderX, dividerY - 1);
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
    
    // 清理分割线和滑块
    if (dividerLine != nullptr) {
        lv_obj_del(dividerLine);
        dividerLine = nullptr;
    }
    
    if (sliderIndicator != nullptr) {
        lv_obj_del(sliderIndicator);
        sliderIndicator = nullptr;
    }
    
    // 清理角标记
    if (topLeftCorner != nullptr) {
        lv_obj_del(topLeftCorner);
        topLeftCorner = nullptr;
    }
    
    if (topRightCorner != nullptr) {
        lv_obj_del(topRightCorner);
        topRightCorner = nullptr;
    }
    
    if (bottomLeftCorner != nullptr) {
        lv_obj_del(bottomLeftCorner);
        bottomLeftCorner = nullptr;
    }
    
    if (bottomRightCorner != nullptr) {
        lv_obj_del(bottomRightCorner);
        bottomRightCorner = nullptr;
    }
    
    // 清理竖直角标记
    for (auto corner : cornerVerticals) {
        if (corner != nullptr) {
            lv_obj_del(corner);
        }
    }
    cornerVerticals.clear();
    
    // 重置菜单对象
    horizontalMenu = SmoothUIToolKit::SelectMenu::SmoothOptions();
    
    // 重置目标屏幕
    targetScreen = nullptr;
    
    // 重置选中框显示状态为可见
    showSelectionFrame = true;
    
    // 重置callback
    onSelectCallback = nullptr;
}

lv_obj_t* HorizontalAppMenu::getAppIcon(int index) const {
    if (index >= 0 && index < appIcons.size()) {
        return appIcons[index];
    }
    return nullptr;
}

size_t HorizontalAppMenu::getAppIconCount() const {
    return appIcons.size();
}

} // namespace MenuModules 