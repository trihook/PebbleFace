#include <pebble.h>
#include "progressbar.h"
#include "main_face1.h"  

// 函数定义
static void update_time();
static void handler_init();


char date_text[32];
char hour_minutes_text[] = "00:00";
char seconds_text[] = ":00";
char ampm_text[] = "AM";
// This was the time at the last call to update_time().
// This is initialized with impossible values to ensure all layers are updated
// on the first call to update_time().
struct tm last_time = {-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0};
// State of clock_is_24h_style() at the last call to update_time().
// We don't care about the initial value of this because the difference
// in last_time will cause everything to be updated.
bool last_24hr;


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

// time 更新
void update_time(void)
{
  time_t temp = time(NULL); 
  struct tm *time = localtime(&temp);
  // Update text layers for time fields that have changed.
  // Month and day.
  if (time->tm_mon != last_time.tm_mon || time->tm_mday != last_time.tm_mday)
  {
    strftime(date_text, sizeof(date_text), "%A\n%b %e", time);
    text_layer_set_text(s_textlayer_date, date_text);
  }
  bool is_24hr = clock_is_24h_style();
  // Hour and minute.
  if (time->tm_hour != last_time.tm_hour || time->tm_sec != last_time.tm_sec || is_24hr != last_24hr)
  {
    // Use snprintf instead of strftime() to get the right padding.
    const char *time_format;
    int hour = time->tm_hour;
    if (is_24hr)
    {
      // 24-hour style.
      // Hour is zero-padded.
      time_format = "%02d:%02d";
    } 
    else 
    {
      // 12-hour style.
      // Hour has no padding.
      time_format = "%d:%02d";
      if (hour == 0)
      {
        // Midnight.
        hour = 12;
      } 
      else if (hour > 12)
      {
        hour -= 12;
      }
    }
    snprintf(hour_minutes_text, sizeof(hour_minutes_text), time_format, hour, time->tm_min);
    text_layer_set_text(s_textlayer_time, hour_minutes_text);
  }
  // AM/PM (blank for 24-hour style).
  if (time->tm_hour != last_time.tm_hour || is_24hr != last_24hr)
  {
    if (is_24hr)
    {
      text_layer_set_text(s_textlayer_ampm, "");
    } 
    else 
    {
      strftime(ampm_text, sizeof(ampm_text), "%p", time);
      text_layer_set_text(s_textlayer_ampm, ampm_text);
    }
  }
  // Seconds.
  if (time->tm_sec != last_time.tm_sec)
  {
    strftime(seconds_text, sizeof(seconds_text), ":%S", time);
    //text_layer_set_text(s_textlayer_second, seconds_text);
    int tempsec;
    tempsec = time->tm_sec;
    progressbar_layer_set_progress(pb_layer_second,100-(uint16_t)(tempsec)*100/60);
  }
  // Save state for next time.
  last_time = *time;
  last_24hr = is_24hr;
}


// handler 初始化
static void handler_init(void)
{
  update_time();
  // Register with TickTimerService
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  // Subscribe to the Battery State Service
  battery_state_service_subscribe(battery_handler);
  // Subscribe to Bluetooth updates
  bluetooth_connection_service_subscribe(bt_handler);
  // Make sure the time is displayed from the start
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

