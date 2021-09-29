/*
 * 	File Name: LED.c
 *
 *  Created on: Sep 26, 2021
 *  Author: Sachin Mathad, Alexander Dean
 *	Tools: MCUXpresso IDE, FRDM-KL25Z Dev board
 *	Purpose: PES Assignment 3
 *	Description: This file contains LED related function related function definitions
 */


#include "LED.h"
#include "log.h"

/* Debug strings for printing the LED info and current time delay  */
#ifdef DEBUG
static char *color_string[] = { "RED", "GREEN", "BLUE", "WHITE"};
static char *time_string[] = {"500", "1000", "2000", "3000"};
#endif

/* THe structure is define */
t_LED LED[4] = {{RED, MASK(RED_LED_SHIFT)},
		{GREEN, MASK(GREEN_LED_SHIFT)},
		{BLUE, MASK(BLUE_LED_SHIFT)},
		{WHITE, (MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT)), (MASK(BLUE_LED_SHIFT))},

};


//uint32_t ontime_delay[5] = {MS_DELAY_100, MS_DELAY_500, MS_DELAY_1000, MS_DELAY_2000, MS_DELAY_3000};

/* global varialbe to update the current blinking color, the color is updated baed on the touch value range*/
static volatile t_color current_blinking_color = WHITE;

/* The array is declared to loop around the timing cycle of 500, 1000, 2000 and 3000ms */
static volatile uint32_t  on_current_delay[4] = { DELAY_500, DELAY_1000, DELAY_2000, DELAY_3000};

/* The flags decalre which cycle is active currently, on timer delay cycle or the off cycle delay cycle */
static volatile uint8_t run_on_timer = ON;
static volatile uint8_t run_off_timer = OFF;

/*
 * @Brief: Hard delay function.
 *
 * Parameters:
 *   Time delay in number of  ticks
 *
 * Returns: none
 */
void Delay(volatile unsigned int time_del) {
		while (time_del--) {
			//__asm("");
		}
}

/*
 * @Brief: Hard delay function for 100MS.
 *
 * Parameters:
 *   none
 *
 * Returns: none
 */
void Delay_MS_100() {
	volatile unsigned int time_del = MS_DELAY_100;
	while (time_del--) {
			//__asm("");
		}
}
/*
 * @Brief: This function initializes the LED port pins for RED, GREEN and BLUE LED.
 * Open clock gating for PORT B and D.
 * Make pins GPIO and output.
 * Turnoff all LEDs
 *
 * Parameters:
 *   none
 *Citation: Implementation taken from Alexander Dean, github repo. For more information, refer to main.c description.
 * Returns: none
 */
void RGB_Init()
{
	/* Enable clock to Port B and Port D*/
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	/* Make 3 pins GPIO*/
	PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);

	/* Set ports to outputs */
	PTB->PDDR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
	PTD->PDDR |= MASK(BLUE_LED_SHIFT);

	/* Turn off all the LEDs */
	PTB->PSOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
	PTD->PSOR |= MASK(BLUE_LED_SHIFT);
}

/*
 * @Brief: This function tests all the LED colors RGB and White (all on)
 *
 * Parameters:
 *   none
 *
 * Returns: none
 *
 */
void Test_RGB_Flasher(void)
{

	/* Turn on each LED one after other for 500ms and turn off for 100ms*/
	/*Enter the color, on time and off time of each of the LEDs  */
	blink_led(RED, MS_DELAY_500_INIT, MS_DELAY_100_INIT);
	blink_led(GREEN, MS_DELAY_500_INIT, MS_DELAY_100_INIT);
	blink_led(BLUE, MS_DELAY_500_INIT, MS_DELAY_100_INIT);
	blink_led(WHITE, MS_DELAY_100_INIT, MS_DELAY_100_INIT);
	blink_led(WHITE, MS_DELAY_100_INIT, MS_DELAY_100_INIT);
}

/*
 * @Brief: This function turns on and off the required LED. This is a stopping function
 *
 * Parameters:
 *   Color to blink, on time of LED and off time of LED
 *
 * Returns: none
 *
*/
void blink_led( t_color color, uint32_t ontime, uint32_t offtime)
{
	/*RED and GREEN LED have the same port implementation, t_LED struct contains the mask for all LEDs  */
		switch(color)
		{
			case RED:
			case GREEN:
			{
				PTB->PCOR  |=  LED[color].mask1;
				Delay(ontime);
				PTB->PSOR |= LED[color].mask1;
				Delay(offtime);
				break;
			}
			case BLUE:
			{
				PTD->PCOR  |=  LED[color].mask1;
				Delay(ontime);
				PTD->PSOR |= LED[color].mask1;
				Delay(offtime);
				break;
			}
	/* The White LED will need two masks, one from blue Port D and the other from Red and Green LED port B */
			case WHITE:
			{
				PTB->PCOR  |=  LED[color].mask1;
				PTD->PCOR |= LED[color].mask2;
				Delay(ontime);
				PTB->PSOR  |=  LED[color].mask1;
				PTD->PSOR |= LED[color].mask2;
				Delay(offtime);
				break;
			}
			default: break;// do nothing
		}
}

