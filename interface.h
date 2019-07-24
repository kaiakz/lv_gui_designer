/**
 * @interface .h
 *
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

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

void lv_gui_designer(void);

/**********************
 *      MACROS
 **********************/


// #endif /*USE_LV_*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _INTERFACE_H_ */





