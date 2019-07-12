#include "lvgl/lvgl.h"
#include <stdio.h>
#include <malloc.h>

lv_obj_t * screen;
lv_obj_t * tft_win;
lv_obj_t * toolbox_win;
lv_obj_t * setting_win;

struct widget_stack{
    lv_obj_t * widget;
    struct widget_stack * next;
};

typedef struct widget_stack widget_stack_t;

static widget_stack_t * wstack = NULL;
void wstack_push(lv_obj_t * new);
lv_obj_t * wstack_pop(void);

void tft_win_init(lv_obj_t * parent);
void setting_win_init(lv_obj_t * parent);
void toolbox_win_init(lv_obj_t * parent);
static void btn_cb(lv_obj_t * btn, lv_event_t ev);
static void update(lv_obj_t * obj, lv_event_t ev);
static void chb_cb(lv_obj_t * btn, lv_event_t ev);
static void create_undo(lv_obj_t * obj, lv_event_t ev);

void lv_gui_designer()
{
    lv_coord_t hres = lv_disp_get_hor_res(NULL);
    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    screen = lv_obj_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_size(screen, hres, vres);
    lv_theme_t * th = lv_theme_material_init(150, NULL);
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

    list_btn = lv_list_add_btn(list, LV_SYMBOL_CLOSE,  "CLEAN UP");
    lv_obj_set_event_cb(list_btn, create_undo);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK,  "Button");
    lv_obj_set_event_cb(list_btn, btn_cb);
 
    // lv_list_add_btn(list, LV_SYMBOL_LIST, "Label");
    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK, "CheckBox");
    lv_obj_set_event_cb(list_btn, chb_cb);
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

static void btn_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_btn_create(tft_win, NULL);
        lv_label_set_text(lv_label_create(new, NULL), "Button");
        if(wstack != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wstack->widget) + 10, lv_obj_get_y(wstack->widget) + 10);
        }
        wstack_push(new);
        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update);
    }
}

static void chb_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * new = lv_cb_create(tft_win, NULL);
        if(wstack != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(wstack->widget) + 10, lv_obj_get_y(wstack->widget) + 10);
        }
        wstack_push(new);
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

static void create_undo(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * last = wstack_pop();
        if(last != NULL)
        {
            lv_obj_del(last);
        }
    }
}

void wstack_push(lv_obj_t * new)
{
    widget_stack_t * new_top = (widget_stack_t *)malloc(sizeof(widget_stack_t));
    new_top->next = wstack;
    new_top->widget = new;
    wstack = new_top;
}

lv_obj_t * wstack_pop(void)
{
    if(wstack != NULL)
    {
        widget_stack_t * tmp = wstack;
        wstack = wstack->next;
        lv_obj_t * last = tmp->widget;
        free(tmp);
        return last;
    }
    return NULL;
}