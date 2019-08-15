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
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    WIDGET_TYPE_OBJ      = 0,
    WIDGET_TYPE_LABEL    = 1,
    WIDGET_TYPE_BTN      = 2,
    WIDGET_TYPE_CB       = 3,
    WIDGET_TYPE_DDLIST   = 4,
    WIDGET_TYPE_BAR      = 5,
    WIDGET_TYPE_LED      = 6,
    WIDGET_TYPE_GAUGE    = 7,
    WIDGET_TYPE_SLIDER   = 8,
}widget_type_t;

typedef struct
{
    uint8_t position : 1;
    uint8_t height : 1;
    uint8_t width : 1;
    uint8_t click : 1;
    uint8_t drag : 1;
}obj_attr_table_t;

typedef struct _widget_info_t_
{
    char id[16];
    widget_type_t type;
    // lv_obj_t * layer;
    // lv_obj_t * align_to;
    // lv_align_t alian_type;
    obj_attr_table_t attr;

}widget_info_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
// void wstack_push(lv_obj_t * new);
// lv_obj_t * wstack_pop(void);
// lv_obj_t * wstack_top(void);
// void wdeque_pushback(lv_obj_t * new_obj);
// lv_obj_t * wdeque_popback(void);
// lv_obj_t * wdeque_gettail(void);
// lv_obj_t * wdeque_traverse(bool reset);

const char * widget_get_type_name(widget_type_t type);
void widget_set_info(lv_obj_t * obj, widget_type_t t);
/**********************
 *      MACROS
 **********************/


// #endif /*USE_LV_*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _H */
