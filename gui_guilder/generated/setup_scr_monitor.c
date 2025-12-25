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


void setup_scr_monitor(lv_ui *ui)
{
	//Write codes monitor
	ui->monitor = lv_obj_create(NULL);
	lv_obj_set_size(ui->monitor, 800, 480);
	lv_obj_set_scrollbar_mode(ui->monitor, LV_SCROLLBAR_MODE_OFF);

	//Write style for monitor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->monitor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->monitor, lv_color_hex(0x00031d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->monitor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes monitor_chart_1
	ui->monitor_chart_1 = lv_chart_create(ui->monitor);
	lv_chart_set_type(ui->monitor_chart_1, LV_CHART_TYPE_LINE);
	lv_chart_set_div_line_count(ui->monitor_chart_1, 10, 20);
	lv_chart_set_point_count(ui->monitor_chart_1, 20);
	lv_chart_set_range(ui->monitor_chart_1, LV_CHART_AXIS_PRIMARY_Y, 0, 2400);
	lv_chart_set_range(ui->monitor_chart_1, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
	lv_chart_set_zoom_x(ui->monitor_chart_1, 256);
	lv_chart_set_zoom_y(ui->monitor_chart_1, 256);
	ui->monitor_chart_1_0 = lv_chart_add_series(ui->monitor_chart_1, lv_color_hex(0x0055ff), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_0, 0);
#endif
	ui->monitor_chart_1_1 = lv_chart_add_series(ui->monitor_chart_1, lv_color_hex(0xf00000), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
	lv_chart_set_next_value(ui->monitor_chart_1, ui->monitor_chart_1_1, 0);
#endif
	lv_obj_set_pos(ui->monitor_chart_1, 93, 53);
	lv_obj_set_size(ui->monitor_chart_1, 652, 374);
	lv_obj_set_scrollbar_mode(ui->monitor_chart_1, LV_SCROLLBAR_MODE_AUTO);
	lv_obj_add_flag(ui->monitor_chart_1, LV_OBJ_FLAG_SCROLLABLE);

	//Write style for monitor_chart_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->monitor_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->monitor_chart_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->monitor_chart_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->monitor_chart_1, lv_color_hex(0x313330), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->monitor_chart_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->monitor_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->monitor_chart_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->monitor_chart_1, lv_color_hex(0x313330), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->monitor_chart_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->monitor_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for monitor_chart_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->monitor_chart_1, lv_color_hex(0xffffff), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->monitor_chart_1, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->monitor_chart_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->monitor_chart_1, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->monitor_chart_1, lv_color_hex(0xe8e8e8), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->monitor_chart_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write codes monitor_label_title
	ui->monitor_label_title = lv_label_create(ui->monitor);
	lv_label_set_text(ui->monitor_label_title, "Speed monitoring chart");
	lv_label_set_long_mode(ui->monitor_label_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->monitor_label_title, 190, 15);
	lv_obj_set_size(ui->monitor_label_title, 420, 42);

	//Write style for monitor_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->monitor_label_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->monitor_label_title, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->monitor_label_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->monitor_label_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->monitor_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes monitor_imgbtn_back
	ui->monitor_imgbtn_back = lv_imgbtn_create(ui->monitor);
	lv_obj_add_flag(ui->monitor_imgbtn_back, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->monitor_imgbtn_back, LV_IMGBTN_STATE_RELEASED, NULL, &_back_alpha_41x41, NULL);
	ui->monitor_imgbtn_back_label = lv_label_create(ui->monitor_imgbtn_back);
	lv_label_set_text(ui->monitor_imgbtn_back_label, "");
	lv_label_set_long_mode(ui->monitor_imgbtn_back_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->monitor_imgbtn_back_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->monitor_imgbtn_back, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->monitor_imgbtn_back, 17, 7);
	lv_obj_set_size(ui->monitor_imgbtn_back, 41, 41);

	//Write style for monitor_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->monitor_imgbtn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->monitor_imgbtn_back, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->monitor_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->monitor_imgbtn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->monitor_imgbtn_back, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for monitor_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_recolor_opa(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->monitor_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->monitor_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->monitor_imgbtn_back, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(ui->monitor_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for monitor_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_recolor_opa(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->monitor_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->monitor_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->monitor_imgbtn_back, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(ui->monitor_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for monitor_imgbtn_back, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_recolor_opa(ui->monitor_imgbtn_back, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
	lv_obj_set_style_img_opa(ui->monitor_imgbtn_back, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes monitor_slider_1
	ui->monitor_slider_1 = lv_slider_create(ui->monitor);
	lv_slider_set_range(ui->monitor_slider_1, 0, 100);
	lv_slider_set_mode(ui->monitor_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->monitor_slider_1, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->monitor_slider_1, 771, 71);
	lv_obj_set_size(ui->monitor_slider_1, 5, 336);

	//Write style for monitor_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->monitor_slider_1, 94, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->monitor_slider_1, lv_color_hex(0xe3e8ed), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->monitor_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->monitor_slider_1, 58, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->monitor_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->monitor_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for monitor_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->monitor_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->monitor_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->monitor_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->monitor_slider_1, 58, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for monitor_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->monitor_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->monitor_slider_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->monitor_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->monitor_slider_1, 58, LV_PART_KNOB|LV_STATE_DEFAULT);

	//The custom code of monitor.
	lv_obj_set_style_size(ui->monitor_chart_1, 0, LV_PART_INDICATOR);
  lv_chart_set_axis_tick(ui->monitor_chart_1, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 10, 5, true, 100);
  lv_chart_set_axis_tick(ui->monitor_chart_1, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 10);
  lv_slider_set_range(ui->monitor_slider_1, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 5);

	//Update current screen layout.
	lv_obj_update_layout(ui->monitor);

	//Init events for screen.
	events_init_monitor(ui);

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
    //Init freeMaster params for screen.
    extData_init_monitor(ui);
#endif

}
