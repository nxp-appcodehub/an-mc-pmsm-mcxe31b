/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mc_periph_init.h"
#include "peripherals.h"

/*******************************************************************************
 * Typedef
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void InitADC(void);
static void InitBCTU(void);
static void InitLCU(void);
static void InitEMIOS(void);
static void InitTRGMUX(void);
static void InitClock(void);
static void InitPIT(void);

#if M1_FAULT_ENABLE   
    static void InitCMP(void);
#endif /* M1_FAULT_ENABLE */


/*******************************************************************************
 * Constants
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Configuration structure for 3-phase PWM mc driver */
mcdrv_pwm3ph_emios_t g_sM1Pwm3ph;

/* Structure for current and voltage measurement*/
mcdrv_adc_t g_sM1Curr3phDcBus;

/* Structure for Encoder driver */
mcdrv_qd_enc_t g_sM1Enc;

/* Clock setup structure */
clock_setup_t g_sClockSetup;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief   void MCDRV_Init_M1(void)
 *           - Motor control driver main initialization
 *           - Calls initialization functions of peripherals required for motor
 *             control functionality
 *
 * @param   void
 *
 * @return  none
 */
void MCDRV_Init_M1(void)
{
    /* Init application clock dependent variables */
    InitClock();
  
    /* Init Body Cross-triggering Unit(BCTU) */
    InitBCTU();
    
    /* Init Logic Control Unit (LCU) */
    InitLCU();
  
    /* Init ADC */
    InitADC();
    
    /* Init eMIOS (PWM) */
    InitEMIOS();
    
    /* Init INPUTMUX */
    InitTRGMUX();
    
    /* Slow loop timer init */
    InitPIT();
	
#if M1_FAULT_ENABLE
    /* Comparator CMP */
    InitCMP();
#endif /* M1_FAULT_ENABLE */

}

/*!
 * @brief      Core, bus, flash clock setup
 *
 * @param      void
 *
 * @return     none
 */
void InitClock(void)
{
    uint32_t ui32CyclesNumber = 0U;
   
    /* The following peripherals use SYSTEM_CLK as APB/IPS clock: FlexPWM0/1, ADC0~3 */
    g_sClockSetup.ui32FastPeripheralClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    g_sClockSetup.ui32CpuFrequency = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    /* Parameters for motor M1 */
    g_sClockSetup.ui16M1PwmFreq   = M1_PWM_FREQ; /* 16 kHz */
    g_sClockSetup.ui16M1PwmModulo = (g_sClockSetup.ui32FastPeripheralClock) / g_sClockSetup.ui16M1PwmFreq;
    ui32CyclesNumber = ((M1_PWM_DEADTIME_NS * (g_sClockSetup.ui32FastPeripheralClock / 1000000U)) / 1000U);
    g_sClockSetup.ui16M1PwmDeadTime   = ui32CyclesNumber;
    g_sClockSetup.ui16M1SpeedLoopFreq = M1_SPEED_LOOP_FREQ; /* 1kHz */
}

/*!
 * @brief   void InitEMIOS(void)
 *
 * @param   void
 *
 * @return  none
 */
