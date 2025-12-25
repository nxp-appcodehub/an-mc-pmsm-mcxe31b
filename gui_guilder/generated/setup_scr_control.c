/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

#include "external_data_init.h"


void setup_scr_control(lv_ui *ui)
{
	//Write codes control
	ui->control = lv_obj_create(NULL);
	lv_obj_set_size(ui->control, 800, 480);
	lv_obj_set_scrollbar_mode(ui->control, LV_SCROLLBAR_MODE_OFF);

	//Write style for control, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->control, &_monitor_800x480, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->control, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor_opa(ui->control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes control_led_1
	ui->control_led_1 = lv_led_create(ui->control);
	lv_led_set_brightness(ui->control_led_1, 226);
	lv_led_set_color(ui->control_led_1, lv_color_hex(0x00922C));
	lv_obj_set_pos(ui->control_led_1, 724, 396);
	lv_obj_set_size(ui->control_led_1, 50, 50);
	lv_obj_add_flag(ui->control_led_1, LV_OBJ_FLAG_HIDDEN);

	//Write codes control_speed_label
	ui->control_speed_label = lv_label_create(ui->control);
	lv_label_set_text(ui->control_speed_label, "Speed Control");
	lv_label_set_long_mode(ui->control_speed_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->control_speed_label, 311, 364);
	lv_obj_set_size(ui->control_speed_label, 177, 29);

	//Write style for control_speed_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->control_speed_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->control_speed_label, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->control_speed_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->control_speed_label, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->control_speed_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_speed_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes control_meter_speed
	ui->control_meter_speed = lv_meter_create(ui->control);
	// add scale ui->control_meter_speed_scale_0
	ui->control_meter_speed_scale_0 = lv_meter_add_scale(ui->control_meter_speed);
	lv_meter_set_scale_ticks(ui->control_meter_speed, ui->control_meter_speed_scale_0, 41, 2, 7, lv_color_hex(0xe8e9ea));
	lv_meter_set_scale_major_ticks(ui->control_meter_speed, ui->control_meter_speed_scale_0, 8, 3, 13, lv_color_hex(0x008fce), 20);
	lv_meter_set_scale_range(ui->control_meter_speed, ui->control_meter_speed_scale_0, 0, 2000, 280, 130);

	// add arc for ui->control_meter_speed_scale_0
	ui->control_meter_speed_scale_0_arc_0 = lv_meter_add_arc(ui->control_meter_speed, ui->control_meter_speed_scale_0, 4, lv_color_hex(0x0d9401), 2);
	lv_meter_set_indicator_start_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_arc_0, 0);
	lv_meter_set_indicator_end_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_arc_0, 800);

	// add arc for ui->control_meter_speed_scale_0
	ui->control_meter_speed_scale_0_arc_1 = lv_meter_add_arc(ui->control_meter_speed, ui->control_meter_speed_scale_0, 4, lv_color_hex(0x7d8301), 2);
	lv_meter_set_indicator_start_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_arc_1, 800);
	lv_meter_set_indicator_end_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_arc_1, 1600);

	// add arc for ui->control_meter_speed_scale_0
	ui->control_meter_speed_scale_0_arc_2 = lv_meter_add_arc(ui->control_meter_speed, ui->control_meter_speed_scale_0, 4, lv_color_hex(0x830115), 2);
	lv_meter_set_indicator_start_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_arc_2, 1600);
	lv_meter_set_indicator_end_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_arc_2, 2000);

	// add scale line for ui->control_meter_speed_scale_0
	ui->control_meter_speed_scale_0_scaleline_0 = lv_meter_add_scale_lines(ui->control_meter_speed, ui->control_meter_speed_scale_0, lv_color_hex(0x2effb2), lv_color_hex(0xaf001b), true, 0);
	lv_meter_set_indicator_start_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_scaleline_0, 0);
	lv_meter_set_indicator_end_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_scaleline_0, 2000);

	// add needle line for ui->control_meter_speed_scale_0.
	ui->control_meter_speed_scale_0_ndline_0 = lv_meter_add_needle_line(ui->control_meter_speed, ui->control_meter_speed_scale_0, 2, lv_color_hex(0xffffff), -21);
	lv_meter_set_indicator_value(ui->control_meter_speed, ui->control_meter_speed_scale_0_ndline_0, 1);
	lv_obj_set_pos(ui->control_meter_speed, 501, 116);
	lv_obj_set_size(ui->control_meter_speed, 250, 250);

	//Write style for control_meter_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_meter_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_meter_speed, 352, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->control_meter_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_meter_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for control_meter_speed, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->control_meter_speed, lv_color_hex(0xb8b8b8), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->control_meter_speed, &lv_font_montserratMedium_16, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->control_meter_speed, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write style for control_meter_speed, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_meter_speed, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_meter_speed, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_meter_speed, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes control_cont_1
	ui->control_cont_1 = lv_obj_create(ui->control);
	lv_obj_set_pos(ui->control_cont_1, 3, -4);
	lv_obj_set_size(ui->control_cont_1, 800, 480);
	lv_obj_set_scrollbar_mode(ui->control_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for control_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->control_cont_1, 144, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes control_slider_1
	ui->control_slider_1 = lv_slider_create(ui->control_cont_1);
	lv_slider_set_range(ui->control_slider_1, 0, 2000);
	lv_slider_set_mode(ui->control_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->control_slider_1, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->control_slider_1, 247, 415);
	lv_obj_set_size(ui->control_slider_1, 305, 11);

	//Write style for control_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_slider_1, 88, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->control_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for control_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_slider_1, 88, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for control_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_slider_1, lv_color_hex(0x2a65ff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_slider_1, 88, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes control_imgbtn_1
	ui->control_imgbtn_1 = lv_imgbtn_create(ui->control_cont_1);
	lv_obj_add_flag(ui->control_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->control_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_go_alpha_41x41, NULL);
	ui->control_imgbtn_1_label = lv_label_create(ui->control_imgbtn_1);
	lv_label_set_text(ui->control_imgbtn_1_label, "");
	lv_label_set_long_mode(ui->control_imgbtn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->control_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->control_imgbtn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->control_imgbtn_1, 732, 21);
	lv_obj_set_size(ui->control_imgbtn_1, 41, 41);

	//Write style for control_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->control_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->control_imgbtn_1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->control_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->control_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->control_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for control_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_recolor_opa(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->control_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->control_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->control_imgbtn_1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(ui->control_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for control_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_recolor_opa(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->control_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->control_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->control_imgbtn_1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(ui->control_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for control_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_recolor_opa(ui->control_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
	lv_obj_set_style_img_opa(ui->control_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes control_sw_1
	ui->control_sw_1 = lv_switch_create(ui->control_cont_1);
	lv_obj_set_pos(ui->control_sw_1, 34, 409);
	lv_obj_set_size(ui->control_sw_1, 69, 32);

	//Write style for control_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_sw_1, lv_color_hex(0x005A9E), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->control_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for control_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
	lv_obj_set_style_bg_opa(ui->control_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->control_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->control_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->control_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style for control_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->control_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->control_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->control_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->control_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes control_img_fan
	ui->control_img_fan = lv_img_create(ui->control);
	lv_obj_add_flag(ui->control_img_fan, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->control_img_fan, &_fan_alpha_166x166);
	lv_img_set_pivot(ui->control_img_fan, 83,83);
	lv_img_set_angle(ui->control_img_fan, 0);
	lv_obj_set_pos(ui->control_img_fan, 95, 163);
	lv_obj_set_size(ui->control_img_fan, 166, 166);

	//Write style for control_img_fan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->control_img_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->control_img_fan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_img_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->control_img_fan, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes control_label_value
	ui->control_label_value = lv_label_create(ui->control);
	lv_label_set_text(ui->control_label_value, "000r/s");
	lv_label_set_long_mode(ui->control_label_value, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->control_label_value, 127, 342);
	lv_obj_set_size(ui->control_label_value, 107, 22);

	//Write style for control_label_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->control_label_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->control_label_value, &lv_font_arial_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->control_label_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->control_label_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->control_label_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_label_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes control_label_title
	ui->control_label_title = lv_label_create(ui->control);
	lv_label_set_text(ui->control_label_title, "FRDM-MCXE31B PMSM Moter Demo");
	lv_label_set_long_mode(ui->control_label_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->control_label_title, 150, 31);
	lv_obj_set_size(ui->control_label_title, 513, 37);

	//Write style for control_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->control_label_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->control_label_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->control_label_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->control_label_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->control_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of control.
	lv_obj_clear_flag(ui->control_slider_1, LV_OBJ_FLAG_CLICKABLE);

	//Update current screen layout.
	lv_obj_update_layout(ui->control);

	//Init events for screen.
	events_init_control(ui);

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
    //Init freeMaster params for screen.
    extData_init_control(ui);
#endif

}
