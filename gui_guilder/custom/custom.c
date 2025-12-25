// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

#include "freemaster_client.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

void image_fan_rotate(int speed)
{
    int time = get_time_by_speed(speed);
    if(lv_anim_get(guider_ui.control_img_fan, NULL) != NULL) {
      lv_anim_t *anim_status = lv_anim_get(guider_ui.control_img_fan, NULL);
      anim_status->time = time;
    } else {
      //Write animation: control_img_fan rotate
      lv_anim_t control_img_fan_anim_rotate;
      lv_anim_init(&control_img_fan_anim_rotate);
      lv_img_set_pivot(guider_ui.control_img_fan, 83, 83);
      lv_anim_set_var(&control_img_fan_anim_rotate, guider_ui.control_img_fan);
      lv_anim_set_time(&control_img_fan_anim_rotate, time);
      lv_anim_set_delay(&control_img_fan_anim_rotate, 0);
      lv_anim_set_exec_cb(&control_img_fan_anim_rotate, (lv_anim_exec_xcb_t)lv_img_set_angle);
      lv_anim_set_values(&control_img_fan_anim_rotate, 0, 360*10);
      lv_anim_set_path_cb(&control_img_fan_anim_rotate, &lv_anim_path_linear);
      control_img_fan_anim_rotate.repeat_cnt = LV_ANIM_REPEAT_INFINITE;
      lv_anim_start(&control_img_fan_anim_rotate);
      
    }
}

int get_time_by_speed(int slider_value)
{
  int time;
  if(slider_value == 0) {
    time = 100000000;
  }
  if(slider_value > 0 && slider_value < 400) {
    time = 1000;
  }
  if(slider_value >= 400  && slider_value < 800) {
    time = 900;
  }
  if(slider_value >= 800 && slider_value < 1200) {
    time = 800;
  }
    if(slider_value >= 1200 && slider_value < 1600) {
    time = 700;
  }
    if(slider_value >= 1600 && slider_value < 2000) {
    time = 600;
  }
  if(slider_value == 2000) {
    time = 500;
  }
  return time;
}
