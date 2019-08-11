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
// typedef struct _widget_stack_t_{
//     lv_obj_t * widget;
//     struct _widget_stack_t_ * next;
// }widget_stack_t;

typedef struct _widget_deque_t_
{
    lv_obj_t * widget;
    struct _widget_deque_t_ * next, * prev;
}widget_deque_t;

const char * widget_type_name[10] = 
{
    "obj",
    "label",
    "btn",
    "cb",
    "ddlist",
    ""
};

typedef struct _widget_tree_node_t_
{
    lv_obj_t * widget;
    lv_obj_t * layer;
    struct _widget_tree_node_t_;
}widget_tree_node_t;



/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
// static widget_stack_t * wstack = NULL;
static widget_deque_t * wdeque_head = NULL;
static widget_deque_t * wdeque_tail = NULL;
static widget_deque_t * wdeque_traverse_sign = NULL;
/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
// void wstack_push(lv_obj_t * new)
// {
//     widget_stack_t * new_top = (widget_stack_t *)malloc(sizeof(widget_stack_t));
//     new_top->next = wstack;
//     new_top->widget = new;
//     wstack = new_top;
// }

// lv_obj_t * wstack_pop(void)
// {
//     if(wstack != NULL)
//     {
//         widget_stack_t * tmp = wstack;
//         wstack = wstack->next;
//         lv_obj_t * last = tmp->widget;
//         free(tmp);
//         return last;
//     }
//     return NULL;
// }

// lv_obj_t * wstack_top(void)
// {
//     if(wstack != NULL) return wstack->widget;
//     return NULL;
// }

void wdeque_pushback(lv_obj_t * new_obj)
{
    widget_deque_t * new_tail = (widget_deque_t *)malloc(sizeof(widget_deque_t));
    new_tail->widget = new_obj;
    if(wdeque_tail == NULL && wdeque_head == NULL)
    {
        new_tail->next = NULL;
        new_tail->prev = NULL;
        wdeque_head = new_tail;
        wdeque_tail = new_tail;
    }
    else{
        new_tail->next = NULL;
        wdeque_tail->next = new_tail;
        new_tail->prev = wdeque_tail;
        wdeque_tail = new_tail;
    }
    
}

lv_obj_t * wdeque_popback(void)
{
    if(wdeque_tail != wdeque_head)
    {
        widget_deque_t * tmp = wdeque_tail;
        wdeque_tail = wdeque_tail->prev;
        lv_obj_t * last = tmp->widget;
        free(tmp);
        return last;
    }else if(wdeque_head != NULL)
    {
        widget_deque_t * tmp = wdeque_tail;
        wdeque_tail = NULL;
        wdeque_head = NULL;
        lv_obj_t * last = tmp->widget;
        free(tmp);
        return last;        
    }
    return NULL;
}

lv_obj_t * wdeque_gettail(void)
{
    if(wdeque_head != NULL && wdeque_tail != NULL) return wdeque_tail->widget;
    return NULL;
}

lv_obj_t * wdeque_traverse(bool reset)
{
    if(reset == true) wdeque_traverse_sign = wdeque_head;
    lv_obj_t * data = NULL;
    if(wdeque_traverse_sign != NULL)
    {
        data = wdeque_traverse_sign->widget;
        wdeque_traverse_sign = wdeque_traverse_sign->next;
    } 
    return data;
}

const char * widget_get_type_name(widget_type_t type)
{
    return widget_type_name[type];
}

void widget_set_info(lv_obj_t * obj, widget_type_t t)
{
    widget_info_t * info = (widget_info_t *)malloc(sizeof(widget_info_t));
    info->type = t;
    strncpy(info->id, widget_get_type_name(t), 15);
    lv_obj_set_user_data(obj, info);
}



/**********************
 *   STATIC FUNCTIONS
 **********************/


