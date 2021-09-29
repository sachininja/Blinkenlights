
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
 *	FW v1.1
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
		LOG("Slider Value %d \n\r",touch_val);

		color_check(touch_val);

		led_update();
	}
	return 0;
}


