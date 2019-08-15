/**
 * @toolbox .c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "toolbox.h"
#include "setting.h"
#include "dataset.h"
#include "custom_widget.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      EXTERN
 **********************/
extern lv_obj_t * toolbox_win;
extern lv_obj_t * tft_win;
/**********************
 *      TYPEDEFS
 **********************/



/**********************
 *  STATIC PROTOTYPES
 **********************/
static void create_label_cb(lv_obj_t * obj, lv_event_t ev);
static void create_btn_cb(lv_obj_t * obj, lv_event_t ev);
static void create_cb_cb(lv_obj_t * obj, lv_event_t ev);
static void create_ddlist_cb(lv_obj_t * obj, lv_event_t ev);
static void create_bar_cb(lv_obj_t * obj, lv_event_t ev);
static void create_gauge_cb(lv_obj_t * obj, lv_event_t ev);
static void create_led_cb(lv_obj_t * obj, lv_event_t ev);
// static void create_line_cb(lv_obj_t * obj, lv_event_t ev);
static void create_slider_cb(lv_obj_t * obj, lv_event_t ev);

static void update_setting(lv_obj_t * obj, lv_event_t ev);
static void create_undo(lv_obj_t * obj, lv_event_t ev);

static void theme_select_event_handler(lv_obj_t * roller, lv_event_t event);
static void hue_select_event_cb(lv_obj_t * roller, lv_event_t event);
static void init_all_themes(uint16_t hue);
/**********************
 *  STATIC VARIABLES
 **********************/
// static int widget_count = 0;
static lv_theme_t * th_act;

static lv_obj_t * last_widget = NULL;   //Use by set position.There may got a error, if we delete this.

static const char * th_options =
{

#if LV_USE_THEME_NIGHT
        "Night"
#endif

#if LV_USE_THEME_MATERIAL
        "\nMaterial"
#endif

#if LV_USE_THEME_ALIEN
        "\nAlien"
#endif

#if LV_USE_THEME_ZEN
        "\nZen"
#endif

#if LV_USE_THEME_NEMO
        "\nNemo"
#endif

#if LV_USE_THEME_MONO
        "\nMono"
#endif

#if LV_USE_THEME_DEFAULT
        "\nDefault"
#endif
        ""
};

static lv_theme_t * themes[8];

/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void toolbox_win_init(lv_obj_t * parent)
{
    init_all_themes(0);
    th_act = themes[0];
    lv_theme_set_current(th_act);


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

    list_btn = lv_list_add_btn(list, LV_SYMBOL_EDIT,  "Label");
    lv_obj_set_event_cb(list_btn, create_label_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK,  "Button");
    lv_obj_set_event_cb(list_btn, create_btn_cb);
    
    list_btn = lv_list_add_btn(list, LV_SYMBOL_OK, "CheckBox");
    lv_obj_set_event_cb(list_btn, create_cb_cb);
    
    list_btn = lv_list_add_btn(list, LV_SYMBOL_LIST, "DDList");
    lv_obj_set_event_cb(list_btn, create_ddlist_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_MINUS, "Bar");
    lv_obj_set_event_cb(list_btn, create_bar_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_DRIVE, "Gauge");
    lv_obj_set_event_cb(list_btn, create_gauge_cb);
    
    list_btn = lv_list_add_btn(list, LV_SYMBOL_POWER, "Led");
    lv_obj_set_event_cb(list_btn, create_led_cb);

    // list_btn = lv_list_add_btn(list, LV_SYMBOL_PLUS, "Line");
    // lv_obj_set_event_cb(list_btn, create_line_cb);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_PLAY, "Slider");
    lv_obj_set_event_cb(list_btn, create_slider_cb);
    // lv_list_add_btn(list, LV_SYMBOL_CHARGE, "Edit");
    // lv_list_add_btn(list, LV_SYMBOL_DIRECTORY,  "Cut");
    // lv_list_add_btn(list, LV_SYMBOL_COPY, "Copy");


    lv_obj_t * th_cont = lv_cont_create(toolbox_win, NULL);
    lv_obj_align(th_cont, list, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 35);
    lv_cont_set_fit(th_cont, LV_FIT_TIGHT);
    lv_cont_set_layout(th_cont, LV_LAYOUT_ROW_M);

    // lv_obj_t * th_la = lv_label_create(th_cont, NULL);
    // lv_label_set_text(th_la, "THEME&HUE\n");

    lv_obj_t * th_roller = lv_roller_create(th_cont, NULL);
    lv_roller_set_options(th_roller, th_options, true);
    lv_obj_set_event_cb(th_roller, theme_select_event_handler);

    lv_obj_t * hue_roller = lv_roller_create(th_cont, NULL);
    lv_roller_set_options(hue_roller, "0\n30\n60\n90\n120\n150\n180\n210\n240\n270\n300\n330", true);
    lv_obj_set_event_cb(hue_roller, hue_select_event_cb);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
// static void widgetview_init(lv_obj_t * toolbox_win)



static void create_label_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_label_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        last_widget = new;
        lv_obj_set_drag(new, true);
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);
        
        widget_set_info(new, WIDGET_TYPE_LABEL);
        layerview_add(layerview_get_sel_layer(), new);
    }
}


