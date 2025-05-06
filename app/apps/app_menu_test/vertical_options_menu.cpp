/**
 * @file vertical_options_menu.cpp
 * @brief 竖向选项列表模块实现
 */
#include "vertical_options_menu.h"
#include <hal/hal.h>
#include <mooncake_log.h>

namespace MenuModules {

// Define tag for logging
const char* VerticalOptionsMenu::_tag = "VerticalOptionsMenu";

void VerticalOptionsMenu::init(lv_obj_t* screen) {
    // 清理之前的菜单资源
    clear();
    
    // 保存目标屏幕
    targetScreen = screen;
    if (targetScreen == nullptr) {
        mclog::tagError(_tag, "初始化时，传入的屏幕对象为空");
        return;
    }
    
    // 重新初始化垂直菜单对象
    verticalMenu = SmoothUIToolKit::SelectMenu::SmoothSelector();
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    int screenHeight = HAL::Display().height();
    
    // 创建选择器UI元素
    selector = lv_obj_create(targetScreen);
    if (selector == nullptr) {
        mclog::tagError(_tag, "创建选择器失败");
        return;
    }
    
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
    verticalMenu.getCamera().setTransitionPath(SmoothUIToolKit::EasingPath::easeOutQuad);
    
    // 初始化摄像机位置为零
    verticalMenu.getCamera().jumpTo(0, 0);
    
    // 设置选择器样式和动画
    verticalMenu.setPositionDuration(300);
    verticalMenu.setShapeDuration(300);
    verticalMenu.setPositionTransitionPath(SmoothUIToolKit::EasingPath::easeOutQuad);
    verticalMenu.setShapeTransitionPath(SmoothUIToolKit::EasingPath::easeOutQuad);
}

int VerticalOptionsMenu::addOption(const MenuOption& option) {
    if (targetScreen == nullptr) {
        mclog::tagError(_tag, "添加选项时，目标屏幕为空");
        return -1;
    }
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    
    // 添加选项到内部列表
    options.push_back(option);
    int optionIndex = options.size() - 1;
    
    // 计算项目Y坐标
    int itemY = 0 + optionIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
    
    try {
        // 创建背景占位符
        lv_obj_t* placeholder = lv_obj_create(targetScreen);
        if (placeholder == nullptr) {
            mclog::tagError(_tag, "创建背景失败");
            options.pop_back(); // 回滚
            return -1;
        }
        
        lv_obj_set_size(placeholder, screenWidth, MENU_ITEM_HEIGHT);
        lv_obj_set_style_bg_opa(placeholder, 0, 0);  // 完全透明
        lv_obj_set_style_border_width(placeholder, 0, 0);
        lv_obj_set_pos(placeholder, 0, itemY);
        menuItems.push_back(placeholder);
        
        // 创建选项标签 - 左对齐
        lv_obj_t* label = lv_label_create(targetScreen);
        if (label == nullptr) {
            mclog::tagError(_tag, "创建标签失败");
            options.pop_back(); // 回滚
            return -1;
        }
        
        // 设置标签文本
        lv_label_set_text(label, option.name.c_str());
        // 设置文本颜色
        lv_obj_set_style_text_color(label, lv_color_hex(0x000000), 0);
        // 恢复使用原来的字体
        lv_obj_set_style_text_font(label, &lv_font_montserrat_10, 0);
        
        // 设置标签位置
        lv_obj_set_pos(label, 5, itemY + (MENU_ITEM_HEIGHT - 10) / 2 - 2);
        menuItems.push_back(label);
        
        // 为非Back选项添加状态标签 (ON/OFF 或 数值)
        if (option.type != TYPE_ACTION) {
            lv_obj_t* stateLabel = lv_label_create(targetScreen);
            if (stateLabel == nullptr) {
                mclog::tagError(_tag, "创建状态标签失败");
                options.pop_back(); // 回滚
                return -1;
            }
            
            lv_label_set_text(stateLabel, getOptionStateText(option).c_str());
            lv_obj_set_style_text_color(stateLabel, lv_color_hex(0x000000), 0);
            // 恢复使用原来的字体
            lv_obj_set_style_text_font(stateLabel, &lv_font_montserrat_10, 0);
            
            // 设置文本右对齐
            lv_obj_set_style_text_align(stateLabel, LV_TEXT_ALIGN_RIGHT, 0);
            int valueWidth = 40;
            lv_obj_set_width(stateLabel, valueWidth);
            
            int rightMargin = 10;
            int xPosition = screenWidth - rightMargin - valueWidth;
            
            lv_obj_set_pos(stateLabel, xPosition, itemY + (MENU_ITEM_HEIGHT - 10) / 2 - 2);
            
            menuItems.push_back(stateLabel);
            stateLabels.push_back(stateLabel);
        } else {
            // 为保持索引对应，添加一个空的占位符
            stateLabels.push_back(nullptr);
        }
        
        // 添加选项到菜单
        SmoothUIToolKit::SelectMenu::SmoothSelector::OptionProps_t optionProps;
        optionProps.keyframe = {
            0, // 从左侧开始
            itemY,
            screenWidth,
            MENU_ITEM_HEIGHT
        };
        verticalMenu.addOption(optionProps);
        
        return optionIndex;
    } catch (const std::exception& e) {
        mclog::tagError(_tag, "添加选项时异常：%s", e.what());
        // 回滚操作
        if (!options.empty()) {
            options.pop_back();
        }
        return -1;
    } catch (...) {
        mclog::tagError(_tag, "添加选项时发生未知异常");
        // 回滚操作
        if (!options.empty()) {
            options.pop_back();
        }
        return -1;
    }
}

void VerticalOptionsMenu::setOptions(const std::vector<MenuOption>& newOptions) {
    // 安全检查
    if (newOptions.empty()) {
        mclog::tagError(_tag, "设置选项时，选项列表为空");
        return;
    }
    
    // 确保目标屏幕有效
    if (targetScreen == nullptr) {
        mclog::tagError(_tag, "设置选项时，目标屏幕为空");
        return;
    }
    
    // 清理现有选项，不要丢失屏幕引用
    // 不直接调用 clear()，而是手动清理资源
    for (auto item : menuItems) {
        if (item != nullptr) {
            lv_obj_del(item);
        }
    }
    menuItems.clear();
    stateLabels.clear();
    
    if (selector != nullptr) {
        lv_obj_del(selector);
        selector = nullptr;
    }
    
    options.clear();
    
    // 重置菜单对象
    verticalMenu = SmoothUIToolKit::SelectMenu::SmoothSelector();
    
    // 重置编辑状态
    isEditingValue = false;
    editingIndex = -1;
    blinkTimer = 0;
    blinkState = true;
    
    // 重置回调
    onSelectCallback = nullptr;
    
    try {
        // 创建新的选择器
        selector = lv_obj_create(targetScreen);
        if (selector == nullptr) {
            mclog::tagError(_tag, "创建选择器失败");
            return;
        }
        
        lv_obj_set_style_bg_color(selector, lv_color_hex(0x3399FF), 0);
        lv_obj_set_style_bg_opa(selector, 80, 0);
        lv_obj_set_style_border_width(selector, 2, 0);
        lv_obj_set_style_border_color(selector, lv_color_hex(0x66AAFF), 0);
        lv_obj_set_style_radius(selector, 6, 0);
        
        // 获取屏幕尺寸
        int screenWidth = HAL::Display().width();
        int screenHeight = HAL::Display().height();
        
        // 设置菜单配置
        verticalMenu.setConfig({
            .moveInLoop = true,
            .cameraSize = {screenWidth, screenHeight},
            .readInputInterval = 20,
            .renderInterval = 15
        });
        
        // 设置摄像机和选择器动画
        verticalMenu.getCamera().setDuration(300);
        verticalMenu.getCamera().setTransitionPath(SmoothUIToolKit::EasingPath::easeOutQuad);
        verticalMenu.getCamera().jumpTo(0, 0);
        verticalMenu.setPositionDuration(300);
        verticalMenu.setShapeDuration(300);
        verticalMenu.setPositionTransitionPath(SmoothUIToolKit::EasingPath::easeOutQuad);
        verticalMenu.setShapeTransitionPath(SmoothUIToolKit::EasingPath::easeOutQuad);
        
        // 批量添加新选项
        for (size_t i = 0; i < newOptions.size(); i++) {
            addOption(newOptions[i]);
        }
        
        // 确保有选项被添加
        if (options.empty()) {
            mclog::tagError(_tag, "添加后选项列表为空");
            return;
        }
        
        // 初始化动画，选中第一项
        verticalMenu.jumpTo(0);
    } catch (const std::exception& e) {
        mclog::tagError(_tag, "设置选项时异常：%s", e.what());
    } catch (...) {
        mclog::tagError(_tag, "设置选项时发生未知异常");
    }
}

void VerticalOptionsMenu::update(uint32_t currentTime) {
    if (targetScreen == nullptr || options.empty()) return;
    
    // 更新垂直菜单
    verticalMenu.update(currentTime);
    
    // 获取摄像机当前偏移
    SmoothUIToolKit::Vector2D_t cameraOffset = verticalMenu.getCameraOffset();
    
    // 处理编辑状态闪烁效果
    if (isEditingValue && editingIndex >= 0 && editingIndex < stateLabels.size()) {
        if (HAL::SysCtrl().millis() - blinkTimer > 300) {
            blinkTimer = HAL::SysCtrl().millis();
            blinkState = !blinkState;
            
            // 切换闪烁状态
            if (stateLabels[editingIndex] != nullptr) {
                lv_obj_set_style_opa(stateLabels[editingIndex], blinkState ? 255 : 0, 0);
            }
        }
    }
    
    // 更新UI元素位置 - 使用简单的摄像机偏移
    for (int i = 0; i < menuItems.size(); i++) {
        if (menuItems[i] != nullptr) {
            // 获取原始位置，不依赖当前位置
            lv_coord_t x = lv_obj_get_x_aligned(menuItems[i]);
            
            // 计算原始Y坐标
            int itemIndex = i / 3; // 计算对应的菜单项索引
            int elementType = i % 3; // 计算元素类型 (0=背景, 1=标签, 2=状态)
            
            lv_coord_t baseY;
            if (elementType == 0) {
                // placeholder
                baseY = 0 + itemIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
            } else if (elementType == 1 || elementType == 2) {
                // label 或 stateLabel
                baseY = 0 + itemIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING) + 
                        (MENU_ITEM_HEIGHT - 10) / 2 - 2;
            } else {
                // 默认情况，使用当前Y值加上摄像机偏移还原原始位置
                baseY = lv_obj_get_y_aligned(menuItems[i]) + cameraOffset.y;
            }
            
            // 应用摄像机偏移
            float newY = baseY - cameraOffset.y;
            
            // 如果项目超出顶部，则隐藏它
            if (newY < -MENU_ITEM_HEIGHT) {
                lv_obj_set_style_opa(menuItems[i], 0, 0); // 隐藏
            } else {
                lv_obj_set_style_opa(menuItems[i], 255, 0); // 显示
                lv_obj_set_y(menuItems[i], newY);
            }
        }
    }
    
