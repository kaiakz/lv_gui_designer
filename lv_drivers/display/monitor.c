/**
 * @file monitor.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "monitor.h"
#if USE_MONITOR

#ifndef MONITOR_SDL_INCLUDE_PATH
#  define MONITOR_SDL_INCLUDE_PATH <SDL2/SDL.h>
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include MONITOR_SDL_INCLUDE_PATH
#include "lvgl/lv_core/lv_vdb.h"
#include "../indev/mouse.h"
#include "../indev/keyboard.h"
#include "../indev/mousewheel.h"

/*********************
 *      DEFINES
 *********************/
#define SDL_REFR_PERIOD     50  /*ms*/

#ifndef MONITOR_ZOOM
#define MONITOR_ZOOM        1
#endif

#if defined(__APPLE__) && defined(TARGET_OS_MAC)
#  if __APPLE__ && TARGET_OS_MAC
#define MONITOR_APPLE
#  endif
#endif

#if defined(__EMSCRIPTEN__)
#  define MONITOR_EMSCRIPTEN
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static int monitor_sdl_refr_thread(void * param);


/***********************
 *   GLOBAL PROTOTYPES
 ***********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static SDL_Window * window;
static SDL_Renderer * renderer;
static SDL_Texture * texture;
static uint32_t tft_fb[MONITOR_HOR_RES * MONITOR_VER_RES];
#if MONITOR_DOUBLE_BUFFERED
#if LV_VDB_SIZE != (LV_HOR_RES * LV_VER_RES) || LV_VDB_DOUBLE == 0 || LV_COLOR_DEPTH != 32
#error "MONITOR_DOUBLE_BUFFERED requires LV_VDB_SIZE = (LV_HOR_RES * LV_VER_RES) and  LV_VDB_DOUBLE = 1 and LV_COLOR_DEPTH = 32"
#endif
static uint32_t tft_fb2[MONITOR_HOR_RES * MONITOR_VER_RES];
static uint32_t * tft_fb_act;
#endif
static volatile bool sdl_inited = false;
static volatile bool sdl_refr_qry = false;
static volatile bool sdl_quit_qry = false;

int quit_filter(void * userdata, SDL_Event * event);
static void monitor_sdl_clean_up(void);
static void monitor_sdl_init(void);
#ifdef MONITOR_EMSCRIPTEN
void monitor_sdl_refr_core(void); /* called from Emscripten loop */
#else
static void monitor_sdl_refr_core(void);
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the monitor
 */
void monitor_init(void)
{
    /*OSX needs to initialize SDL here*/
#if defined(MONITOR_APPLE) || defined(MONITOR_EMSCRIPTEN)
    monitor_sdl_init();
#endif

#ifndef MONITOR_EMSCRIPTEN
    SDL_CreateThread(monitor_sdl_refr_thread, "sdl_refr", NULL);
    while(sdl_inited == false); /*Wait until 'sdl_refr' initializes the SDL*/
#endif
}


/**
 * Flush a buffer to the display. Calls 'lv_flush_ready()' when finished
 * @param x1 left coordinate
 * @param y1 top coordinate
 * @param x2 right coordinate
 * @param y2 bottom coordinate
 * @param color_p array of colors to be flushed
 */
void monitor_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
    /*Return if the area is out the screen*/
    if(x2 < 0 || y2 < 0 || x1 > MONITOR_HOR_RES - 1 || y1 > MONITOR_VER_RES - 1) {
        lv_flush_ready();
        return;
    }

#if MONITOR_DOUBLE_BUFFERED
    tft_fb_act = (uint32_t *)color_p;

    sdl_refr_qry = true;

    /*IMPORTANT! It must be called to tell the system the flush is ready*/
    lv_flush_ready();
#else

    int32_t y;
#if LV_COLOR_DEPTH != 24 && LV_COLOR_DEPTH != 32    /*32 is valid but support 24 for backward compatibility too*/
    int32_t x;
    for(y = y1; y <= y2; y++) {
        for(x = x1; x <= x2; x++) {
            tft_fb[y * MONITOR_HOR_RES + x] = lv_color_to32(*color_p);
            color_p++;
        }

    }
#else
    uint32_t w = x2 - x1 + 1;
    for(y = y1; y <= y2; y++) {
        memcpy(&tft_fb[y * MONITOR_HOR_RES + x1], color_p, w * sizeof(lv_color_t));

        color_p += w;
    }
#endif

    sdl_refr_qry = true;

    /*IMPORTANT! It must be called to tell the system the flush is ready*/
    lv_flush_ready();
#endif
}


/**
 * Fill out the marked area with a color
 * @param x1 left coordinate
 * @param y1 top coordinate
 * @param x2 right coordinate
 * @param y2 bottom coordinate
 * @param color fill color
 */
void monitor_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
    /*Return if the area is out the screen*/
    if(x2 < 0) return;
    if(y2 < 0) return;
    if(x1 > MONITOR_HOR_RES - 1) return;
    if(y1 > MONITOR_VER_RES - 1) return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = x1 < 0 ? 0 : x1;
    int32_t act_y1 = y1 < 0 ? 0 : y1;
    int32_t act_x2 = x2 > MONITOR_HOR_RES - 1 ? MONITOR_HOR_RES - 1 : x2;
    int32_t act_y2 = y2 > MONITOR_VER_RES - 1 ? MONITOR_VER_RES - 1 : y2;

    int32_t x;
    int32_t y;
    uint32_t color32 = lv_color_to32(color);

    for(x = act_x1; x <= act_x2; x++) {
        for(y = act_y1; y <= act_y2; y++) {
            tft_fb[y * MONITOR_HOR_RES + x] = color32;
        }
    }

    sdl_refr_qry = true;
}

