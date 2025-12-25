/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fccu.h"

/******************************************************************************
 * static data definitions                                                      *
 ******************************************************************************/
static tFCCU_CALLBACK pCallbackFCCU;

/******************************************************************************
 * public function definitions                                                *
 ******************************************************************************/
void FCCU_prvInstallCallback (uint8_t ip, tFCCU_CALLBACK pCallback)
{
  pCallbackFCCU = pCallback;
  NVIC_SetPriority (FCCU_0_IRQn, ip);
  NVIC_EnableIRQ (FCCU_0_IRQn);
  NVIC_SetPriority (FCCU_1_IRQn, ip);
  NVIC_EnableIRQ (FCCU_1_IRQn);
}

tFCCU_RET FCCU_prvSetConfigMode (void)
{
  uint32_t tmp;
  if(FCCU_GetState() != FCCU_STATE_NORMAL)
    return FCCU_RETURN_ERROR;
  FCCU_UnlockCfg();                                  /* unlock FCCU configuration             */
  while(FCCU_GetOps() == FCCU_OPS_IN_PROGRESS){}     /* wait if FCCU operation is in process  */
  tmp = FCCU->CTRL;
  FCCU_SetOP1(tmp);                                  /* change FCCU to CONFIG state           */
  while(FCCU_GetOps() == FCCU_OPS_IN_PROGRESS){}     /* wait if FCCU operation is in process  */
  if(FCCU_GetOps() == FCCU_OPS_SUCCESSFUL && FCCU_GetState() == FCCU_STATE_CONFIG)
    return FCCU_RETURN_OK;
  else
    return FCCU_RETURN_ERROR;
}

tFCCU_RET FCCU_prvSetNormalMode (void)
{
  uint32_t tmp;
  if(FCCU_GetState() != FCCU_STATE_CONFIG)
    return FCCU_RETURN_ERROR;
  while(FCCU_GetOps() == FCCU_OPS_IN_PROGRESS){}     /* wait if FCCU operation is in process  */
  tmp = FCCU->CTRL;
  FCCU_SetOP2(tmp);                                  /* change FCCU to NORMAL state */
  while(FCCU_GetOps() == FCCU_OPS_IN_PROGRESS){}     /* wait if FCCU operation is in process  */
  if(FCCU_GetOps() == FCCU_OPS_SUCCESSFUL && FCCU_GetState() == FCCU_STATE_NORMAL)
    return FCCU_RETURN_OK;
  else
    return FCCU_RETURN_ERROR;
}

tFCCU_RET FCCU_prvInit (tFCCU_CFG fccu_cfg, tFCCU_NCF fccu_ncf_cfg[8], tFCCU_DCM dcm_cfg)
{
  tFCCU_RET ret;
  uint32_t i;

  FCCU->CTRL = fccu_cfg.CTRL;
  FCCU->CFG_TO = fccu_cfg.CFG_TO;
  FCCU->IRQ_EN = fccu_cfg.IRQ_EN;
  ret = FCCU_SetConfigMode();
  FCCU->CFG = fccu_cfg.CFG;
  FCCU->NCF_TO = fccu_cfg.NCF_TO;
  FCCU->DELTA_T = fccu_cfg.DELTA_T;
  ret |= FCCU_SetNormalMode();
  FCCU->EINOUT = fccu_cfg.EINOUT;

  FCCU_DcmInit(dcm_cfg);                              /* initialize FCCU DCM registers */

  FCCU_ClrNCFS(FCCU_GetNCFS());                       /* clear all NCF flags before enabling the NCF channels */
  
  for(i=0; i<8; i++){
    ret |= FCCU_ConfigNCF(fccu_ncf_cfg[i]);
  }
  FCCU->PERMNT_LOCK = fccu_cfg.PERMNT_LOCK;
  return ret;
}

tFCCU_RET FCCU_prvConfigNCF (tFCCU_NCF fccu_ncf_cfg)
{
  uint32_t nNCF = fccu_ncf_cfg.NCF_nCh;
  tFCCU_RET ret = FCCU_RETURN_OK;
  if(nNCF>127)
    return ret;
  ret = FCCU_SetConfigMode();
  if(fccu_ncf_cfg.NCF_Attr & FCCU_NCF_CFG)
    FCCU->NCF_CFG[nNCF/32] |= 1<<(nNCF%32);
  else
    FCCU->NCF_CFG[nNCF/32] &= ~(1<<(nNCF%32));

  FCCU->NCFS_CFG[nNCF/16] &= ~(3<<((nNCF%16)*2));
  if(fccu_ncf_cfg.NCF_Attr & FCCU_NCFS_CFG)
    FCCU->NCFS_CFG[nNCF/16] |= 1<<((nNCF%16)*2);

  if(fccu_ncf_cfg.NCF_Attr & FCCU_NCF_E)
    FCCU->NCF_E[nNCF/32] |= 1<<(nNCF%32);
  else
    FCCU->NCF_E[nNCF/32] &= ~(1<<(nNCF%32));

  if(fccu_ncf_cfg.NCF_Attr & FCCU_NCF_TO_EN)
    FCCU->NCF_TOE[nNCF/32] |= 1<<(nNCF%32);
  else
    FCCU->NCF_TOE[nNCF/32] &= ~(1<<(nNCF%32));

  if(fccu_ncf_cfg.NCF_Attr & FCCU_EOUT_SIG_EN)
    FCCU->EOUT_SIG_EN[nNCF/32] |= 1<<(nNCF%32);
  else
    FCCU->EOUT_SIG_EN[nNCF/32] &= ~(1<<(nNCF%32));

  if(fccu_ncf_cfg.NCF_Attr & FCCU_IRQ_ALARM_EN)
    FCCU->IRQ_ALARM_EN[nNCF/32] |= 1<<(nNCF%32);
  else
    FCCU->IRQ_ALARM_EN[nNCF/32] &= ~(1<<(nNCF%32));

  ret |= FCCU_SetNormalMode();
  return ret;
}

