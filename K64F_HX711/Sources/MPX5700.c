/*
 * MPX5700.c
 *
 *  Created on: 09/10/2016
 *      Author: eduda
 */

#include "Librerias.h"


sAdc gsAdc;

float MPX5700_Leer (void)
{
unsigned short value;

	(void)AD1_Measure(TRUE); /* do conversion and wait for the result */
	(void)AD1_GetValue16(&value); /* get the result into value variable */

//	gsAdc.AD_finished = FALSE; /* reset flag */
//	(void)AD1_Measure(FALSE); /* AD_finished will be set to TRUE once */
//	while(!gsAdc.AD_finished) {
//	/* do something else here... */
//	}
//	/* AD_finished set to TRUE by the interrupt to indicate the result is ready */
//	(void)AD1_GetValue16(&value); /* get the result into value variable */

	return ((5 * (0.0012858 * (value + 0.04))));
//	return (value * 0.0000503);
}