/**
 * Put a color map to the marked area
 * @param x1 left coordinate
 * @param y1 top coordinate
 * @param x2 right coordinate
 * @param y2 bottom coordinate
 * @param color_p an array of colors
 */
void monitor_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
    /*Return if the area is out the screen*/
    if(x2 < 0) return;
    if(y2 < 0) return;
    if(x1 > MONITOR_HOR_RES - 1) return;
    if(y1 > MONITOR_VER_RES - 1) return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = x1 < 0 ? 0 : x1;
    int32_t act_y1 = y1 < 0 ? 0 : y1;
    int32_t act_x2 = x2 > MONITOR_HOR_RES - 1 ? MONITOR_HOR_RES - 1 : x2;
    int32_t act_y2 = y2 > MONITOR_VER_RES - 1 ? MONITOR_VER_RES - 1 : y2;

    int32_t x;
    int32_t y;

    for(y = act_y1; y <= act_y2; y++) {
        for(x = act_x1; x <= act_x2; x++) {
            tft_fb[y * MONITOR_HOR_RES + x] = lv_color_to32(*color_p);
            color_p++;
        }

        color_p += x2 - act_x2;
    }

    sdl_refr_qry = true;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * SDL main thread. All SDL related task have to be handled here!
 * It initializes SDL, handles drawing and the mouse.
 */

static int monitor_sdl_refr_thread(void * param)
{
    (void)param;

    /*If not OSX initialize SDL in the Thread*/
#ifndef MONITOR_APPLE
    monitor_sdl_init();
#endif
    /*Run until quit event not arrives*/
    while(sdl_quit_qry == false) {
        /*Refresh handling*/
        monitor_sdl_refr_core();
    }

    monitor_sdl_clean_up();
    exit(0);

    return 0;
}

int quit_filter(void * userdata, SDL_Event * event)
{
    (void)userdata;

    if(event->type == SDL_QUIT) {
        sdl_quit_qry = true;
    }

    return 1;
}

static void monitor_sdl_clean_up(void)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void monitor_sdl_init(void)
{
    /*Initialize the SDL*/
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetEventFilter(quit_filter, NULL);

    window = SDL_CreateWindow("TFT Simulator",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              MONITOR_HOR_RES * MONITOR_ZOOM, MONITOR_VER_RES * MONITOR_ZOOM, 0);       /*last param. SDL_WINDOW_BORDERLESS to hide borders*/

#if MONITOR_VIRTUAL_MACHINE || defined(MONITOR_EMSCRIPTEN)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
#else
    renderer = SDL_CreateRenderer(window, -1, 0);
#endif
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, MONITOR_HOR_RES, MONITOR_VER_RES);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    /*Initialize the frame buffer to gray (77 is an empirical value) */
    memset(tft_fb, 0x44, MONITOR_HOR_RES * MONITOR_VER_RES * sizeof(uint32_t));
#if MONITOR_DOUBLE_BUFFERED
    memset(tft_fb2, 0xbb, MONITOR_HOR_RES * MONITOR_VER_RES * sizeof(uint32_t));
#if LV_VDB_ADR == LV_VDB_ADR_INV && LV_VDB2_ADR == LV_VDB_ADR_INV
    lv_vdb_set_adr(tft_fb, tft_fb2);
#endif
    tft_fb_act = tft_fb;
#endif
    SDL_UpdateTexture(texture, NULL, tft_fb, MONITOR_HOR_RES * sizeof(uint32_t));
    sdl_refr_qry = true;
    sdl_inited = true;
}

#ifdef MONITOR_EMSCRIPTEN
void monitor_sdl_refr_core(void)
#else
static void monitor_sdl_refr_core(void)
#endif
{
    if(sdl_refr_qry != false) {
        sdl_refr_qry = false;

#if MONITOR_DOUBLE_BUFFERED == 0
        SDL_UpdateTexture(texture, NULL, tft_fb, MONITOR_HOR_RES * sizeof(uint32_t));
#else
        SDL_UpdateTexture(texture, NULL, tft_fb_act, MONITOR_HOR_RES * sizeof(uint32_t));
#endif
        SDL_RenderClear(renderer);
        /*Test: Draw a background to test transparent screens (LV_COLOR_SCREEN_TRANSP)*/
//        SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
//        SDL_Rect r;
//        r.x = 0; r.y = 0; r.w = MONITOR_HOR_RES; r.w = MONITOR_VER_RES;
//        SDL_RenderDrawRect(renderer, &r);

        /*Update the renderer with the texture containing the rendered image*/
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
#if !defined(MONITOR_APPLE) && !defined(MONITOR_EMSCRIPTEN)
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
#if USE_MOUSE != 0
        mouse_handler(&event);
#endif

#if USE_MOUSEWHEEL != 0
        mousewheel_handler(&event);
#endif

#if USE_KEYBOARD
        keyboard_handler(&event);
#endif
        if((&event)->type == SDL_WINDOWEVENT) {
            switch((&event)->window.event) {
#if SDL_VERSION_ATLEAST(2, 0, 5)
                case SDL_WINDOWEVENT_TAKE_FOCUS:
#endif
                case SDL_WINDOWEVENT_EXPOSED:
#if MONITOR_DOUBLE_BUFFERED == 0
                    SDL_UpdateTexture(texture, NULL, tft_fb, MONITOR_HOR_RES * sizeof(uint32_t));
#else
                    SDL_UpdateTexture(texture, NULL, tft_fb_act, MONITOR_HOR_RES * sizeof(uint32_t));
#endif
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    break;
                default:
                    break;
            }
        }
    }
#endif /*MONITOR_APPLE*/

    /*Sleep some time*/
    SDL_Delay(SDL_REFR_PERIOD);

}

#endif /*USE_MONITOR*/
