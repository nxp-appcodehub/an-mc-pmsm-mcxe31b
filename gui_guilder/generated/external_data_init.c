/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "external_data_init.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER


static readVariableParm control_meter_speed_param = { NULL, NULL, NULL, NULL, 1, GG_METER, "ReadVariable"};
static fm_var control_meter_speedVarArray[] = { {"M1 Speed Actual Filtered", "IEEE floating point"} };
static lv_meter_indicator_t * control_meter_speed_Array[1] = {};
static readVariableParm monitor_chart_1_param = { NULL, NULL, NULL, NULL, 2, GG_CHART, "ReadVariable"};
static fm_var monitor_chart_1VarArray[] = { {"M1 Speed Actual", "IEEE floating point"},{"M1 Speed Required", "IEEE floating point"}, };
static lv_chart_series_t * monitor_chart_1_Array[2] = {};

void external_task_init()
{
    gg_edata_task_init();
}

void external_task_clear(lv_obj_t *act_scr)
{
    gg_edata_task_clear(act_scr);
}

void extData_init_control(lv_ui *ui)
{

    control_meter_speed_param.screen = ui->control;
    control_meter_speed_param.parentObj = ui->control_meter_speed;
    control_meter_speed_param.varArray = control_meter_speedVarArray;
  
	control_meter_speed_Array[0] = ui->control_meter_speed_scale_0_ndline_0;
    control_meter_speed_param.childObjArray = (void **)control_meter_speed_Array;
  
    gg_edata_task_create(100, (void *)freeMasterParse, &control_meter_speed_param);

}
void extData_init_monitor(lv_ui *ui)
{

    monitor_chart_1_param.screen = ui->monitor;
    monitor_chart_1_param.parentObj = ui->monitor_chart_1;
    monitor_chart_1_param.varArray = monitor_chart_1VarArray;
  
	monitor_chart_1_Array[0] = ui->monitor_chart_1_0;
	monitor_chart_1_Array[1] = ui->monitor_chart_1_1;
    monitor_chart_1_param.childObjArray = (void **)monitor_chart_1_Array;
  
    gg_edata_task_create(1000, (void *)freeMasterParse, &monitor_chart_1_param);

}

#endif
