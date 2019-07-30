# lv_gui_designer

![image](https://github.com/kaiakz/lv_gui_designer/blob/dev/docs/image/sceenshot_lv_gui_designer_1.gif)
![image](https://github.com/kaiakz/lv_gui_designer/blob/dev/docs/image/sceenshot_lv_gui_designer_2.gif)

## What is lv_gui_designer?
lv_gui_designer is a drag-and-drop, simple GUI designer built with LittlevGL, and is based on [pc_simulator_sdl_eclipse](https://github.com/littlevgl/pc_simulator_sdl_eclipse). Its interface is built with LittlevGL.

## Feature
* Create object based on an object, Parent-child structure(In test, now if you want to create a obj, you need to choose a parent in layerview).
* Drag and drop to control the postion of the widget.
* TFT_simulator can be customized(size), supports mutiple windows.(To do)
* Modfied attribute(postion, size, click, etc) and style. (Doing)
* Save project in XML format.
* XML can be converted to C and Python: includes GUI and Callback. Just add a line "lv_gui_main();" to your code.(Doing)

## Get Start
* Download SDL from [https://www.libsdl.org/](https://www.libsdl.org/). 
* Git clone the project.
* **cd** into the folder, and **make**
* run **./lv_gui_designer**