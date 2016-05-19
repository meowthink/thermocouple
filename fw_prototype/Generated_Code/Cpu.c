/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Cpu.c
**     Project     : fw_prototype
**     Processor   : MC9S08DZ60CLC
**     Component   : MC9S08DZ60_32
**     Version     : Component 01.043, Driver 01.40, CPU db: 3.00.025
**     Datasheet   : MC9S08DZ60 Rev. 3 10/2007
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-05-19, 16:27, # CodeGen: 39
**     Abstract    :
**         This component "MC9S08DZ60_32" contains initialization 
**         of the CPU and provides basic methods and events for 
**         CPU core settings.
**     Settings    :
**
**     Contents    :
**         EnableInt  - void Cpu_EnableInt(void);
**         DisableInt - void Cpu_DisableInt(void);
**         Delay100US - void Cpu_Delay100US(word us100);
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
** @file Cpu.c
** @version 01.40
** @brief
**         This component "MC9S08DZ60_32" contains initialization 
**         of the CPU and provides basic methods and events for 
**         CPU core settings.
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

#pragma MESSAGE DISABLE C4002 /* WARNING C4002: Result not used is ignored */

#include "SM.h"
#include "BitsCS.h"
#include "BitsMux.h"
#include "TIKrnl.h"
#include "AD.h"
#include "AS.h"
#include "CAN.h"
#include "BitDCCTL.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Events.h"
#include "Cpu.h"


/* Global variables */
volatile byte CCR_reg;                 /* Current CCR register */
volatile byte CCR_lock;                /* Nesting level of critical regions */


/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component MC9S08DZ60_32)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(Cpu_Interrupt)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  /*lint -save -e950 Disable MISRA rule (1.1) checking. */
  asm(BGND);
  /*lint -restore Enable MISRA rule (1.1) checking. */
}


/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MC9S08DZ60_32)
**     Description :
**         Disables maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MC9S08DZ60_32)
**     Description :
**         Enables maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_Delay100US (component MC9S08DZ60_32)
**     Description :
**         This method realizes software delay. The length of delay
**         is at least 100 microsecond multiply input parameter
**         [us100]. As the delay implementation is not based on real
**         clock, the delay time may be increased by interrupt
**         service routines processed during the delay. The method
**         is independent on selected speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**     Returns     : Nothing
** ===================================================================
*/
#pragma NO_ENTRY
#pragma NO_EXIT
#pragma MESSAGE DISABLE C5703
void Cpu_Delay100US(word us100)
{
  /* Total irremovable overhead: 16 cycles */
  /* ldhx: 5 cycles overhead (load parameter into register) */
  /* jsr:  5 cycles overhead (jump to subroutine) */
  /* rts:  6 cycles overhead (return from subroutine) */

  /* aproximate irremovable overhead for each 100us cycle (counted) : 8 cycles */
  /* aix:  2 cycles overhead  */
  /* cphx: 3 cycles overhead  */
  /* bne:  3 cycles overhead  */
  /*lint -save  -e950 -e522 Disable MISRA rule (1.1,14.2) checking. */
  asm {
loop:
    /* 100 us delay block begin */
    /*
     * Delay
     *   - requested                  : 100 us @ 8MHz,
     *   - possible                   : 800 c, 100000 ns
     *   - without removable overhead : 792 c, 99000 ns
     */
    pshh                               /* (2 c: 250 ns) backup H */
    pshx                               /* (2 c: 250 ns) backup X */
    ldhx #$0061                        /* (3 c: 375 ns) number of iterations */
label0:
    aix #-1                            /* (2 c: 250 ns) decrement H:X */
    cphx #0                            /* (3 c: 375 ns) compare it to zero */
    bne label0                         /* (3 c: 375 ns) repeat 97x */
    pulx                               /* (3 c: 375 ns) restore X */
    pulh                               /* (3 c: 375 ns) restore H */
    nop                                /* (1 c: 125 ns) wait for 1 c */
    nop                                /* (1 c: 125 ns) wait for 1 c */
    nop                                /* (1 c: 125 ns) wait for 1 c */
    /* 100 us delay block end */
    aix #-1                            /* us100 parameter is passed via H:X registers */
    cphx #0
    bne loop                           /* next loop */
    rts                                /* return from subroutine */
  }
  /*lint -restore Enable MISRA rule (1.1,14.2) checking. */
}

/*
** ===================================================================
**     Method      :  _EntryPoint (component MC9S08DZ60_32)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void _Startup(void);            /* Forward declaration of external startup function declared in file Start12.c */

