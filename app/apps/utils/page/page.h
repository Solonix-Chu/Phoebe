/**
 * @file page.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-11-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "../widget/widget.h"
#include "../smooth_widget/smooth_widget.h"

namespace page {

class PageSelectMenu {
public:
    void create(size_t startupIndex = 0);
    void show();
    void hide();
    void update();
    int getCurrentTargetIndex();
    std::string getCurrntTargetOption();
    bool isAllSmoothingFinish();

    std::vector<std::string> optionList;
    bool wasSelected = false;
    int hideDelay = 0;

private:
    std::unique_ptr<smooth_widget::SmoothWidgetBase> _menu_base;
    std::unique_ptr<smooth_widget::SmoothWidgetMouse> _mouse;
    std::vector<std::unique_ptr<widget::WidgetLabel>> _option_widget_list;
    bool _is_hiding = true;
};

typedef std::function<void(std::vector<std::string>& optionList, size_t& startupIndex)> OnSelectMenuSetupCallback_t;
typedef std::function<void(int selectIndex, std::string& option)> OnSelectMenuSelectCallback_t;

int CreateSelecMenuPageAndWaitResult(OnSelectMenuSetupCallback_t onSetup,
                                     OnSelectMenuSelectCallback_t onSelect = nullptr);

} // namespace page
