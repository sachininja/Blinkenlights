# PES-Assignment-3
Blinkenlights - Uses the capacitive touch of the FRDM-KL25Z to change the LED colors on the development board.

 *File Name: README
 *	Purpose: PES Assignment 3
 *  Created on: Sep 26, 2021
 *  Author: Sachin Mathad
 *	Description: This file contains README instructions and answers for the extra credit questions.   
 *	Tools: MCUXpresso IDE
 * 	Citations: The driver level implementation of the TSI and LED driver functions are borrowed from
 *	Citations: Alexander G Dean github repo. The implementations are modified to suit assignment requirement
 *	Citations: LOG macro for logging debug data has been implemented from class lecture slides.
 *
 *	Links: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 *	Links: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *	Links: https://canvas.colorado.edu/courses/75704/files/folder/Lectures

 FW v2.1 -<br /> 
 *	Update information from v2.0 to v2.1<br /> 
 *  Deleted additional test files<br /> 
 *
 *
 FW v2.2 - Final Release<br /> 
 *	Update information from v2.0 to v2.1<br /> 
 *  Deleted additional test files<br /> 
 *  Calibrated delay for release build<br /> 
 *  Changed logging details, logs only during slider touch, color change and timer start<br /> 
 



------------------------------------------------------------------------------

Code for Assignment 3 for PES, ECEN-5813,<br /> Fall 2021 Description: This repository contains the project for ‘Blinkenlights’.
Author: Sachin Mathad<br /> 
Tools: MCUXpresso IDE, FRDM-KL25Z Dev board<br />

Headers<br />
Log.h, LED.h, TSI.h, global_headers.h<br />
.C files<br />

Main.c, LED.c, TSI.c <br />
Steps to compile and run<br />
*Clone and download the project. <br />
*Open the project using MCUXpresso IDE. <br />
*Build the project in either release mode or debug mode and flash the build onto the board. <br />
*If the debug logs do not work, try putting the IDE in the Debug mode, build the project, flash the debug.launch under the debug<br />
folder by right click -> Debug As -> Project PE Debug

Note: The FW uses 2 different delays for the Debug version and Release version. Debug version requires a larger value due to the logging overhead.

Version Control <br />
FW v1.0 - Peer review release<br />
 * Implemented the LED driver and Touch Driver.<br />
 * Implemented LED_Timer_Handler function to provide fixed delay pattern along with color change due to <br />
   touch response. 
 
FW v2.0 - <br />
 *	Update information from v1.1 to v2.0<br />
 *	Note : No logic changes have been made in this commit.<br />
 *	1. Modularity changes, TSI and LED functions have been separated into different files.<br />
 *	2. Changes in the delay function. Addition of Delay_100_MS.<br />
 *	3. Added default switch case in all switches in LED.c file.<br />
 *	4. Added an Enum of ON OFF flags in LED.h<br />
 
 
FW v2.1 <br />
 *	Update information from v2.0 to v2.1<br />
 *  Deleted additional test files<br />
 *
 *  
 FW v2.2 - Final Release<br />
 *	Update information from v2.0 to v2.1<br />
 *  Deleted additional test files<br />
 *  Calibrated delay for release build<br />
 *  Changed logging details, logs only during slider touch, color change and timer start<br />
 */

----------------------------------------------------------------------------------
Extra credit answers<br />
Q. What is the address of your main() function?<br />
Answer: Address of main is : 00000d3a <br />

Q. What is the size in bytes of your delay() function, as shown by objdump?<br />
Answer : 17bytes - from 00000d28 to 00000d38  <br />
00000d28 <Delay>:<br />
 d28:	b082      	sub	sp, #8<br />
 d2a:	9001      	str	r0, [sp, #4]<br />
 d2c:	9b01      	ldr	r3, [sp, #4]<br />
 d2e:	1e5a      	subs	r2, r3, #1<br />
 d30:	9201      	str	r2, [sp, #4]<br />
 d32:	2b00      	cmp	r3, #0<br />
 d34:	d1fa      	bne.n	d2c <Delay+0x4><br />
 d36:	b002      	add	sp, #8<br /><br />
 d38:	4770      	bx	lr<br />

Q. Show the full disassembly of your delay() function, adding comments to each line to explain the
functionality.<br />
Answer: Answer source - stackoverflow.com, ARM intruction set manual. <br />
d28:	b082      	sub	sp, #8<br />
Comment : This instruction is used to reserve the stack. This is done to reserve stack for delay function internal operation.<br />
		More the number of variables in delay function, more will be the reservation.<br /> 
 d2a:	9001      	str	r0, [sp, #4]<br />
Comment: Store the value of r0 into the immediate offset of 4 from the sp(reserved previously).<br />
 d2c:	9b01      	ldr	r3, [sp, #4]<br />
Comment: Store the value of r3 into the immediate offset of 4 from the sp(reserved previously).<br />

 d2e:	1e5a      	subs	r2, r3, #1<br />
Comment : SUBS saves the flags of the subtraction operation like N,Z,C and V according to the result. Decrement the given number of iterations.<br />

 d30:	9201      	str	r2, [sp, #4]<br />
Comment: Store the value of r2 into the immediate offset of 4 from the sp.<br />

 d32:	2b00      	cmp	r3, #0<br />
Comment: Compares R3 value with 0 and updates the conditional flags. The compare is required for the branch instruction for the delay loop. <br />

 d34:	d1fa      	bne.n	d2c <Delay+0x4><br />
Comment: .n suffix specifies 32 bit Thumb - 2 wide encoding. Disaasemblers do this so that if passed back through assembler results in same object code.<br />
	bne - Branch if not equal checks if the compare operation gave a value of non zero and jumps back to d2c, hence performing delay by looping. <br />

 d36:	b002      	add	sp, #8<br />
Comment:   Add 8 to the value obtained from SP. Values are multiples of 4 in the range 0-1020 for encoding T1, multiples of 4 in the range 0-508 for<br />
encoding T2 and any value in the range 0-4095 for encoding T4.The value obtained is used to return to the calling function after the delay. <br />

 d38:	4770      	bx	lr <br />
Comment: bx - Branch and exchange intruction set. lr holds the return address to the calling function.The LSB of lr also decides the instruction set to <br />
follow after the branch. If the lr LSB is 1, it will treat the code at the address as thumb.<br />