/*
 * @Brief: This function turns on  the required LED. This function is called from a polling function every 100ms
 * to update the status of the LED if run_on_timer is set.
 *
 * Parameters:
 *   Color to blink.
 *
 * Returns: none
 *
*/
void blink_led_on( t_color color)
{
#ifdef DEBUG
	/*Debug def to print when there is a color change */
	static uint8_t previous_color = WHITE;
#endif
	/* Turn off all the LEDs, do not want to mix colors */
		PTB->PSOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
		PTD->PSOR |= MASK(BLUE_LED_SHIFT);

		switch(color)
		{
			case RED:
			case GREEN:
			{
				PTB->PCOR  |=  LED[color].mask1;
				break;
			}
			case BLUE:
			{
				PTD->PCOR  |=  LED[color].mask1;
				break;
			}
			case WHITE:
			{
				PTB->PCOR  |=  LED[color].mask1;
				PTD->PCOR |= LED[color].mask2;
				break;
			}
			default: break;// do nothing
		}
#ifdef DEBUG
		if(previous_color != color )
		{
			LOG("CHANGE LED TO %s\n\r", color_string[color] );
			previous_color = color;
		}
#endif
}

/*
 * @Brief: This function turns off the required LED. This function is called from a polling function every 100ms
 * to update the status of the LED if the run_off_timer is set.
 *
 * Parameters:
 *   Color to blink.
 *
 * Returns: none
 *
*/
void blink_led_off( t_color color)
{

		switch(color)
		{
			case RED:
			case GREEN:
			{
				PTB->PSOR |= LED[color].mask1;
				break;
			}
			case BLUE:
			{
				PTD->PSOR |= LED[color].mask1;
				break;
			}
			case WHITE:
			{
				PTB->PSOR  |=  LED[color].mask1;
				PTD->PSOR |= LED[color].mask2;
				break;
			}
			default: break;// do nothing
		}
}

/*
 * @Brief: This function handles the delay of 100ms, 500ms, 1000ms, 2000ms and 3000ms.
 * This function is called every 100ms, status of the run_off_timer, run_on_timer flags are
 * updated here.
 *
 * Parameters:
 *   none
 *
 * Returns: none
 *
*/
void LED_timer_handler()
{
/* The counters count the elapsed time * 100ms */
	static volatile uint8_t on_counter = OFF;
	static volatile uint8_t off_counter = OFF;
	/* i helps in the looping the timer from 500ms to 3000ms and back with the help of on_current_delay array. */
	static volatile uint8_t i=0;
	static volatile t_current_delay off_current_delay = DELAY_500;

#ifdef DEBUG
	/*The function is called every 100ms but print the delay value just once, after every change in delay */
	static uint8_t print_timer_once = 1;

	if(print_timer_once == 1)
	{
		LOG("STARTED TIMER %s\n\r", time_string[i]);
		print_timer_once = 0;
	}
#endif

/*If the on timer is running, update the on counter and flag until the on timer expires, else update the off counter  */
/* This if case will run for 500ms, 1000ms, 2000ms or 3000ms */
	if(run_on_timer)
	{

		Delay_MS_100();
		on_counter++;

		if(on_counter == on_current_delay[i])
		{
			i++;
			if(i == 4)
			{
				i = 0;
			}
			on_counter = OFF;
			run_on_timer = OFF;
			run_off_timer = ON;
#ifdef DEBUG
			print_timer_once = 1;
#endif
		}
		else
		{
			// do nothing
		}
	}
/* run the off timer, runs for 500ms after every on time delay */
	else if(run_off_timer)
	{
		Delay_MS_100();
		off_counter++;
		if(off_counter == off_current_delay)
		{
			off_current_delay++;
			if(off_current_delay > DELAY_500) // change
			{
				off_current_delay = DELAY_500 ;
			}
			off_counter = OFF;
			run_on_timer = ON;
			run_off_timer = OFF;
		}
		else
		{
			// do nothing
		}
	}

}

/*
 * @Brief: Update the LED based on the current active color and the on or off timer running
 *
 * Parameters:
 *   none
 *
 * Returns: none
 *
*/
void led_update()
{
	if(run_on_timer)
	{
		blink_led_on(current_blinking_color);
	}
	else if(run_off_timer)
	{
		blink_led_off(current_blinking_color);
	}
}

/*
 * @Brief: Check the range of the TSI, based on that, update the colors RED, GREEN and BLUE.
 * Values in the left of the touch pad blinks RED
 * Values in the center of the touch pad blinks GREEN
 * Values in the right of the touch pad blinks BLUE.
 * Make sure to touch the pad with standard amount of force.
 * Parameters:
 *   touch_val - sensed from the TSI module
 *
 * Returns: none
 *
*/
void color_check(uint32_t touch_val)
{
	if(touch_val >= RED_TOUCH_RANGE_LOW && touch_val < RED_TOUCH_RANGE_HIGH)
	{
		current_blinking_color = RED;
	}
	else if(touch_val >= GREEN_TOUCH_RANGE_LOW && touch_val < GREEN_TOUCH_RANGE_HIGH)
	{
		current_blinking_color = GREEN;
	}

	else if(touch_val >= BLUE_TOUCH_RANGE_LOW && touch_val < BLUE_TOUCH_RANGE_HIGH)
	{
		current_blinking_color = BLUE;
	}
	else
	{
		//do nothing
	}
}

