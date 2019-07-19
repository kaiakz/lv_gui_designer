/**
 * @setting.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "./lvgl/lvgl.h"
#include "setting.h"
#include "interface.h"
#include "dataset.h"
#include <malloc.h>
#include "gencode.h"
/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/
extern lv_obj_t * setting_win;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void getcode_cb(lv_obj_t * obj, lv_event_t ev);

/**********************
 *  STATIC VARIABLES
 **********************/


/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void setting_win_init(lv_obj_t * parent)
{
    setting_win = lv_win_create(parent, NULL);
    lv_win_set_title(setting_win, "Setting");
    lv_obj_set_size(setting_win, lv_obj_get_width_fit(parent) / 4.5 , lv_obj_get_height(parent));
    lv_obj_align(setting_win, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_page_set_scrl_fit(lv_win_get_content(setting_win), LV_FIT_TIGHT);

    lv_obj_t * getcode_btn = lv_win_add_btn(setting_win, LV_SYMBOL_DOWNLOAD);
    lv_obj_set_protect(getcode_btn, LV_PROTECT_CLICK_FOCUS);
    lv_obj_set_event_cb(getcode_btn, getcode_cb);


    lv_obj_t * title = lv_label_create(setting_win, NULL);
    lv_label_set_text(title, "Postion");

    lv_obj_t * lb1 = lv_label_create(setting_win, NULL);
    lv_label_set_text(lb1, "X:");
    lv_obj_align(lb1, title, LV_ALIGN_OUT_BOTTOM_LEFT,0,15);    

    lv_obj_t * ta = lv_ta_create(setting_win, NULL);
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "");
    lv_ta_set_cursor_blink_time(ta, 0);
    lv_obj_align(ta, lb1, LV_ALIGN_OUT_RIGHT_MID, 15, 0);

    lv_obj_t * lb_plus = lv_label_create(ta, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lv_obj_t * lb_minus = lv_label_create(ta, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );

    lv_obj_t * lb2 = lv_label_create(setting_win, lb1);
    lv_label_set_text(lb2, "Y:");
    lv_obj_align(lb2, lb1, LV_ALIGN_OUT_BOTTOM_MID,0 , 30);
    
    lv_obj_t * ta2 = lv_ta_create(setting_win, NULL);
    lv_ta_set_one_line(ta2, true);
    lv_ta_set_text(ta2, "");
    lv_obj_align(ta2, lb2, LV_ALIGN_OUT_RIGHT_MID, 15, 0);
    lb_plus = lv_label_create(ta2, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta2, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lb_minus = lv_label_create(ta2, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );


    title = lv_label_create(setting_win, NULL);
    lv_label_set_text(title, "Size");
    lv_obj_align(title, lb2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 40);

    lb1 = lv_label_create(setting_win, NULL);
    lv_label_set_text(lb1, "Height:");
    lv_obj_align(lb1, title, LV_ALIGN_OUT_BOTTOM_LEFT,0,15);    

    ta = lv_ta_create(setting_win, NULL);
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "");
    lv_ta_set_cursor_blink_time(ta, 0);
    lv_obj_align(ta, lb1, LV_ALIGN_OUT_RIGHT_MID, 15, 0);

    lb_plus = lv_label_create(ta, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lb_minus = lv_label_create(ta, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );

    lb2 = lv_label_create(setting_win, lb1);
    lv_label_set_text(lb1, "Width: ");
    lv_obj_align(lb1, lb2, LV_ALIGN_OUT_BOTTOM_MID,0 , 30);
    ta2 = lv_ta_create(setting_win, ta);
    // lv_ta_set_one_line(ta2, true);
    // lv_ta_set_text(ta2, "");
    lv_obj_align(ta2, lb1, LV_ALIGN_OUT_RIGHT_MID, 15, 0);
    lb_plus = lv_label_create(ta2, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta2, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lb_minus = lv_label_create(ta2, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );


    title = lv_label_create(setting_win, NULL);
    lv_label_set_text(title, "Drag");
    lv_obj_align(title, lb2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 75);

    lv_obj_t * sw = lv_sw_create(setting_win, NULL);
    lv_sw_on(sw, LV_ANIM_ON);
    lv_obj_align(sw, title, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    title = lv_label_create(setting_win, NULL);
    lv_label_set_text(title, "Click");
    lv_obj_align(title, sw, LV_ALIGN_OUT_RIGHT_MID, 20, 0);

    sw = lv_sw_create(setting_win, NULL);
    lv_sw_on(sw, LV_ANIM_ON);
    lv_obj_align(sw, title, LV_ALIGN_OUT_RIGHT_MID, 10, 0);    

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void getcode_cb(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_CLICKED)
    {
        // code_generation();
    }
}

