#include "saveproj.h"
#include <mxml.h>
#include "dataset.h"
#include "custom_widget.h"

static void widget2xml_traverse(lv_obj_t * layer, mxml_node_t * par_node);


void save_project(lv_obj_t * par_layer)
{
    mxml_node_t * xml_root = mxmlNewXML("1.0");
    widget2xml_traverse(par_layer, xml_root);
    printf("Create OK");
    FILE * fp = fopen("save.xml", "w");

    mxmlSaveFile(xml_root, fp, MXML_NO_CALLBACK);
    fclose(fp);
}

static void widget2xml_traverse(lv_obj_t * layer, mxml_node_t * par_node)
{  
    layerview_ext_t * ext = lv_obj_get_ext_attr(layer);
    widget_info_t * info = lv_obj_get_user_data(ext->bind);
    mxml_node_t * node = mxmlNewElement(par_node, widget_get_type_name(info->type));

    lv_obj_t * child_layer = ext->child;

    while (child_layer)     //Iterate all children
    {
        widget2xml_traverse(child_layer, node);
        ext = lv_obj_get_ext_attr(child_layer);
        child_layer = ext->right;
    } 
}