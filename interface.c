#include <stdio.h>
#include <malloc.h>
#include "interface.h"
#include "toolbox.h"
#include "setting.h"

lv_obj_t * screen;
lv_obj_t * tft_win;
lv_obj_t * toolbox_win;
lv_obj_t * setting_win;

void tft_win_init(lv_obj_t * parent);



void lv_gui_designer()
{
    lv_coord_t hres = lv_disp_get_hor_res(NULL);
    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    screen = lv_obj_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_size(screen, hres, vres);
    lv_theme_t * th = lv_theme_material_init(150, NULL);
    lv_theme_set_current(th);
     
    toolbox_win_init(screen);
    setting_win_init(screen);
    tft_win_init(screen); 
}

void tft_win_init(lv_obj_t * parent)
{
    tft_win = lv_win_create(parent, NULL);
    lv_win_set_title(tft_win, "TFT Simulator");
    lv_win_set_drag(tft_win, true);
    lv_obj_set_size(tft_win, 480, 320);
    lv_obj_align(tft_win, NULL, LV_ALIGN_CENTER, 0, 0);
}





