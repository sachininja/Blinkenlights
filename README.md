README.md
PES-Assignment-3
Blinkenlights - Uses the capacitive touch of the FRDM-KL25Z to change the LED colors on the development board.

*File Name: README

Purpose: PES Assignment 3
Created on: Sep 26, 2021
Author: Sachin Mathad
Description: This file contains README instructions and answers for the extra credit questions.
Tools: MCUXpresso IDE
Citations: The driver level implementation of the TSI and LED driver functions are borrowed from
Citations: Alexander G Dean github repo. The implementations are modified to suit assignment requirement
Citations: LOG macro for logging debug data has been implemented from class lecture slides.
Links: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
Links: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
Links: https://canvas.colorado.edu/courses/75704/files/folder/Lectures
FW v1.0
Code for Assignment 3 for PES, ECEN-5813,
Fall 2021 Description: This repository contains the project for ‘Blinkenlights’. Author: Sachin Mathad
Tools: MCUXpresso IDE, FRDM-KL25Z Dev board

Headers
Log.h, HMI.h, global_headers.h
.C files

Main.c, Human_interface.c
Steps to compile and run
Pull and download the project.
Open the project using MCUXpresso IDE.
Build the project in either release mode or debug mode and flash the build onto the board.

Extra credit answers
Q. What is the address of your main() function?
Answer: Address of main is : 00000d3a

Q. What is the size in bytes of your delay() function, as shown by objdump?
Answer : 17bytes - from 00000d28 to 00000d38
00000d28 :
d28: b082 sub sp, #8
d2a: 9001 str r0, [sp, #4]
d2c: 9b01 ldr r3, [sp, #4]
d2e: 1e5a subs r2, r3, #1
d30: 9201 str r2, [sp, #4]
d32: 2b00 cmp r3, #0
d34: d1fa bne.n d2c <Delay+0x4>
d36: b002 add sp, #8

d38: 4770 bx lr

Q. Show the full disassembly of your delay() function, adding comments to each line to explain the functionality.
Answer: Answer source - stackoverflow.com, ARM intruction set manual.
d28: b082 sub sp, #8
Comment : This instruction is used to reserve the stack. This is done to reserve stack for delay function internal operation.
More the number of variables in delay function, more will be the reservation.
d2a: 9001 str r0, [sp, #4]
Comment: Store the value of r0 into the immediate offset of 4 from the sp(reserved previously).
d2c: 9b01 ldr r3, [sp, #4]
Comment: Store the value of r3 into the immediate offset of 4 from the sp(reserved previously).

d2e: 1e5a subs r2, r3, #1
Comment : SUBS saves the flags of the subtraction operation like N,Z,C and V according to the result. Decrement the given number of iterations.

d30: 9201 str r2, [sp, #4]
Comment: Store the value of r2 into the immediate offset of 4 from the sp.

d32: 2b00 cmp r3, #0
Comment: Compares R3 value with 0 and updates the conditional flags. The compare is required for the branch instruction for the delay loop.

d34: d1fa bne.n d2c <Delay+0x4>
Comment: .n suffix specifies 32 bit Thumb - 2 wide encoding. Disaasemblers do this so that if passed back through assembler results in same object code.
bne - Branch if not equal checks if the compare operation gave a value of non zero and jumps back to d2c, hence performing delay by looping.

d36: b002 add sp, #8
Comment: Add 8 to the value obtained from SP. Values are multiples of 4 in the range 0-1020 for encoding T1, multiples of 4 in the range 0-508 for
encoding T2 and any value in the range 0-4095 for encoding T4.The value obtained is used to return to the calling function after the delay.

d38: 4770 bx lr
Comment: bx - Branch and exchange intruction set. lr holds the return address to the calling function.The LSB of lr also decides the instruction set to
follow after the branch. If the lr LSB is 1, it will treat the code at the address as thumb.
