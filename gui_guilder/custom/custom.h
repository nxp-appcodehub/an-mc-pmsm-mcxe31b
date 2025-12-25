// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void custom_init(lv_ui *ui);
void record_chart_timer_cb(lv_timer_t * t);
int get_time_by_speed(int slider_value);
void image_fan_rotate(int speed);
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
