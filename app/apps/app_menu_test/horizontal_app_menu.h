/**
 * @file horizontal_app_menu.h
 * @brief 横向应用菜单模块
 */
#pragma once
#include <lvgl.h>
#include <vector>
#include <string>
#include "dependencies/smooth_ui_toolkit/src/select_menu/smooth_options/smooth_options.h"
#include <functional>

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
     * @return 返回选中的应用索引
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
     * @brief 更新横向菜单布局
     * @param currentTime 当前时间
     */
    void update(uint32_t currentTime);
    
    /**
     * @brief 向前移动选择器
     */
    void goNext();
    
    /**
     * @brief 向后移动选择器
     */
    void goLast();
    
    /**
     * @brief 直接跳转到指定索引
     * @param index 目标索引
     */
    void goToIndex(int index);

    /**
     * @brief 获取当前选中的应用索引
     * @return 当前选中的应用索引
     */
    int getSelectedIndex() const;

    /**
     * @brief 获取图标对象
     * @param index 索引
     * @return 返回对应索引的图标对象
     */
    lv_obj_t* getAppIcon(int index) const;
    
    /**
     * @brief 获取应用图标数量
     * @return 图标数量
     */
    size_t getAppIconCount() const;
    
    /**
     * @brief 设置选中回调函数
     * @param callback 回调函数
     */
    void setSelectCallback(std::function<void(int)> callback);
    
    /**
     * @brief 设置选中框的显示状态
     * @param show 是否显示选中框
     */
    void setSelectionFrameVisible(bool show);
    
    /**
     * @brief 清理资源
     */
    void clear();

private:
    /**
     * @brief 更新菜单关键帧
     */
    void updateKeyframes();
    
    /**
     * @brief 创建或更新分割线和滑块
     */
    void createOrUpdateDivider();

    // 目标屏幕
    lv_obj_t* targetScreen = nullptr;
    
    // 分割线和滑块
    lv_obj_t* dividerLine = nullptr;
    lv_obj_t* sliderIndicator = nullptr;
    
    // 选中框角标记
    lv_obj_t* topLeftCorner = nullptr;
    lv_obj_t* topRightCorner = nullptr;
    lv_obj_t* bottomLeftCorner = nullptr;
    lv_obj_t* bottomRightCorner = nullptr;
    std::vector<lv_obj_t*> cornerVerticals; // 存储临时创建的竖直标记
    
    // 控制选中框是否显示
    bool showSelectionFrame = true;
    
    // 存储创建的图标
    std::vector<lv_obj_t*> appIcons;
    SmoothUIToolKit::SelectMenu::SmoothOptions horizontalMenu;
    std::function<void(int)> onSelectCallback = nullptr;
};

} // namespace MenuModules 