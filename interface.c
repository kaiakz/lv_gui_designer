#include "lvgl/lvgl.h"

lv_obj_t * screen;
lv_obj_t * tft_win;
lv_obj_t * toolbox_win;
lv_obj_t * setting_win;
void tft_win_create(lv_obj_t * parent);
void setting_win_create(lv_obj_t * parent);
void toolbox_win_create(lv_obj_t * parent);
static void btn_cb(lv_obj_t * btn, lv_event_t ev);

void lv_gui_designer()
{
    screen = lv_obj_create(NULL, NULL);
    lv_scr_load(screen);
    lv_theme_t * th = lv_theme_night_init(100, NULL);
    lv_theme_set_current(th);

    toolbox_win_create(screen);
    tft_win_create(screen);    
    setting_win_create(screen);
}

void tft_win_create(lv_obj_t * parent)
{
    tft_win = lv_win_create(parent, NULL);
    lv_win_set_title(tft_win, "TFT Simulator");
    lv_obj_set_size(tft_win, 200, 100);
    lv_obj_align(tft_win, parent, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t * btn = lv_btn_create(tft_win, NULL);
    lv_obj_set_drag(btn, true);
}

void toolbox_win_create(lv_obj_t * parent)
{
    toolbox_win = lv_win_create(parent, NULL);
    lv_win_set_title(toolbox_win, "ToolBox");
    lv_obj_set_size(parent, 200, lv_obj_get_height(parent));
    lv_obj_align(toolbox_win, toolbox_win, LV_ALIGN_IN_LEFT_MID, 0, 0);


    lv_obj_t * btn = lv_btn_create(toolbox_win, NULL);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &lv_style_transp_tight);
    lv_obj_set_event_cb(btn, btn_cb);


}

void setting_win_create(lv_obj_t * parent)
{
    
}

static void btn_cb(lv_obj_t * btn, lv_event_t ev)
{
    if(ev == LV_EVENT_PRESSED)
    {
        lv_obj_set_size(tft_win, lv_obj_get_width(tft_win) + 2, lv_obj_get_height(tft_win) + 2);
    }
}