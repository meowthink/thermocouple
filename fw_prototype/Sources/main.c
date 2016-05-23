/* ###################################################################
**     Filename    : main.c
**     Project     : fw_prototype
**     Processor   : MC9S08DZ60CLC
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-05-05, 09:14, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM.h"
#include "BitsCS.h"
#include "BitsMux.h"
#include "TIKrnl.h"
#include "AD.h"
#include "AS.h"
#include "CAN.h"
#include "BitDCCTL.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
/*
 * Copyright (c) 2016, meowthink
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* Functions for operating Flash through SPI, blocking */
void SFlash_reset(void)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x66); // Op reset enable
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x99); // Op reset
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(0); // Set CS high
}
void SFlash_read(const long addr, char *data, unsigned char size)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x03); // Op read
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr >> 16) & 0xff); // Addr[23:16]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr >> 8) & 0xff); // Addr[15:8]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr) & 0xff); // Addr[7:0]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	for(; size > 0; size --)
	{
		while(!testReg8Bit(SPIS, SPTEF));
		setReg8(SPID, 0);
		while(!testReg8Bit(SPIS, SPRF));
		*data = getReg8(SPID); // Shift in reg content
		data ++;
	}
	BitsCS_SetBit(0); // Set CS high
}
#pragma INLINE
void SFlash_wren(void)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x06); // Op write enable
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(0); // Set CS high
}
#pragma INLINE
void SFlash_wrdi(void)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x04); // Op write disable
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(0); // Set CS high
}
#pragma INLINE
void SFlash_chiperase(void)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x60); // Op chip erase
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(0); // Set CS high
}
void SFlash_4kerase(const long addr)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x20); // Op 4-kiB sector erase
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr >> 16) & 0xff); // Addr[23:16]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr >> 8) & 0xf0); // masked to [15:12]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0); // masked to 0
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(0); // Set CS high
}
void SFlash_program(const long addr, char *data, unsigned char size)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x02); // Op program
	/* Reminder:
	 * For Microchip/SST Flashes, this op is byte program
	 * For Winbond Flashes, this op is page program
	 */
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr >> 16) & 0xff); // Addr[23:16]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr >> 8) & 0xff); // Addr[15:8]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr) & 0xff); // Addr[7:0]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	for(; size > 0; size --)
	{
		while(!testReg8Bit(SPIS, SPTEF));
		setReg8(SPID, *data);
		while(!testReg8Bit(SPIS, SPRF));
		(void)getReg8(SPID);
		data ++;
	}
	BitsCS_SetBit(0); // Set CS high
}
char SFlash_rdsr8()
{
	char data;
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x05); // op read status register
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0);
	while(!testReg8Bit(SPIS, SPRF));
	data = getReg8(SPID); // Shift in reg content
	BitsCS_SetBit(0); // Set CS high
	return data;
}
void SFlash_wrsr8(const char data)
{
	BitsCS_ClrBit(0); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0x01); // op write status register
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, data); // Shift out reg content
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(0); // Set CS high
}

/* Functions for operating AD7793(85/92) through SPI, blocking */
void AD7793_reset(void)
{
	char i;
	BitsCS_ClrBit(1); // Pull CS low
	for (i = 0; i < 4; i ++)
	{
		while(!testReg8Bit(SPIS, SPTEF));
		setReg8(SPID, 0xff); // 32 cycles of high level == reset
		while(!testReg8Bit(SPIS, SPRF));
		(void)getReg8(SPID);
	}
	BitsCS_SetBit(1); // Set CS high
}
char AD7793_getReg8(const char addr)
{
	char data;
	BitsCS_ClrBit(1); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr & 0x7) << 3 | 0x40); // Load addr into comm reg, indicates read
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, 0);
	while(!testReg8Bit(SPIS, SPRF));
	data = getReg8(SPID); // Shift in reg content
	BitsCS_SetBit(1); // Set CS high
	return data;
}
void AD7793_setReg16(const char addr, const short data)
{
	BitsCS_ClrBit(1); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr & 0x7) << 3); // Load addr into comm reg
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (data >> 8) & 0xff); // Shift out data[15:8]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (data) & 0xff); // Shift out data[7:0]
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	BitsCS_SetBit(1); // Set CS high
}
void AD7793_getReg(const char addr, char *data, unsigned char size)
{
	BitsCS_ClrBit(1); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr & 0x7) << 3 | 0x40); // Load addr into comm reg, indicates read
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	for(; size > 0; size --)
	{
		while(!testReg8Bit(SPIS, SPTEF));
		setReg8(SPID, 0);
		while(!testReg8Bit(SPIS, SPRF));
		*data = getReg8(SPID); // Shift in reg content
		data ++;
	}
	BitsCS_SetBit(1); // Set CS high
}
void AD7793_setReg(const char addr, char *data, unsigned char size)
{
	BitsCS_ClrBit(1); // Pull CS low
	while(!testReg8Bit(SPIS, SPTEF));
	setReg8(SPID, (addr & 0x7) << 3); // Load addr into comm reg
	while(!testReg8Bit(SPIS, SPRF));
	(void)getReg8(SPID);
	for(; size > 0; size --)
	{
		while(!testReg8Bit(SPIS, SPTEF));
		setReg8(SPID, *data); // Shift out data
		while(!testReg8Bit(SPIS, SPRF));
		(void)getReg8(SPID);
		data ++;
	}
	BitsCS_SetBit(1); // Set CS high
}

