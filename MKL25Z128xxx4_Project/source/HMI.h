/*
 * File Name: HMI.h
 *
 *  Created on: Sep 26, 2021
 *      Author: Sachin Mathad
 *
 *Purpose: PES Assignment 3
 *Description: This file contains LED and touch related function declarations
 */
#ifndef HMI_H_
#define HMI_H_

#include "global_headers.h"

/*
 * @Brief: Enum to number colors.
 * Type : enum
 *
 */
typedef enum{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	WHITE = 3
}t_color;


#define RED_LED_SHIFT   (18)	// on port B shift 18
#define GREEN_LED_SHIFT (19)	// on port B shift 19
#define BLUE_LED_SHIFT  (1)		// on port D shift 1

/* value for delay during debug mode, debug mode takes time to execute printf hence lesser delay */
#ifdef DEBUG
#define MS_DELAY_50  65000
#else
/*value of delay during release mode, no overhead of printf */
#define MS_DELAY_50  135000  // value for delay
#endif

#define MS_DELAY_3000 (MS_DELAY_100 * 30)
#define MS_DELAY_2000 (MS_DELAY_100 * 20)
#define MS_DELAY_1000 (MS_DELAY_100 * 10)
#define MS_DELAY_500  (MS_DELAY_100 * 5)
#define MS_DELAY_100  (MS_DELAY_50 * 2)

/*Delay during init changes due to the lack of TSI update overhead */
#define MS_DELAY_100_INIT (250000)
#define MS_DELAY_500_INIT (MS_DELAY_100_INIT * 5)
#define LED1_SHIFT (1)	// on port A
#define LED2_SHIFT (2)	// on port A

#define MASK(x) (1UL << (x))

/*
 * @Brief: Struct to change the colors with the required mask value
 * White requires 2 masks, Port B and Port D mask.
 * Type : struct element - color - RGB
 * 							mask1 - for PORTB
 * 							mask 2 - for PORTD
 *
 */
typedef struct
{
	t_color color;
	unsigned mask1;
	unsigned mask2;

}t_LED;


/*
 * @Brief: Enum to track the delay for LED blink. Roll over to 500 after 3000.
 */
typedef enum
{
	//DELAY_100 = 1,
	DELAY_500 = 5,
	DELAY_1000 = 10,
	DELAY_2000 = 20,
	DELAY_3000 = 30
}t_current_delay;

void blink_led( t_color color, uint32_t ontime, uint32_t offtime);
void blink_led_off( t_color color);
void blink_led_on( t_color color);
void LED_timer_handler(void);
void led_update(void);
void color_check(uint32_t touch_val);
void Test_RGB_Flasher(void);
void RGB_Init(void);

#define TOUCH_OFFSET 630  // offset value to be subtracted from the scanned TSI value
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register

#define RED_TOUCH_RANGE_LOW 270u
#define RED_TOUCH_RANGE_HIGH 850u

#define GREEN_TOUCH_RANGE_LOW 850u
#define GREEN_TOUCH_RANGE_HIGH 1525u

#define BLUE_TOUCH_RANGE_LOW 1525u
#define BLUE_TOUCH_RANGE_HIGH 4000u

#define CAPACITIVE_CHANNEL_SELECT 10u

uint32_t Touch_Scan(void);
void Touch_Init(void);

#endif/*LED.h */
