/**
 * @file vertical_options_menu.h
 * @brief 竖向选项列表模块
 */
#pragma once
#include <lvgl.h>
#include <vector>
#include <string>
#include <functional>
#include "dependencies/smooth_ui_toolkit/src/select_menu/smooth_selector/smooth_selector.h"

namespace MenuModules {

/**
 * @brief 菜单选项类型
 */
enum OptionType {
    TYPE_TOGGLE,   // 开关类型
    TYPE_VALUE,    // 数值类型
    TYPE_ACTION    // 动作类型（如返回）
};

/**
 * @brief 菜单选项数据结构
 */
struct MenuOption {
    std::string name;
    OptionType type;
    bool toggleState = false;    // 开关状态
    int value = 0;               // 数值
    int minValue = 0;            // 最小值
    int maxValue = 100;          // 最大值
    int step = 1;                // 步长
};

/**
 * @brief 竖向选项列表类
 * 用于实现竖向滚动的选项列表菜单
 */
class VerticalOptionsMenu {
public:
    /**
     * @brief 初始化竖向选项列表
     * @param screen 目标屏幕对象
     */
    void init(lv_obj_t* screen);

    /**
     * @brief 添加选项
     * @param option 选项数据
     * @return 选项索引
     */
    int addOption(const MenuOption& option);

    /**
     * @brief 批量设置选项
     * @param options 选项数据列表
     */
    void setOptions(const std::vector<MenuOption>& options);

    /**
     * @brief 更新菜单
     * @param currentTime 当前时间戳
     */
    void update(uint32_t currentTime);

    /**
     * @brief 移动到下一个选项
     */
    void goNext();

    /**
     * @brief 移动到上一个选项
     */
    void goLast();

    /**
     * @brief 获取当前选中的选项索引
     * @return 当前选中的选项索引
     */
    int getSelectedIndex() const;

    /**
     * @brief 获取选项
     * @param index 选项索引
     * @return 选项数据
     */
    MenuOption& getOption(int index);

    /**
     * @brief 获取所有选项
     * @return 选项数据列表
     */
    const std::vector<MenuOption>& getOptions() const;

    /**
     * @brief 切换选项状态（仅适用于TYPE_TOGGLE类型）
     * @param index 选项索引
     * @return 切换后的状态
     */
    bool toggleOption(int index);

    /**
     * @brief 调整选项数值（仅适用于TYPE_VALUE类型）
     * @param index 选项索引
     * @param increment 是否增加数值
     * @return 调整后的数值
     */
    int adjustValue(int index, bool increment);

    /**
     * @brief 切换数值编辑状态
     * @param index 选项索引
     * @return 是否进入编辑状态
     */
    bool toggleEditMode(int index);

    /**
     * @brief 获取选项状态文本
     * @param index 选项索引
     * @return 状态文本
     */
    std::string getOptionStateText(int index) const;

    /**
     * @brief 检查是否处于编辑模式
     * @return 是否处于编辑模式
     */
    bool isInEditMode() const;

    /**
     * @brief 获取当前编辑的选项索引
     * @return 编辑索引，如果不在编辑模式则返回-1
     */
    int getEditingIndex() const;

    /**
     * @brief 设置选定选项的回调函数
     * @param callback 选中选项时的回调函数
     */
    void setSelectCallback(std::function<void(int, OptionType)> callback);

    /**
     * @brief 清理菜单资源
     */
    void clear();

private:
    /**
     * @brief 更新选项状态标签文本
     * @param index 选项索引
     */
    void updateStateLabel(int index);

    /**
     * @brief 获取选项状态文本
     * @param option 选项数据
     * @return 状态文本
     */
    std::string getOptionStateText(const MenuOption& option) const;

    lv_obj_t* targetScreen = nullptr;
    lv_obj_t* selector = nullptr;
    std::vector<MenuOption> options;
    std::vector<lv_obj_t*> menuItems;
    std::vector<lv_obj_t*> stateLabels;
    SmoothUIToolKit::SelectMenu::SmoothSelector verticalMenu;
    std::function<void(int, OptionType)> onSelectCallback = nullptr;
    
    // 编辑状态
    bool isEditingValue = false;
    uint32_t blinkTimer = 0;
    bool blinkState = true;
    int editingIndex = -1;
    
    // 布局常量
    int MENU_ITEM_HEIGHT = 28;     // 选项高度
    int MENU_ITEM_SPACING = 3;     // 选项间距
    
    // Logging tag
    static const char* _tag;
};

} // namespace MenuModules 