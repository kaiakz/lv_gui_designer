/**
 * @dataset .c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <malloc.h>
#include "dataset.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/
typedef struct _widget_stack_t_{
    lv_obj_t * widget;
    struct widget_stack * next;
}widget_stack_t;

typedef enum
{
    WIDGET_TYPE_OBJ,
    WIDGET_TYPE_BTN,
    WIDGET_TYPE_CB,
    WIDGET_TYPE_LB,
}widget_type_t;

typedef struct _widget_info_t_
{
    char id[16];
    widget_type_t type;
    // lv_obj_t * align_to;
    // lv_align_t alian_type;
    
}widget_info_t;




/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
static widget_stack_t * wstack = NULL;

/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
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

lv_obj_t * wstack_top(void)
{
    if(wstack != NULL) return wstack->widget;
    return NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


