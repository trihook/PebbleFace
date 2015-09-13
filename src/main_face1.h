#ifndef MAIN_FACE1_H
#define MAIN_FACE1_H

void show_main_face(void);
void hide_main_face(void);

TextLayer *s_textlayer_battery;
TextLayer *s_textlayer_time;
TextLayer *s_textlayer_date;
TextLayer *s_textlayer_ampm;
TextLayer *s_textlayer_second;
TextLayer *s_textlayer_bt;
BitmapLayer *s_bitmaplayer_bt;


ProgressBarLayer *pb_layer_battery;
ProgressBarLayer *pb_layer_second;




#endif