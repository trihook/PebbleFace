#include <pebble.h>
#include "progressbar.h"
#include "main_face1.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_font_perfect_dos_48;
static GFont s_res_gothic_18;
static GFont s_res_roboto_condensed_21;
static GBitmap *s_res_image_bt_white;
static Layer *s_layer_main;
static Layer *s_canvaslayer_second;

/*
static void sencond_update_proc(Layer *layer, GContext *ctx)
{
  //Draw border
  GRect outer = layer_get_bounds(layer);

  GPoint p0 = GPoint(0,0);
  GPoint p1 = GPoint(143 , 0);
  GPoint p2 = GPoint(0, 59); 
  GPoint p3 = GPoint(143, 59); 
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_draw_line(ctx, p0, p1);
  graphics_draw_line(ctx, p0, p2);
  graphics_draw_line(ctx, p1, p3);
  graphics_draw_line(ctx, p2, p3);
}
*/

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_font_perfect_dos_48 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_48));
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_image_bt_white = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_WHITE);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(0, 54, 144, 60));
  text_layer_set_background_color(s_textlayer_time, GColorClear);
  text_layer_set_text_color(s_textlayer_time, GColorWhite);
  //text_layer_set_text(s_textlayer_time, "00:00");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_font_perfect_dos_48);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  
  // Create canvas layer
  /*
  s_canvaslayer_second = layer_create(GRect(0, 54, 144, 60));
  layer_add_child(window_get_root_layer(s_window), s_canvaslayer_second);
  layer_set_update_proc(s_canvaslayer_second, sencond_update_proc);
  */
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(0, 7, 90, 48));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text_color(s_textlayer_date, GColorWhite);
  text_layer_set_text(s_textlayer_date, "Sunday");
  text_layer_set_font(s_textlayer_date, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_textlayer_ampm
  s_textlayer_ampm = text_layer_create(GRect(96, 25, 40, 25));
  text_layer_set_background_color(s_textlayer_ampm, GColorBlack);
  text_layer_set_text_color(s_textlayer_ampm, GColorWhite);
  //text_layer_set_text(s_textlayer_ampm, "AM");
  text_layer_set_font(s_textlayer_ampm, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_ampm);
  
  // s_textlayer_second
  /*
  s_textlayer_second = text_layer_create(GRect(110, 130, 65, 60));
  text_layer_set_background_color(s_textlayer_second, GColorClear);
  text_layer_set_text_color(s_textlayer_second, GColorWhite);
  //text_layer_set_text(s_textlayer_second, ":00");
  text_layer_set_font(s_textlayer_second, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_second);
  */
  
  // s_textlayer_battery
  s_textlayer_battery = text_layer_create(GRect(71, 1, 55, 20));
  text_layer_set_background_color(s_textlayer_battery, GColorClear);
  text_layer_set_text_color(s_textlayer_battery, GColorWhite);
  text_layer_set_text(s_textlayer_battery, "100%");
  text_layer_set_text_alignment(s_textlayer_battery, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_battery, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_battery);
  
  // creat power process_bar
  pb_layer_battery = progressbar_layer_create(GRect(0, 0, 144, 3));
  layer_add_child(window_get_root_layer(s_window), progressbar_layer_get_layer(pb_layer_battery));
  
  // creat power second_bar
  pb_layer_second = progressbar_layer_create(GRect(0, 110, 144, 10));
  layer_add_child(window_get_root_layer(s_window), progressbar_layer_get_layer(pb_layer_second));
  
  // s_bitmaplayer_bt
  s_bitmaplayer_bt = bitmap_layer_create(GRect(127, 3, 16, 16));
  bitmap_layer_set_bitmap(s_bitmaplayer_bt, s_res_image_bt_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_bt);
  
  // s_layer_main
  s_layer_main = layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_layer_main);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_time);
  layer_destroy(s_canvaslayer_second);
  text_layer_destroy(s_textlayer_battery);
  bitmap_layer_destroy(s_bitmaplayer_bt);
  layer_destroy(s_layer_main);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_ampm);
  text_layer_destroy(s_textlayer_second);
  fonts_unload_custom_font(s_res_font_perfect_dos_48);
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



