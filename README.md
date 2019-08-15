# lv_gui_designer

![image](https://github.com/kaiakz/lv_gui_designer/blob/dev/docs/image/sceenshot_lv_gui_designer_1.gif)

## What is lv_gui_designer?
lv_gui_designer is a drag-and-drop, simple GUI designer built with LittlevGL, and is based on [pc_simulator_sdl_eclipse](https://github.com/littlevgl/pc_simulator_sdl_eclipse). Its interface is built with LittlevGL.

## Feature
* Create object based on an object, Parent-child structure(In test, now if you want to create a obj, you need to choose a parent in layerview).
* Drag and drop to control the postion of the widget.
* TFT_simulator can be customized(size), supports mutiple windows.(To do)
* Modfied attribute(postion, size, click, etc) and style. (Doing)
* Save project in XML format, project can be loaded as live-demo. 
* XML can be converted to C and Python: includes GUI and Callback. Just add a function `lv_gui_main` to your code.(Doing)

## Screenshot
Select a parent for a widget:
![image](https://github.com/kaiakz/lv_gui_designer/blob/dev/docs/image/treeview.gif)
Load XML File to live-demo(Beta), try to write some tags `<CONTAINER><BTN><LABEL><ARC><DDLIST>, etc`to design your GUI:
![image](https://github.com/kaiakz/lv_gui_designer/blob/dev/docs/image/load.gif)

## How it works?
lv_gui_designer is very dependent on LittlevGL v6.0:
* USE [EVENT](https://docs.littlevgl.com/en/html/overview/event.html)
* Three parts: Creator, Simulator, Setting, just three `lv_win` object.
* Creator: Select what widget you want to create at Simulator, and the widget will enable "drag" (lv_obj_set_drag & lv_obj_set_drag_parent), so we can drag-and-drop it. 
* Simulator: Only its child can be drag-and-drop, its grandchild is not a drag-able widget, for example, there are a Button on the Simulator with a Label, due to Button is a auto-align Container, Label will be sticked to Button's centre. Every widget on there has a callback function to transport some information to Settting.
* Setting: Select a widget on Simulator by LayerView, we can create a new son-widget on it and change its attribute, style, animation, we can delete it. 


## Get Start
### Prerequreies [SDL](https://www.libsdl.org/) & [Mini-XML](https://github.com/michaelrsweet/mxml)
* Git clone the project.
* **cd** into the folder, and **make** (Linux is fine)
* run **./lv_gui_designer**