static void InitEMIOS(void)
{
    CLOCK_EnableClock(kCLOCK_Emios0);

#if 1
    /* Ch1-Ch6 are used for PWMA-PWMC signal generation */
    EMIOS_0->UC[1U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[1U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[1U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[1U].CNT |= EMIOS_CNT_C(0U);

    EMIOS_0->UC[2U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(0U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[2U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[2U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[2U].CNT |= EMIOS_CNT_C(0U);

    EMIOS_0->UC[3U].C |=  EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[3U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[3U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[3U].CNT |= EMIOS_CNT_C(0U);

	EMIOS_0->UC[4U].C |=  EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(0U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[4U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[4U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[4U].CNT |= EMIOS_CNT_C(0U);

    EMIOS_0->UC[5U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[5U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[5U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[5U].CNT |= EMIOS_CNT_C(0U);

    EMIOS_0->UC[6U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(0U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[6U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[6U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[6U].CNT |= EMIOS_CNT_C(0U);

    /* Ch0 is used for time base and reload signal generation */
    EMIOS_0->UC[0U].C |= EMIOS_C_MODE(0x50U) | EMIOS_C_EDPOL(0U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(3U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[0U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(1U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[0U].A = EMIOS_A_A(g_sClockSetup.ui16M1PwmModulo);
    EMIOS_0->UC[0U].B = EMIOS_B_B(0U);
    EMIOS_0->UC[0U].ALTA = EMIOS_ALTA_ALTA(0U);
    EMIOS_0->UC[0U].CNT |= EMIOS_CNT_C(0x0001U);

    /*Ch7 is used for ADC triggering through BCTU */
    EMIOS_0->UC[7U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[7U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[7U].A = EMIOS_A_A(1U);
    EMIOS_0->UC[7U].B = EMIOS_B_B(96);
    EMIOS_0->UC[7U].ALTA = EMIOS_ALTA_ALTA(0U);
    EMIOS_0->UC[7U].CNT |= EMIOS_CNT_C(0x0U);

    EMIOS_0->UC[1U].C |= EMIOS_C_ODIS_MASK;
    EMIOS_0->UC[2U].C |= EMIOS_C_ODIS_MASK;
    EMIOS_0->UC[3U].C |= EMIOS_C_ODIS_MASK;
    EMIOS_0->UC[4U].C |= EMIOS_C_ODIS_MASK;
    EMIOS_0->UC[5U].C |= EMIOS_C_ODIS_MASK;
    EMIOS_0->UC[6U].C |= EMIOS_C_ODIS_MASK;

    //EMIOS_EnableUpdate(EMIOS0, EMIOS_CH1|EMIOS_CH2|EMIOS_CH3|EMIOS_CH4);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU1(1U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU2(1U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU3(1U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU4(1U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU5(1U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU6(1U);

#else
    /* Ch1-Ch3 are used for PWMA-PWMC signal generation */
    // EMIOS_Init(EMIOS0,EMIOS_CH1,EMIOS_MODE_OPWMB_TB(EMIOS_BUS_BCDE,EMIOS_B1M_F,EMIOS_EDPOL_OUT_A_SET_B_CLR,APP_OPWMB_A_DC_0,APP_OPWMB_B_DC_0));
    EMIOS_0->UC[1U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[1U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[1U].A = EMIOS_A_A(g_sClockSetup.ui16M1PwmModulo/2 - g_sClockSetup.ui16M1PwmModulo/4);
    EMIOS_0->UC[1U].B = EMIOS_B_B(g_sClockSetup.ui16M1PwmModulo/2 + g_sClockSetup.ui16M1PwmModulo/4);
    EMIOS_0->UC[1U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[1U].CNT |= EMIOS_CNT_C(0U);
      
    //EMIOS_Init(EMIOS0,EMIOS_CH2,EMIOS_MODE_OPWMB_TB(EMIOS_BUS_BCDE,EMIOS_B1M_F,EMIOS_EDPOL_OUT_A_SET_B_CLR,APP_OPWMB_A_DC_0,APP_OPWMB_B_DC_0));
    EMIOS_0->UC[2U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[2U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[2U].A = EMIOS_A_A(g_sClockSetup.ui16M1PwmModulo/2 - g_sClockSetup.ui16M1PwmModulo/4);
    EMIOS_0->UC[2U].B = EMIOS_B_B(g_sClockSetup.ui16M1PwmModulo/2 + g_sClockSetup.ui16M1PwmModulo/4);
    EMIOS_0->UC[2U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[2U].CNT |= EMIOS_CNT_C(0U);
    
    //EMIOS_Init(EMIOS0,EMIOS_CH3,EMIOS_MODE_OPWMB_TB(EMIOS_BUS_BCDE,EMIOS_B1M_F,EMIOS_EDPOL_OUT_A_SET_B_CLR,APP_OPWMB_A_DC_0,APP_OPWMB_B_DC_0));
    EMIOS_0->UC[3U].C |=  EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[3U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[3U].A = EMIOS_A_A(g_sClockSetup.ui16M1PwmModulo/2 - g_sClockSetup.ui16M1PwmModulo/4);
    EMIOS_0->UC[3U].B = EMIOS_B_B(g_sClockSetup.ui16M1PwmModulo/2 + g_sClockSetup.ui16M1PwmModulo/4);
    EMIOS_0->UC[3U].ALTA = EMIOS_ALTA_ALTA(1U);
    EMIOS_0->UC[3U].CNT |= EMIOS_CNT_C(0U);
    
    /* Ch0 is used for time base and reload signal generation */
    //EMIOS_Init(EMIOS0,EMIOS_CH0,EMIOS_MODE_MCB_UP_ICLK(EMIOS_PRESC_1,EMIOS_PRESC_CLOCK,0x0001U,APP_MC_A1));
    EMIOS_0->UC[0U].C |= EMIOS_C_MODE(0x50U) | EMIOS_C_EDPOL(0U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(3U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[0U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(1U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[0U].A = EMIOS_A_A(g_sClockSetup.ui16M1PwmModulo);
    EMIOS_0->UC[0U].B = EMIOS_B_B(0U);
    EMIOS_0->UC[0U].ALTA = EMIOS_ALTA_ALTA(0U);
    EMIOS_0->UC[0U].CNT |= EMIOS_CNT_C(0x0001U);
        
    /*Ch4 is used for ADC triggering through BCTU */
    //EMIOS_Init(EMIOS0,EMIOS_CH4,EMIOS_MODE_OPWMB_TB(EMIOS_BUS_A,EMIOS_B1M_F,EMIOS_EDPOL_OUT_A_SET_B_CLR,APP_OPWMB_A_DC_0,APP_OPWMB_B_DC_0));
    EMIOS_0->UC[4U].C |= EMIOS_C_MODE(0x60U | 0x00U) | EMIOS_C_EDPOL(1U) | EMIOS_C_EDSEL(0U) | EMIOS_C_BSL(1U)| EMIOS_C_UCPRE(0U);
    EMIOS_0->UC[4U].C2 |= EMIOS_C2_UCRELDEL_INT(0U) | EMIOS_C2_UCPRECLK(0U) | EMIOS_C2_UCEXTPRE(0U);
    EMIOS_0->UC[4U].A = EMIOS_A_A(1U);
    EMIOS_0->UC[4U].B = EMIOS_B_B(96);
    EMIOS_0->UC[4U].ALTA = EMIOS_ALTA_ALTA(0U);
    EMIOS_0->UC[4U].CNT |= EMIOS_CNT_C(0x0U);    
    
    //EMIOS_EnableUpdate(EMIOS0, EMIOS_CH1|EMIOS_CH2|EMIOS_CH3|EMIOS_CH4);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU1(0U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU2(0U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU3(0U);
    EMIOS_0->OUDIS |= EMIOS_OUDIS_OU4(0U);

#endif
//    EMIOS_Enable(EMIOS0, EMIOS_CH0|EMIOS_CH23);
    EMIOS_0->UC[0].C |= EMIOS_C_UCPREN(1U);

//    EMIOS_EnablePrescaler(EMIOS0, 1u);
    EMIOS_0->MCR |= EMIOS_MCR_GTBE_MASK | EMIOS_MCR_GPREN_MASK | EMIOS_MCR_GPRE(1U);

    /* Initialize MC driver */
    g_sM1Pwm3ph.pui32PwmBaseAddress = (EMIOS_Type *)EMIOS_0;
    g_sM1Pwm3ph.ui16DeadTimeCnt = g_sClockSetup.ui16M1PwmDeadTime;

}

static void InitBCTU(void)
{
  
    bctu_config_t config;
    bctu_trig_config_t trigConfig;

    bctu_convlist_config_t convListConfig[3U] = {
      {
            // LIST0
            .lastChan           = false,
            .lastChanPlusOne    = false,
            .waitTrig           = false,
            .waitTrigPlusOne    = false,
            .adcChan            = 43U, // CURA_S19_ADC0_CHN43
            .adcChanPlusOne     = 41U, // CURC_S17_ADC1_CHN41
      },
      {     
            // LIST1
            .lastChan           = false,
            .lastChanPlusOne    = false,
            .waitTrig           = false,
            .waitTrigPlusOne    = false,
            .adcChan            = 40U, // CURB_S16_ADC0_CHN40
            .adcChanPlusOne     = 41U, // CURC_S17_ADC1_CHN41
      },
      {     
            // LIST2
            .lastChan           = false,
            .lastChanPlusOne    = true,
            .waitTrig           = false,
            .waitTrigPlusOne    = false,
            .adcChan            = 88U, // VOLT_DCB
            .adcChanPlusOne     = 41U, // Dummy
      },

    };

    BCTU_GetDefaultConfig(&config);
    config.writeProtect = kBCTU_ProtectDis_Permanent;
    BCTU_Init(BCTU, &config);
    
    trigConfig.trigIndex = kBCTU_TrigSourceEmios0Ch7; //DEMO_BCTU_TRIGGER_INDEX;
    trigConfig.chanAddr = 0U; //DEMO_BCTU_TRIG_CHAN_ADDR;
    trigConfig.dataDest = kBCTU_DataDest_Fifo1;
    trigConfig.enableLoop = false;
    trigConfig.targetAdc = (kBCTU_TrigAdc_0 | kBCTU_TrigAdc_1);
    trigConfig.trigRes = kBCTU_TrigRes_ConvList;
    BCTU_SetTrigConfig(BCTU, &trigConfig);

    for(uint8_t index = 0U; index < 3U; ++index)
    {
        BCTU_SetConvListConfig(BCTU, &(convListConfig[index]), index);
    }

    BCTU_SetFifoWaterMark(BCTU, kBCTU_Fifo_1, 5U);
    BCTU_EnableFifoInt(BCTU, kBCTU_Fifo_1_Int, true);
    EnableIRQ(BCTU_IRQn);
}

static void InitLCU(void)
{
    /* Structure of initialize LCU. */
    lcu_output_config_t outputConfig;

    /* Init pit module. */
    LCU_Init(LCU_0);

    /* Get LCU output default configuration. */
    LCU_GetOutputDefaultConfig(&outputConfig);
    
    outputConfig.outputEnable = true;
    outputConfig.softwareOverrideEnable = false;
    outputConfig.outputPolarity = kLCU_OutputPolarityNotInverted;
    outputConfig.forceInputSentivity = 0U;

    outputConfig.riseFilter = g_sClockSetup.ui16M1PwmDeadTime;
    outputConfig.fallFilter = 0U;
    outputConfig.lutValue = 0xAAAAU;

    /* Init LCU output. */
    LCU_OutputInit(LCU_0, kLCU_Lc0Output0, &outputConfig);

    outputConfig.lutValue = 0x5555U;

    /* Init LCU output. */
    LCU_OutputInit(LCU_0, kLCU_Lc0Output1, &outputConfig);

    outputConfig.lutValue = 0xCCCCU;

    /* Init LCU output. */
    LCU_OutputInit(LCU_0, kLCU_Lc0Output2, &outputConfig);

    outputConfig.lutValue = 0x3333U;

    /* Init LCU output. */
    LCU_OutputInit(LCU_0, kLCU_Lc0Output3, &outputConfig);

    outputConfig.lutValue = 0xAAAAU;
  
    /* Init LCU output. */
    LCU_OutputInit(LCU_0, kLCU_Lc1Output0, &outputConfig);

    outputConfig.lutValue = 0x5555U;

    /* Init LCU output. */
    LCU_OutputInit(LCU_0, kLCU_Lc1Output1, &outputConfig);

    LCU_MuxSelect(LCU_0, kLCU_Lc0Input0, kLCU_MuxSelInput0);
    LCU_MuxSelect(LCU_0, kLCU_Lc0Input1, kLCU_MuxSelInput1);
    //LCU_MuxSelect(LCU_0, kLCU_Lc0Input2, kLCU_MuxSelInput2);

    //LCU_MuxSelect(LCU_0, kLCU_Lc1Input0, kLCU_MuxSelInput0);
    //LCU_MuxSelect(LCU_0, kLCU_Lc1Input1, kLCU_MuxSelInput1);
    LCU_MuxSelect(LCU_0, kLCU_Lc1Input0, kLCU_MuxSelInput2);

}


/*!
 * @brief   void InitADC(void)
 *           - Initialization of the ADC16 peripheral
 *           - Initialization of the A/D converter for current and voltage sensing
 *
 * @param   void
 *
 * @return  none
 */
static void InitADC(void)
{

    adc_config_t adcConfig;
    adc_calibration_config_t calibrationConfig;

    ADC_GetDefaultConfig(&adcConfig);
    adcConfig.clockFrequency    = kADC_ModuleClockFreqDivide2;
    adcConfig.bctuMode          = kADC_BctuTrig;
    adcConfig.convAvg           = kADC_ConvAvgDisable;
    ADC_Init(ADC_0, &adcConfig);
    ADC_Init(ADC_1, &adcConfig);
    ADC_Init(ADC_2, &adcConfig);

    calibrationConfig.enableAverage        = false;

    if (!(ADC_DoCalibration(ADC_0, &calibrationConfig)))
    {
    }
    if (!(ADC_DoCalibration(ADC_1, &calibrationConfig)))
    {
    }
    if (!(ADC_DoCalibration(ADC_2, &calibrationConfig)))
    {
    }

}


/*!
 * @brief   void INPUTMUX(void)
 *
 * @param   void
 *
 * @return  none
 */
static void InitTRGMUX(void)
{
    CLOCK_EnableClock(kCLOCK_Trgmux);   

    //TRGMUX_SetTriggerSource(TRGMUX, kTRGMUX_ExtOut0, kTRGMUX_TriggerInput1, kTRGMUX_SourceEmios0IppDoEmiosCh4);
    
    // LCU1
    TRGMUX_SetTriggerSource(TRGMUX, kTRGMUX_Lcu0_0, kTRGMUX_TriggerInput0, kTRGMUX_SourceEmios0IppDoEmiosCh1);
    TRGMUX_SetTriggerSource(TRGMUX, kTRGMUX_Lcu0_0, kTRGMUX_TriggerInput1, kTRGMUX_SourceEmios0IppDoEmiosCh2);
    TRGMUX_SetTriggerSource(TRGMUX, kTRGMUX_Lcu0_0, kTRGMUX_TriggerInput2, kTRGMUX_SourceEmios0IppDoEmiosCh3);

}

/*!
 * @brief   void InitPIT(void)
 *           - Initialization of the CTIMER0 peripheral
 *           - performs slow control loop counter
 *
 * @param   void
 *
 * @return  none
 */
static void InitPIT(void)
{
    /* Structure of initialize PIT */
    pit_config_t pitConfig;

    PIT_GetDefaultConfig(&pitConfig);

    /* Init pit module */
    PIT_Init(PIT_0, &pitConfig);

    /* Set timer period for channel 0 */
    PIT_SetTimerPeriod(PIT_0, kPIT_Chnl_0, USEC_TO_COUNT(1000U, CLOCK_GetFreq(kCLOCK_Pit0Clk)));

    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(PIT_0, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(PIT0_IRQn);
    NVIC_SetPriority(PIT0_IRQn, 1);

    /* Start channel 0 */
    PIT_StartTimer(PIT_0, kPIT_Chnl_0);

}

/*!
 * @brief   void InitCMP(void)
 *
 * @param   void
 *
 * @return  none
 */
#if M1_FAULT_ENABLE
static void InitCMP(void)
{
    lpcmp_config_t mLpcmpConfigStruct;
    lpcmp_dac_config_t mLpcmpDacConfigStruct;

    LPCMP_GetDefaultConfig(&mLpcmpConfigStruct);
    
    /* Configure LPCMP input channels. */
    mLpcmpConfigStruct.plusInputSrc = kLPCMP_PlusInputSrcMux;
    mLpcmpConfigStruct.minusInputSrc = kLPCMP_MinusInputSrcDac;

    /* Init the LPCMP module. */
    LPCMP_Init(LPCMP_1, &mLpcmpConfigStruct);

    //LPCMP_1->CCR1 |= LPCMP_CCR1_SAMPLE_EN_MASK;
    //LPCMP_1->CCR1 |= LPCMP_CCR1_FILT_PER(1);
    //LPCMP_1->CCR1 |= LPCMP_CCR1_FILT_CNT(1);

    mLpcmpDacConfigStruct.referenceVoltageSource = kLPCMP_VrefSourceVin1;
    mLpcmpDacConfigStruct.DACValue = 220U;
    LPCMP_SetDACConfig(LPCMP_1, &mLpcmpDacConfigStruct);

    LPCMP_SetInputChannels(LPCMP_1, 2U, 0U);
    
}
#endif /* M1_FAULT_ENABLE */

