#include <pebble.h>
#include "progressbar.h"
#include "main_face1.h"  

  
// 函数定义
static void update_time();
static void handler_init();


// time tick 处理  
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
  update_time();
}

//电量事件处理
static void battery_handler(BatteryChargeState new_state) 
{
  // Write to buffer and display
  static char s_battery_buffer[16];
  if(new_state.is_charging)
  {
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "charging");
  }  
  else
  {  
    // update the battery testlayer
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "%d%%", new_state.charge_percent);
    // update the battery process bar layer
    progressbar_layer_set_progress(pb_layer_battery, (100-new_state.charge_percent));
  }
  text_layer_set_text(s_textlayer_battery, s_battery_buffer);
}

//蓝牙事件处理
static void bt_handler(bool connected) {
  // Show current connection state
  if (connected) {
    //震动提醒
    //vibes_short_pulse();
    layer_set_hidden(bitmap_layer_get_layer(s_bitmaplayer_bt), 0);
  } 
  else 
  {
    //震动提醒
    layer_set_hidden(bitmap_layer_get_layer(s_bitmaplayer_bt), 1);
    vibes_short_pulse();
  }
}


// 时间更新
static void update_time()
{
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  // Display this time on the TextLayer
  text_layer_set_text(s_textlayer_time, buffer);
}


// handler 初始化
static void handler_init(void)
{
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  // Subscribe to the Battery State Service
  battery_state_service_subscribe(battery_handler);
  // Subscribe to Bluetooth updates
  bluetooth_connection_service_subscribe(bt_handler);
  // Make sure the time is displayed from the start
  update_time();
} 


void init() 
{
  //show face
  show_main_face();
  // get the battery level
  battery_handler(battery_state_service_peek());
  // Show current connection state
  bt_handler(bluetooth_connection_service_peek());
  // register handler 
  handler_init();
 
}

void deinit() {
  hide_main_face();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

