/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef EXTERNAL_DATA_INIT_H
#define EXTERNAL_DATA_INIT_H

#include "lvgl.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "gui_guider.h"
#include "gg_external_data.h"
#include "freemaster_client.h"

#define FREEMASTER_SERVER "ws://localhost:41000"

void external_task_init();
void external_task_clear(lv_obj_t *act_scr);
void extData_init_control(lv_ui *ui);
void extData_init_monitor(lv_ui *ui);

#endif
#endif
