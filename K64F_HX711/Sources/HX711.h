/*
 * HX711.h
 *
 *  Created on: 09/10/2016
 *      Author: eduda
 */

#ifndef SOURCES_HX711_HX711_H_
#define SOURCES_HX711_HX711_H_

#include "PE_Types.h"

typedef struct
{
	unsigned char PD_SCK;	// Power Down and Serial Clock Input Pin
	unsigned char DOUT;		// Serial Data Output Pin
	unsigned char GAIN;		// amplification factor
	long OFFSET;	// used for tare weight
	float SCALE;	// used to return weight in grams, kg, ounces, whatever
}sHX711;

extern sHX711 gsHX711;


// define clock and data pin, channel, and gain factor
// channel selection is made by passing the appropriate gain: 128 or 64 for channel A, 32 for channel B
// gain: 128 or 64 for channel A; channel B works with 32 gain factor only

// Allows to set the pins and gain later than in the constructor
void begin(unsigned char gain);

// check if HX711 is ready
// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
unsigned char is_ready();

// set the gain factor; takes effect only after a call to read()
// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
// depending on the parameter, the channel is also set to either A or B
void set_gain(unsigned char gain);

// waits for the chip to be ready and returns a reading
long read();

// returns an average reading; times = how many times to read
long read_average(unsigned char times);

// returns (read_average() - OFFSET), that is the current value without the tare weight; times = how many readings to do
double get_value(unsigned char times);

// returns get_value() divided by SCALE, that is the raw value divided by a value obtained via calibration
// times = how many readings to do
float get_units(unsigned char times);

// set the OFFSET value for tare weight; times = how many times to read the tare value
void tare(unsigned char times);

// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
void set_scale(float scale);

// get the current SCALE
float get_scale();

// set OFFSET, the value that's subtracted from the actual reading (tare weight)
void set_offset(long offset);

// get the current OFFSET
long get_offset();

// puts the chip into power down mode
void power_down();

// wakes up the chip after power down mode
void power_up();

unsigned char shiftIn (void);

#endif /* SOURCES_HX711_HX711_H_ */
