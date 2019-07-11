#include "lvgl/lvgl.h"
#include <stdio.h>

lv_obj_t * screen;
lv_obj_t * tft_win;
lv_obj_t * toolbox_win;
lv_obj_t * setting_win;

void tft_win_init(lv_obj_t * parent);
void setting_win_init(lv_obj_t * parent);
void toolbox_win_init(lv_obj_t * parent);
static void btn_cb(lv_obj_t * btn, lv_event_t ev);
static void update(lv_obj_t * obj, lv_event_t ev);

void lv_gui_designer()
{
    lv_coord_t hres = lv_disp_get_hor_res(NULL);
    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    screen = lv_obj_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_size(screen, hres, vres);
    lv_theme_t * th = lv_theme_material_init(10, NULL);
    lv_theme_set_current(th);
     
    toolbox_win_init(screen);
    tft_win_init(screen);
    setting_win_init(screen);
}

void tft_win_init(lv_obj_t * parent)
{
    tft_win = lv_win_create(parent, NULL);
    lv_win_set_title(tft_win, "TFT Simulator");
    lv_win_set_drag(tft_win, true);
    lv_obj_set_size(tft_win, 480, 320);
    lv_obj_align(tft_win, NULL, LV_ALIGN_CENTER, 0, 0);

    // lv_obj_set_drag(lv_btn_create(tft_win, NULL), true);
}

void toolbox_win_init(lv_obj_t * parent)
{
    toolbox_win = lv_win_create(parent, NULL);
    lv_win_set_title(toolbox_win, "ToolBox");
    lv_obj_set_size(toolbox_win, lv_obj_get_width_fit(parent) / 5, lv_obj_get_height_fit(parent));

    lv_obj_align(toolbox_win, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);

    lv_obj_t * list = lv_list_create(toolbox_win, NULL);
    lv_obj_set_size(list, lv_obj_get_width_fit(toolbox_win) + 5, lv_obj_get_height_fit(toolbox_win) * 0.7);
    lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
    lv_obj_t * list_btn;
    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK,  "Button");
    lv_obj_set_event_cb(list_btn, btn_cb);
 
    // lv_list_add_btn(list, LV_SYMBOL_LIST, "Label");
    lv_list_add_btn(list, LV_SYMBOL_OK, "CheckBox");
    // lv_list_add_btn(list, LV_SYMBOL_LOOP, "GPS");
    // lv_list_add_btn(list, LV_SYMBOL_EJECT, "Video");
    // lv_list_add_btn(list, LV_SYMBOL_POWER, "Call");
    // lv_list_add_btn(list, LV_SYMBOL_FILE, "Bell");
    // lv_list_add_btn(list, LV_SYMBOL_EDIT, "File");
    // lv_list_add_btn(list, LV_SYMBOL_CHARGE, "Edit");
    // lv_list_add_btn(list, LV_SYMBOL_DIRECTORY,  "Cut");
    // lv_list_add_btn(list, LV_SYMBOL_COPY, "Copy");


    // lv_obj_t * roller = lv_roller_create(toolbox_win, NULL);
    // lv_roller_set_options(roller, "Monday\nTuesday\nWednesday\nThursday\nFriday\nSaturday\nSunday", true);
    // lv_roller_set_selected(roller, 1, false);
    // lv_roller_set_visible_row_count(roller, 3);
    // lv_obj_align(roller, list, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
}

void setting_win_init(lv_obj_t * parent)
{
    
}

static void btn_cb(lv_obj_t * btn, lv_event_t ev)
{
    if(ev == LV_EVENT_PRESSED || ev == LV_EVENT_CLICKED)
    {
        // lv_obj_set_size(tft_win, lv_obj_get_width(tft_win) + 2, lv_obj_get_height(tft_win) + 2);
        lv_obj_t * new = lv_btn_create(tft_win, NULL);
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update);
    }
}

static void update(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_DRAG_END)
    {
        printf("X:%d Y:%d\n", lv_obj_get_x(obj), lv_obj_get_y(obj));
    }
}