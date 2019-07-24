/**
 * @gencode .c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "gencode.h"
#include "dataset.h"
#include <stdio.h>
#include <string.h>

/*********************
 *      DEFINES
 *********************/
#define bool2str(x) x==0?"false":"true"

/**********************
 *      TYPEDEFS
 **********************/
extern const char * widget_type_name[];
extern lv_obj_t * tft_win;
/**********************
 *  STATIC PROTOTYPES
 **********************/
static inline void code_header_write(FILE * lv_gui_h_fp);


static inline void code_source_write(FILE * lv_gui_c_fp);
static inline void code_source_head_write(FILE * lv_gui_c_fp);
static void code_source_body_write(FILE * lv_gui_c_fp);

static void src_write_obj_create(lv_obj_t * obj, FILE * lv_gui_c_fp);
/**********************
 *  STATIC VARIABLES
 **********************/
const char gui_main_name[] = "lv_gui_main";
// const static char lv_obj_src_templ[][60] = {
//     "lv_obj_create(%s, %s);\n",
//     "lv_obj_set_x(%s, %s);\n",
//     "lv_obj_set_y(%s, %s);\n",
//     "lv_obj_set_width(%s, %s);\n",
// };

// const static char lv_btn_src_templ[][60] = {
//     "lv_btn_create(%s, %s);\n",
//     "lv_btn_set"
// };

/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void code_generation(void)
{
    
    FILE * lv_gui_h_fp = fopen("lv_gui.h", "w");
    if (lv_gui_h_fp == NULL)
    {
        fclose(lv_gui_h_fp);
        return;
    }    
    code_header_write(lv_gui_h_fp);
    fclose(lv_gui_h_fp);
    
    FILE * lv_gui_c_fp = fopen("lv_gui.c", "w");
    if (lv_gui_c_fp == NULL)
    {
        fclose(lv_gui_c_fp);
        return;
    }    
    code_source_write(lv_gui_c_fp);
    fclose(lv_gui_c_fp);
    
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static inline void code_header_write(FILE * lv_gui_h_fp)
{
    fprintf(lv_gui_h_fp, "#ifndef _INTERFACE_H \n#define _INTERFACE_H \n\nvoid %s(void);\n\n\n#endif", gui_main_name);
}

static inline void code_source_write(FILE * lv_gui_c_fp)
{
    code_source_head_write(lv_gui_c_fp);
    code_source_body_write(lv_gui_c_fp);
}

static inline void code_source_head_write(FILE * lv_gui_c_fp)
{
    fputs("#include \"lvgl.h\"\n\n", lv_gui_c_fp);
}

static void code_source_body_write(FILE * lv_gui_c_fp)
{
    fprintf(lv_gui_c_fp, "void %s()\n{\n", gui_main_name);

    for (lv_obj_t * i = wdeque_traverse(true); i != NULL; i = wdeque_traverse(false))
    {
        src_write_obj_create(i, lv_gui_c_fp);
    }


    fputs("\n}\n", lv_gui_c_fp);
}

static void src_write_obj_create(lv_obj_t * obj, FILE * lv_gui_c_fp)
{
    widget_info_t * info = (widget_info_t *)lv_obj_get_user_data(obj);

    // lv_obj_t * parent = lv_obj_get_parent(obj);
    // if(parent == NULL || parent == tft_win)
    // {
    //     fprintf(lv_gui_c_fp, "lv_obj_t * %s = lv_%s_create(%s, %s);\n", info->id , widget_type_name[info->type], "lv_scr_act()", "NULL");
    //     return;
    // }    
    
    // widget_info_t * par_info = (widget_info_t *)lv_obj_get_user_data(parent);
    fprintf(lv_gui_c_fp, "    lv_obj_t * %s = lv_%s_create(%s, %s);\n", info->id , widget_type_name[info->type], "lv_scr_act()", "NULL");
}

static void src_write_obj_attr(lv_obj_t * obj, FILE * lv_gui_c_fp)
{

}