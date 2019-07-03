<h1 align="center"> LittlevGL - Open-source Embedded GUI Library</h1>
<p align="center">
<img src="https://img.shields.io/badge/licence-MIT-blue.svg">
<img src="https://img.shields.io/badge/version-v5.2-blue.svg">
<br>
<img src="https://littlevgl.com/github/cover3.gif">
</p>

<p align="center">
LittlevGL provides everything you need to create a Graphical User Interface (GUI) on embedded systems with easy-to-use graphical elements, beautiful visual effects and low memory footprint. 
</p>

<h4 align="center">
<a href="https://littlevgl.com">Website </a> &middot; 
<a href="https://littlevgl.com/live-demo">Live demo</a> &middot; 
<a href="https://docs.littlevgl.com/#PC-simulator">Simulator</a> &middot; 
<a href="https://docs.littlevgl.com/">Docs</a> &middot;
<a href="https://blog.littlevgl.com/">Blog</a>
</h4>

<!--
<p align="center">
:star: Star the project if you like it! And share with your friends <a href="https://twitter.com/intent/tweet?text=LittlevGL%20is%20a%20free%20and%20open%20source%20embedded%20GUI%20library%20with%20easy-to-use%20graphical%20elements,%20beautiful%20visual%20effects%20and%20low%20memory%20footprint.&url=https://littlevgl.com/&hashtags=littlevgl,embedded,gui,free,opensource"><img src="https://img.shields.io/twitter/url/http/shields.io.svg?style=social"></a>
</p>
-->

### Features
* **Powerful building blocks** buttons, charts, lists, sliders, images, etc.
* **Advanced graphics** with animations, anti-aliasing, opacity, smooth scrolling
* **Various input devices** touch pad, mouse, keyboard, encoder, buttons, etc.
* **Multi-language support** with UTF-8 encoding
* **Fully customizable** graphical elements
* **Hardware independent** to use with any microcontroller or display
* **Scalable** to operate with little memory (64 kB Flash, 10 kB RAM)
* **OS, External memory and GPU** supported but not required
* **Single frame buffer** operation even with advances graphical effects
* **Written in C** for maximal compatibility
* **Simulator** to develop on PC without embedded hardware
* **Tutorials, examples, themes** for rapid development
* **Documentation** and API references online

### Supported devices
Basically, every modern controller - which is able to drive a display - is suitable to run LittlevGL. The minimal requirements:
- **16, 32 or 64-bit** microcontroller or processor
- **&gt; 16 MHz** clock speed
- **&gt; 8 kB RAM for static data** and **&gt; 2 KB RAM for dynamic data** (graphical objects)
- **&gt; 64 kB flash** program memory
- **Optionally ~1/10 screen sized memory** for buffered drawing (on 240 × 320, 16-bit colors it's 15 kB)

Just to mention some **platforms**:
- STM32F1, STM32F3, [STM32F4](https://blog.littlevgl.com/2017-07-15/stm32f429_disco_port), [STM32F7](https://github.com/littlevgl/stm32f746_disco_no_os_sw4stm32)
- Microchip dsPIC33, PIC24, PIC32MX, PIC32MZ
- NXP Kinetis, LPC, iMX
- [Linux frame buffer](https://blog.littlevgl.com/2018-01-03/linux_fb) (/dev/fb)
- [Raspberry PI](http://www.vk3erw.com/index.php/16-software/63-raspberry-pi-official-7-touchscreen-and-littlevgl)
- [Espressif ESP32](https://github.com/littlevgl/esp32_ili9431)
- Nordic nrf52
- Quectell M66

### Quick start in a simulator
The easiest way to get started with LittlevGL is to run it in a simulator on your PC without any embedded hardware. 

Choose a project with your favourite IDE:

|   Eclipse   | CodeBlock  | Visual Studio | PlatfomIO | Qt Creator |
|-------------|----------- |---------------|-----------|------------|
|  [![Eclipse](https://littlevgl.com/logo/ide/eclipse.jpg)](https://github.com/littlevgl/pc_simulator_sdl_eclipse) | [![CodeBlocks](https://littlevgl.com/logo/ide/codeblocks.jpg)](https://github.com/littlevgl/pc_simulator_win_codeblocks) | [![VisualStudio](https://littlevgl.com/logo/ide/visualstudio.jpg)](https://github.com/littlevgl/visual_studio_2017_sdl_x64)   |   [![PlatformIO](https://littlevgl.com/logo/ide/platformio.jpg)](https://github.com/littlevgl/pc_simulator_sdl_platformio) | [![QtCreator](https://littlevgl.com/logo/ide/qtcreator.jpg)](https://blog.littlevgl.com/2019-01-03/qt-creator) |
| Cross-platform<br>with SDL | Native Windows | Cross-platform<br>with SDL | Cross-platform<br>with SDL | Cross-platform<br>with SDL |

### Porting to an embedded hardware
In the most simple case you need to do these steps:
1. Copy `lv_conf_templ.h` as `lv_conf.h` next to `lvgl` and set at least `LV_HOR_RES`, `LV_VER_RES` and `LV_COLOR_DEPTH`. 
2. Call `lv_tick_inc(x)` every `x` milliseconds in a Timer or Task (`x` should be between 1 and 10)
3. Call `lv_init()`
4. Register a function which can **copy a pixel array** to an area of the screen:
```c
lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
disp_drv.disp_flush = disp_flush;     /*Set your driver function*/
lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/
    
void disp_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
    int32_t x, y;
    for(y = y1; y <= y2; y++) {
        for(x = x1; x <= x2; x++) {
            sep_pixel(x, y, *color_p);  /* Put a pixel to the display.*/
            color_p++;
        }
    }

    lv_flush_ready();                  /* Tell you are ready with the flushing*/
}
    
```
5. Register a function which can **read an input device**. E.g. for a touch pad:
```c
lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
indev_drv.read = touchpad_read;            /*Set your driver function*/
lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/

bool touchpad_read(lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    /*Save the state and save the pressed cooridnate*/
    data->state = touchpad_is_pressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
    if(data->state == LV_INDEV_STATE_PR) touchpad_get_xy(&last_x, &last_y);
   
    /*Set the coordinates (if released use the last pressed cooridantes)*/
    data->point.x = last_x;
    data->point.y = last_y;

    return false; /*Return `false` because we are not buffering and no more data to read*/
}
```
6. Call `lv_task_handler()` periodically every few milliseconds.

For a detailed description check the [Online documatation](https://docs.littlevgl.com/#Porting) or the [Porting tutorial](https://github.com/littlevgl/lv_examples/blob/master/lv_tutorial/0_porting/lv_tutorial_porting.c)
 
 
### Code examples
#### Create a button with a label and assign a click callback
```c
lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
lv_obj_set_size(btn, 100, 50);                          /*Set its size*/

lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_action);/*Assign a callback to the button*/
lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
lv_label_set_text(label, "Button");                     /*Set the labels text*/

lv_res_t btn_action(lv_obj_t * btn)
{
    printf("Clicked\n");
    return LV_RES_OK;
}
```
![Simple button with LittelvGL](https://littlevgl.com/github/btn1.gif)

#### Modify the styles
```c
static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
style_btn_rel.body.border.color = LV_COLOR_HEX3(0x269);
style_btn_rel.body.border.width = 1;
style_btn_rel.body.main_color = LV_COLOR_HEX3(0xADF);
style_btn_rel.body.grad_color = LV_COLOR_HEX3(0x46B);
style_btn_rel.body.shadow.width = 4;
style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
style_btn_rel.text.color = LV_COLOR_HEX3(0xDEF);

static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from a built-in style*/
style_btn_pr.body.border.color = LV_COLOR_HEX3(0x46B);
style_btn_pr.body.main_color = LV_COLOR_HEX3(0x8BD);
style_btn_pr.body.grad_color = LV_COLOR_HEX3(0x24A);
style_btn_pr.body.shadow.width = 2;
style_btn_pr.text.color = LV_COLOR_HEX3(0xBCD);

lv_btn_set_style(btn, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the buton's released style*/
lv_btn_set_style(btn, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the buton's pressed style*/
```

![Simple button with LittelvGL](https://littlevgl.com/github/btn2.gif)

#### Enable a fancy effect
```c
/*Add some effects when the button is clicked*/
lv_btn_set_ink_in_time(btn, 300);
lv_btn_set_ink_wait_time(btn, 100);
lv_btn_set_ink_out_time(btn, 300);
```

![Simple button with LittelvGL](https://littlevgl.com/github/btn3.gif)

Check out the [Documentation](https://docs.littlevgl.com/) for more!

### Contributing
To ask questions and discuss topics we use [GitHub's Issue tracker](https://github.com/littlevgl/lvgl/issues). 
You contribute in several ways:
- **Answer other's question** click the Watch button on the top to get notified about the issues
- **Report and/or fix bugs** using the issue tracker and in Pull-request
- **Suggest and/or implement new features** using the issue tracker and in Pull-request
- **Improve and/or translate the documentation** learn more [here](https://github.com/littlevgl/docs)
- **Write a blog post about your experiences** learn more [here](https://github.com/littlevgl/blog)
- **Upload your project or product as a reference** to [this site](https://blog.littlevgl.com/2018-12-26/references)

Before contributing, please read [CONTRIBUTING.md](https://github.com/littlevgl/lvgl/blob/master/docs/CONTRIBUTING.md).  

### Donate
If you are pleased with the library, found it useful, or you are happy with the support you got, please help its further development:

[![Donate](https://littlevgl.com/donate_dir/donate_btn.png)](https://littlevgl.com/donate)
