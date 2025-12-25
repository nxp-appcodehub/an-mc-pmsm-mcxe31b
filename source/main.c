/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mc_periph_init.h"
#include "freemaster.h"
#include "freemaster_serial_lpuart.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "fsl_lpuart.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "m1_sm_snsless_enc.h"
#include "clock_config.h"
#include "board.h"
#include "fccu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Version info */
#define MCRSP_VER "2.0.0" /* motor control package version */

/* Example's feature set in form of bits inside ui16featureSet.
   This feature set is expected to be growing over time.
   ... | FEATURE_S_RAMP | FEATURE_FIELD_WEAKENING | FEATURE_ENC
*/
#define FEATURE_ENC (1)               /* Encoder feature flag */
#define FEATURE_FIELD_WEAKENING (0)   /* Field weakening feature flag */
#define FEATURE_S_RAMP (0)            /* S-ramp feature flag */

#define FEATURE_SET (FEATURE_ENC << (0) | \
                     FEATURE_FIELD_WEAKENING << (1) | \
                     FEATURE_S_RAMP << (2))

/* Macro for correct Cortex CM0 / CM4 end of interrupt */
#define M1_END_OF_ISR \
    {                 \
        __DSB();      \
        __ISB();      \
    }

/* CPU load measurement SysTick START / STOP macros */
#define SYSTICK_START_COUNT() (SysTick->VAL = SysTick->LOAD)
#define SYSTICK_STOP_COUNT(par1)   \
    uint32_t val  = SysTick->VAL;  \
    uint32_t load = SysTick->LOAD; \
    par1          = load - val

