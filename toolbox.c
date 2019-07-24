/**
 * @toolbox .c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "toolbox.h"
#include "dataset.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/
extern lv_obj_t * toolbox_win;
extern lv_obj_t * tft_win;


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void create_btn_cb(lv_obj_t * btn, lv_event_t ev);
static void create_chb_cb(lv_obj_t * btn, lv_event_t ev);
static void create_ddlist_cb(lv_obj_t * obj, lv_event_t ev);
static void create_bar_cb(lv_obj_t * obj, lv_event_t ev);
static void create_gauge_cb(lv_obj_t * obj, lv_event_t ev);
static void create_led_cb(lv_obj_t * obj, lv_event_t ev);
static void create_line_cb(lv_obj_t * obj, lv_event_t ev);
static void create_slider_cb(lv_obj_t * obj, lv_event_t ev);

static void update_setting(lv_obj_t * obj, lv_event_t ev);
static void create_undo(lv_obj_t * obj, lv_event_t ev);
/**********************
 *  STATIC VARIABLES
 **********************/
static int widget_count = 0;


/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void toolbox_win_init(lv_obj_t * parent)
{
    toolbox_win = lv_win_create(parent, NULL);
    lv_win_set_title(toolbox_win, "ToolBox");
    lv_obj_set_size(toolbox_win, lv_obj_get_width_fit(parent) / 5, lv_obj_get_height_fit(parent));

    lv_obj_align(toolbox_win, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);

    lv_obj_t * win_btn = lv_win_add_btn(toolbox_win, LV_SYMBOL_TRASH);
    lv_obj_set_event_cb(win_btn, create_undo);

    lv_obj_t * list = lv_list_create(toolbox_win, NULL);
    lv_obj_set_size(list, lv_obj_get_width_fit(toolbox_win) + 5, lv_obj_get_height_fit(toolbox_win) * 0.7);
    lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
    
    lv_obj_t * list_btn;

    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK,  "Button");
    lv_obj_set_event_cb(list_btn, create_btn_cb);
 
    
    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK, "CheckBox");
    lv_obj_set_event_cb(list_btn, create_chb_cb);
    
    list_btn = lv_list_add_btn(list, LV_SYMBOL_LIST, "DDList");
    lv_obj_set_event_cb(list_btn, create_ddlist_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_MINUS, "Bar");
    lv_obj_set_event_cb(list_btn, create_bar_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_DRIVE, "Gauge");
    lv_obj_set_event_cb(list_btn, create_gauge_cb);
    
    list_btn = lv_list_add_btn(list, LV_SYMBOL_POWER, "Led");
    lv_obj_set_event_cb(list_btn, create_led_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_PLUS, "Line");
    lv_obj_set_event_cb(list_btn, create_line_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_PLAY, "Slider");
    lv_obj_set_event_cb(list_btn, create_slider_cb);
    // lv_list_add_btn(list, LV_SYMBOL_CHARGE, "Edit");
    // lv_list_add_btn(list, LV_SYMBOL_DIRECTORY,  "Cut");
    // lv_list_add_btn(list, LV_SYMBOL_COPY, "Copy");


    // lv_obj_t * roller = lv_roller_create(toolbox_win, NULL);
    // lv_roller_set_options(roller, "Monday\nTuesday\nWednesday\nThursday\nFriday\nSaturday\nSunday", true);
    // lv_roller_set_selected(roller, 1, false);
    // lv_roller_set_visible_row_count(roller, 3);
    // lv_obj_align(roller, list, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

static void create_btn_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_btn_create(tft_win, NULL);
        lv_label_set_text(lv_label_create(new, NULL), "Button");
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }
        wdeque_pushback(new);
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
        
        widget_info_t * info = (widget_info_t *)malloc(sizeof(widget_info_t));
        info->type = WIDGET_TYPE_BTN;
        sprintf(info->id, "%s_%d", "btn", widget_count++);
        lv_obj_set_user_data(new, info); 
    }

}

static void create_chb_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_cb_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }
        wdeque_pushback(new);
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}

static void create_ddlist_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_ddlist_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }
        wdeque_pushback(new);     
        lv_obj_set_drag(new, true);
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_t * scrl = lv_page_get_scrl(new);
        lv_obj_set_drag_parent(scrl, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}

static void create_bar_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_bar_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }

        lv_bar_set_anim_time(new, 10000);
        lv_bar_set_value(new, 100, LV_ANIM_ON);
        wdeque_pushback(new);
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}

static void create_led_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_led_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }
        wdeque_pushback(new);     
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}

static void create_gauge_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_gauge_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }

        wdeque_pushback(new);
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}

static void create_line_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_line_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
            lv_point_t p[2] = {{LV_DPI, LV_DPI}, {LV_DPI + 10, LV_DPI + 10}};
            lv_line_set_points(new, p, 2);
        }
        wdeque_pushback(new);     
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}

static void create_slider_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_slider_create(tft_win, NULL);
        if(wdeque_gettail() != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wdeque_gettail()) + 10, lv_obj_get_y(wdeque_gettail()) + 10);
        }
        wdeque_pushback(new);     
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
    }
}


static void update_setting(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_DRAG_END)
    {
        printf("X:%d Y:%d\n", lv_obj_get_x(obj), lv_obj_get_y(obj));
    }
    // if(ev == LV_EVENT_LONG_PRESSED)
    // {
    //     lv_obj_set_hidden(obj, true);
    //     lv_line_create(tft_win, NULL);
    // }
    // if(ev == LV_EVENT_PRESS_LOST)
    // {
        
    // }
}

static void create_undo(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * last = wdeque_popback();
        if(last != NULL)
        {
            free((widget_info_t *)lv_obj_get_user_data(last));
            lv_obj_del(last);
            widget_count--;
        }
    }
}






