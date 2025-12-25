/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FCCU_H
#define __FCCU_H

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"



#define SET(mask)   (mask)

/***************************************************************************//*!
 * @brief   Clears register field in peripheral configuration structure.
 * @details This macro clears register field <c>mask</c> in the peripheral
 *          configuration structure.
 * @param   mask  Register field to be cleared.
 * @note    Implemented as a macro.
 ******************************************************************************/
#define CLR(mask)   0


/******************************************************************************
 * Configuration structure definition
 ******************************************************************************/
/*! tFCCU_CFG type definition - 32 bytes                                      */
typedef struct
{
  uint32_t CTRL;        ///< Operation run control and status
  uint32_t CFG;         ///< EOUT settings
  uint32_t NCF_TO;      ///< Alarm state timeout interval
  uint32_t CFG_TO;      ///< Configuration state timeout interval
  uint32_t EINOUT;      ///< EOUT force control
  uint32_t IRQ_EN;      ///< IRQ enable
  uint32_t DELTA_T;     ///< Min EOUT timer interval
  uint32_t PERMNT_LOCK; ///< permanent configuration lock when writing 0xFF until FCCU is reset
} tFCCU_CFG;

/*! tFCCU_NCF type definition - 4 bytes                                       */
typedef struct
{
  uint8_t NCF_nCh;      ///< 0~127 fault channel number, @ref fccu_ncf_channel_num.
  uint8_t NCF_Attr;     ///< NCF attributes, @ref fccu_ncf_attribute_mask.
} tFCCU_NCF;

/*! tFCCU_FMAP type definition - 4 bytes                                      */
typedef struct
{
  uint8_t  Fault_Id;    ///< bit position in registers DCMRWD3/4/5, @ref fccu_fault_id.
  uint8_t  NCF_nCh;     ///< The NCF channel that it is routed to.
  uint16_t Fault_Mark;  ///< 0x5ace marks a valid record.
} tFCCU_FMAP;

/*! tFCCU_DCM type definition - 3 words                                       */
typedef struct
{
  uint32_t DcmRWD3;     ///< DCMRWD3
  uint32_t DcmRWD4;     ///< DCMRWD4
  uint32_t DcmRWD5;     ///< DCMRWD5
} tFCCU_DCM;