static void BOARD_Init(void);
static void BOARD_InitSysTick(void);
static void BOARD_InitGPIO(void);
static void DemoSpeedStimulator(void);
static void DemoPositionStimulator(void);
static void init_freemaster_lpuart(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* CPU load measurement using Systick */
uint32_t g_ui32NumberOfCycles    = 0U;
uint32_t g_ui32MaxNumberOfCycles = 0U;
uint32_t g_ui32NumberOfCycles_slow    = 0U;
uint32_t g_ui32MaxNumberOfCycles_slow = 0U;
float_t cpu_loading_rt = 0.0f;

/* Demo mode enabled/disabled */
bool_t bDemoModeSpeed = FALSE;
bool_t bDemoModePosition = FALSE;

/* Used for demo mode */
static uint32_t ui32SpeedStimulatorCnt    = 0U;
static uint32_t ui32PositionStimulatorCnt = 0U;

/* Structure used in FM to get required ID's */
app_ver_t g_sAppIdFM = {
    "../boards/frdmmcxe31b/mc_pmsm/pmsm_snsless",                       /* User Path 1- the highest priority */
    "../../../boards/frdmmcxe31b/demo_apps/mc_pmsm/pmsm_snsless",       /* User Path 2 */
    "frdmmcxe31b",    /* board id */
    "pmsm_snsless", /* example id */
    MCRSP_VER,      /* sw version */
    FEATURE_SET,    /* example's feature-set */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief   Application main function processing peripheral function calling and
 *          infinite loop
 *
 * @param   void
 *
 * @return  none
 */
int main(void)
{
    /*Accessing ID structure to prevent optimization*/
    g_sAppIdFM.ui16FeatureSet = FEATURE_SET;

    uint32_t ui32PrimaskReg;

    /* Disable all interrupts before peripherals are initialized */
    ui32PrimaskReg = DisableGlobalIRQ();

    /* Disable demo mode after reset */
    bDemoModeSpeed    = FALSE;
    bDemoModePosition = FALSE;
    ui32SpeedStimulatorCnt = 0U;
    
    /* Init board hardware. */
    BOARD_Init();
    
    /* FreeMASTER communication layer initialization */
    init_freemaster_lpuart();
    
    /* FreeMASTER initialization */
    FMSTR_Init();

    /* Initialize peripheral motor control driver for motor M1 */
    MCDRV_Init_M1();   

    /* SysTick initialization for CPU load measurement */
    BOARD_InitSysTick();

    FCCU_Init (FCCU_MODULE_DBG_EN_BI_STABLE_IRQ_EN_NO_LOCK_CONFIG(360000, 7, 0),
    FCCU_NCF_RECOMMENDED_CONFIG,
    FCCU_DCM_MODULE_ALL_FAULTS_EN_CONFIG);
    NVIC_EnableIRQ (FCCU_0_IRQn);

    /* Turn off application */
    M1_SetAppSwitch(FALSE);

    /* Enable interrupts  */
    EnableGlobalIRQ(ui32PrimaskReg);
    
    /* Start PWM */    
    BCTU_EnableModule(BCTU, true);
    BCTU_EnableGlobalTrig(BCTU, true);
    
    BCTU_EnableHardwareTrig(BCTU, kBCTU_TrigSourceEmios0Ch7, true);

    /* Infinite loop */
    while (1)
    {
        /* FreeMASTER Polling function */
        FMSTR_Poll();
    }
}

/*!
 * @brief   BCTU ISR called with 100us period processes
 *           - motor M1 fast application machine function
 *           - demo mode if enabled
 *
 * @param   void
 *
 * @return  none
 */
void BCTU_IRQHandler(void)
{
    /* Start CPU tick number couting */
    SYSTICK_START_COUNT();    

	//SIUL2_PortPinWrite(SIUL2, BOARD_INITPINS_GPIO_TP0_GPIO,
	//		BOARD_INITPINS_GPIO_TP0_PIN, 1);

    SM_StateMachineFast(&g_sM1Ctrl);
        
	//SIUL2_PortPinWrite(SIUL2, BOARD_INITPINS_GPIO_TP0_GPIO,
	//		BOARD_INITPINS_GPIO_TP0_PIN, 0);

    /* Stop CPU tick number couting and store actual and maximum ticks */
    SYSTICK_STOP_COUNT(g_ui32NumberOfCycles);
    g_ui32MaxNumberOfCycles =
        g_ui32NumberOfCycles > g_ui32MaxNumberOfCycles ? g_ui32NumberOfCycles : g_ui32MaxNumberOfCycles;

    BCTU->FIFOERR |= BCTU_FIFOERR_WM_INT_FIFO1_MASK;

    /* Call FreeMASTER recorder */
    FMSTR_Recorder(0);

    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
    
}

/*!
 * @brief   Slow loop interrupt handler (1ms period)
 *           - motor M1 slow application machine function
 *
 * @param   void
 *
 * @return  none
 */
void PIT0_IRQHandler(void)
{
    static int16_t ui16i = 0;

	//SIUL2_PortPinWrite(SIUL2, BOARD_INITPINS_GPIO_TP1_GPIO,
	//		BOARD_INITPINS_GPIO_TP1_PIN, 1);

    /* Start CPU tick number couting */
    SYSTICK_START_COUNT();

    /* M1 Slow StateMachine call */
    SM_StateMachineSlow(&g_sM1Ctrl);

    SYSTICK_STOP_COUNT(g_ui32NumberOfCycles_slow);
    g_ui32MaxNumberOfCycles_slow =
        g_ui32NumberOfCycles_slow > g_ui32MaxNumberOfCycles_slow ? g_ui32NumberOfCycles_slow : g_ui32MaxNumberOfCycles_slow;

    cpu_loading_rt = ((float_t)g_ui32NumberOfCycles)*0.01f + ((float_t)g_ui32NumberOfCycles_slow)*0.000625f;

    /* If in STOP state turn on RED */
    if (M1_GetAppState() == 2)
    {
        /* Red LED on */
    	SIUL2_PortPinWrite(SIUL2, BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, LOGIC_LED_ON);
        /* Green LED off */
    	SIUL2_PortPinWrite(SIUL2, BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, LOGIC_LED_OFF);
    }

    /* If in FAULT state RED blinking*/
    else if (M1_GetAppState() == 0)
    {
        if (ui16i-- < 0)
        {
            LED_RED_TOGGLE();
            bDemoModeSpeed = FALSE;
            bDemoModePosition = FALSE;
            ui16i = 125;
        }
        /* Green LED off */
    	SIUL2_PortPinWrite(SIUL2, BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, LOGIC_LED_OFF);
    }

    /* If in RUN or INIT state turn on green */
    else
    {
        /* Red LED off */
        SIUL2_PortPinWrite(SIUL2, BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, LOGIC_LED_OFF);
        /* Green LED on */
    	SIUL2_PortPinWrite(SIUL2, BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, LOGIC_LED_ON);

    }

    /* Demo speed stimulator */
    DemoSpeedStimulator();

    /* Demo position stimulator */
    DemoPositionStimulator();

    /* Call FreeMASTER recorder */
    FMSTR_Recorder(0);

	//SIUL2_PortPinWrite(SIUL2, BOARD_INITPINS_GPIO_TP1_GPIO,
	//		BOARD_INITPINS_GPIO_TP1_PIN, 0);

    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT_0, kPIT_Chnl_0, kPIT_TimerFlag);

    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;

}

/*!
 * @brief   DemoSpeedStimulator
 *           - When demo mode is enabled it changes the required speed according
 *             to predefined profile
 *
 * @param   void
 *
 * @return  none
 */
static void DemoSpeedStimulator(void)
{
    if (bDemoModeSpeed)
    {
        ui32SpeedStimulatorCnt++;
        switch (ui32SpeedStimulatorCnt)
        {
            case 10:
                g_sM1Drive.eControl                  = kControlMode_SpeedFOC;
                g_sM1Drive.sMCATctrl.ui16PospeSensor = MCAT_SENSORLESS_CTRL;
                break;
            case 100:
                M1_SetSpeed(1000.0F);
                break;
            case 3000:
                M1_SetSpeed(2000.0F);
                break;
            case 6000:
                M1_SetSpeed(4000.0F);
                break;
            case 9000:
                M1_SetSpeed(-1000.0F);
                break;
            case 12000:
                M1_SetSpeed(-2000.0F);
                break;
            case 15000:
                M1_SetSpeed(-4000.0F);
                break;
            case 18000:
                M1_SetSpeed(800.0F);
                ui32SpeedStimulatorCnt = 0;
                break;
            default:
            	;
                break;
        }
    }
    else
    {
        ui32SpeedStimulatorCnt = 0U;
    }
}

/*!
 * @brief   DemoPositionStimulator
 *           - When demo mode is enabled it changes the required position according
 *             to predefined profile
 *
 * @param   void
 *
 * @return  none
 */
static void DemoPositionStimulator(void)
{
    if (bDemoModePosition)
    {
        ui32PositionStimulatorCnt++;
        switch (ui32PositionStimulatorCnt)
        {
            case 2:
                g_sM1Drive.eControl                  = kControlMode_PositionFOC;
                g_sM1Drive.sMCATctrl.ui16PospeSensor = MCAT_ENC_CTRL;
                break;
            case 10:
                M1_SetPosition(ACC32(20));
                break;
            case 3000:
                M1_SetPosition(ACC32(10));
                break;
            case 6000:
                M1_SetPosition(ACC32(20));
                break;
            case 9000:
                M1_SetPosition(ACC32(0));
                break;
            case 12000:
                M1_SetPosition(ACC32(20));
                break;
            case 15000:
                M1_SetPosition(ACC32(0));
                break;
            case 18000:
                ui32PositionStimulatorCnt = 0;
                break;
            default:
			    ;
            	break;
        }
    }
}

void FCCU_0_IRQHandler (void)
{
	uint32_t fccu_ncf_status, fccu_dcm_faults[3];

    /* Stop application */
    M1_SetSpeed(0);
    M1_SetAppSwitch(0);
    bDemoModeSpeed = FALSE;


	fccu_ncf_status = FCCU_GetNCFS();

	FCCU_GetFaults(fccu_dcm_faults);

	FCCU_ClrNCFS(fccu_ncf_status);

	FCCU_ClrFaults(fccu_dcm_faults);
}


/*!
 * @brief   Port interrupt handler
 *
 * @param   void
 *
 * @return  none
 */
void SIUL2_1_IRQHandler(void)
{
	if((SIUL2->DISR0 & SIUL2_DISR0_EIF13_MASK) >0)
	{
	    /* Speed demo */
	    if (bDemoModeSpeed)
	    {
	        /* Stop application */
	        M1_SetSpeed(0);
	        M1_SetAppSwitch(0);
	        bDemoModeSpeed = FALSE;
	    }
	    else
	    {
	        /* Start application */
	        M1_SetAppSwitch(1);
	        bDemoModeSpeed         = TRUE;
	        ui32SpeedStimulatorCnt = 0;
	    }

	    /* Clear external interrupt flag. */
	    SIUL2_ClearExtDmaInterruptStatusFlags(SIUL2, 1U << BOARD_SW3_EIRQ);
	}
	else
	{
        FCCU->NCFF = FCCU_NCF_7;  // NCF7 maps to SW_NCF_0

        SIUL2_ClearExtDmaInterruptStatusFlags(SIUL2, 1U << BOARD_SW2_EIRQ);
	}

    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
  
}

/*!
 *@brief      Initialization of the GPIO pins
 *
 *@param      none
 *
 *@return     none
 */
static void BOARD_InitGPIO(void)
{
    /* Switch off all LEDs */
	LED_RED_INIT(LOGIC_LED_OFF);
	LED_GREEN_INIT(LOGIC_LED_OFF);
	LED_BLUE_INIT(LOGIC_LED_OFF);

    /* Init input switch GPIO. */
    SIUL2_SetGlitchFilterPrescaler(SIUL2, 1U);
    SIUL2_EnableExtInterrupt(SIUL2, BOARD_SW3_EIRQ, kSIUL2_InterruptFallingEdge, 2U);

    SIUL2_SetGlitchFilterPrescaler(SIUL2, 1U);
    SIUL2_EnableExtInterrupt(SIUL2, BOARD_SW2_EIRQ, kSIUL2_InterruptFallingEdge, 2U);
    EnableIRQ(SIUL2_1_IRQn);

}

/*!
 *@brief      SysTick initialization for CPU cycle measurement
 *
 *@param      none
 *
 *@return     none
 */
static void BOARD_InitSysTick(void)
{
    /* Initialize SysTick core timer to run free */
    /* Set period to maximum value 2^24*/
    SysTick->LOAD = 0xFFFFFF;

    /*Clock source - System Clock*/
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    /*Start Sys Timer*/
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/*!
 * @brief LPUART Module initialization (LPUART is a the standard block included e.g. in K66F)
 */
static void init_freemaster_lpuart(void)
{
    lpuart_config_t config;

    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 1;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200U;
    config.enableTx     = false;
    config.enableRx     = false;

    LPUART_Init((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR, &config, BOARD_DEBUG_UART_CLK_FREQ);

    /* Register communication module used by FreeMASTER driver. */
    FMSTR_SerialSetBaseAddress((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR);

}

/*!
 * @brief   static void BOARD_Init(void)
 *           - Initialization of clocks, pins and GPIO
 *
 * @param   void
 *
 * @return  none
 */
static void BOARD_Init(void)
{
    
    /* Init pins set in pin_mux file */
    BOARD_InitBootPins();
    
    /* Initialize clock configuration */
    BOARD_InitBootClocks();
    
    /* Init peripherals set in peripherals file */
    BOARD_InitBootPeripherals();
            
    /* Init GPIO pins */
    BOARD_InitGPIO();
      
}
