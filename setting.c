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
 *      EXTERN
 **********************/
extern lv_obj_t * setting_win;
/**********************
 *      TYPEDEFS
 **********************/
typedef struct
{
    lv_obj_t * pos_x;
    lv_obj_t * pos_y;
    lv_obj_t * size_h;
    lv_obj_t * size_w;
    lv_obj_t * drag;
    lv_obj_t * click;
}setting_attr_handler_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void getcode_cb(lv_obj_t * obj, lv_event_t ev);

/**********************
 *  STATIC VARIABLES
 **********************/
setting_attr_handler_t base_attr;


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


    //POSITION
    lv_obj_t * title = lv_label_create(setting_win, NULL);
    lv_label_set_text(title, "Postion");

    lv_obj_t * lb1 = lv_label_create(setting_win, NULL);
    lv_label_set_text(lb1, "X:");
    lv_obj_align(lb1, title, LV_ALIGN_OUT_BOTTOM_LEFT,0,15);    

    lv_obj_t * ta_x = lv_ta_create(setting_win, NULL);
    lv_ta_set_one_line(ta_x, true);
    lv_ta_set_text(ta_x, "");
    lv_ta_set_cursor_type(ta_x, LV_CURSOR_NONE);
    lv_ta_set_cursor_blink_time(ta_x, 0);
    lv_obj_align(ta_x, lb1, LV_ALIGN_OUT_RIGHT_MID, 15, 0); 
    base_attr.pos_x = ta_x;

    lv_obj_t * lb_plus = lv_label_create(ta_x, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta_x, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lv_obj_t * lb_minus = lv_label_create(ta_x, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );

    lv_obj_t * lb2 = lv_label_create(setting_win, lb1);
    lv_label_set_text(lb2, "Y:");
    lv_obj_align(lb2, lb1, LV_ALIGN_OUT_BOTTOM_MID,0 , 30);
    
    lv_obj_t * ta_y = lv_ta_create(setting_win, ta_x);
    lv_ta_set_one_line(ta_y, true);
    lv_ta_set_text(ta_y, "");
    lv_obj_align(ta_y, lb2, LV_ALIGN_OUT_RIGHT_MID, 15, 0);
    base_attr.pos_y = ta_y;


    lb_plus = lv_label_create(ta_y, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta_y, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lb_minus = lv_label_create(ta_y, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );


    //SIZE
    title = lv_label_create(setting_win, NULL);
    lv_label_set_text(title, "Size");
    lv_obj_align(title, lb2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 40);

    lb1 = lv_label_create(setting_win, NULL);
    lv_label_set_text(lb1, "Height:");
    lv_obj_align(lb1, title, LV_ALIGN_OUT_BOTTOM_LEFT,0,15);    

    lv_obj_t * ta_h = lv_ta_create(setting_win, NULL);
    lv_ta_set_one_line(ta_h, true);
    lv_ta_set_text(ta_h, "");
    lv_ta_set_cursor_type(ta_h, LV_CURSOR_HIDDEN);
    lv_ta_set_cursor_blink_time(ta_h, 0);
    lv_obj_align(ta_h, lb1, LV_ALIGN_OUT_RIGHT_MID, 15, 0);
    base_attr.size_h = ta_h;

    lb_plus = lv_label_create(ta_h, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta_h, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lb_minus = lv_label_create(ta_h, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );

    lb2 = lv_label_create(setting_win, lb1);
    lv_label_set_text(lb1, "Width: ");
    lv_obj_align(lb1, lb2, LV_ALIGN_OUT_BOTTOM_MID,0 , 30);
    lv_obj_t * ta_w = lv_ta_create(setting_win, ta_h);
    lv_obj_align(ta_w, lb1, LV_ALIGN_OUT_RIGHT_MID, 15, 0);
    base_attr.size_h = ta_w;

    lb_plus = lv_label_create(ta_w, NULL);
    lv_label_set_text(lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(lb_plus, ta_w, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(lb_plus, true);
    // lv_obj_set_event_cb(lb_plus, );
    lb_minus = lv_label_create(ta_w, lb_plus);
    lv_label_set_text(lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(lb_minus, lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(lb_minus, true);
    // lv_obj_set_event_cb(lb_minus, );

    //DRAG && CLICK
    lv_obj_t * cb_drag = lv_cb_create(setting_win, NULL);
    lv_cb_set_text(cb_drag, "Drag");
    lv_obj_align(cb_drag, lb2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 75);

    lv_obj_t * cb_click = lv_cb_create(setting_win, cb_drag);
    lv_cb_set_text(cb_click, "Click");
    lv_obj_align(cb_click, cb_drag, LV_ALIGN_OUT_RIGHT_MID, 20, 0); 

}

void setting_attr_mod(lv_obj_t * obj)
{
    lv_coord_t x = lv_obj_get_x(obj);
    char x_str[8];
    snprintf(x_str, 8, "%d", x);
    lv_ta_set_text(base_attr.pos_x, x_str);
    lv_coord_t y = lv_obj_get_y(obj);
    char y_str[8];
    snprintf(y_str, 8, "%d", y);    
    lv_ta_set_text(base_attr.pos_y, y_str);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void getcode_cb(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_CLICKED)
    {
        code_generation();
    }
}

