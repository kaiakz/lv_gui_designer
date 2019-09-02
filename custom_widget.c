#include "custom_widget.h"
#include "dataset.h"
#include "setting.h"
#include <stdio.h>
typedef struct 
{
    lv_cont_ext_t cont;
    lv_obj_t * title;
    lv_obj_t * ta;
    lv_obj_t * lb_plus;
    lv_obj_t * lb_minus;
}tbox_ext_t;

lv_obj_t * layerview_base = NULL;
lv_obj_t * scr1 = NULL;
lv_obj_t * sel_layer = NULL;


static void update_sel_cb(lv_obj_t * obj, lv_event_t ev);


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

lv_obj_t * layerview_init(lv_obj_t * win)  //This is only a layer
{
    lv_obj_t * layer_base = lv_cont_create(win, NULL);
    lv_cont_set_fit4(layer_base, LV_FIT_FLOOD, LV_FIT_FLOOD, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_layout(layer_base, LV_LAYOUT_PRETTY);

    lv_obj_t * title = lv_label_create(layer_base, NULL);
    lv_label_set_text(title, "[Layer View]");

    layerview_base = layer_base;
    return layer_base;
    //todo:Del Button

}

//Create a newlayer by a obj on Simulator, use obj's TYPE && ID to set title
lv_obj_t * layerview_add(lv_obj_t * par_layer, lv_obj_t * obj)   
{
    if(par_layer == NULL)
    {
        return NULL;
    }
    lv_obj_t * layer = lv_cont_create(par_layer, NULL);
    lv_cont_set_fit4(layer, LV_FIT_FLOOD, LV_FIT_FLOOD, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_layout(layer, LV_LAYOUT_COL_L);

    layerview_ext_t * ext = lv_obj_allocate_ext_attr(layer, sizeof(layerview_ext_t));

    ext->bind = obj;
    ext->title = lv_label_create(layer, NULL);
    ext->child = NULL;
    ext->left = NULL;
    ext->right = NULL;

    widget_info_t * info = lv_obj_get_user_data(obj);
    // lv_obj_set_click(ext->title, true);
    // lv_obj_set_user_data(ext->title, obj);     //Bind label with obj by user_data
    
    lv_label_set_text(ext->title, widget_get_type_name(info->type));

    layerview_ext_t * par_ext = lv_obj_get_ext_attr(par_layer);
    if(par_ext->child == NULL)
    {
        par_ext->child = layer;
    }else
    {
        layerview_add_bro(layer, par_ext->child);
    }    


    lv_obj_set_event_cb(layer, update_sel_cb);

    return layer;
}

lv_obj_t * layerview_get_base(void)
{
    return layerview_base;
}

lv_obj_t * layerview_get_sel_obj(void)
{
    if (sel_layer)
    {
        layerview_ext_t * ext = lv_obj_get_ext_attr(sel_layer);
        return ext->bind;        
    }
    return NULL;
}

lv_obj_t * layerview_get_sel_layer(void)
{
    return sel_layer;
}


void layerview_add_bro(lv_obj_t * left_layer, lv_obj_t * layer)
{
    layerview_ext_t * left_ext = lv_obj_get_ext_attr(left_layer);
    if(left_ext->right == NULL)
    {
        layerview_ext_t * ext = lv_obj_get_ext_attr(layer);
        ext->left = left_layer;
        left_ext->right = layer;
    }else
    {
        layerview_add_bro(left_ext->right, layer);
    }
    
}

void layerview_del(lv_obj_t * layer)   //Delete a layer and its child && move its brother layer
{
    if(layer == NULL)
    {
        return;
    }
    lv_obj_t * par_layer = lv_obj_get_parent(layer);

    if(par_layer == layerview_base)     //Now we can't delete the screen(TFT Simulator)
    {
        return;
    }

    layerview_ext_t * par_ext = lv_obj_get_ext_attr(par_layer);
    layerview_ext_t * ext = lv_obj_get_ext_attr(layer);
    if(layer == par_ext->child)
    {
        par_ext->child = ext->right;
        
        if(ext->right != NULL)
        {
            layerview_ext_t * right_ext = lv_obj_get_ext_attr(ext->right);
            right_ext->left = NULL;            
        }
    }else
    {
        layerview_ext_t * left_ext = lv_obj_get_ext_attr(ext->left);
        left_ext->right = ext->right;
        if(ext->right != NULL)
        {
            layerview_ext_t * right_ext = lv_obj_get_ext_attr(ext->right);
            right_ext->left = ext->left;
        }
    }
    lv_obj_del(ext->bind);
    lv_obj_del(layer);
}

void layerview_del_sel(void)    //Delete the selected layer & bind obj
{
    layerview_del(sel_layer);
    sel_layer = NULL;
}

static void update_sel_cb(lv_obj_t * layer, lv_event_t ev)
{
    if(ev == LV_EVENT_CLICKED)
    {
        sel_layer = layer;
        layerview_ext_t * ext = lv_obj_get_ext_attr(layer);
        lb_selected_mod(ext->bind);
    }

}