/**
 * @file horizontal_app_menu.h
 * @brief 横向应用菜单模块
 */
#pragma once
#include <lvgl.h>
#include <vector>
#include <string>
#include "dependencies/smooth_ui_toolkit/src/select_menu/smooth_options/smooth_options.h"

namespace MenuModules {

/**
 * @brief 横向应用菜单类
 * 用于实现横向滚动的应用图标选择菜单
 */
class HorizontalAppMenu {
public:
    /**
     * @brief 初始化横向菜单
     * @param screen 目标屏幕对象
     */
    void init(lv_obj_t* screen);

    /**
     * @brief 添加应用
     * @param name 应用名称
     * @param color 应用图标颜色
     * @param isCircle 是否使用圆形图标
     * @return 应用索引
     */
    int addApp(const char* name, lv_color_t color, bool isCircle = false);

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
     * @brief 获取当前选中的应用索引
     * @return 当前选中的应用索引
     */
    int getSelectedIndex() const;

    /**
     * @brief 设置选定应用的回调函数
     * @param callback 选中应用时的回调函数
     */
    void setSelectCallback(std::function<void(int)> callback);

    /**
     * @brief 清理菜单资源
     */
    void clear();

private:
    /**
     * @brief 更新图标关键帧布局
     */
    void updateKeyframes();
    
    lv_obj_t* targetScreen = nullptr;
    std::vector<lv_obj_t*> appIcons;
    SmoothUIToolKit::SelectMenu::SmoothOptions horizontalMenu;
    std::function<void(int)> onSelectCallback = nullptr;
};

} // namespace MenuModules 