#include "saveproj.h"
#include <mxml.h>
#include "dataset.h"

static void widget2xml_traverse(lv_obj_t * par, mxml_node_t * par_node);

void save_project(lv_obj_t * tft_win)
{
    mxml_node_t * xml_root = mxmlNewXML("1.0");
    widget2xml_traverse(tft_win, xml_root);
    printf("Create OK");
    FILE * fp = fopen("save.xml", "w");

    mxmlSaveFile(xml_root, fp, MXML_NO_CALLBACK);
    fclose(fp);
}

static void widget2xml_traverse(lv_obj_t * par, mxml_node_t * par_node)
{
    lv_obj_t * i;
    mxml_node_t * node;
    widget_info_t * info;
    LV_LL_READ(par->child_ll, i)
    {
        // info = lv_obj_get_user_data(i);
        // node = mxmlNewElement(par_node, widget_get_type_name(info->type));
        printf("HELLO %d\n", (int)i);
        node = mxmlNewElement(par_node, "BOY");
        widget2xml_traverse(i, node);
    }
}