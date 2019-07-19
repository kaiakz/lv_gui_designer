/**
 * @dataset .h
 *
 */

#ifndef _DATASET_H_
#define _DATASET_H_

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

// #if USE_LV_


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void wstack_push(lv_obj_t * new);
lv_obj_t * wstack_pop(void);
lv_obj_t * wstack_top(void);

/**********************
 *      MACROS
 **********************/


// #endif /*USE_LV_*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _H */
