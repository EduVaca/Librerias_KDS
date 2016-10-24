/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : TU2.c
**     Project     : K64F_HX711
**     Processor   : MK64FN1M0VLQ12
**     Component   : TimerUnit_LDD
**     Version     : Component 01.164, Driver 01.11, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-22, 18:14, # CodeGen: 16
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : TU2
**          Module name                                    : FTM0
**          Counter                                        : FTM0_CNT
**          Counter direction                              : Up
**          Counter width                                  : 16 bits
**          Value type                                     : Optimal
**          Input clock source                             : Internal
**            Counter frequency                            : 3.75 MHz
**          Counter restart                                : On-overrun
**            Overrun period                               : 17.476267 ms
**            Interrupt                                    : Enabled
**              Interrupt                                  : INT_FTM0
**              Interrupt priority                         : medium priority
**          Channel list                                   : 1
**            Channel 0                                    : 
**              Mode                                       : Capture
**                Capture                                  : FTM0_C2V
**                Capture input pin                        : PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/FB_AD10/CMP0_OUT/FTM0_CH2
**                Edge                                     : both edges
**                Maximum time of event                    : 17.476288512 ms
**                Interrupt                                : Enabled
**                  Interrupt                              : INT_FTM0
**                  Interrupt priority                     : medium priority
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Enabled
**              OnChannel0                                 : Enabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init            - LDD_TDeviceData* TU2_Init(LDD_TUserData *UserDataPtr);
**         ResetCounter    - LDD_TError TU2_ResetCounter(LDD_TDeviceData *DeviceDataPtr);
**         GetCaptureValue - LDD_TError TU2_GetCaptureValue(LDD_TDeviceData *DeviceDataPtr, uint8_t...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file TU2.c
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup TU2_module TU2 module documentation
**  @{
*/         

/* MODULE TU2. */

#include "Events.h"
#include "TU2.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* List of channels used by component */
static const uint8_t ChannelDevice[TU2_NUMBER_OF_CHANNELS] = {0x02U};

/* Table of channels mode / 0 - compare mode, 1 - capture mode */
static const uint8_t ChannelMode[TU2_NUMBER_OF_CHANNELS] = {0x01U};


typedef struct {
  LDD_TEventMask EnEvents;             /* Enable/Disable events mask */
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} TU2_TDeviceData;

typedef TU2_TDeviceData *TU2_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static TU2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static TU2_TDeviceDataPtr INT_FTM0__DEFAULT_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_TEventMask)(LDD_TIMERUNIT_ON_CHANNEL_0 | LDD_TIMERUNIT_ON_COUNTER_RESTART)
#define AVAILABLE_PIN_MASK (LDD_TPinMask)(TU2_CHANNEL_0_PIN)
#define LAST_CHANNEL 0x00U

/* Internal method prototypes */
/*
** ===================================================================
**     Method      :  TU2_Init (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* TU2_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  TU2_TDeviceData *DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_FTM0__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* SIM_SCGC6: FTM0=1 */
  SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
  /* SIM_SCGC5: PORTC=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
  /* FTM0_MODE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,FAULTIE=0,FAULTM=0,CAPTEST=0,PWMSYNC=0,WPDIS=1,INIT=0,FTMEN=0 */
  FTM0_MODE = (FTM_MODE_FAULTM(0x00) | FTM_MODE_WPDIS_MASK); /* Set up mode register */
  /* FTM0_SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TOF=0,TOIE=0,CPWMS=0,CLKS=0,PS=0 */
  FTM0_SC = (FTM_SC_CLKS(0x00) | FTM_SC_PS(0x00)); /* Clear status and control register */
  /* FTM0_CNTIN: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,INIT=0 */
  FTM0_CNTIN = FTM_CNTIN_INIT(0x00);   /* Clear counter initial register */
  /* FTM0_CNT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNT=0 */
  FTM0_CNT = FTM_CNT_COUNT(0x00);      /* Reset counter register */
  /* FTM0_C0SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C0SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C1SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C1SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C2SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C2SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C3SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C3SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C4SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C4SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C5SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C5SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C6SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C6SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_C7SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM0_C7SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM0_MOD: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,MOD=0xFFFF */
  FTM0_MOD = FTM_MOD_MOD(0xFFFF);      /* Set up modulo register */
  /* FTM0_C2SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=1,MSB=0,MSA=0,ELSB=1,ELSA=1,??=0,DMA=0 */
  FTM0_C2SC = (FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK); /* Set up channel status and control register */
  /* PORTC_PCR5: ISF=0,MUX=7 */
  PORTC_PCR5 = (uint32_t)((PORTC_PCR5 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
  DeviceDataPrv->EnEvents = 0x0101U;   /* Enable selected events */
  /* NVICIP42: PRI42=0x70 */
  NVICIP42 = NVIC_IP_PRI42(0x70);
  /* NVICISER1: SETENA|=0x0400 */
  NVICISER1 |= NVIC_ISER_SETENA(0x0400);
  /* FTM0_SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TOF=0,TOIE=1,CPWMS=0,CLKS=1,PS=4 */
  FTM0_SC = (FTM_SC_TOIE_MASK | FTM_SC_CLKS(0x01) | FTM_SC_PS(0x04)); /* Set up status and control register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_TU2_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  TU2_ResetCounter (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_ResetCounter(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  FTM_PDD_InitializeCounter(FTM0_BASE_PTR);
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TU2_GetCaptureValue (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the content of capture register specified by the
**         parameter ChannelIdx. This method is available when at least
**         one channel is configured.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         ChannelIdx      - Index of the component
**                           channel.
**     @param
**         ValuePtr        - Pointer to return value of the
**                           capture register.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_PARAM_INDEX - ChannelIdx parameter is
**                           out of possible range
**                           ERR_NOTAVAIL -  The capture mode is not
**                           selected for selected channel.
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_GetCaptureValue(LDD_TDeviceData *DeviceDataPtr, uint8_t ChannelIdx, TU2_TValueType *ValuePtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Parameter test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (ChannelIdx > LAST_CHANNEL) {     /* Is the channel index out of range? */
    return ERR_PARAM_INDEX;            /* If yes then error */
  }
  if ((ChannelMode[ChannelIdx]) != 1u) { /* Is the channel in capture mode? */
    return ERR_NOTAVAIL;               /* If not then error */
  }
  *ValuePtr = (TU2_TValueType)(FTM_PDD_ReadChannelValueReg(FTM0_BASE_PTR, ChannelDevice[ChannelIdx]));
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TU2_Interrupt (component TimerUnit_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(TU2_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  TU2_TDeviceDataPtr DeviceDataPrv = INT_FTM0__DEFAULT_RTOS_ISRPARAM;

  LDD_TEventMask State = 0U;

  if ((FTM_PDD_GetOverflowInterruptFlag(FTM0_BASE_PTR)) != 0U) { /* Is the overflow interrupt flag pending? */
    State |= LDD_TIMERUNIT_ON_COUNTER_RESTART; /* and set mask */
  }
  if ((FTM_PDD_GetChannelInterruptFlag(FTM0_BASE_PTR, ChannelDevice[0])) != 0U) { /* Is the channel interrupt flag pending? */
    State |= LDD_TIMERUNIT_ON_CHANNEL_0; /* and set mask */
  }
  State &= DeviceDataPrv->EnEvents;    /* Handle only enabled interrupts */
  if (State & LDD_TIMERUNIT_ON_COUNTER_RESTART) { /* Is the overflow interrupt flag pending? */
    FTM_PDD_ClearOverflowInterruptFlag(FTM0_BASE_PTR); /* Clear flag */
    TU2_OnCounterRestart(DeviceDataPrv->UserDataPtr); /* Invoke OnCounterRestart event */
  }
  if (State & LDD_TIMERUNIT_ON_CHANNEL_0) { /* Is the channel 0 interrupt flag pending? */
    FTM_PDD_ClearChannelInterruptFlag(FTM0_BASE_PTR, ChannelDevice[0]); /* Clear flag */
    TU2_OnChannel0(DeviceDataPrv->UserDataPtr); /* Invoke OnChannel0 event */
  }
}

/* END TU2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
