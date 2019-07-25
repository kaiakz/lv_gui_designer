#include "custom_widget.h"

typedef struct 
{
    lv_cont_ext_t cont;
    lv_obj_t * title;
    lv_obj_t * ta;
    lv_obj_t * lb_plus;
    lv_obj_t * lb_minus;
}tbox_ext_t;

lv_obj_t * layerview_create(lv_obj_t * par, char * txt)
{
    lv_obj_t * item = lv_cont_create(par, NULL);
    lv_cont_set_fit4(item, LV_FIT_FLOOD, LV_FIT_FLOOD, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_layout(item, LV_LAYOUT_COL_L);

    if(txt != NULL)
    {
        lv_obj_t * item_lb = lv_label_create(item, NULL);
        lv_label_set_text(item_lb, txt);        
    }
    return item;
}

lv_obj_t * tbox_create(lv_obj_t * par, char * title)
{
    lv_obj_t * cont = lv_cont_create(par, NULL);
    lv_cont_set_fit2(cont, LV_FIT_FLOOD, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_ROW_M);

    tbox_ext_t * ext = lv_obj_allocate_ext_attr(cont, sizeof(tbox_ext_t));
    ext->title = lv_label_create(cont, NULL);
    lv_label_set_text(ext->title, title);

    ext->ta = lv_ta_create(cont, NULL);
    lv_ta_set_one_line(ext->ta, true);
    lv_ta_set_text(ext->ta, "");
    lv_ta_set_cursor_type(ext->ta, LV_CURSOR_NONE);
    lv_ta_set_cursor_blink_time(ext->ta, 0);

    ext->lb_plus = lv_label_create(ext->ta, NULL);
    lv_label_set_text(ext->lb_plus, LV_SYMBOL_PLUS);
    lv_obj_align(ext->lb_plus, ext->ta, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_click(ext->lb_plus, true);

    ext->lb_minus = lv_label_create(ext->ta, ext->lb_plus);
    lv_label_set_text(ext->lb_minus, LV_SYMBOL_MINUS" ");
    lv_obj_align(ext->lb_minus, ext->lb_plus, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_set_click(ext->lb_minus, true);


    return cont;
}

lv_obj_t * tbox_get_ta(lv_obj_t * tbox)
{
    tbox_ext_t * ext = lv_obj_get_ext_attr(tbox);
    return ext->ta;
}