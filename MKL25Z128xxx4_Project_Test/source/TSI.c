/*
 * TSI.c
 *
 *  Created on: Sep 29, 2021
 *      Author: HP
 */
#include "TSI.h"
#include "global_headers.h"
/*
 * @Brief: SCAN TSI and get data.
 * Parameters:
 *   none
 *
 * Returns: return the touch value
 *Citations: From Alexander Dean github repo, refer to main.c comments for links
*/
uint32_t Touch_Scan(void)
{
	uint32_t scan = 0;
	TSI0->DATA = 	TSI_DATA_TSICH(CAPACITIVE_CHANNEL_SELECT);
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) // waiting for the scan to complete 32 times
	;
	scan = TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; //writing one to clear the end of scan flag
	return scan - TOUCH_OFFSET;
}

/*
 * @Brief: Init the TSI.
 * Parameters:
 *   none
 *
 * Returns: none
 *Citations: From Alexander Dean github repo, refer to main.c comments for links
*/
void Touch_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enabling the clock

	TSI0->GENCS = TSI_GENCS_MODE(0u) | //operating in non-noise mode
				TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
				TSI_GENCS_DVOLT(0u) | //oscillator voltage rails set to default
				TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
				TSI_GENCS_PS(0u) |  // frequency clock divided by one
				TSI_GENCS_NSCN(31u) | //scanning the electrode 32 times
				TSI_GENCS_TSIEN_MASK | //enabling the TSI module
				TSI_GENCS_EOSF_MASK; // writing one to clear the end of scan flag
}