extern volatile char fWrk;
extern volatile short AD_OutV[];

void main(void)
{
  /* Write your local variable definition here */
  char iChn;
  char buf[4];
  char f7792 = 0;
  unsigned short iDID = 0x400;
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

#if 0
{
  /* External flash programming */
  unsigned long len, addr;

  SFlash_reset();
  buf[0] = 0;
  do
  {
	  while (!AS_GetCharsInRxBuf());
	  (void)AS_RecvChar(buf);
  } while (buf[0] != 'E');
  SFlash_wren();
  SFlash_wrsr8(0); // Unprotect
  SFlash_wren();
  SFlash_chiperase();
  while(SFlash_rdsr8() & 0x1); // wait if BUSY
  buf[0] = 0;
  do
  {
	  while (!AS_GetCharsInRxBuf());
	  (void)AS_RecvChar(buf);
  } while (buf[0] != 'F');
  while (!AS_GetCharsInRxBuf());
  (void)AS_RecvChar(&buf[1]);
  while (!AS_GetCharsInRxBuf());
  (void)AS_RecvChar(&buf[2]);
  while (!AS_GetCharsInRxBuf());
  (void)AS_RecvChar(&buf[3]);
  buf[0] = 0;
  len = *(unsigned long *)buf;// buf is now length in word
  for (addr = 0; addr < (len * 2); addr ++)
  {
	  while (!AS_GetCharsInRxBuf());
	  (void)AS_RecvChar(buf);
	  SFlash_wren();
	  SFlash_program(addr, buf, 1);
	  //while(SFlash_rdsr8() & 0x1); // wait if BUSY
  }
  for (;;) {}
}
#endif

  /* Init */
  // Determine device id by listen on CAN bus
  (void)CAN_SetAcceptanceCode(iDID << 5, 0); // 11-bit ID
  (void)CAN_SetAcceptanceMask(0x38, 0); // LSB of ID, RTR & IDE don't care
  //SFlash_reset();
  AD7793_reset();
  Cpu_Delay100US(6); // 500us+ to reset
  //while (AD7793_getReg8(0) & 0x80);
  f7792 = ((AD7793_getReg8(0x4) & 0xf) == 0xa);
  AD7793_setReg16(0x2, 0x8490); // Config: VBIAS on AIN2, Bipolar, Gain = 16, Internal VRef, AIN1
  //AD7793_setReg16(0x2, 0x2490); // Config: BO, Bipolar, Gain = 16, Internal VRef, AIN1
  //AD7793_setReg16(0x2, 0xa490); // Config: Above + VBIAS on AIN2
  AD7793_setReg16(0x1, 0xa00a); // Mode: Internal Full-scale calibration, tSETTLE = 200ms
  Cpu_Delay100US(5000); // 4 conv cycles
  while (AD7793_getReg8(0) & 0x80);
  AD7793_setReg16(0x1, 0x8001); // Mode: Internal Zero-scale calibration, tSETTLE = 4ms
  Cpu_Delay100US(60); // 2 conv cycles
  while (AD7793_getReg8(0) & 0x80);
  // For BO, adjust zero offset + 0x58
  /*AD7793_getReg(0x6, buf, f7792 ? 2 : 3);
  *(short *)&buf += 0x58;
  AD7793_setReg(0x6, buf, f7792 ? 2 : 3);*/
  while (CAN_GetStateRX())
  {
	  iDID += 2;
	  (void)CAN_SetAcceptanceCode(0, 0);
	  while (CAN_GetStateRX())
		  CANRFLG = CANRFLG_RXF_MASK;
	  (void)CAN_SetAcceptanceCode(iDID << 5, 0);
	  Cpu_Delay100US(1000); // 100ms+ is sufficient
	  // (Or longer than the whole init duration for a multiple powered situation)
  } // Loop till a free device id found
  BitDCCTL_ClrVal(); // Chain power up
  // Before start main loop, switch multiplexer on the 1st channel
  iChn = 0;
  BitsMux_PutVal(0x8 | iChn);
  Cpu_EnableInt();

  /* Main working loop */
  for (;;)
  {
	  char fTxSlot = 1;
	  short iResult[8];
	  unsigned short iCJ[8];
	  /* Timeline/ms  0 1 2 3 4 5 6 7 8 9 10 11 12 13 
	   * MCU          SPI1 ~~~~AD~~~~ SPI1 SPI0/Calc
	   * AD7793       Settle~sample~~    ~BO~  ~Idle~ */
	  if(fWrk)
	  {
		  char i;
		  AD7793_setReg16(0x2, 0x8490); // Config: Switch off BO, VBIAS on AIN2
		  //AD7793_setReg16(0x1, 0x0001); // Mode: Continuous Conv, tSETTLE = 4ms
		  AD7793_setReg16(0x1, 0x2001); // Mode: Single Conv, tSETTLE = 4ms
		  //Cpu_Delay100US(50); // 1st sample: 1ms + tSETTLE
		  // AD takes ~200us * 64
		  iCJ[iChn] = 0;
		  for (i = 0; i < 4; i ++) // To oversample 3 bits by 64 samples
		  {
			  (void)AD_MeasureChan(-1, iChn); // 16 samples
			  if (AD_OutV[iChn] & 0x3 > 1)
				  iCJ[iChn] ++;
			  iCJ[iChn] += (unsigned)AD_OutV[iChn] >> 2; // sum 14 effective bits up
		  }
		  // iCJ is 15 effective bits + 1 bit noise
		  //Cpu_Delay100US(21); // 2nd sample: tSETTLE/2
		  while (AD7793_getReg8(0) & 0x80);
		  BitsMux_PutVal(0); // Switch multiplexer off
		  //AD7793_setReg16(0x1, 0x4001); // Mode: Idle
		  AD7793_setReg16(0x2, 0x2490); // Config: Switch on BO, to discharge input lines
		  AD7793_setReg16(0x1, 0x0001); // Mode: Continuous Conv, tSETTLE = 4ms
		  AD7793_getReg(0x3, buf, f7792 ? 2 : 3); // Last result
		  iResult[iChn] = *(short *)buf;
		  SFlash_read(((long)0x10000 + iCJ[iChn]) * 2, buf, 2); // Lookup the cold junction conversion
		  iResult[iChn] += *(short *)buf;// Combine the result
		  SFlash_read(((long)iResult[iChn] * 2) & 0x1fffe, buf, 2); // Lookup the result
		  iResult[iChn] = *(short *)buf;
	      if (!(iChn & 0x3 )) { // Send through CAN every 4 channels
	    	if (CANTFLG & fTxSlot)
	          CAN_AbortMessage(fTxSlot); // Drop old frames if overrun
	        (void)CAN_SendFrame(fTxSlot, iDID + (iChn >> 2), 0, 8, (unsigned char *)&iResult[iChn]);
	        fTxSlot <<= 1;
	        if (fTxSlot >= 0x08)
	          fTxSlot = 1;
	      }
		  iChn ++;
		  iChn &= 0x7; // Loop in 0~7
		  Cpu_Delay100US(20); // 2ms
		  AD7793_setReg16(0x1, 0x4001); // Mode: Idle
		  BitsMux_PutVal(0x8 | iChn); // Switch multiplexer to next channel
		  fWrk = 0;
	  }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
