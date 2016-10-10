/*
 * Timer.h
 *
 *  Created on: 09/10/2016
 *      Author: eduda
 */

#ifndef SOURCES_TIMER_TIMER_H_
#define SOURCES_TIMER_TIMER_H_


typedef struct
{
	unsigned long contador;
}sTimer;

extern sTimer gsTimer;

void TimerDelay (unsigned long cuentas);
void TimerInterrupcion (void);

#endif /* SOURCES_TIMER_TIMER_H_ */
