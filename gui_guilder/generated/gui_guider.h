/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *control;
	bool control_del;
	lv_obj_t *control_led_1;
	lv_obj_t *control_speed_label;
	lv_obj_t *control_meter_speed;
	lv_meter_scale_t *control_meter_speed_scale_0;
	lv_meter_indicator_t *control_meter_speed_scale_0_ndline_0;
	lv_meter_indicator_t *control_meter_speed_scale_0_arc_0;
	lv_meter_indicator_t *control_meter_speed_scale_0_arc_1;
	lv_meter_indicator_t *control_meter_speed_scale_0_arc_2;
	lv_meter_indicator_t *control_meter_speed_scale_0_scaleline_0;
	lv_obj_t *control_cont_1;
	lv_obj_t *control_slider_1;
	lv_obj_t *control_imgbtn_1;
	lv_obj_t *control_imgbtn_1_label;
	lv_obj_t *control_sw_1;
	lv_obj_t *control_img_fan;
	lv_obj_t *control_label_value;
	lv_obj_t *control_label_title;
	lv_obj_t *monitor;
	bool monitor_del;
	lv_obj_t *monitor_chart_1;
	lv_chart_series_t *monitor_chart_1_0;
	lv_chart_series_t *monitor_chart_1_1;
	lv_obj_t *monitor_label_title;
	lv_obj_t *monitor_imgbtn_back;
	lv_obj_t *monitor_imgbtn_back_label;
	lv_obj_t *monitor_slider_1;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_control(lv_ui *ui);
void setup_scr_monitor(lv_ui *ui);

LV_IMG_DECLARE(_monitor_800x480);
LV_IMG_DECLARE(_go_alpha_41x41);
LV_IMG_DECLARE(_fan_alpha_166x166);
LV_IMG_DECLARE(_back_alpha_41x41);

LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_montserratMedium_26)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_arial_16)
LV_FONT_DECLARE(lv_font_montserratMedium_24)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_22)


#ifdef __cplusplus
}
#endif
#endif
