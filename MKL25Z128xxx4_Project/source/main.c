
 /*
 *File Name: main.c
 *	Purpose: PES Assignment 3
 *  Created on: Sep 26, 2021
 *  Author: Sachin Mathad
 *	Description: This file contains main function implementations of PES-Assignment-3.
 *	Tools: MCUXpresso IDE, FRDM-KL25Z Dev board
 *
 *	Citations: The driver level implementation of the TSI and LED driver functions are borrowed from
 *	Citations: Alexander G Dean github repo. The implementations are modified to suit assignment requirement
 *	Citations: LOG macro for logging debug data has been implemented from class lecture slides.
 *
 *	Links: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 *	Links: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *	Links: https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 *
 *	Version Control
FW v1.0 - Peer review release
 * Implemented the LED driver and Touch Driver.
 * Implemented LED_Timer_Handler function to provide fixed delay pattern along with color change due to
   touch response.

FW v2.0
 *	Update information from v1.0 to v2.0
 *	Note : No logic changes have been made in this commit.
 *	1. Modularity changes, TSI and LED functions have been separated into different files.
 *	2. Changes in the delay function. Addition of Delay_100_MS.
 *	3. Added default switch case in all switches in LED.c file.
 *	4. Added an Enum of ON OFF flags in LED.h
 *
FW v2.1 -
 *	Update information from v2.0 to v2.1
 *  Deleted additional test files

 FW v2.2 - Final Release
 *	Update information from v2.0 to v2.1
 *  Calibrated delay for release build
 *  Changed logging details, logs only during slider touch, color change and timer start
 */

#include "TSI.h"
#include "LED.h"
#include "global_headers.h"
#include "log.h"

/*
 * @Brief: Program execution begins
 *
 * Parameters:
 *   none
 *
 * Returns: Zero as exit code on successful execution
 */
int main(void)
{
	uint32_t touch_val;
	RGB_Init();
	Touch_Init();
	Test_RGB_Flasher();

	while(1)
	{
  		LED_timer_handler();

		led_update();

		touch_val = Touch_Scan();

		color_check(touch_val);

		led_update();
	}
	return 0;
}