#pragma NO_FRAME
#pragma NO_EXIT
void _EntryPoint(void)
{
  /* ### MC9S08DZ60_32 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /* Common initialization of the write once registers */
  /* SOPT1: COPT=0,STOPE=0,SCI2PS=0,IICPS=0,??=0,??=0,??=0 */
  setReg8(SOPT1, 0x00U);                
  /* SOPT2: COPCLKS=0,COPW=0,??=0,ADHTS=0,??=0,MCSEL=0 */
  setReg8(SOPT2, 0x00U);                
  /* SPMSC1: LVWF=0,LVWACK=0,LVWIE=0,LVDRE=1,LVDSE=1,LVDE=1,??=0,BGBE=0 */
  setReg8(SPMSC1, 0x1CU);               
  /* SPMSC2: ??=0,??=0,LVDV=0,LVWV=0,PPDF=0,PPDACK=0,??=0,PPDC=0 */
  setReg8(SPMSC2, 0x00U);               
  /*  System clock initialization */
  /*lint -save  -e923 Disable MISRA rule (11.3) checking. */
  if (*(uint8_t*)0xFFAFU != 0xFFU) {   /* Test if the device trim value is stored on the specified address */
    MCGTRM = *(uint8_t*)0xFFAFU;       /* Initialize MCGTRM register from a non volatile memory */
    MCGSC = *(uint8_t*)0xFFAEU;        /* Initialize MCGSC register from a non volatile memory */
  }
  /*lint -restore Enable MISRA rule (11.3) checking. */
  /* MCGC2: BDIV=0,RANGE=1,HGO=0,LP=0,EREFS=1,ERCLKEN=1,EREFSTEN=0 */
  setReg8(MCGC2, 0x26U);               /* Set MCGC2 register */ 
  /* MCGC1: CLKS=2,RDIV=7,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  setReg8(MCGC1, 0xBAU);               /* Set MCGC1 register */ 
  while(MCGSC_OSCINIT == 0U) {         /* Wait until external reference is stable */
  }
  while(MCGSC_IREFST != 0U) {          /* Wait until external reference is selected */
  }
  while((MCGSC & 0x0CU) != 0x08U) {    /* Wait until external clock is selected as a bus clock reference */
  }
  /* MCGC2: BDIV=0,RANGE=1,HGO=0,LP=1,EREFS=1,ERCLKEN=1,EREFSTEN=0 */
  setReg8(MCGC2, 0x2EU);               /* Set MCGC2 register */ 
  /* MCGC1: CLKS=2,RDIV=2,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  setReg8(MCGC1, 0x92U);               /* Set MCGC1 register */ 
  /* MCGC3: LOLIE=0,PLLS=1,CME=0,??=0,VDIV=2 */
  setReg8(MCGC3, 0x42U);               /* Set MCGC3 register */ 
  /* MCGC2: LP=0 */
  clrReg8Bits(MCGC2, 0x08U);            
  while(MCGSC_PLLST == 0U) {           /* Wait until PLL is selected */
  }
  while(MCGSC_LOCK == 0U) {            /* Wait until PLL is locked */
  }
  /* MCGC1: CLKS=0,RDIV=2,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  setReg8(MCGC1, 0x12U);               /* Set MCGC1 register */ 
  while((MCGSC & 0x0CU) != 0x0CU) {    /* Wait until PLL clock is selected as a bus clock reference */
  }
  

  /*** End of PE initialization code after reset ***/
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  __asm   jmp _Startup ;               /* Jump to C startup code */
  /*lint -restore Enable MISRA rule (1.1) checking. */
}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component MC9S08DZ60_32)
**
**     Description :
**         Initializes components and provides common register 
**         initialization. The method is called automatically as a part 
**         of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /* Common initialization of the CPU registers */
  /* PTEDD: PTEDD5=0,PTEDD4=1,PTEDD3=1,PTEDD1=0,PTEDD0=1 */
  clrSetReg8Bits(PTEDD, 0x22U, 0x19U);  
  /* PTED: PTED3=1,PTED0=1 */
  setReg8Bits(PTED, 0x09U);             
  /* PTBD: PTBD1=1,PTBD0=1 */
  setReg8Bits(PTBD, 0x03U);             
  /* PTBPE: PTBPE1=0,PTBPE0=0 */
  clrReg8Bits(PTBPE, 0x03U);            
  /* PTBDD: PTBDD7=1,PTBDD6=1,PTBDD5=1,PTBDD4=1,PTBDD3=1,PTBDD2=1,PTBDD1=1,PTBDD0=1 */
  setReg8(PTBDD, 0xFFU);                
  /* PTDD: PTDD5=1,PTDD3=0,PTDD2=0,PTDD1=0,PTDD0=0 */
  clrSetReg8Bits(PTDD, 0x0FU, 0x20U);   
  /* PTDPE: PTDPE5=0,PTDPE3=0,PTDPE2=0,PTDPE1=0,PTDPE0=0 */
  clrReg8Bits(PTDPE, 0x2FU);            
  /* PTDDD: PTDDD7=1,PTDDD6=1,PTDDD5=1,PTDDD3=1,PTDDD2=1,PTDDD1=1,PTDDD0=1 */
  setReg8Bits(PTDDD, 0xEFU);            
  /* APCTL1: ADPC7=1,ADPC6=1,ADPC5=1,ADPC4=1,ADPC3=1,ADPC2=1,ADPC1=1,ADPC0=1 */
  setReg8(APCTL1, 0xFFU);               
  /* PTASE: PTASE7=0,PTASE6=0,PTASE5=0,PTASE4=0,PTASE3=0,PTASE2=0,PTASE1=0,PTASE0=0 */
  setReg8(PTASE, 0x00U);                
  /* PTBSE: PTBSE1=0,PTBSE0=0 */
  clrReg8Bits(PTBSE, 0x03U);            
  /* PTDSE: PTDSE5=0,PTDSE4=0,PTDSE3=0,PTDSE2=0,PTDSE1=0,PTDSE0=0 */
  clrReg8Bits(PTDSE, 0x3FU);            
  /* PTESE: PTESE7=0,PTESE6=0,PTESE5=0,PTESE4=0,PTESE3=0,PTESE2=0,PTESE0=0 */
  clrReg8Bits(PTESE, 0xFDU);            
  /* PTGSE: PTGSE1=0,PTGSE0=0 */
  clrReg8Bits(PTGSE, 0x03U);            
  /* PTADS: PTADS7=1,PTADS6=1,PTADS5=1,PTADS4=1,PTADS3=1,PTADS2=1,PTADS1=1,PTADS0=1 */
  setReg8(PTADS, 0xFFU);                
  /* PTBDS: PTBDS7=0,PTBDS6=0,PTBDS5=0,PTBDS4=0,PTBDS3=0,PTBDS2=0,PTBDS1=1,PTBDS0=1 */
  setReg8(PTBDS, 0x03U);                
  /* PTDDS: PTDDS7=0,PTDDS6=0,PTDDS5=1,PTDDS4=1,PTDDS3=1,PTDDS2=1,PTDDS1=1,PTDDS0=1 */
  setReg8(PTDDS, 0x3FU);                
  /* PTEDS: PTEDS7=1,PTEDS6=1,PTEDS5=1,PTEDS4=1,PTEDS3=1,PTEDS2=1,PTEDS1=0,PTEDS0=1 */
  setReg8(PTEDS, 0xFDU);                
  /* PTGDS: ??=0,??=0,PTGDS5=0,PTGDS4=0,PTGDS3=0,PTGDS2=0,PTGDS1=1,PTGDS0=1 */
  setReg8(PTGDS, 0x03U);                
  /* PTCDD: PTCDD7=1,PTCDD6=1,PTCDD5=1,PTCDD4=1,PTCDD3=1,PTCDD2=1,PTCDD1=1,PTCDD0=1 */
  setReg8(PTCDD, 0xFFU);                
  /* PTFDD: PTFDD7=1,PTFDD6=1,PTFDD5=1,PTFDD4=1,PTFDD3=1,PTFDD2=1,PTFDD1=1,PTFDD0=1 */
  setReg8(PTFDD, 0xFFU);                
  /* PTGDD: PTGDD5=1,PTGDD4=1,PTGDD3=1,PTGDD2=1 */
  setReg8Bits(PTGDD, 0x3CU);            
  /* ### Shared modules init code ... */
  /* ###  Synchro master "SM" init code ... */
  SM_Init();
  /* ### BitsIO "BitsCS" init code ... */
  /* ### BitsIO "BitsMux" init code ... */
  /* ### TimerInt "TIKrnl" init code ... */
  TIKrnl_Init();
  /* ###  "AD" init code ... */
  AD_Init();
  /* ### Asynchro serial "AS" init code ... */
  AS_Init();
  /* ###  "CAN" init code ... */
  CAN_Init();
  /* ### BitIO "BitDCCTL" init code ... */
  CCR_lock = (byte)0;
  __DI();                              /* Disable interrupts */
}

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
/* Initialization of the CPU registers in FLASH */
/* NVPROT: EPS=3,FPS=0x3F */
static const uint8_t NVPROT_INIT @0x0000FFBDU = 0xFFU;
/* NVOPT: KEYEN=0,FNORED=1,EPGMOD=1,??=1,??=1,??=1,SEC1=1,SEC0=0 */
static const uint8_t NVOPT_INIT @0x0000FFBFU = 0x7EU;
/*lint -restore Enable MISRA rule (1.1) checking. */

/* END Cpu. */

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