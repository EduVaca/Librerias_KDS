/*
 * MPX5700.h
 *
 *  Created on: 09/10/2016
 *      Author: eduda
 */

#ifndef SOURCES_MPX5700_H_
#define SOURCES_MPX5700_H_

typedef struct
{
	unsigned char AD_finished;
}sAdc;

extern sAdc gsAdc;

float MPX5700_Leer (void);

#endif /* SOURCES_MPX5700_H_ */
