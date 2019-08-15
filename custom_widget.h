/**
 * @file gencode.h
 *
 */

#ifndef _CUSTOM_WIDGET_H_
#define _CUSTOM_WIDGET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "./lvgl/lvgl.h"
#include "./lv_ex_conf.h"
#endif



/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct 
{
    lv_cont_ext_t cont;
    lv_obj_t * title;
    lv_obj_t * bind;
    lv_obj_t * left, * right;     //Brother LayerView
    lv_obj_t * child;       //Child LayerView
}layerview_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


lv_obj_t * tbox_create(lv_obj_t * par, char * title);
lv_obj_t * tbox_get_ta(lv_obj_t * tbox);

lv_obj_t * layerview_init(lv_obj_t * win);
lv_obj_t * layerview_add(lv_obj_t * par, lv_obj_t * obj);
void layerview_add_bro(lv_obj_t * left_layer, lv_obj_t * layer);
lv_obj_t * layerview_get_sel_obj(void);
lv_obj_t * layerview_get_sel_layer(void);
void layerview_del_sel(void);
lv_obj_t * layerview_get_base(void);
/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif