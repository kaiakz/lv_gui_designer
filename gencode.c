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
#define strBOOL(x) x==0?"false":"true"

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
char obj_code_templ[][60] = {
    "lv_obj_create(%s, %s);\n",
    "lv_obj_set_x(%s, %s);\n",
    "lv_obj_set_y(%s, %s);\n",
};

/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/


/**********************
 *   STATIC FUNCTIONS
 **********************/
static void getcode_obj()
{
    char tmp[300];
    snprintf(tmp, sizeof(tmp), obj_code_templ[1],lv_obj_get_x() , );
}

