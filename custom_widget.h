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

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t * layerview_create(lv_obj_t * par, char * txt);

lv_obj_t * tbox_create(lv_obj_t * par, char * title);
lv_obj_t * tbox_get_ta(lv_obj_t * tbox);
/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif