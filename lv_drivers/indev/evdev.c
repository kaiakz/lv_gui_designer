/**
 * @file evdev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "evdev.h"
#if USE_EVDEV != 0

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
int map(int x, int in_min, int in_max, int out_min, int out_max);

/**********************
 *  STATIC VARIABLES
 **********************/
int evdev_fd;
int evdev_root_x;
int evdev_root_y;
int evdev_button;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the evdev interface
 */
void evdev_init(void)
{
    evdev_fd = open(EVDEV_NAME, O_RDWR | O_NOCTTY | O_NDELAY);
    if(evdev_fd == -1) {
        perror("unable open evdev interface:");
        return;
    }

    fcntl(evdev_fd, F_SETFL, O_ASYNC | O_NONBLOCK);

    evdev_root_x = 0;
    evdev_root_y = 0;
    evdev_button = LV_INDEV_STATE_REL;
}
/**
 * reconfigure the device file for evdev
 * @param dev_name set the evdev device filename
 * @return true: the device file set complete
 *         false: the device file doesn't exist current system
 */
bool evdev_set_file(char* dev_name)
{ 
     if(evdev_fd != -1) {
        close(evdev_fd);
     }
     evdev_fd = open(dev_name, O_RDWR | O_NOCTTY | O_NDELAY);

     if(evdev_fd == -1) {
        perror("unable open evdev interface:");
        return false;
     }

     fcntl(evdev_fd, F_SETFL, O_ASYNC | O_NONBLOCK);

     evdev_root_x = 0;
     evdev_root_y = 0;
     evdev_button = LV_INDEV_STATE_REL;

     return true;
}
/**
 * Get the current position and state of the evdev
 * @param data store the evdev data here
 * @return false: because the points are not buffered, so no more data to be read
 */
bool evdev_read(lv_indev_data_t * data)
{
    struct input_event in;

    while(read(evdev_fd, &in, sizeof(struct input_event)) > 0) {
        if(in.type == EV_REL) {
            if(in.code == REL_X)
				#if EVDEV_SWAP_AXES
					evdev_root_y += in.value;
				#else
					evdev_root_x += in.value;
				#endif
            else if(in.code == REL_Y)
				#if EVDEV_SWAP_AXES
					evdev_root_x += in.value;
				#else
					evdev_root_y += in.value;
				#endif
        } else if(in.type == EV_ABS) {
            if(in.code == ABS_X)
				#if EVDEV_SWAP_AXES
					evdev_root_y = in.value;
				#else
					evdev_root_x = in.value;
				#endif
            else if(in.code == ABS_Y)
				#if EVDEV_SWAP_AXES
					evdev_root_x = in.value;
				#else
					evdev_root_y = in.value;
				#endif
        } else if(in.type == EV_KEY) {
            if(in.code == BTN_MOUSE || in.code == BTN_TOUCH) {
                if(in.value == 0)
                    evdev_button = LV_INDEV_STATE_REL;
                else if(in.value == 1)
                    evdev_button = LV_INDEV_STATE_PR;
            }
        }
    }

    /*Store the collected data*/

#if EVDEV_SCALE
    data->point.x = map(evdev_root_x, 0, EVDEV_SCALE_HOR_RES, 0, LV_HOR_RES);
    data->point.y = map(evdev_root_y, 0, EVDEV_SCALE_VER_RES, 0, LV_VER_RES);
#else
#if EVDEV_CALIBRATE
	data->point.x = map(evdev_root_x, EVDEV_HOR_MIN, EVDEV_HOR_MAX, 0, LV_HOR_RES);
	data->point.y = map(evdev_root_y, EVDEV_VER_MIN, EVDEV_VER_MAX, 0, LV_VER_RES);
#else
    data->point.x = evdev_root_x;
    data->point.y = evdev_root_y;
#endif
#endif

    data->state = evdev_button;

    if(data->point.x < 0)
      data->point.x = 0;
    if(data->point.y < 0)
      data->point.y = 0;
    if(data->point.x >= LV_HOR_RES)
      data->point.x = LV_HOR_RES - 1;
    if(data->point.y >= LV_VER_RES)
      data->point.y = LV_VER_RES - 1;

    return false;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif
