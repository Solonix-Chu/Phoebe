/**
 * @file vertical_options_menu.cpp
 * @brief 竖向选项列表模块实现
 */
#include "vertical_options_menu.h"
#include <hal/hal.h>
#include <lvgl.h>
#include <mooncake_log.h>
#include <cstdio>
#include <sstream>

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
    
    // 设置黑色背景 - OLED显示屏默认背景为黑色
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), LV_PART_MAIN);
    
    // 创建菜单选择器 - 占据整个屏幕
    selector = lv_obj_create(screen);
    lv_obj_set_size(selector, HAL::Display().width(), HAL::Display().height());
    lv_obj_set_pos(selector, 0, 0);
    lv_obj_set_style_radius(selector, 0, 0);
    lv_obj_set_style_border_width(selector, 0, 0);
    lv_obj_set_style_bg_color(selector, lv_color_hex(0x000000), 0); // 黑色背景
    lv_obj_set_style_pad_all(selector, 0, 0);
    // 确保没有任何边框，包括右侧边框
    lv_obj_set_style_border_side(selector, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_outline_width(selector, 0, 0); // 移除轮廓
    // 禁用滚动条
    lv_obj_set_scrollbar_mode(selector, LV_SCROLLBAR_MODE_OFF);
    
    // 重新初始化竖向菜单对象
    verticalMenu = SmoothUIToolKit::SelectMenu::SmoothSelector();
    
    // 设置菜单项高度和间距 - 减小值以适应小屏幕
    MENU_ITEM_HEIGHT = 12; // 更小的项目高度
    MENU_ITEM_SPACING = 1; // 最小间距
    
    // 设置菜单配置，包括摄像机设置
    verticalMenu.setConfig({
        .moveInLoop = true,      // 循环模式
        .cameraSize = {HAL::Display().width(), HAL::Display().height()},
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
    
    // 添加选项到数据列表
    options.push_back(option);
    int optionIndex = options.size() - 1;
    
    // 添加选项到菜单 - 每项都有自己的平移距离
    // 创建选项属性并设置关键帧
    SmoothUIToolKit::SelectMenu::SmoothSelector::OptionProps_t optionProps;
    optionProps.keyframe = {
        0, // 从左侧开始
        optionIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING),
        HAL::Display().width(),
        MENU_ITEM_HEIGHT
    };
    verticalMenu.addOption(optionProps);
    
    // 获取屏幕尺寸
    int screenWidth = HAL::Display().width();
    
    // 创建选项项容器 - 占据整个宽度
    lv_obj_t* menuItem = lv_obj_create(selector);
    lv_obj_set_size(menuItem, screenWidth, MENU_ITEM_HEIGHT); // 完整宽度
    lv_obj_set_pos(menuItem, 0, optionIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING));
    lv_obj_set_style_radius(menuItem, 0, 0);
    lv_obj_set_style_border_width(menuItem, 0, 0); // 移除边框
    lv_obj_set_style_bg_color(menuItem, lv_color_hex(0x000000), 0); // 黑色背景
    lv_obj_set_style_pad_all(menuItem, 0, 0);
    // 确保没有任何边框，包括右侧边框
    lv_obj_set_style_border_side(menuItem, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_outline_width(menuItem, 0, 0); // 移除轮廓
    // 禁用滚动条
    lv_obj_set_scrollbar_mode(menuItem, LV_SCROLLBAR_MODE_OFF);
    
    // 计算选项文本和状态的布局
    int textAreaWidth = screenWidth * 0.6; // 文本区域宽度占60%
    
    // 创建选项名称标签 - 使用更小的字体
    lv_obj_t* nameLabel = lv_label_create(menuItem);
    lv_label_set_text(nameLabel, option.name.c_str());
    lv_obj_set_style_text_color(nameLabel, lv_color_hex(0xFFFFFF), 0); // 白色文本
    lv_obj_set_style_text_font(nameLabel, &lv_font_montserrat_10, 0); // 较小的字体
    lv_obj_set_pos(nameLabel, 2, 1); // 减少边距，更紧凑
    lv_obj_set_width(nameLabel, textAreaWidth);
    
    // 创建状态标签 - 使用更小的字体
    lv_obj_t* stateLabel = lv_label_create(menuItem);
    std::string stateText = getOptionStateText(option);
    lv_label_set_text(stateLabel, stateText.c_str());
    lv_obj_set_style_text_color(stateLabel, lv_color_hex(0xFFFFFF), 0); // 白色文本
    lv_obj_set_style_text_font(stateLabel, &lv_font_montserrat_10, 0); // 较小的字体
    lv_obj_align(stateLabel, LV_ALIGN_RIGHT_MID, -4, 0); // 调整右边距
    
    // 保存UI元素引用
    menuItems.push_back(menuItem);
    stateLabels.push_back(stateLabel);
    
    return optionIndex;
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
        // 创建新的选择器 - 适合小型OLED
        int screenWidth = HAL::Display().width();
        int screenHeight = HAL::Display().height();
        
        selector = lv_obj_create(targetScreen);
        if (selector == nullptr) {
            mclog::tagError(_tag, "创建选择器失败");
            return;
        }
        
        // 设置选择器为黑色背景
        lv_obj_set_size(selector, screenWidth, screenHeight);
        lv_obj_set_pos(selector, 0, 0);
        lv_obj_set_style_radius(selector, 0, 0);
        lv_obj_set_style_border_width(selector, 0, 0);
        lv_obj_set_style_bg_color(selector, lv_color_hex(0x000000), 0); // 黑色背景
        lv_obj_set_style_pad_all(selector, 0, 0);
        // 确保没有任何边框，包括右侧边框
        lv_obj_set_style_border_side(selector, LV_BORDER_SIDE_NONE, 0);
        lv_obj_set_style_outline_width(selector, 0, 0); // 移除轮廓
        // 禁用滚动条
        lv_obj_set_scrollbar_mode(selector, LV_SCROLLBAR_MODE_OFF);
        
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
            int itemIndex = i;  // 调整为直接使用索引，不再需要计算
            lv_coord_t baseY = itemIndex * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
            
            // 应用摄像机偏移
            float newY = baseY - cameraOffset.y;
            
            // 如果项目超出顶部，则隐藏它
            if (newY < -MENU_ITEM_HEIGHT || newY > HAL::Display().height()) {
                lv_obj_set_style_opa(menuItems[i], 0, 0); // 隐藏
            } else {
                lv_obj_set_style_opa(menuItems[i], 255, 0); // 显示
                lv_obj_set_y(menuItems[i], newY);
            }
        }
    }
    
    // 更新状态标签可见性
    for (int i = 0; i < stateLabels.size(); i++) {
        if (stateLabels[i] != nullptr) {
            // 获取父菜单项的可见性并应用相同设置
            if (i < menuItems.size()) {
                lv_opa_t parentOpa = lv_obj_get_style_opa(menuItems[i], 0);
                
                // 如果正在编辑此状态，根据闪烁状态决定是否显示
                if (isEditingValue && i == editingIndex) {
                    lv_obj_set_style_opa(stateLabels[i], blinkState ? parentOpa : 0, 0);
                } else {
                    lv_obj_set_style_opa(stateLabels[i], parentOpa, 0);
                }
            }
        }
    }
    
    // 更新选中项的高亮状态 - 使用简单的反转显示效果，没有滑动指示器
    int selectedIndex = verticalMenu.getSelectedOptionIndex();
    for (int i = 0; i < menuItems.size(); i++) {
        lv_obj_t* menuItem = menuItems[i];
        lv_obj_t* nameLabel = nullptr;
        
        // 获取子对象（第一个子对象是名称标签）
        if (lv_obj_get_child_cnt(menuItem) > 0) {
            nameLabel = lv_obj_get_child(menuItem, 0);
        }
        
        if (i == selectedIndex) {
            // 选中项高亮 - 使用白色底黑字效果
            lv_obj_set_style_bg_opa(menuItem, 255, 0);
            lv_obj_set_style_bg_color(menuItem, lv_color_hex(0xFFFFFF), 0);
            
            // 设置选中项的文本为黑色
            if (nameLabel) {
                lv_obj_set_style_text_color(nameLabel, lv_color_hex(0x000000), 0);
            }
            
            // 设置状态标签为黑色
            if (i < stateLabels.size() && stateLabels[i] != nullptr) {
                lv_obj_set_style_text_color(stateLabels[i], lv_color_hex(0x000000), 0);
            }
        } else {
            // 非选中项 - 黑底白字
            lv_obj_set_style_bg_opa(menuItem, 0, 0);
            
            // 设置非选中项的文本为白色
            if (nameLabel) {
                lv_obj_set_style_text_color(nameLabel, lv_color_hex(0xFFFFFF), 0);
            }
            
            // 设置状态标签为白色
            if (i < stateLabels.size() && stateLabels[i] != nullptr) {
                lv_obj_set_style_text_color(stateLabels[i], lv_color_hex(0xFFFFFF), 0);
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
    
    // 如果未处于编辑状态，仅返回当前值
    if (!isEditingValue) {
        return options[index].value;
    }
    
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
    
    // 重置闪烁计时器
    blinkTimer = HAL::SysCtrl().millis();
    blinkState = true;
    
    return option.value;
}

/**
 * @brief 切换数值编辑状态
 * @param index 选项索引
 * @return 是否进入编辑状态
 */
bool VerticalOptionsMenu::toggleEditMode(int index) {
    if (index < 0 || index >= options.size() || options[index].type != TYPE_VALUE) {
        return false;
    }
    
    // 如果已经在编辑中但不是同一个选项
    if (isEditingValue && editingIndex != index) {
        // 退出之前的编辑状态
        isEditingValue = false;
        
        // 恢复之前编辑项的显示
        if (editingIndex >= 0 && editingIndex < stateLabels.size() && stateLabels[editingIndex] != nullptr) {
            lv_obj_set_style_opa(stateLabels[editingIndex], 255, 0);
        }
    }
    
    // 切换编辑状态
    isEditingValue = !isEditingValue;
    
    // 设置当前编辑索引
    editingIndex = isEditingValue ? index : -1;
    
    // 重置闪烁计时器
    blinkTimer = HAL::SysCtrl().millis();
    blinkState = true;
    
    return isEditingValue;
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

bool VerticalOptionsMenu::isInEditMode() const {
    return isEditingValue && editingIndex >= 0;
}

int VerticalOptionsMenu::getEditingIndex() const {
    return isEditingValue ? editingIndex : -1;
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