/******************************************************************************
* FCCU fault id definition
*
*//*! @addtogroup fccu_fault_id
* @{
* @details fault id mapping within DCMRWD3~DCMRWD5 registers:
* |DCMRWD3 bit0  |DCMRWD3 bit31 |DCMRWD4 bit0  |DCMRWD4 bit31 |DCMRWD5 bit0  |DCMRWD5 bit22 |
* |:------------:|:------------:|:------------:|:------------:|:------------:|:------------:|
* |fault id 0    |fault id 31   |fault id 32   |fault id 63   |fault id 64   |fault id 86   |
*******************************************************************************/
#define CM7_0_LOCKUP                      0    ///< NCF0, DCMRWD3, bit0, CM7_0 core lockup
#define CM7_1_LOCKUP                      1    ///< NCF0, DCMRWD3, bit1, CM7_1 core lockup
#define FAULT_RESERVED_2                  2    ///< reserved fault id2
#define CM7_RCCU1_ALARM                   3    ///< NCF0, DCMRWD3, bit3, CM7 cores lockstep error
#define CM7_RCCU2_ALARM                   4    ///< NCF0, DCMRWD3, bit4, CM7 cores redundant lockstep error
#define TCM_GSKT_ALARM                    5    ///< NCF1, DCMRWD3, bit5, TCM IAHB gasket monitor alarm
#define DMA_SYS_GSKT_ALARM                6    ///< NCF1, DCMRWD3, bit6, DMA system AXBS IAHB gasket safety alarm
#define DMA_PERIPH_GSKT_ALARM             7    ///< NCF1, DCMRWD3, bit7, DMA periph AXBS IAHB gasket safety alarm
#define SYS_AXBS_ALARM                    8    ///< NCF1, DCMRWD3, bit8, system AXBS safety allarm
#define DMA_AXBS_ALARM                    9    ///< NCF1, DCMRWD3, bit9, DMA AXBS_Lite safety alarm
#define FAULT_RESERVED_10                 10   ///< NCF1, DCMRWD3, bit10, reserved fault id10
#define HSE_GSKT_ALARM                    11   ///< NCF1, DCMRWD3, bit11, HSE IAHB gasket alarm
#define QSPI_GSKT_ALARM                   12   ///< NCF1, DCMRWD3, bit12, QSPI IAHB gasket alarm
#define AIPS1_GSKT_ALARM                  13   ///< NCF1, DCMRWD3, bit13, AIPS1 IAHB gasket alarm
#define AIPS2_GSKT_ALARM                  14   ///< NCF1, DCMRWD3, bit14, AIPS2 IAHB gasket alarm
#define ADDR_EDC_ERR                      15   ///< NCF1, DCMRWD3, bit15, integrity error on address
#define DATA_EDC_ERR                      16   ///< NCF1, DCMRWD3, bit16, integrity error on data
#define TCM_AXBS_ALARM                    17   ///< NCF1, DCMRWD3, bit17, TCM AHB splitter safety alarm
#define EMAC_GSKT_ALARM                   18   ///< NCF1, DCMRWD3, bit18, EMAC IAHB gasket alarm
#define PERIPH_AXBS_ALARM                 19   ///< NCF1, DCMRWD3, bit19, Periph AXBS_Lite safety alarm
#define FAULT_RESERVED_20                 20   ///< NCF1, DCMRWD3, bit20, reserved fault id20
#define FAULT_RESERVED_21                 21   ///< NCF1, DCMRWD3, bit21, reserved fault id21
#define LC_ERR                            22   ///< NCF3, DCMRWD3, bit22, Errong in lifecycle scan
#define FAULT_RESERVED_23                 23   ///< NCF3, DCMRWD3, bit23, reserved fault id23
#define PRAM1_ECC_ERR                     24   ///< NCF2, DCMRWD3, bit24, SRAM1 multi bit ECC error
#define PRAM0_ECC_ERR                     25   ///< NCF2, DCMRWD3, bit25, SRAM0 multi bit ECC error
#define CM7_0_DCDATA_ECC_ERR              26   ///< NCF2, DCMRWD3, bit26, CM7_0 DCache data memory multi bit ECC error
#define CM7_1_DCDATA_ECC_ERR              27   ///< NCF2, DCMRWD3, bit27, CM7_1 DCache data memory multi bit ECC error
#define CM7_0_DCTAG_ECC_ERR               28   ///< NCF2, DCMRWD3, bit28, CM7_0 DCache tag memory multi bit ECC error
#define CM7_1_DCTAG_ECC_ERR               29   ///< NCF2, DCMRWD3, bit29, CM7_1 DCache tag memory multi bit ECC error
#define CM7_0_ICDATA_ECC_ERR              30   ///< NCF2, DCMRWD3, bit30, CM7_0 ICache data memory multi bit ECC error
#define CM7_1_ICDATA_ECC_ERR              31   ///< NCF2, DCMRWD3, bit31, CM7_1 ICache data memory multi bit ECC error
#define CM7_0_ICTAG_ECC_ERR               32   ///< NCF2, DCMRWD4, bit0, CM7_0 ICache tag memory multi bit ECC error
#define CM7_1_ICTAG_ECC_ERR               33   ///< NCF2, DCMRWD4, bit1, CM7_1 ICache tag memory multi bit ECC error
#define CM7_0_ITCM_ECC_ERR                34   ///< NCF2, DCMRWD4, bit2, CM7_0 ITCM memory multi bit ECC error
#define CM7_0_DTCM0_ECC_ERR               35   ///< NCF2, DCMRWD4, bit3, CM7_0 DTCM0 memory multi bit ECC error
#define CM7_0_DTCM1_ECC_ERR               36   ///< NCF2, DCMRWD4, bit4, CM7_0 DTCM1 memory multi bit ECC error
#define CM7_1_ITCM_ECC_ERR                37   ///< NCF2, DCMRWD4, bit5, CM7_1 ITCM memory multi bit ECC error
#define CM7_1_DTCM0_ECC_ERR               38   ///< NCF2, DCMRWD4, bit6, CM7_1 DTCM0 memory multi bit ECC error
#define CM7_1_DTCM1_ECC_ERR               39   ///< NCF2, DCMRWD4, bit7, CM7_1 DTCM1 memory multi bit ECC error
#define DMA_TCD_RAM_ECC_ERR               40   ///< NCF2, DCMRWD4, bit8, DMA TCD uncorrectable ECC error reported in ERM
#define PRAM0_FCCU_ALARM                  41   ///< NCF2, DCMRWD4, bit9, PRAM0 safety alarm
#define PRAM1_FCCU_ALARM                  42   ///< NCF2, DCMRWD4, bit10, PRAM1 safety alarm
#define HSE_RAM_ECC_ERR                   43   ///< NCF2, DCMRWD4, bit11, HSE RAM uncorrectable ECC error
#define PF0_CODE_ECC_ERR                  44   ///< NCF3, DCMRWD4, bit12, Flash0 code ECC uncorrectable error
#define PF0_DATA_ECC_ERR                  45   ///< NCF3, DCMRWD4, bit13, Flash0 data ECC uncorrectable error
#define PF1_CODE_ECC_ERR                  46   ///< NCF3, DCMRWD4, bit14, Flash1 code ECC uncorrectable error
#define PF1_DATA_ECC_ERR                  47   ///< NCF3, DCMRWD4, bit15, Flash1 data ECC uncorrectable error
#define PF2_CODE_ECC_ERR                  48   ///< NCF3, DCMRWD4, bit16, Flash2 code ECC uncorrectable error
#define PF2_DATA_ECC_ERR                  49   ///< NCF3, DCMRWD4, bit17, Flash2 data ECC uncorrectable error
#define FLASH_EDC_ERR                     50   ///< NCF3, DCMRWD4, bit18, Flash EDC after ECC error reported by FMU.
#define FLASH_ADDR_ENC_ERR                51   ///< NCF3, DCMRWD4, bit19, Flash address encode error.
#define FLASH_REF_ERR                     52   ///< NCF3, DCMRWD4, bit20, Flash reference current loss or read voltage error.
#define FLASH_RST_ERR                     53   ///< NCF3, DCMRWD4, bit21, Flash encounters errors during its reset reads.
#define FLASH_SCAN_ERR                    54   ///< NCF3, DCMRWD4, bit22, DCM flash scanning error
#define FAULT_RESERVED_55                 55   ///< NCF4, DCMRWD4, bit23, reserved fault id55
#define FLASH_ECC_ERR                     56   ///< NCF3, DCMRWD4, bit24, Flash ECC error through EDC
#define FLASH_ACCESS_ERR                  57   ///< NCF3, DCMRWD4, bit25, Flash address mismatch
#define VDD1P1_GNG_ERR                    58   ///< NCF4, DCMRWD4, bit26, VDD1PD1 no go indication
#define VDD2P5_GNG_ERR                    59   ///< NCF4, DCMRWD4, bit27, VDD_HV_FLA no go indication
#define FAULT_RESERVED_59                 60   ///< NCF4, DCMRWD4, bit28, reserved fault id59
#define TEST_ACTIVATION_0_ERR             61   ///< NCF5, DCMRWD4, bit29, Accidental partial test activation
#define TEST_ACTIVATION_1_ERR             62   ///< NCF5, DCMRWD4, bit30, Accidental partial test activation
#define TEST_ACTIVATION_2_ERR             63   ///< NCF5, DCMRWD4, bit31, Accidental partial test activation
#define TEST_ACTIVATION_3_ERR             64   ///< NCF5, DCMRWD5, bit0, Accidental partial test activation
#define INTM_0_ERR                        65   ///< NCF6, DCMRWD5, bit1, Interrupt monitor0 error
#define INTM_1_ERR                        66   ///< NCF6, DCMRWD5, bit2, Interrupt monitor1 error
#define INTM_2_ERR                        67   ///< NCF6, DCMRWD5, bit3, Interrupt monitor2 error
#define INTM_3_ERR                        68   ///< NCF6, DCMRWD5, bit4, Interrupt monitor3 error
#define SW_NCF_0                          69   ///< NCF7, DCMRWD5, bit5, Software NCF0 DCMRWF1[FCCU_SW_NCF0].
#define SW_NCF_1                          70   ///< NCF7, DCMRWD5, bit6, Software NCF1 DCMRWF1[FCCU_SW_NCF1].
#define SW_NCF_2                          71   ///< NCF7, DCMRWD5, bit7, Software NCF2 DCMRWF1[FCCU_SW_NCF2].
#define SW_NCF_3                          72   ///< NCF7, DCMRWD5, bit8, Software NCF3 DCMRWF1[FCCU_SW_NCF3].
#define STCU_NCF                          73   ///< NCF5, DCMRWD5, bit9, STCU non-critical fault BIST result error
#define MBIST_ACTIVATION_ERR              74   ///< NCF5, DCMRWD5, bit10, Accidental backdoor enabled on memories
#define STCU_BIST_USER_CF                 75   ///< NCF5, DCMRWD5, bit11, LBIST or MBIST enabled accidentally
#define MTR_BUS_ERR                       76   ///< NCF5, DCMRWD5, bit12, Fault reported due to illegal access on MTR
#define DEBUG_ACTIVATION_ERR              77   ///< NCF5, DCMRWD5, bit13, Monitoring of unintended debug activation
#define TCM_RDATA_EDC_ERR                 78   ///< NCF1, DCMRWD5, bit14, Integrity(EDC) error on TCM read data
#define EMAC_RDATA_EDC_ERR                79   ///< NCF1, DCMRWD5, bit15, Integrity(EDC) error on EMAC read data
#define FAULT_RESERVED_80                 80   ///< NCF1, DCMRWD5, bit16, reserved fault Id80
#define DMA_RDATA_EDC_ERR                 81   ///< NCF1, DCMRWD5, bit17, Integrity(EDC) error on eDMA read data
#define CM7_1_AHBP_RDATA_EDC_ERR          82   ///< NCF1, DCMRWD5, bit18, Integrity error on CM7_1 peripheral read data
#define CM7_1_AHBM_RDATA_EDC_ERR          83   ///< NCF1, DCMRWD5, bit19, Integrity error on CM7_1 main read data
#define CM7_0_AHBP_RDATA_EDC_ERR          84   ///< NCF1, DCMRWD5, bit20, Integrity error on CM7_0 peripheral read data
#define CM7_0_AHBM_RDATA_EDC_ERR          85   ///< NCF1, DCMRWD5, bit21, Integrity error on CM7_0 main read data
#define HSE_RDATA_EDC_ERR                 86   ///< NCF1, DCMRWD5, bit22, Integrity (EDC) error on HSE read data
/*! @} End of fccu_fault_id                                                   */

