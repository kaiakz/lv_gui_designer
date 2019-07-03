/**
 * @file ST7565.h
 *
 */

#ifndef ST7565_H
#define ST7565_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif

#if USE_ST7565

#include <stdint.h>
#include "lvgl/lv_misc/lv_color.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void st7565_init(void);
void st7565_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
void st7565_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
void st7565_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);

/**********************
 *      MACROS
 **********************/

#endif /* USE_ST7565 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ST7565_H */
