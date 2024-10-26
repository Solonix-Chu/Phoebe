/**
 * @file page.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../utils/smooth_lv_widgets/lv_obj.h"
#include "../../utils/watch_face_ability/watch_face_ability.h"
#include <mooncake.h>
#include <memory>
#include <vector>

/**
 * @brief 启动器页面基类，在 UIAbility 基础上加上二级页面状态，方便页面接管按键输入事件
 *
 */
class LauncherPageBase : public mooncake::UIAbility {
public:
    virtual void onEnterSubPage() {}
    virtual void onQuitSubPage() {}

    bool isOnSubPage()
    {
        return _is_on_sub_page;
    }

    void enterSubPage()
    {
        _is_on_sub_page = true;
        onEnterSubPage();
    }

    void quitSubPage()
    {
        _is_on_sub_page = false;
        onQuitSubPage();
    }

protected:
    bool _is_on_sub_page = false;
};

class LauncherPageWatchFace : public LauncherPageBase {
public:
    void onCreate() override;
    void onShow() override;
    void onForeground() override;
    void onBackground() override;
    void onHide() override;
    // void onDestroy() override {}

private:
    std::unique_ptr<smooth_lv_widgets::LvObj> _canvas;

    WatchFaceAbility* _watch_face_ability_instance = nullptr;
    int _watch_face_ability_id = -1;
};

class LauncherPageNotification : public LauncherPageBase {
public:
    void onCreate() override;
    void onShow() override;
    void onForeground() override;
    void onBackground() override;
    void onHide() override;
    // void onDestroy() override {}

private:
    std::vector<std::unique_ptr<smooth_lv_widgets::LvObj>> _canvas_list;
};

class LauncherPageWidgets : public LauncherPageBase {
public:
    void onCreate() override;
    void onShow() override;
    void onForeground() override;
    void onBackground() override;
    void onHide() override;
    // void onDestroy() override {}

private:
    std::vector<std::unique_ptr<smooth_lv_widgets::LvObj>> _canvas_list;
};

class LauncherPageAppList : public LauncherPageBase {
public:
    // void onCreate() override {}
    void onShow() override;
    void onForeground() override;
    void onBackground() override;
    void onHide() override;
    // void onDestroy() override {}

private:
    std::unique_ptr<smooth_lv_widgets::LvObj> _canvas;
};