/******************************************************************************
* FCCU NCF mapping
*
*//*! @addtogroup fccu_ncf_channel_num
* @{
* @details FCCU faults are ORed to NCF0..NCF7 according to the following table:
* |NCF0 | ORed core lockstep error or core lockup error                        |
* |:---:|:--------------------------------------------------------------------:|
* |NCF0 | DCMRWD3, bit0,  CM7_0 core lockup                                    |
* |NCF0 | DCMRWD3, bit1,  CM7_1 core lockup                                    |
* |NCF0 | DCMRWD3, bit3,  CM7 cores lockstep error                             |
* |NCF0 | DCMRWD3, bit4,  CM7 cores redundant lockstep error                   |
*
* |NCF1 | ORed interconnect errors                                             |
* |:---:|:--------------------------------------------------------------------:|
* |NCF1 | DCMRWD3, bit5,  TCM IAHB gasket monitor alarm                        |
* |NCF1 | DCMRWD3, bit6,  DMA system AXBS IAHB gasket safety alarm             |
* |NCF1 | DCMRWD3, bit7,  DMA periph AXBS IAHB gasket safety alarm             |
* |NCF1 | DCMRWD3, bit8,  system AXBS safety allarm                            |
* |NCF1 | DCMRWD3, bit9,  DMA AXBS_Lite safety alarm                           |
* |NCF1 | DCMRWD3, bit11, HSE IAHB gasket alarm                                |
* |NCF1 | DCMRWD3, bit12, QSPI IAHB gasket alarm                               |
* |NCF1 | DCMRWD3, bit13, AIPS1 IAHB gasket alarm                              |
* |NCF1 | DCMRWD3, bit14, AIPS2 IAHB gasket alarm                              |
* |NCF1 | DCMRWD3, bit15, integrity error on address                           |
* |NCF1 | DCMRWD3, bit16, integrity error on data                              |
* |NCF1 | DCMRWD3, bit17, TCM AHB splitter safety alarm                        |
* |NCF1 | DCMRWD3, bit18, EMAC IAHB gasket alarm                               |
* |NCF1 | DCMRWD3, bit19, Periph AXBS_Lite safety alarm                        |
* |NCF1 | DCMRWD5, bit14, Integrity(EDC) error on TCM read data                |
* |NCF1 | DCMRWD5, bit15, Integrity(EDC) error on EMAC read data               |
* |NCF1 | DCMRWD5, bit17, Integrity(EDC) error on eDMA read data               |
* |NCF1 | DCMRWD5, bit18, Integrity error on CM7_1 peripheral read data        |
* |NCF1 | DCMRWD5, bit19, Integrity error on CM7_1 main read data              |
* |NCF1 | DCMRWD5, bit20, Integrity error on CM7_0 peripheral read data        |
* |NCF1 | DCMRWD5, bit21, Integrity error on CM7_0 main read data              |
* |NCF1 | DCMRWD5, bit22, Integrity (EDC) error on HSE read data               |
*
* |NCF2 | ORed memory ECC errors                                               |
* |:---:|:--------------------------------------------------------------------:|
* |NCF2 | DCMRWD3, bit24, SRAM1 multi bit ECC error                            |
* |NCF2 | DCMRWD3, bit25, SRAM0 multi bit ECC error                            |
* |NCF2 | DCMRWD3, bit26, CM7_0 DCache data memory multi bit ECC error         |
* |NCF2 | DCMRWD3, bit27, CM7_1 DCache data memory multi bit ECC error         |
* |NCF2 | DCMRWD3, bit28, CM7_0 DCache tag memory multi bit ECC error          |
* |NCF2 | DCMRWD3, bit29, CM7_1 DCache tag memory multi bit ECC error          |
* |NCF2 | DCMRWD3, bit30, CM7_0 ICache data memory multi bit ECC error         |
* |NCF2 | DCMRWD3, bit31, CM7_1 ICache data memory multi bit ECC error         |
* |NCF2 | DCMRWD4, bit0,  CM7_0 ICache tag memory multi bit ECC error          |
* |NCF2 | DCMRWD4, bit1,  CM7_1 ICache tag memory multi bit ECC error          |
* |NCF2 | DCMRWD4, bit2,  CM7_0 ITCM memory multi bit ECC error                |
* |NCF2 | DCMRWD4, bit3,  CM7_0 DTCM0 memory multi bit ECC error               |
* |NCF2 | DCMRWD4, bit4,  CM7_0 DTCM1 memory multi bit ECC error               |
* |NCF2 | DCMRWD4, bit5,  CM7_1 ITCM memory multi bit ECC error                |
* |NCF2 | DCMRWD4, bit6,  CM7_1 DTCM0 memory multi bit ECC error               |
* |NCF2 | DCMRWD4, bit7,  CM7_1 DTCM1 memory multi bit ECC error               |
* |NCF2 | DCMRWD4, bit8,  DMA TCD uncorrectable ECC error reported in ERM      |
* |NCF2 | DCMRWD4, bit9,  PRAM0 safety alarm                                   |
* |NCF2 | DCMRWD4, bit10, PRAM1 safety alarm                                   |
* |NCF2 | DCMRWD4, bit11, HSE RAM uncorrectable ECC error                      |
*
* |NCF3 | ORed flash errors                                                    |
* |:---:|:--------------------------------------------------------------------:|
* |NCF3 | DCMRWD3, bit22, Errong in lifecycle scan                             |
* |NCF3 | DCMRWD4, bit12, Flash0 code ECC uncorrectable error                  |
* |NCF3 | DCMRWD4, bit13, Flash0 data ECC uncorrectable error                  |
* |NCF3 | DCMRWD4, bit14, Flash1 code ECC uncorrectable error                  |
* |NCF3 | DCMRWD4, bit15, Flash1 data ECC uncorrectable error                  |
* |NCF3 | DCMRWD4, bit16, Flash2 code ECC uncorrectable error                  |
* |NCF3 | DCMRWD4, bit17, Flash2 data ECC uncorrectable error                  |
* |NCF3 | DCMRWD4, bit18, Flash EDC after ECC error reported by FMU.           |
* |NCF3 | DCMRWD4, bit19, Flash address encode error.                          |
* |NCF3 | DCMRWD4, bit20, Flash reference current loss or read voltage error.  |
* |NCF3 | DCMRWD4, bit21, Flash encounters errors during its reset reads.      |
* |NCF3 | DCMRWD4, bit22, DCM flash scanning error                             |
* |NCF3 | DCMRWD4, bit24, Flash ECC error through EDC                          |
* |NCF3 | DCMRWD4, bit25, Flash address mismatch                               |
*
* |NCF4 | ORed voltage errors                                                  |
* |:---:|:--------------------------------------------------------------------:|
* |NCF4 | DCMRWD4, bit26, VDD1PD1 no go indication                             |
* |NCF4 | DCMRWD4, bit27, VDD_HV_FLA no go indication                          |
*
* |NCF5 | ORed debug and test errors                                           |
* |:---:|:--------------------------------------------------------------------:|
* |NCF5 | DCMRWD4, bit29, Accidental partial test activation                   |
* |NCF5 | DCMRWD4, bit30, Accidental partial test activation                   |
* |NCF5 | DCMRWD4, bit31, Accidental partial test activation                   |
* |NCF5 | DCMRWD5, bit0,  Accidental partial test activation                   |
* |NCF5 | DCMRWD5, bit9,  STCU non-critical fault BIST result error            |
* |NCF5 | DCMRWD5, bit10, Accidental backdoor enabled on memories              |
* |NCF5 | DCMRWD5, bit11, LBIST or MBIST enabled accidentally                  |
* |NCF5 | DCMRWD5, bit12, Fault reported due to illegal access on MTR          |
* |NCF5 | DCMRWD5, bit13, Monitoring of unintended debug activation            |
*
* |NCF6 | ORed INTM errors                                                     |
* |:---:|:--------------------------------------------------------------------:|
* |NCF6 | DCMRWD5, bit1,  Interrupt monitor0 error                             |
* |NCF6 | DCMRWD5, bit2,  Interrupt monitor1 error                             |
* |NCF6 | DCMRWD5, bit3,  Interrupt monitor2 error                             |
* |NCF6 | DCMRWD5, bit4,  Interrupt monitor3 error                             |
*
* |NCF7 | ORed INTM errors                                                     |
* |:---:|:--------------------------------------------------------------------:|
* |NCF7 | DCMRWD5, bit5,  Software NCF0 DCMRWF1[FCCU_SW_NCF0].                 |
* |NCF7 | DCMRWD5, bit6,  Software NCF1 DCMRWF1[FCCU_SW_NCF1].                 |
* |NCF7 | DCMRWD5, bit7,  Software NCF2 DCMRWF1[FCCU_SW_NCF2].                 |
* |NCF7 | DCMRWD5, bit8,  Software NCF3 DCMRWF1[FCCU_SW_NCF3].                 |
*******************************************************************************/
#define FCCU_NCF_0    0U    ///< NCF0
#define FCCU_NCF_1    1U    ///< NCF1
#define FCCU_NCF_2    2U    ///< NCF2
#define FCCU_NCF_3    3U    ///< NCF3
#define FCCU_NCF_4    4U    ///< NCF4
#define FCCU_NCF_5    5U    ///< NCF5
#define FCCU_NCF_6    6U    ///< NCF6
#define FCCU_NCF_7    7U    ///< NCF7
/*! @} End of fccu_ncf_channel_num                                            */

/******************************************************************************
* FCCU NCF channels configurations used by FCCU_Init() function
*
*//*! @addtogroup fccu_ncf_channel_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief NCF channel configuration.
 * @details Configure the NCF channel attributes.
 * @param ncf_ch       Specify the NCF channel number @ref fccu_ncf_channel_num
 *                     [0..7].
 * @param ncf_attr     NCF attributes combination @ref fccu_ncf_attribute_mask.
 * @showinitializer
 ******************************************************************************/