    // 更新状态标签位置和可见性
    for (int i = 0; i < stateLabels.size(); i++) {
        if (stateLabels[i] != nullptr) {
            // 获取X坐标 (保持不变)
            lv_coord_t x = lv_obj_get_x(stateLabels[i]);
            
            // 计算原始Y坐标
            lv_coord_t baseY = 0 + i * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING) +
                               (MENU_ITEM_HEIGHT - 10) / 2 - 2;
            
            // 应用摄像机偏移
            float newY = baseY - cameraOffset.y;
            
            // 如果状态标签超出顶部，则隐藏它
            if (newY < -MENU_ITEM_HEIGHT) {
                lv_obj_set_style_opa(stateLabels[i], 0, 0); // 隐藏
            } else {
                // 如果正在编辑此状态，根据闪烁状态决定是否显示
                if (isEditingValue && i == editingIndex) {
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
    }
    
    // 更新选中项的高亮状态
    int selectedIndex = verticalMenu.getSelectedOptionIndex();
    for (int i = 0; i < options.size(); i++) {
        // 获取背景对象和标签对象的索引
        int bgIndex = i * 3;      // 背景索引
        int labelIndex = i * 3 + 1; // 标签索引
        
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

void VerticalOptionsMenu::goNext() {
    // 获取当前选中索引和下一个索引
    int currentIndex = verticalMenu.getSelectedOptionIndex();
    int nextIndex = (currentIndex + 1) % verticalMenu.getOptionList().size();
    
    // 检查是否从最后一项到第一项（循环向下）
    if (currentIndex == verticalMenu.getOptionList().size() - 1 && nextIndex == 0) {
        // 重置摄像机到顶部
        verticalMenu.getCamera().setDuration(300);
        verticalMenu.getCamera().moveTo(0, 0);
    }
    // 标准移动
    else {
        // 检查下一项距离底部的可见性
        SmoothUIToolKit::Vector2D_t cameraOffset = verticalMenu.getCameraOffset();
        
        // 计算下一项的位置
        float nextItemY = 0 + nextIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
        int screenHeight = HAL::Display().height();
        float screenNextY = nextItemY - cameraOffset.y;
        
        // 如果下一项会超出底部可见区域
        if (screenNextY + MENU_ITEM_HEIGHT > screenHeight) {
            // 增加摄像机偏移，使下一项保持在可见区域
            float additionalOffset = MENU_ITEM_HEIGHT + MENU_ITEM_SPACING;
            
            // 计算最大允许偏移量，防止超出列表总高度
            int lastItemIndex = verticalMenu.getOptionList().size() - 1;
            float lastItemY = 0 + lastItemIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
            float maxOffset = lastItemY + MENU_ITEM_HEIGHT - screenHeight;
            
            // 确保不超过最大偏移量
            float newOffset = cameraOffset.y + additionalOffset;
            if (newOffset > maxOffset && maxOffset > 0) {
                newOffset = maxOffset;
            }
            
            // 设置摄像机动画
            verticalMenu.getCamera().setDuration(300);
            verticalMenu.getCamera().moveTo(0, newOffset);
        }
    }
    
    // 移动选择器
    verticalMenu.goNext();
    
    // 如果有回调，触发回调
    if (onSelectCallback) {
        int newIndex = verticalMenu.getSelectedOptionIndex();
        if (newIndex >= 0 && newIndex < options.size()) {
            onSelectCallback(newIndex, options[newIndex].type);
        }
    }
}

void VerticalOptionsMenu::goLast() {
    // 获取当前选中索引和上一个索引
    int currentIndex = verticalMenu.getSelectedOptionIndex();
    int prevIndex = (currentIndex - 1 + verticalMenu.getOptionList().size()) % verticalMenu.getOptionList().size();
    
    // 检查是否从第一项到最后一项（循环向上）
    if (currentIndex == 0 && prevIndex == verticalMenu.getOptionList().size() - 1) {
        // 获取屏幕高度
        int screenHeight = HAL::Display().height();
        
        // 计算最后一项的位置
        float lastItemY = 0 + prevIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
        
        // 计算需要的摄像机偏移，使最后一项在底部可见区域内
        float targetOffset = (lastItemY - (screenHeight - 40) > 0) ? lastItemY - (screenHeight - 40) : 0;
        
        // 设置摄像机位置
        verticalMenu.getCamera().setDuration(300);
        verticalMenu.getCamera().moveTo(0, targetOffset);
    }
    // 标准移动
    else {
        // 检查当前项距离顶部的可见性
        SmoothUIToolKit::Vector2D_t cameraOffset = verticalMenu.getCameraOffset();
        
        // 计算上一项的位置
        float prevItemY = 0 + prevIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
        float screenPrevY = prevItemY - cameraOffset.y;
        
        // 如果上一项会超出顶部可见区域
        if (screenPrevY < 0) {
            // 计算新的摄像机偏移，使上一项保持在可见区域
            float newOffset = (cameraOffset.y - (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING) > 0) ? 
                cameraOffset.y - (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING) : 0;
            
            // 设置摄像机动画
            verticalMenu.getCamera().setDuration(300);
            verticalMenu.getCamera().moveTo(0, newOffset);
        }
    }
    
    // 移动选择器
    verticalMenu.goLast();
    
    // 如果有回调，触发回调
    if (onSelectCallback) {
        int newIndex = verticalMenu.getSelectedOptionIndex();
        if (newIndex >= 0 && newIndex < options.size()) {
            onSelectCallback(newIndex, options[newIndex].type);
        }
    }
}

int VerticalOptionsMenu::getSelectedIndex() const {
    try {
        if (options.empty()) {
            return -1; // 返回无效索引，表示没有选项
        }
        return verticalMenu.getSelectedOptionIndex();
    } catch (const std::exception& e) {
        // 捕获可能的异常，返回安全的默认值
        return 0;
    }
}

MenuOption& VerticalOptionsMenu::getOption(int index) {
    if (index >= 0 && index < options.size()) {
        return options[index];
    }
    static MenuOption emptyOption;
    return emptyOption;
}

const std::vector<MenuOption>& VerticalOptionsMenu::getOptions() const {
    return options;
}

bool VerticalOptionsMenu::toggleOption(int index) {
    if (index < 0 || index >= options.size() || options[index].type != TYPE_TOGGLE) {
        return false;
    }
    
    // 切换开关状态
    options[index].toggleState = !options[index].toggleState;
    
    // 更新UI
    updateStateLabel(index);
    
    return options[index].toggleState;
}

int VerticalOptionsMenu::adjustValue(int index, bool increment) {
    if (index < 0 || index >= options.size() || options[index].type != TYPE_VALUE) {
        return -1;
    }
    
    // 设置编辑状态
    isEditingValue = true;
    editingIndex = index;
    blinkTimer = HAL::SysCtrl().millis();
    blinkState = true;
    
    // 调整值
    MenuOption& option = options[index];
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
    updateStateLabel(index);
    
    return option.value;
}

void VerticalOptionsMenu::updateStateLabel(int index) {
    if (index >= 0 && index < options.size() && index < stateLabels.size() && stateLabels[index] != nullptr) {
        lv_label_set_text(stateLabels[index], getOptionStateText(options[index]).c_str());
    }
}

std::string VerticalOptionsMenu::getOptionStateText(int index) const {
    if (index >= 0 && index < options.size()) {
        return getOptionStateText(options[index]);
    }
    return "";
}

std::string VerticalOptionsMenu::getOptionStateText(const MenuOption& option) const {
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

void VerticalOptionsMenu::setSelectCallback(std::function<void(int, OptionType)> callback) {
    onSelectCallback = callback;
}

void VerticalOptionsMenu::clear() {
    // 保存目标屏幕的临时引用，防止丢失
    lv_obj_t* savedScreen = targetScreen;
    
    // 清理菜单项资源
    for (auto item : menuItems) {
        if (item != nullptr) {
            lv_obj_del(item);
        }
    }
    menuItems.clear();
    
    // 清理状态标签
    stateLabels.clear();
    
    // 清理选择器
    if (selector != nullptr) {
        lv_obj_del(selector);
        selector = nullptr;
    }
    
    // 清理选项列表
    options.clear();
    
    // 重置菜单对象
    verticalMenu = SmoothUIToolKit::SelectMenu::SmoothSelector();
    
    // 重置编辑状态
    isEditingValue = false;
    editingIndex = -1;
    blinkTimer = 0;
    blinkState = true;
    
    // 重置回调
    onSelectCallback = nullptr;
    
    // 恢复保存的屏幕引用
    targetScreen = savedScreen;
}

} // namespace MenuModules 