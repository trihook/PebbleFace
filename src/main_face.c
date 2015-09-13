#if 0 

#include <pebble.h>
#include "main_face.h"
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18;
static GBitmap *s_res_image_bt_white;
static GFont s_res_roboto_condensed_21;
static TextLayer *s_textlayer_battery;
static BitmapLayer *s_bitmaplayer_bt;
static Layer *s_layer_main;
static TextLayer *s_textlayer_date;
static TextLayer *s_textlayer_ampm;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_image_bt_white = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_WHITE);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // s_textlayer_battery
  s_textlayer_battery = text_layer_create(GRect(71, 2, 55, 20));
  text_layer_set_background_color(s_textlayer_battery, GColorClear);
  text_layer_set_text_color(s_textlayer_battery, GColorWhite);
  text_layer_set_text(s_textlayer_battery, "100%");
  text_layer_set_text_alignment(s_textlayer_battery, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_battery, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_battery);
  
  // s_bitmaplayer_bt
  s_bitmaplayer_bt = bitmap_layer_create(GRect(127, 3, 16, 16));
  bitmap_layer_set_bitmap(s_bitmaplayer_bt, s_res_image_bt_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_bt);
  
  // s_layer_main
  s_layer_main = layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_layer_main);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(11, 7, 70, 48));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text_color(s_textlayer_date, GColorWhite);
  text_layer_set_text(s_textlayer_date, "Sunday");
  text_layer_set_font(s_textlayer_date, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_textlayer_ampm
  s_textlayer_ampm = text_layer_create(GRect(96, 29, 40, 30));
  text_layer_set_background_color(s_textlayer_ampm, GColorBlack);
  text_layer_set_text_color(s_textlayer_ampm, GColorWhite);
  text_layer_set_text(s_textlayer_ampm, "AM");
  text_layer_set_font(s_textlayer_ampm, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_ampm);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_battery);
  bitmap_layer_destroy(s_bitmaplayer_bt);
  layer_destroy(s_layer_main);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_ampm);
  gbitmap_destroy(s_res_image_bt_white);
}
// END AUTO-GENERATED UI CODE



static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_face(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_face(void) {
  window_stack_remove(s_window, true);
}


#endif