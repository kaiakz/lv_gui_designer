#include <mxml.h>
#include <stdio.h>
#include "loadproj.h"
#include "dataset.h"

typedef struct _widget_stack_t_{
    lv_obj_t * widget;
    struct _widget_stack_t_ * next;
}widget_stack_t;

static widget_stack_t * wstack = NULL;

static mxml_sax_cb_t sax_cb(mxml_node_t *node, mxml_sax_event_t event, void *data);
static void wstack_push(lv_obj_t * new);
static void wstack_pop(void);
static lv_obj_t * wstack_top(void);


void load_project(lv_obj_t * tft_win)
{
    FILE * fp = fopen("lgd.xml", "r");
    if(!fp)
    {
        printf("Project file not found!");
        return;
    }

    wstack_push(tft_win);
    mxml_node_t * sax_node = mxmlSAXLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK, sax_cb, NULL);
    fclose(fp);
}

static mxml_sax_cb_t sax_cb(mxml_node_t *node, mxml_sax_event_t event, void *data)
{
    if(event == MXML_SAX_ELEMENT_OPEN)
    {
        //create a new widget and PUSH to stack
        const char * element = mxmlGetElement(node);
        if(!strcmp(element, "BTN"))
        {
            lv_obj_t * obj = lv_btn_create(wstack_top(), NULL);
            wstack_push(obj);
            
        }
        if(!strcmp(element, "LABEL"))
        {
            lv_obj_t * obj = lv_label_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "LED"))
        {
            lv_obj_t * obj = lv_led_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "CHECKBOX"))
        {
            lv_obj_t * obj = lv_cb_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "BAR"))
        {
            lv_obj_t * obj = lv_bar_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "ROLLER"))
        {
            lv_obj_t * obj = lv_roller_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "DDLIST"))
        {
            lv_obj_t * obj = lv_ddlist_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "ARC"))
        {
            lv_obj_t * obj = lv_arc_create(wstack_top(), NULL);
            wstack_push(obj);
        }
        if(!strcmp(element, "CONTAINER"))
        {
            lv_obj_t * obj = lv_cont_create(wstack_top(), NULL);
            lv_cont_set_fit(obj, LV_FIT_FLOOD);
            lv_cont_set_layout(obj, LV_LAYOUT_PRETTY);  //TEST Attribute
            wstack_push(obj);
        }
        //Set Attribute
        int i, count;
        for (i = 0, count = mxmlElementGetAttrCount(node); i < count; i++)
        {
            const char * name, * value;
            value = mxmlElementGetAttrByIndex(node, i, &name);
            if(!strcmp(name, "x"))
            {
                lv_coord_t x = atoi(value);
                lv_obj_set_x(wstack_top(), x);
            }
            if(!strcmp(name, "y"))
            {
                lv_coord_t y = atoi(value);
                lv_obj_set_y(wstack_top(), y);
            }
            // if(!strcmp(name, "fit"))
            // {
            //     atoi(value);
            //     lv_obj_set_y(wstack_top(), y);
            // }       
        }
        
    }else if(event == MXML_SAX_ELEMENT_CLOSE)
    {
        //POP
        wstack_pop();
    }
}

static void wstack_push(lv_obj_t * new)
{
    widget_stack_t * new_top = (widget_stack_t *)malloc(sizeof(widget_stack_t));
    new_top->next = wstack;
    new_top->widget = new;
    wstack = new_top;
}

static void wstack_pop(void)
{
    if(wstack != NULL)
    {
        widget_stack_t * tmp = wstack;
        wstack = wstack->next;
        // lv_obj_t * last = tmp->widget;
        free(tmp);
    }
}

static lv_obj_t * wstack_top(void)
{
    if(wstack != NULL) return wstack->widget;
    return NULL;
}