#define FCCU_NCF_CONFIG(ncf_ch, ncf_attr) \
(tFCCU_NCF){                              \
/* NCF fault channel */ ncf_ch,           \
/* NCF attributes    */ ncf_attr          \
}

/***************************************************************************//*!
 * @brief Recommended FCCU NCF configurations.
 * @details Recommended recovery mechanism is reset for NCF_0~NCF_3 according to s32k3 RM.
 * |NCF Channel | Configurations description                       |
 * |:----------:|:------------------------------------------------:|
 * |NCF_0       |Alarm state IRQ enable, Fault state reset enable  |
 * |NCF_1       |Alarm state IRQ enable, Fault state reset enable  |
 * |NCF_2       |Alarm state IRQ enable, Fault state reset enable  |
 * |NCF_3       |Alarm state IRQ enable, Fault state reset enable  |
 * |NCF_4       |Alarm state IRQ enable, Fault state reset disable |
 * |NCF_5       |Alarm state IRQ enable, Fault state reset disable |
 * |NCF_6       |Alarm state IRQ enable, Fault state reset disable |
 * |NCF_7       |Alarm state IRQ enable, Fault state reset disable |
 * @showinitializer
 ******************************************************************************/
#define FCCU_NCF_RECOMMENDED_CONFIG                                      \
(tFCCU_NCF[]){                                                           \
  FCCU_NCF_CONFIG(FCCU_NCF_0, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|SET(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_1, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|SET(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_2, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|SET(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_3, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|SET(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_4, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|CLR(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_5, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|CLR(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_6, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|CLR(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN)), \
  FCCU_NCF_CONFIG(FCCU_NCF_7, SET(FCCU_NCF_CFG)|SET(FCCU_NCF_E)|CLR(FCCU_NCFS_CFG)|SET(FCCU_NCF_TO_EN)|SET(FCCU_IRQ_ALARM_EN)|SET(FCCU_EOUT_SIG_EN))  \
}
/*! @} End of fccu_ncf_channel_config                                         */

/******************************************************************************
* FCCU default configurations used by FCCU_Init() function
*
*//*! @addtogroup fccu_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief FCCU basic initialization configurations.
 * @details FCCU dconfig state TO IRQ enable and FCCU settings unlocked.
 * |Registers   | Description                          |
 * |:----------:|:------------------------------------:|
 * |CTRL        |FCCU Debug mode enabled.              |
 * |CFG         |EOUT signal not active.               |
 * |NCF_TO      |fault alarm state timeout interval.   |
 * |CFG_TO      |configuration state timeout interval. |
 * |EINOUT      |EOUT0/1 force output state.           |
 * |IRQ_EN      |enable CFG TO interrupt.              |
 * |DELTA_T     |minimum EOUT timer interval.          |
 * |PERMNT_LOCK |not lock FCCU configurations.         |
 * @showinitializer
 ******************************************************************************/
#define FCCU_MODULE_IRQ_EN_CONFIG                                      \
(tFCCU_CFG){                                                           \
/* CTRL   */  SET(FCCU_CTRL_DEBUG_MASK),                               \
/* CFG    */  CLR(FCCU_CFG_CM_MASK)|CLR(FCCU_CFG_SM_MASK)|             \
/* ...... */  CLR(FCCU_CFG_PS_MASK)|FCCU_CFG_FOM(0)|                   \
/* .....  */  CLR(FCCU_CFG_FCCU_SET_AFTER_RESET_MASK)|                 \
/* .....  */  FCCU_CFG_FCCU_SET_CLEAR(0),                              \
/* NCF_TO */  FCCU_NCF_TO_TO(0x3A980),                                 \
/* CFG_TO */  FCCU_CFG_TO_TO(5),                                       \
/* EINOUT */  CLR(FCCU_EINOUT_EOUT1_MASK)|CLR(FCCU_EINOUT_EOUT0_MASK), \
/* IRQ_EN */  SET(FCCU_IRQ_EN_CFG_TO_IEN_MASK),                        \
/* DELTA_T*/  FCCU_DELTA_T_DELTA_T(0),                                 \
/* PERMNT_LOCK*/ 0x00                                                  \
}

/***************************************************************************//*!
 * @brief FCCU user defined initialization configurations.
 * @details FCCU config state TO IRQ enable and FCCU settings locked.
 * |Registers   | Description                          |
 * |:----------:|:------------------------------------:|
 * |CTRL        |FCCU Debug mode enabled.              |
 * |CFG         |EOUT fault-toggle mode.               |
 * |NCF_TO      |fault alarm state timeout interval.   |
 * |CFG_TO      |configuration state timeout interval. |
 * |EINOUT      |EOUT0/1 force output state.           |
 * |IRQ_EN      |enable CFG TO interrupt.              |
 * |DELTA_T     |minimum EOUT timer interval.          |
 * |PERMNT_LOCK |0xFF=lock FCCU config until reset.    |
 * @param   ncf_to    NCF alarm state timeout period [1..480000]
 *                    T_clksafe*ncf_to.
 * @param   cfg_to    Configuration state timeout period [1..7]
 *                    T_clksafe*2^(cfg_to+13).
 * @param   delta_t   DELTA_T minimum EOUT timer interval [1..0x3FFF]
 *                    250uS+T_clksafe*delta_t.
 * @showinitializer
 ******************************************************************************/
#define FCCU_MODULE_DBG_EN_FAULT_TGL_IRQ_EN_PERM_LOCK_CONFIG(ncf_to, cfg_to, delta_t) \
(tFCCU_CFG){                                                                          \
/* CTRL   */  SET(FCCU_CTRL_DEBUG_MASK),                                              \
/* CFG    */  SET(FCCU_CFG_CM_MASK)|CLR(FCCU_CFG_SM_MASK)|                            \
/* ...... */  CLR(FCCU_CFG_PS_MASK)|FCCU_CFG_FOM(3)|                                  \
/* .....  */  SET(FCCU_CFG_FCCU_SET_AFTER_RESET_MASK)|                                \
/* .....  */  FCCU_CFG_FCCU_SET_CLEAR(2),                                             \
/* NCF_TO */  FCCU_NCF_TO_TO(ncf_to),                                                 \
/* CFG_TO */  FCCU_CFG_TO_TO(cfg_to),                                                 \
/* EINOUT */  CLR(FCCU_EINOUT_EOUT1_MASK)|CLR(FCCU_EINOUT_EOUT0_MASK),                \
/* IRQ_EN */  SET(FCCU_IRQ_EN_CFG_TO_IEN_MASK),                                       \
/* DELTA_T*/  FCCU_DELTA_T_DELTA_T(delta_t),                                          \
/* PERMNT_LOCK*/ 0xFF                                                                 \
}

/***************************************************************************//*!
 * @brief FCCU user defined initialization configurations.
 * @details  FCCU config state TO IRQ enable, fault output bi-stable and FCCU settings unlocked.
 * |Registers   | Description                          |
 * |:----------:|:------------------------------------:|
 * |CTRL        |FCCU Debug mode enabled.              |
 * |CFG         |EOUT bi-stable mode.                  |
 * |NCF_TO      |fault alarm state timeout interval.   |
 * |CFG_TO      |configuration state timeout interval. |
 * |EINOUT      |EOUT0/1 force output state.           |
 * |IRQ_EN      |enable CFG TO interrupt.              |
 * |DELTA_T     |minimum EOUT timer interval.          |
 * |PERMNT_LOCK |0x00=not lock FCCU configurations.    |
 * @param   ncf_to    NCF alarm state timeout period [1..480000]
 *                    T_clksafe*ncf_to.
 * @param   cfg_to    Configuration state timeout period [1..7]
 *                    T_clksafe*2^(cfg_to+13).
 * @param   delta_t   DELTA_T minimum EOUT timer interval [1..0x3FFF]
 *                    250uS+T_clksafe*delta_t.
 * @showinitializer
 ******************************************************************************/
#define FCCU_MODULE_DBG_EN_BI_STABLE_IRQ_EN_NO_LOCK_CONFIG(ncf_to, cfg_to, delta_t) \
(tFCCU_CFG){                                                                        \
/* CTRL   */  SET(FCCU_CTRL_DEBUG_MASK),                                            \
/* CFG    */  SET(FCCU_CFG_CM_MASK)|CLR(FCCU_CFG_SM_MASK)|                          \
/* ...... */  CLR(FCCU_CFG_PS_MASK)|FCCU_CFG_FOM(2)|                                \
/* .....  */  SET(FCCU_CFG_FCCU_SET_AFTER_RESET_MASK)|                              \
/* .....  */  FCCU_CFG_FCCU_SET_CLEAR(2),                                           \
/* NCF_TO */  FCCU_NCF_TO_TO(ncf_to),                                               \
/* CFG_TO */  FCCU_CFG_TO_TO(cfg_to),                                               \
/* EINOUT */  CLR(FCCU_EINOUT_EOUT1_MASK)|CLR(FCCU_EINOUT_EOUT0_MASK),              \
/* IRQ_EN */  SET(FCCU_IRQ_EN_CFG_TO_IEN_MASK),                                     \
/* DELTA_T*/  FCCU_DELTA_T_DELTA_T(delta_t),                                        \
/* PERMNT_LOCK*/ 0x00                                                               \
}
/*! @} End of fccu_config                                                     */

/******************************************************************************
* FCCU DCM configurations used by FCCU_Init() function
*
*//*! @addtogroup fccu_dcm_cfg
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief FCCU DCM configurations.
 * @details DCMRWD3 - Faults 0~31 enable/disable control.
 *          DCMRWD4 - Faults 32~63 enable/disable control.
 *          DCMRWD5 - Faults 64~85 enable/disable control.
 * @showinitializer
 ******************************************************************************/
#define FCCU_DCM_MODULE_ALL_FAULTS_EN_CONFIG          \
(tFCCU_DCM){                                          \
/* DCMRWD3 */  SET(1<<CM7_0_LOCKUP)|                  \
/* ......  */  SET(1<<CM7_1_LOCKUP)|                  \
/* ......  */  CLR(1<<CM7_RCCU1_ALARM)|               \
/* ......  */  CLR(1<<CM7_RCCU2_ALARM)|               \
/* ......  */  SET(1<<TCM_GSKT_ALARM)|                \
/* ......  */  SET(1<<DMA_SYS_GSKT_ALARM)|            \
/* ......  */  SET(1<<DMA_PERIPH_GSKT_ALARM)|         \
/* ......  */  SET(1<<SYS_AXBS_ALARM)|                \
/* ......  */  SET(1<<DMA_AXBS_ALARM)|                \
/* ......  */  SET(1<<HSE_GSKT_ALARM)|                \
/* ......  */  SET(1<<QSPI_GSKT_ALARM)|               \
/* ......  */  SET(1<<AIPS1_GSKT_ALARM)|              \
/* ......  */  SET(1<<AIPS2_GSKT_ALARM)|              \
/* ......  */  SET(1<<ADDR_EDC_ERR)|                  \
/* ......  */  SET(1<<DATA_EDC_ERR)|                  \
/* ......  */  SET(1<<TCM_AXBS_ALARM)|                \
/* ......  */  SET(1<<EMAC_GSKT_ALARM)|               \
/* ......  */  SET(1<<PERIPH_AXBS_ALARM)|             \
/* ......  */  SET(1<<LC_ERR)|                        \
/* ......  */  CLR(1<<PRAM1_ECC_ERR)|                 \
/* ......  */  SET(1<<PRAM0_ECC_ERR)|                 \
/* ......  */  SET(1<<CM7_0_DCDATA_ECC_ERR)|          \
/* ......  */  SET(1<<CM7_1_DCDATA_ECC_ERR)|          \
/* ......  */  SET(1<<CM7_0_DCTAG_ECC_ERR)|           \
/* ......  */  SET(1<<CM7_1_DCTAG_ECC_ERR)|           \
/* ......  */  SET(1<<CM7_0_ICDATA_ECC_ERR)|          \
/* ......  */  SET(1<<CM7_1_ICDATA_ECC_ERR),          \
/* DCMRWD4 */  SET(1<<(CM7_0_ICTAG_ECC_ERR-32))|      \
/* ......  */  SET(1<<(CM7_1_ICTAG_ECC_ERR-32))|      \
/* ......  */  CLR(1<<(CM7_0_ITCM_ECC_ERR-32))|       \
/* ......  */  SET(1<<(CM7_0_DTCM0_ECC_ERR-32))|      \
/* ......  */  SET(1<<(CM7_0_DTCM1_ECC_ERR-32))|      \
/* ......  */  SET(1<<(CM7_1_ITCM_ECC_ERR-32))|       \
/* ......  */  SET(1<<(CM7_1_DTCM0_ECC_ERR-32))|      \
/* ......  */  SET(1<<(CM7_1_DTCM1_ECC_ERR-32))|      \
/* ......  */  SET(1<<(DMA_TCD_RAM_ECC_ERR-32))|      \
/* ......  */  SET(1<<(PRAM0_FCCU_ALARM-32))|         \
/* ......  */  SET(1<<(PRAM1_FCCU_ALARM-32))|         \
/* ......  */  SET(1<<(HSE_RAM_ECC_ERR-32))|          \
/* ......  */  SET(1<<(PF0_CODE_ECC_ERR-32))|         \
/* ......  */  SET(1<<(PF0_DATA_ECC_ERR-32))|         \
/* ......  */  SET(1<<(PF1_CODE_ECC_ERR-32))|         \
/* ......  */  SET(1<<(PF1_DATA_ECC_ERR-32))|         \
/* ......  */  SET(1<<(PF2_CODE_ECC_ERR-32))|         \
/* ......  */  SET(1<<(PF2_DATA_ECC_ERR-32))|         \
/* ......  */  SET(1<<(FLASH_EDC_ERR-32))|            \
/* ......  */  SET(1<<(FLASH_ADDR_ENC_ERR-32))|       \
/* ......  */  SET(1<<(FLASH_REF_ERR-32))|            \
/* ......  */  SET(1<<(FLASH_RST_ERR-32))|            \
/* ......  */  SET(1<<(FLASH_SCAN_ERR-32))|           \
/* ......  */  SET(1<<(FLASH_ECC_ERR-32))|            \
/* ......  */  SET(1<<(FLASH_ACCESS_ERR-32))|         \
/* ......  */  SET(1<<(VDD1P1_GNG_ERR-32))|           \
/* ......  */  SET(1<<(VDD2P5_GNG_ERR-32))|           \
/* ......  */  SET(1<<(TEST_ACTIVATION_0_ERR-32))|    \
/* ......  */  SET(1<<(TEST_ACTIVATION_1_ERR-32))|    \
/* ......  */  SET(1<<(TEST_ACTIVATION_2_ERR-32)),    \
/* DCMRWD5 */  SET(1<<(TEST_ACTIVATION_3_ERR-64))|    \
/* ......  */  SET(1<<(INTM_0_ERR-64))|               \
/* ......  */  SET(1<<(INTM_1_ERR-64))|               \
/* ......  */  SET(1<<(INTM_2_ERR-64))|               \
/* ......  */  SET(1<<(INTM_3_ERR-64))|               \
/* ......  */  SET(1<<(SW_NCF_0-64))|                 \
/* ......  */  SET(1<<(SW_NCF_1-64))|                 \
/* ......  */  SET(1<<(SW_NCF_2-64))|                 \
/* ......  */  SET(1<<(SW_NCF_3-64))|                 \
/* ......  */  SET(1<<(STCU_NCF-64))|                 \
/* ......  */  SET(1<<(MBIST_ACTIVATION_ERR-64))|     \
/* ......  */  SET(1<<(STCU_BIST_USER_CF-64))|        \
/* ......  */  SET(1<<(MTR_BUS_ERR-64))|              \
/* ......  */  SET(1<<(DEBUG_ACTIVATION_ERR-64))|     \
/* ......  */  SET(1<<(TCM_RDATA_EDC_ERR-64))|        \
/* ......  */  SET(1<<(EMAC_RDATA_EDC_ERR-64))|       \
/* ......  */  SET(1<<(DMA_RDATA_EDC_ERR-64))|        \
/* ......  */  SET(1<<(CM7_1_AHBP_RDATA_EDC_ERR-64))| \
/* ......  */  SET(1<<(CM7_1_AHBM_RDATA_EDC_ERR-64))| \
/* ......  */  SET(1<<(CM7_0_AHBP_RDATA_EDC_ERR-64))| \
/* ......  */  SET(1<<(CM7_0_AHBM_RDATA_EDC_ERR-64))| \
/* ......  */  SET(1<<(HSE_RDATA_EDC_ERR-64))         \
}

 /***************************************************************************//*!
  * @brief FCCU DCM configurations.
  * @details DCMRWD3 - Faults 0~31 enable/disable control.
  *          DCMRWD4 - Faults 32~63 enable/disable control.
  *          DCMRWD5 - Faults 64~85 enable/disable control.
  * @showinitializer
  ******************************************************************************/
 #define FCCU_DCM_MODULE_ALL_FAULTS_DI_CONFIG          \
 (tFCCU_DCM){                                          \
 /* DCMRWD3 */  CLR(1<<CM7_0_LOCKUP)|                  \
 /* ......  */  CLR(1<<CM7_1_LOCKUP)|                  \
 /* ......  */  CLR(1<<CM7_RCCU1_ALARM)|               \
 /* ......  */  CLR(1<<CM7_RCCU2_ALARM)|               \
 /* ......  */  CLR(1<<TCM_GSKT_ALARM)|                \
 /* ......  */  CLR(1<<DMA_SYS_GSKT_ALARM)|            \
 /* ......  */  CLR(1<<DMA_PERIPH_GSKT_ALARM)|         \
 /* ......  */  CLR(1<<SYS_AXBS_ALARM)|                \
 /* ......  */  CLR(1<<DMA_AXBS_ALARM)|                \
 /* ......  */  CLR(1<<HSE_GSKT_ALARM)|                \
 /* ......  */  CLR(1<<QSPI_GSKT_ALARM)|               \
 /* ......  */  CLR(1<<AIPS1_GSKT_ALARM)|              \
 /* ......  */  CLR(1<<AIPS2_GSKT_ALARM)|              \
 /* ......  */  CLR(1<<ADDR_EDC_ERR)|                  \
 /* ......  */  CLR(1<<DATA_EDC_ERR)|                  \
 /* ......  */  CLR(1<<TCM_AXBS_ALARM)|                \
 /* ......  */  CLR(1<<EMAC_GSKT_ALARM)|               \
 /* ......  */  CLR(1<<PERIPH_AXBS_ALARM)|             \
 /* ......  */  CLR(1<<LC_ERR)|                        \
 /* ......  */  CLR(1<<PRAM1_ECC_ERR)|                 \
 /* ......  */  CLR(1<<PRAM0_ECC_ERR)|                 \
 /* ......  */  CLR(1<<CM7_0_DCDATA_ECC_ERR)|          \
 /* ......  */  CLR(1<<CM7_1_DCDATA_ECC_ERR)|          \
 /* ......  */  CLR(1<<CM7_0_DCTAG_ECC_ERR)|           \
 /* ......  */  CLR(1<<CM7_1_DCTAG_ECC_ERR)|           \
 /* ......  */  CLR(1<<CM7_0_ICDATA_ECC_ERR)|          \
 /* ......  */  CLR(1<<CM7_1_ICDATA_ECC_ERR),          \
 /* DCMRWD4 */  CLR(1<<(CM7_0_ICTAG_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(CM7_1_ICTAG_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(CM7_0_ITCM_ECC_ERR-32))|       \
 /* ......  */  CLR(1<<(CM7_0_DTCM0_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(CM7_0_DTCM1_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(CM7_1_ITCM_ECC_ERR-32))|       \
 /* ......  */  CLR(1<<(CM7_1_DTCM0_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(CM7_1_DTCM1_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(DMA_TCD_RAM_ECC_ERR-32))|      \
 /* ......  */  CLR(1<<(PRAM0_FCCU_ALARM-32))|         \
 /* ......  */  CLR(1<<(PRAM1_FCCU_ALARM-32))|         \
 /* ......  */  CLR(1<<(HSE_RAM_ECC_ERR-32))|          \
 /* ......  */  CLR(1<<(PF0_CODE_ECC_ERR-32))|         \
 /* ......  */  CLR(1<<(PF0_DATA_ECC_ERR-32))|         \
 /* ......  */  CLR(1<<(PF1_CODE_ECC_ERR-32))|         \
 /* ......  */  CLR(1<<(PF1_DATA_ECC_ERR-32))|         \
 /* ......  */  CLR(1<<(PF2_CODE_ECC_ERR-32))|         \
 /* ......  */  CLR(1<<(PF2_DATA_ECC_ERR-32))|         \
 /* ......  */  CLR(1<<(FLASH_EDC_ERR-32))|            \
 /* ......  */  CLR(1<<(FLASH_ADDR_ENC_ERR-32))|       \
 /* ......  */  CLR(1<<(FLASH_REF_ERR-32))|            \
 /* ......  */  CLR(1<<(FLASH_RST_ERR-32))|            \
 /* ......  */  CLR(1<<(FLASH_SCAN_ERR-32))|           \
 /* ......  */  CLR(1<<(FLASH_ECC_ERR-32))|            \
 /* ......  */  CLR(1<<(FLASH_ACCESS_ERR-32))|         \
 /* ......  */  CLR(1<<(VDD1P1_GNG_ERR-32))|           \
 /* ......  */  CLR(1<<(VDD2P5_GNG_ERR-32))|           \
 /* ......  */  CLR(1<<(TEST_ACTIVATION_0_ERR-32))|    \
 /* ......  */  CLR(1<<(TEST_ACTIVATION_1_ERR-32))|    \
 /* ......  */  CLR(1<<(TEST_ACTIVATION_2_ERR-32)),    \
 /* DCMRWD5 */  CLR(1<<(TEST_ACTIVATION_3_ERR-64))|    \
 /* ......  */  CLR(1<<(INTM_0_ERR-64))|               \
 /* ......  */  CLR(1<<(INTM_1_ERR-64))|               \
 /* ......  */  CLR(1<<(INTM_2_ERR-64))|               \
 /* ......  */  CLR(1<<(INTM_3_ERR-64))|               \
 /* ......  */  CLR(1<<(SW_NCF_0-64))|                 \
 /* ......  */  CLR(1<<(SW_NCF_1-64))|                 \
 /* ......  */  CLR(1<<(SW_NCF_2-64))|                 \
 /* ......  */  CLR(1<<(SW_NCF_3-64))|                 \
 /* ......  */  CLR(1<<(STCU_NCF-64))|                 \
 /* ......  */  CLR(1<<(MBIST_ACTIVATION_ERR-64))|     \
 /* ......  */  CLR(1<<(STCU_BIST_USER_CF-64))|        \
 /* ......  */  CLR(1<<(MTR_BUS_ERR-64))|              \
 /* ......  */  CLR(1<<(DEBUG_ACTIVATION_ERR-64))|     \
 /* ......  */  CLR(1<<(TCM_RDATA_EDC_ERR-64))|        \
 /* ......  */  CLR(1<<(EMAC_RDATA_EDC_ERR-64))|       \
 /* ......  */  CLR(1<<(DMA_RDATA_EDC_ERR-64))|        \
 /* ......  */  CLR(1<<(CM7_1_AHBP_RDATA_EDC_ERR-64))| \
 /* ......  */  CLR(1<<(CM7_1_AHBM_RDATA_EDC_ERR-64))| \
 /* ......  */  CLR(1<<(CM7_0_AHBP_RDATA_EDC_ERR-64))| \
 /* ......  */  CLR(1<<(CM7_0_AHBM_RDATA_EDC_ERR-64))| \
 /* ......  */  CLR(1<<(HSE_RDATA_EDC_ERR-64))         \
 }
/*! @} End of fccu_dcm_cfg                                                    */

/******************************************************************************
* FCCU NCF attributes masks definitions
*
*//*! @addtogroup fccu_ncf_attribute_mask
* @{
*******************************************************************************/
#define FCCU_NCF_CFG       (1U << 7)  ///< Configure the NCF to be SW recoverable @ref SET(@ref FCCU_NCF_CFG) or HW recoverable @ref CLR(@ref FCCU_NCF_CFG).
#define FCCU_NCF_E         (1U << 6)  ///< Enable the NCF channel to monitor FCCU faults.
#define FCCU_NCFS_CFG      (1U << 5)  ///< Configure the NCF fault state reaction to be MCU functional reset @ref SET(@ref FCCU_NCFS_CFG) or no reaction @ref CLR(@ref FCCU_NCFS_CFG).
#define FCCU_NCF_TO_EN     (1U << 3)  ///< Enable @ref SET(@ref FCCU_NCF_TO_EN) or disable @ref CLR(@ref FCCU_NCF_TO_EN) the NCF alarm state timeout.
#define FCCU_IRQ_ALARM_EN  (1U << 2)  ///< Enable @ref SET(@ref FCCU_IRQ_ALARM_EN) or disable @ref CLR(@ref FCCU_IRQ_ALARM_EN) alarm state IRQ for this NCF.
#define FCCU_EOUT_SIG_EN   (1U << 1)  ///< Enable @ref SET(@ref FCCU_EOUT_SIG_EN) or disable @ref CLR(@ref FCCU_EOUT_SIG_EN) the reaction of EOUT signals for this NCF fault state.
/*! @} End of fccu_ncf_attribute_mask                                         */

/******************************************************************************
* FCCU interrupt request flags used by FCCU_GetIrqFlags and FCCU_ClrIrqFlags
* functions
*
*//*! @addtogroup fccu_irqs
* @{
*******************************************************************************/
#define FCCU_NMI_STAT    (uint32_t)(1UL << 0)  ///< FCCU NMI interrupt status
#define FCCU_ALARM_STAT  (uint32_t)(1UL << 1)  ///< FCCU Alarm interrupt status
#define FCCU_CFG_TO_STAT (uint32_t)(1UL << 2)  ///< FCCU Configuration-state timeout status
/*! @} End of fccu_irqs                                                       */

/******************************************************************************
* FCCU interrupt request sources used by FCCU_EnableIrq and FCCU_DisableIrq functions
*
*//*! @addtogroup fccu_irq_sources
* @{
*******************************************************************************/
#define FCCU_CFG_TO_IEN  (uint32_t)(1UL <<  0) ///< FCCU Configuration-state timeout interrupt.
/*! @} End of fccu_irq_sources     */

/******************************************************************************
* FCCU callback registered by FCCU_InstallCallback() function
*
*//*! @addtogroup fccu_callback
* @{
*******************************************************************************/
/*! @brief tFCCU_CALLBACK type declaration                                    */
typedef enum
{
  FCCU_CFG_TO_CALLBACK     = (uint32_t)(1UL << 0), ///< CFG timeout interrupt
  FCCU_ALARM_STAT_CALLBACK = (uint32_t)(1UL << 1), ///< ALARM interrupt
  FCCU_NMI_STAT_CALLBACK   = (uint32_t)(1UL << 2)  ///< NMI interrupt
} tFCCU_CALLBACK_TYPE;

/*! @brief tFCCU_CALLBACK function declaration                                */
/*! @note Callback function is called by the driver prior flags are cleared   */
/*! to allow user to retrieve error flags that caused interrupt. Driver will  */
/*! clear all active error flags upon callback return.                        */ 
typedef void (*tFCCU_CALLBACK)(tFCCU_CALLBACK_TYPE type);
/*! @} End of fccu_callback                                                   */

/******************************************************************************
* FCCU state
*
*//*! @addtogroup fccu_state
* @{
*******************************************************************************/
/*! tFCCU_STATE type declaration                                              */
typedef enum
{
  FCCU_STATE_NORMAL = (uint32_t)0UL,  ///< fccu normal state
  FCCU_STATE_CONFIG = (uint32_t)1UL,  ///< fccu config state
  FCCU_STATE_ALARM  = (uint32_t)2UL,  ///< fccu alarm state
  FCCU_STATE_FAULT  = (uint32_t)3UL   ///< fccu fault state
} tFCCU_STATE;
/*! @} End of fccu_state                                                      */

/******************************************************************************
* FCCU operation status
*
*//*! @addtogroup fccu_ops
* @{
*******************************************************************************/
/*! tFCCU_OPS type declaration                                                */
typedef enum
{
  FCCU_OPS_IDLE        = (uint32_t)0UL,  ///< fccu ops idle
  FCCU_OPS_IN_PROGRESS = (uint32_t)1UL,  ///< fccu ops in progress
  FCCU_OPS_ABORTED     = (uint32_t)2UL,  ///< fccu ops aborted
  FCCU_OPS_SUCCESSFUL  = (uint32_t)3UL   ///< fccu ops successful
} tFCCU_OPS;
/*! @} End of fccu_ops                                                        */

/******************************************************************************
* FCCU driver functions return state
*
*//*! @addtogroup fccu_drv_return_state
* @{
*******************************************************************************/
/*! tFCCU_OPS type declaration                                                */
typedef enum
{
  FCCU_RETURN_OK       = (uint32_t)0UL,  ///< fccu driver function return OK
  FCCU_RETURN_ABORT    = (uint32_t)1UL,  ///< fccu driver function return ABORT
  FCCU_RETURN_ERROR    = (uint32_t)2UL   ///< fccu driver function return error
} tFCCU_RET;
/*! @} End of fccu_drv_return_state                                           */

/******************************************************************************
* FCCU function and macro definitions
*
*//*! @addtogroup fccu_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Returns FCCU State.
 * @details This macro returns current state of FCCU.
 * @return  @ref tFCCU_STATE.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define FCCU_GetState()    (FCCU->STAT&FCCU_STAT_STATUS_MASK)

/***************************************************************************//*!
 * @brief   Returns FCCU operation status.
 * @details This macro returns FCCU operation status.
 * @return  @ref tFCCU_OPS.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define FCCU_GetOps()     ((FCCU->CTRL&FCCU_CTRL_OPS_MASK)>>FCCU_CTRL_OPS_SHIFT)

/***************************************************************************//*!
 * @brief   Unlock FCCU configuration.
 * @details Unlock FCCU configuration registers so that they can be modified.
 * @note    Implemented as an inline macro.
 ******************************************************************************/
#define FCCU_UnlockCfg()    do{ FCCU->TRANS_LOCK=0xBC; }while(0)

/***************************************************************************//*!
 * @brief   Unlock FCCU CTRL OP1 operation.
 * @details This macro unlock FCCU CTRL OP1 operation (entering CONFIG state).
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define FCCU_UnlockOP1()    do{ FCCU->CTRLK = 0x913756AF; }while(0)

/***************************************************************************//*!
 * @brief   Unlock FCCU CTRL OP2 operation.
 * @details This macro unlock FCCU CTRL OP2 operation (entering NORMAL state).
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define FCCU_UnlockOP2()    do{ FCCU->CTRLK = 0x825A132B; }while(0)

/***************************************************************************//*!
 * @brief   Set FCCU CTRL OP1 operation.
 * @details This macro Set FCCU CTRL OP1 operation (entering CONFIG state).
 * @param   ctrl  CTRL register original value.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define FCCU_SetOP1(ctrl)   do{ FCCU_UnlockOP1(); FCCU->CTRL = ctrl|1; }while(0)

/***************************************************************************//*!
 * @brief   Set FCCU CTRL OP2 operation.
 * @details This macro Set FCCU CTRL OP2 operation (entering NORMAL state).
 * @param   ctrl  CTRL register original value.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define FCCU_SetOP2(ctrl)   do{ FCCU_UnlockOP2(); FCCU->CTRL = ctrl|2; }while(0)

/***************************************************************************//*!
 * @brief   Returns interrupt flags.
 * @details This macro returns interrupt flags.
 * @return  uint32_t  Mask of interrupt flags @ref fccu_irqs.
 * @note    Implemented as an inline macro.
 * @see     @ref FCCU_ClrIrqFlags.
 ******************************************************************************/
#define FCCU_GetIrqFlags()  FCCU->IRQ_STAT

/***************************************************************************//*!
 * @brief   Clears interrupt flags.
 * @details This macro clears interrupt flags given by mask parameter.
 * @param   mask  Mask of interrupt flags @ref fccu_irqs.
 * @note    Implemented as an inline macro.
 * @see     @ref FCCU_GetIrqFlags.
 ******************************************************************************/
#define FCCU_ClrIrqFlags(mask)  do{ FCCU->IRQ_STAT = mask; }while(0)

/***************************************************************************//*!
 * @brief   Enable interrupt request.
 * @details Enables interrupt request for source given by argument.
 * @param   mask  @ref fccu_irq_sources.
 * @note    Implemented as an inline macro.
 * @see     @ref FCCU_DisableIrq.
 ******************************************************************************/
#define FCCU_EnableIrq(mask)    do{ FCCU->IRQ_EN |= mask; }while(0)

/***************************************************************************//*!
 * @brief   Disable interrupt request.
 * @details Disables interrupt request for source given by argument.
 * @param   mask  @ref fccu_irq_sources.
 * @note    Implemented as an inline macro.
 * @see     @ref FCCU_EnableIrq.
 ******************************************************************************/
#define FCCU_DisableIrq(mask)   do{ FCCU->IRQ_EN &= ~mask; }while(0)

/***************************************************************************//*!
 * @brief   Controls FCCU module operation in debug mode.
 * @details This macro enables FCCU Debug mode. When FCCU enters the debug mode,
 *          it halts operation and remains in the state it was in before it
 *          entered this mode.
 * @note    Implemented as an inline macro.
 ******************************************************************************/
#define FCCU_DebugFreezeOn()    do{ FCCU->CTRL |= FCCU_CTRL_DEBUG_MASK; }while(0)

/***************************************************************************//*!
 * @brief   Controls FCCU module operation in debug mode.
 * @details This macro disables FCCU debug mode. When FCCU enters the debug mode,
 *          it halts operation and remains in the state it was in before it
 *          entered this mode
 * @note    Implemented as an inline macro.
 ******************************************************************************/
#define FCCU_DebugFreezeOff()   do{ FCCU->CTRL &= ~FCCU_CTRL_DEBUG_MASK; }while(0)

/***************************************************************************//*!
 * @brief   Configure an FCCU NCF channel.
 * @details This function configures an FCCU NCF channel.
 * @param   fccu_ncf_cfg  An NCF configuration structure @ref tFCCU_NCF.
 * @return  @ref fccu_drv_return_state.
 ******************************************************************************/
#define FCCU_ConfigNCF(fccu_ncf_cfg)    FCCU_prvConfigNCF(fccu_ncf_cfg)

/***************************************************************************//*!
 * @brief   Clear FCCU NCFS flags
 * @details Write FCCU NCFS register to clear the flags.
 * @param   ncfs  NCF status flags to clear. bit0-NCF0, bit1-NCF1, ......
 * @return  @ref fccu_drv_return_state.
 ******************************************************************************/
#define FCCU_ClrNCFS(ncfs)              FCCU_prvClrNCFS(ncfs)

/***************************************************************************//*!
 * @brief   Get FCCU NCFS flags.
 * @details Return FCCU register NCF_S[0].
 * @return  FCCU NCFS flags.
 ******************************************************************************/
#define FCCU_GetNCFS()                  FCCU->NCF_S[0]

/***************************************************************************//*!
 * @brief   Put FCCU to configuration mode.
 * @details Put FCCU to configuration mode so that software can modify some
 *          FCCU configurations.
 * @return  @ref tFCCU_RET.
 ******************************************************************************/
#define FCCU_SetConfigMode()            FCCU_prvSetConfigMode()

/***************************************************************************//*!
 * @brief   Put FCCU to normal mode.
 * @details Put FCCU to normal mode after FCCU configurations are done.
 * @return  @ref tFCCU_RET.
 ******************************************************************************/
#define FCCU_SetNormalMode()            FCCU_prvSetNormalMode()

/***************************************************************************//*!
 * @brief   Trigger a fake fault in FCCU.
 * @details This function write FCCU registers NCFF to inject a fake fault.
 * @param   nNCF - FCCU NCF channel number.
 ******************************************************************************/
#define FCCU_FakeNCF(nNCF)              do{ FCCU->NCFF = nNCF; }while(0)

/***************************************************************************//*!
 * @brief   Installs callback function for FCCU Alarm State interrupt.
 * @details This function install callback function for FCCU Alarm State IRQ and CFG TO IRQ.
 * @param   ip        @ref irq_prilvl "Interrupt Priority Levels".
 * @param   callback  Pointer to the @ref fccu_callback.
 * @note    Implemented as a function call.
 * @see     @ref FCCU_Init.
 ******************************************************************************/
#define FCCU_InstallCallback(ip,callback) FCCU_prvInstallCallback(ip,callback)

/***************************************************************************//*!
 * @brief   FCCU initialization.
 * @details This function initializes the FCCU module.
 * @param   fccu_cfg         FCCU basic configurations @ref fccu_config.
 * @param   fccu_ncf_ch_cfg  Array of FCCU NCF channels configurations
 *                           @ref fccu_ncf_channel_config.
 * @param   dcm_cfg          DCMROD3/4/5 settings to enable/disable faults
 *                           monitoring @ref fccu_dcm_cfg.
 * @return  @ref fccu_drv_return_state.
 * @note    Implemented as a function call.
 * @see     @ref FCCU_InstallCallback @ref FCCU_ConfigNCF.
 ******************************************************************************/
#define FCCU_Init(fccu_cfg, fccu_ncf_ch_cfg, dcm_cfg)   \
  FCCU_prvInit(fccu_cfg, fccu_ncf_ch_cfg, dcm_cfg)

/***************************************************************************//*!
 * @brief   FCCU DCM initialization.
 * @details This function initializes the FCCU related settings in DCM.
 * @param   dcm_cfg    FCCU DCM configurations @ref fccu_dcm_cfg.
 ******************************************************************************/
#define FCCU_DcmInit(dcm_cfg)          FCCU_prvDcmInit(dcm_cfg)

/***************************************************************************//*!
 * @brief   Get FCCU DCM faults.
 * @details This function get the faults flags in DCMGPR registers DCMROD3/4/5.
 * @param   pDcmFaults    Buffer to save the faults flags.
 ******************************************************************************/
#define FCCU_GetFaults(pDcmFaults)      FCCU_prvGetFaults(pDcmFaults)

/***************************************************************************//*!
 * @brief   Clear FCCU DCM faults.
 * @details This function clear the faults flags in DCMGPR registers DCMROD3/4/5.
 * @param   pDcmFaults    Faults flags to be cleared.
 ******************************************************************************/
#define FCCU_ClrFaults(pDcmFaults)      FCCU_prvClrFaults(pDcmFaults)

/***************************************************************************//*!
 * @brief   Enable an FCCU DCM fault.
 * @details This function enable one fault by setting a bit in registers DCMROD3/4/5.
 * @param   fault_id    @ref fccu_fault_id.
 ******************************************************************************/
#define FCCU_EnableFault(fault_id)      FCCU_prvEnableFault(fault_id)

/***************************************************************************//*!
 * @brief   Disable an FCCU DCM fault.
 * @details This function disable one fault by clearing a bit in registers DCMROD3/4/5.
 * @param   fault_id    @ref fccu_fault_id.
 ******************************************************************************/
#define FCCU_DisableFault(fault_id)     FCCU_prvDisableFault(fault_id)
/*! @} End of fccu_macro                                                      */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
void FCCU_prvInstallCallback (uint8_t ip, tFCCU_CALLBACK pCallback);
tFCCU_RET FCCU_prvInit (tFCCU_CFG fccu_cfg, tFCCU_NCF fccu_ncf_cfg[8], tFCCU_DCM dcm_cfg);
tFCCU_RET FCCU_prvConfigNCF(tFCCU_NCF fccu_ncf_cfg);
tFCCU_RET FCCU_prvClrNCFS(uint32_t nNCF);
tFCCU_RET FCCU_prvSetConfigMode(void);
tFCCU_RET FCCU_prvSetNormalMode(void);
void FCCU_prvDcmInit(tFCCU_DCM dcm_cfg);
void FCCU_prvGetFaults(uint32_t *pDcmFaults);
void FCCU_prvClrFaults(uint32_t *pDcmFaults);
void FCCU_prvEnableFault(uint32_t fault_id);
void FCCU_prvDisableFault(uint32_t fault_id);

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
void FCCU_0_Handler (void);
void FCCU_1_Handler (void);

#endif /* __FCCU_H */
