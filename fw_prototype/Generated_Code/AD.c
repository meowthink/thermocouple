/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : AD.c
**     Project     : fw_prototype
**     Processor   : MC9S08DZ60CLC
**     Component   : ADC
**     Version     : Component 01.697, Driver 01.30, CPU db: 3.00.025
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-05-21, 23:15, # CodeGen: 43
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AD
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Disabled
**          A/D channels                                   : 8
**            Channel0                                     : 
**              A/D channel (pin)                          : PTA7_PIA7_ADP7_IRQ
**              A/D channel (pin) signal                   : 
**            Channel1                                     : 
**              A/D channel (pin)                          : PTA6_PIA6_ADP6
**              A/D channel (pin) signal                   : 
**            Channel2                                     : 
**              A/D channel (pin)                          : PTA5_PIA5_ADP5
**              A/D channel (pin) signal                   : 
**            Channel3                                     : 
**              A/D channel (pin)                          : PTA4_PIA4_ADP4
**              A/D channel (pin) signal                   : 
**            Channel4                                     : 
**              A/D channel (pin)                          : PTA3_PIA3_ADP3_ACMP1O
**              A/D channel (pin) signal                   : 
**            Channel5                                     : 
**              A/D channel (pin)                          : PTA2_PIA2_ADP2_ACMP1MINUS
**              A/D channel (pin) signal                   : 
**            Channel6                                     : 
**              A/D channel (pin)                          : PTA1_PIA1_ADP1_ACMP1PLUS
**              A/D channel (pin) signal                   : 
**            Channel7                                     : 
**              A/D channel (pin)                          : PTA0_PIA0_ADP0_MCLK
**              A/D channel (pin) signal                   : 
**          A/D resolution                                 : 12 bits
**          Conversion time                                : 46 �s
**          Low-power mode                                 : Enabled
**          Sample time                                    : long
**          External trigger                               : Disabled
**          Internal trigger                               : Disabled
**          Number of conversions                          : 16
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents    :
**         MeasureChan - byte AD_MeasureChan(bool WaitForResult, byte Channel);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
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
** @file AD.c
** @version 01.30
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD_module AD module documentation
**  @{
*/         


/* MODULE AD. */

#include "AD.h"



static void AD_MainMeasure(void);
/*
** ===================================================================
**     Method      :  MainMeasure (component ADC)
**
**     Description :
**         The method performs the conversion of the input channels in 
**         the polling mode.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define STOP            0x00U          /* STOP state           */
#define MEASURE         0x01U          /* MESURE state         */
#define CONTINUOUS      0x02U          /* CONTINUOS state      */
#define SINGLE          0x03U          /* SINGLE state         */

static const  byte Table[8] = {0x01U,0x02U,0x04U,0x08U,0x10U,0x20U,0x40U,0x80U};  /* Table of mask constants */

static const  byte Channels[8] = {0x07U,0x06U,0x05U,0x04U,0x03U,0x02U,0x01U,0x00U
};  /* Contents for the device control register */

static volatile byte OutFlg;           /* Measurement finish flag */
static volatile byte SumChan;          /* Number of measured channels */
static volatile byte ModeFlg;          /* Current state of device */

volatile word AD_OutV[8];              /* Sum of measured values */





/*
** ===================================================================
**     Method      :  MainMeasure (component ADC)
**
**     Description :
**         The method performs the conversion of the input channels in 
**         the polling mode.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void AD_MainMeasure(void)
{
  byte SumCnt;                         /* Number of measured channels */
  TWREG tmpTwreg;

  for (SumCnt=0U; SumCnt<16U; SumCnt++) {
    ADCSC1 = Channels[SumChan];        /* Start measurement of next channel */
    while (ADCSC1_COCO == 0U) {}       /* Wait for AD conversion complete */
    /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
    tmpTwreg.b.high = ADCRH;
    tmpTwreg.b.low = ADCRL;
    AD_OutV[SumChan] += tmpTwreg.w;    /* Save measured value */
    /*lint -restore Enable MISRA rule (1.2) checking. */
  }
  /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
  OutFlg |= Table[SumChan];            /* Value of measured channel is available */
  /*lint -restore Enable MISRA rule (1.2) checking. */
  ModeFlg = STOP;                      /* Set the device to the stop mode */
}
/*
** ===================================================================
**     Method      :  AD_HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD_HWEnDi(void)
{
  if (ModeFlg) {                       /* Start or stop measurement? */
    /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
    OutFlg &= (byte)(~(byte)Table[SumChan]); /* Output value isn't available */
    /*lint -restore Enable MISRA rule (1.2) checking. */
    AD_OutV[SumChan] = 0U;             /* Set variable for storing measured values to 0 */
    AD_MainMeasure();
  }
}

/*
** ===================================================================
**     Method      :  AD_MeasureChan (component ADC)
*/
/*!
**     @brief
**         This method performs measurement on one channel. (Note: If
**         the [number of conversions] is more than one the conversion
**         of the A/D channel is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of
**                           conversion. If the [interrupt service] is
**                           disabled and at the same time a [number of
**                           conversions] is greater than 1, the
**                           WaitForResult parameter is ignored and the
**                           method waits for each result every time.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
*/
/* ===================================================================*/
byte PE_AD_MeasureChan(byte Channel)
{
  if (Channel >= 8U) {                 /* Is channel number greater than or equal to 8 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = SINGLE;                    /* Set state of device to the measure mode */
  SumChan = Channel;                   /* Set required channel */
  AD_HWEnDi();                         /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD_Init(void)
{
  /* ADCSC1: COCO=0,AIEN=0,ADCO=0,ADCH4=1,ADCH3=1,ADCH2=1,ADCH1=1,ADCH0=1 */
  setReg8(ADCSC1, 0x1FU);              /* Disable the module */ 
  /* ADCSC2: ADACT=0,ADTRG=0,ACFE=0,ACFGT=0,??=0,??=0,??=0,??=0 */
  setReg8(ADCSC2, 0x00U);              /* Disable HW trigger and autocompare */ 
  OutFlg = 0U;                         /* No measured value */
  SumChan = 0U;
  ModeFlg = STOP;                      /* Device isn't running */
  /* ADCCFG: ADLPC=1,ADIV1=1,ADIV0=1,ADLSMP=1,MODE1=0,MODE0=1,ADICLK1=0,ADICLK0=1 */
  setReg8(ADCCFG, 0xF5U);              /* Set prescaler bits */ 
}


/* END AD. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
