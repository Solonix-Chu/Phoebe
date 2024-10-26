/**
 * @file widget_helper.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widget.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lvgl.h>
#include <assets/assets.h>

lv_align_t widget_helper::get_lv_align_by_string(const char* align)
{
    if (strcmp(align, "lv_align_default") == 0)
        return LV_ALIGN_DEFAULT;
    if (strcmp(align, "lv_align_top_left") == 0)
        return LV_ALIGN_TOP_LEFT;
    if (strcmp(align, "lv_align_top_mid") == 0)
        return LV_ALIGN_TOP_MID;
    if (strcmp(align, "lv_align_top_right") == 0)
        return LV_ALIGN_TOP_RIGHT;
    if (strcmp(align, "lv_align_bottom_left") == 0)
        return LV_ALIGN_BOTTOM_LEFT;
    if (strcmp(align, "lv_align_bottom_mid") == 0)
        return LV_ALIGN_BOTTOM_MID;
    if (strcmp(align, "lv_align_bottom_right") == 0)
        return LV_ALIGN_BOTTOM_RIGHT;
    if (strcmp(align, "lv_align_left_mid") == 0)
        return LV_ALIGN_LEFT_MID;
    if (strcmp(align, "lv_align_right_mid") == 0)
        return LV_ALIGN_RIGHT_MID;
    if (strcmp(align, "lv_align_center") == 0)
        return LV_ALIGN_CENTER;
    return LV_ALIGN_DEFAULT;
}

lv_color_t widget_helper::get_lv_color_by_string(const char* hexColor)
{
    lv_color_t color = {0, 0, 0};

    if (hexColor[0] == '#' && strlen(hexColor) == 7) {
        sscanf(hexColor + 1, "%2hhx%2hhx%2hhx", &color.red, &color.green, &color.blue);
    }
    return color;
}

const lv_font_t* widget_helper::get_lv_font_by_string(const char* fontName)
{
    if (strcmp(fontName, "RajdhaniBold16") == 0)
        return AssetPool::Font().RajdhaniBold16;
    if (strcmp(fontName, "RajdhaniBold24") == 0)
        return AssetPool::Font().RajdhaniBold24;
    if (strcmp(fontName, "RajdhaniBold36") == 0)
        return AssetPool::Font().RajdhaniBold36;
    if (strcmp(fontName, "RajdhaniBold48") == 0)
        return AssetPool::Font().RajdhaniBold48;
    if (strcmp(fontName, "RajdhaniBold64") == 0)
        return AssetPool::Font().RajdhaniBold64;
    if (strcmp(fontName, "RajdhaniBold72") == 0)
        return AssetPool::Font().RajdhaniBold72;
    if (strcmp(fontName, "RajdhaniBold96") == 0)
        return AssetPool::Font().RajdhaniBold96;
    if (strcmp(fontName, "RajdhaniBold144") == 0)
        return AssetPool::Font().RajdhaniBold144;
    if (strcmp(fontName, "Zpix12") == 0)
        return AssetPool::Font().Zpix12;
    return AssetPool::Font().RajdhaniBold16;
}