static void create_btn_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        printf("1\n");
        lv_obj_t * par = layerview_get_sel_obj();
        printf("1.2\n");
        if(par == NULL) return;
        lv_obj_t * new = lv_btn_create(par, NULL);
        printf("1.3\n");
        // lv_label_set_text(lv_label_create(new, NULL), "Button");
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        if (par != tft_win)
        {
            lv_obj_set_drag_parent(new, true);
        }else
        {
            lv_obj_set_drag(new, true);
        }
        last_widget = new;
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);
        
        // widget_info_t * info = (widget_info_t *)malloc(sizeof(widget_info_t));
        // info->type = WIDGET_TYPE_BTN;
        // sprintf(info->id, "%s_%d", "btn", widget_count++);
        // lv_obj_set_user_data(new, info);
        widget_set_info(new, WIDGET_TYPE_BTN);
        layerview_add(layerview_get_sel_layer(), new);
    }

}

static void create_cb_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_cb_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        last_widget = new;
        lv_obj_set_drag(new, true);
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);

        widget_set_info(new, WIDGET_TYPE_CB);
        layerview_add(layerview_get_sel_layer(), new);   
    }
}

static void create_ddlist_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_ddlist_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        last_widget = new;
        if (par != tft_win)
        {
            lv_obj_set_drag_parent(new, true);
        }else
        {
            lv_obj_set_drag(new, true);
        }
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);

        lv_obj_t * scrl = lv_page_get_scrl(new);
        lv_obj_set_drag_parent(scrl, true);

        widget_set_info(new, WIDGET_TYPE_DDLIST);
        layerview_add(layerview_get_sel_layer(), new);          
    }
}

static void create_bar_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_bar_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }

        lv_bar_set_anim_time(new, 10000);
        lv_bar_set_value(new, 100, LV_ANIM_ON);
        last_widget = new;
        lv_obj_set_drag(new, true);
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);

        widget_set_info(new, WIDGET_TYPE_BAR);
        layerview_add(layerview_get_sel_layer(), new);     
    }
}

static void create_led_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_led_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        last_widget = new;
        if (par != tft_win)
        {
            lv_obj_set_drag_parent(new, true);
        }else
        {
            lv_obj_set_drag(new, true);
        }
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);

        widget_set_info(new, WIDGET_TYPE_LED);
        layerview_add(layerview_get_sel_layer(), new);         
    }
}

static void create_gauge_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_gauge_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        last_widget = new;
        if (par != tft_win)
        {
            lv_obj_set_drag_parent(new, true);
        }else
        {
            lv_obj_set_drag(new, true);
        }
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);

        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        
        widget_set_info(new, WIDGET_TYPE_GAUGE);
        layerview_add(layerview_get_sel_layer(), new);       
    }
}

