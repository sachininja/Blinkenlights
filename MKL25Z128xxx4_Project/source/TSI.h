/*
 * File Name: TSI.h
 *
 *  Created on: Sep 26, 2021
 *      Author: Sachin Mathad
 *
 *Purpose: PES Assignment 3
 *Description: This file contains Touch Sense Interface related function declarations
 */

#ifndef TSI_H_
#define TSI_H_

#include "global_headers.h"
#include "log.h"


/************************************************************************************************************/

/*   MACROS  */

/************************************************************************************************************/
 /* offset value to be subtracted from the scanned TSI value */
#define TOUCH_OFFSET 630
/* macro for extracting the count from data register */
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)

/*Capacitive touch channel */
#define CAPACITIVE_CHANNEL_SELECT 10u

/************************************************************************************************************/

/*  FUNCTION DECLARATIONS  */

/************************************************************************************************************/
uint32_t Touch_Scan(void);
void Touch_Init(void);

#endif /* TSI_H_ */