tFCCU_RET FCCU_prvClrNCFS (uint32_t ncfs)
{
  FCCU->NCFK = 0xAB3498FE;
  FCCU->NCF_S[0] = ncfs;
  while(FCCU_GetOps() == FCCU_OPS_IN_PROGRESS){}

  if(FCCU_GetOps() == FCCU_OPS_SUCCESSFUL)
    return FCCU_RETURN_OK;
  else if(FCCU_GetOps() == FCCU_OPS_ABORTED)
    return FCCU_RETURN_ABORT;
  else
    return FCCU_RETURN_ERROR;
}

void FCCU_prvDcmInit(tFCCU_DCM dcm_cfg)
{
  /* clear FCCU faults flags */
  DCM_GPR->DCMROD3 = DCM_GPR->DCMROD3;
  DCM_GPR->DCMROD4 = DCM_GPR->DCMROD4;
  DCM_GPR->DCMROD5 = DCM_GPR->DCMROD5;
  DCM_GPR->DCMRWD3 = dcm_cfg.DcmRWD3;
  DCM_GPR->DCMRWD4 = dcm_cfg.DcmRWD4;
  DCM_GPR->DCMRWD5 = dcm_cfg.DcmRWD5;
}

#if defined (__ICCARM__)
  #pragma diag_suppress=Pa082
#endif
void FCCU_prvGetFaults(uint32_t *pDcmFaults)
{
  pDcmFaults[0] = DCM_GPR->DCMROD3 & DCM_GPR->DCMRWD3;
  pDcmFaults[1] = DCM_GPR->DCMROD4 & DCM_GPR->DCMRWD4;
  pDcmFaults[2] = DCM_GPR->DCMROD5 & DCM_GPR->DCMRWD5;
}

void FCCU_prvClrFaults(uint32_t *pDcmFaults)
{
  DCM_GPR->DCMROD3 = pDcmFaults[0];
  DCM_GPR->DCMROD4 = pDcmFaults[1];
  DCM_GPR->DCMROD5 = pDcmFaults[2];
}

void FCCU_prvEnableFault(uint32_t fault_id)
{
  if(fault_id<32){
    DCM_GPR->DCMROD3 |= (1<<fault_id);
  }else if(fault_id<64){
    DCM_GPR->DCMROD4 |= (1<<(fault_id-32));
  }else if(fault_id<96){
    DCM_GPR->DCMROD5 |= (1<<(fault_id-64));
  }
}

void FCCU_prvDisableFault(uint32_t fault_id)
{
  if(fault_id<32){
    DCM_GPR->DCMROD3 &= ~(1<<fault_id);
  }else if(fault_id<64){
    DCM_GPR->DCMROD4 &= ~(1<<(fault_id-32));
  }else if(fault_id<96){
    DCM_GPR->DCMROD5 &= ~(1<<(fault_id-64));
  }
}

/******************************************************************************
 * interrupt function definitions                                             *
 ******************************************************************************/
//__WEAK __HANDLERFUNC void FCCU_0_Handler (void)
//{
//  uint32_t fccu_ncf_status, fccu_dcm_faults[3];

//  /* save NCF bits                                                            */
//  fccu_ncf_status = FCCU_GetNCFS();
//  /* get faults flags in DCMROD3/4/5                                          */
//  FCCU_GetFaults(fccu_dcm_faults);

//  /* run callback function defined by customer prior clearing flags           */
//  pCallbackFCCU(FCCU_ALARM_STAT_CALLBACK);

//  /* clear all NCF bits                                                       */
//  FCCU_ClrNCFS(fccu_ncf_status);
//  /* Clear faults flags in DCMROD3/4/5                                        */
//  FCCU_ClrFaults(fccu_dcm_faults);
//}

//__WEAK __HANDLERFUNC void FCCU_1_Handler (void)
//{
//  FCCU_ClrIrqFlags(FCCU_IRQ_STAT_CFG_TO_STAT_MASK);
//  /* run callback function defined by customer                                */
//  pCallbackFCCU(FCCU_CFG_TO_CALLBACK);
//}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