// static void create_line_cb(lv_obj_t * obj, lv_event_t ev)
// {
//     (void)obj;
//     if(ev == LV_EVENT_CLICKED)
//     {
//         lv_obj_t * new = lv_line_create(tft_win, NULL);
//         if(last_widget != NULL)
//         {
//             lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
//             lv_point_t p[2] = {{LV_DPI, LV_DPI}, {LV_DPI + 10, LV_DPI + 10}};
//             lv_line_set_points(new, p, 2);
//         }
//      last_widget = new;     
//         lv_obj_set_drag(new, true);
//         lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
//         lv_obj_set_event_cb(new, update_setting);
//     }
// }

static void create_slider_cb(lv_obj_t * obj, lv_event_t ev)
{
    (void)obj;
    if(ev == LV_EVENT_CLICKED)
    {
        lv_obj_t * par = layerview_get_sel_obj();
        if(par == NULL) return;
        lv_obj_t * new = lv_slider_create(par, NULL);
        if(last_widget != NULL)
        {
            lv_obj_set_pos(new, lv_obj_get_x(last_widget) + 10, lv_obj_get_y(last_widget) + 10);
        }
        last_widget = new;
        if (par != tft_win)
        {
            lv_obj_set_drag_parent(new, true);
        }else
        {
            lv_obj_set_drag(new, true);
        }
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        lv_obj_set_event_cb(new, update_setting);

        lv_obj_set_drag(new, true);
        lv_obj_set_event_cb(new, update_setting);
        lv_obj_set_protect(new, LV_PROTECT_PRESS_LOST);
        
        widget_set_info(new, WIDGET_TYPE_SLIDER);
        layerview_add(layerview_get_sel_layer(), new);
    }
}


static void update_setting(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_DRAG_END)
    {
        setting_attr_mod(obj);
    }
}

static void create_undo(lv_obj_t * obj, lv_event_t ev)
{
    if(ev == LV_EVENT_CLICKED)
    {
        layerview_del_sel();
        last_widget = NULL;
    }
}













static void theme_select_event_handler(lv_obj_t * roller, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        // lv_coord_t hres = lv_disp_get_hor_res(NULL);
        // lv_coord_t vres = lv_disp_get_ver_res(NULL);

        uint16_t opt = lv_roller_get_selected(roller);
        th_act = themes[opt];
        lv_theme_set_current(th_act);

        // lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
        // lv_obj_align(sb, header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    // if(hres > vres) {
    //     lv_obj_set_size(content, hres - lv_obj_get_width(sb), vres - lv_obj_get_height(header));
    //     lv_obj_set_pos(content,  lv_obj_get_width(sb), lv_obj_get_height(header));
    // } else {
    //     lv_obj_set_size(content, hres , vres / 2);
    //     lv_obj_set_pos(content,  0, vres / 2);
    // }

        // lv_page_focus(sb, roller, LV_ANIM_ON);
    }
}


static void hue_select_event_cb(lv_obj_t * roller, lv_event_t event)
{

    if(event == LV_EVENT_VALUE_CHANGED) {
        uint16_t hue = lv_roller_get_selected(roller) * 30;

        init_all_themes(hue);

        lv_theme_set_current(th_act);

        // lv_page_focus(sb, roller, LV_ANIM_ON);
    }
}


static void init_all_themes(uint16_t hue)
{
    /* NOTE: This must be adjusted if more themes are added. */
    int i = 0;
#if LV_USE_THEME_NIGHT
    themes[i++] = lv_theme_night_init(hue, NULL);
#endif

#if LV_USE_THEME_MATERIAL
    themes[i++] = lv_theme_material_init(hue, NULL);
#endif

#if LV_USE_THEME_ALIEN
    themes[i++] = lv_theme_alien_init(hue, NULL);
#endif

#if LV_USE_THEME_ZEN
    themes[i++] = lv_theme_zen_init(hue, NULL);
#endif

#if LV_USE_THEME_NEMO
    themes[i++] = lv_theme_nemo_init(hue, NULL);
#endif

#if LV_USE_THEME_MONO
    themes[i++] = lv_theme_mono_init(hue, NULL);
#endif

#if LV_USE_THEME_DEFAULT
    themes[i++] = lv_theme_default_init(hue, NULL);
#endif
}




