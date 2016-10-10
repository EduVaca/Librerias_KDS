/*
 * Timer.c
 *
 *  Created on: 09/10/2016
 *      Author: eduda
 */

#include "Librerias.h"

sTimer gsTimer;

void TimerDelay (unsigned long cuentas)
{
	gsTimer.contador = cuentas;
	while(gsTimer.contador);
}
