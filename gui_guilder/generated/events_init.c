/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "custom.h"

static void control_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{	lv_obj_t * obj = lv_event_get_target(e);
	int32_t value = lv_slider_get_value(obj);

				#if LV_USE_FREEMASTER && LV_USE_GUIDER_SIMULATOR
	write_variable("M1 Speed Required", value);
	#endif
			if(lv_anim_get(guider_ui.control_img_fan, NULL) != NULL) {
		          lv_anim_t *anim_status = lv_anim_get(guider_ui.control_img_fan, NULL);
		          anim_status->time = get_time_by_speed(value);
		          lv_anim_refr_now();
		      }
		break;
	}
    default:
        break;
    }
}

static void control_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
			ui_load_scr_animation(&guider_ui, &guider_ui.monitor, guider_ui.monitor_del, &guider_ui.control_del, setup_scr_monitor, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, false);
		break;
	}
    default:
        break;
    }
}

static void control_sw_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		lv_obj_t * status_obj = lv_event_get_target(e);
		int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? 1 : 0;
		switch (status) {
		case (true):
		{
			image_fan_rotate(0);
			lv_obj_set_style_bg_opa(guider_ui.control_cont_1, 0, LV_PART_MAIN);
			lv_obj_clear_flag(guider_ui.control_led_1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.control_slider_1, LV_OBJ_FLAG_CLICKABLE);
				#if LV_USE_FREEMASTER && LV_USE_GUIDER_SIMULATOR
	write_variable("M1 Application Switch", 1);
	#endif
			break;
		}
		case (false):
		{
			if(lv_anim_get(guider_ui.control_img_fan, NULL) != NULL) {
		        lv_anim_t *anim_status = lv_anim_get(guider_ui.control_img_fan, NULL);
		        lv_anim_del(guider_ui.control_img_fan, NULL);
		    }
		    lv_slider_set_value(guider_ui.control_slider_1, 0, false);
		    lv_meter_set_indicator_value(guider_ui.control_meter_speed, guider_ui.control_meter_speed_scale_0_ndline_0, 0);
						lv_obj_set_style_text_font(guider_ui.control_label_value, &lv_font_arial_16, 0);
			lv_obj_set_style_bg_opa(guider_ui.control_cont_1, 167, LV_PART_MAIN);
			lv_obj_add_flag(guider_ui.control_led_1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.control_slider_1, LV_OBJ_FLAG_CLICKABLE);
				#if LV_USE_FREEMASTER && LV_USE_GUIDER_SIMULATOR
	write_variable("M1 Application Switch", 0);
	#endif
			break;
		}
		default:
			break;
		}
		break;
	}
    default:
        break;
    }
}

void events_init_control (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->control_slider_1, control_slider_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->control_imgbtn_1, control_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->control_sw_1, control_sw_1_event_handler, LV_EVENT_ALL, ui);
}

static void monitor_imgbtn_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
			ui_load_scr_animation(&guider_ui, &guider_ui.control, guider_ui.control_del, &guider_ui.monitor_del, setup_scr_control, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, false);
		break;
	}
    default:
        break;
    }
}

static void monitor_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_RELEASED:
	{
			lv_obj_t * obj = lv_event_get_target(e);
		  int32_t v = lv_slider_get_value(obj);
		  lv_chart_set_zoom_y(guider_ui.monitor_chart_1, v);
		  break;
		break;
	}
    default:
        break;
    }
}

void events_init_monitor (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->monitor_imgbtn_back, monitor_imgbtn_back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->monitor_slider_1, monitor_slider_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
