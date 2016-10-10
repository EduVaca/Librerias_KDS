/*
 * HX711.c
 *
 *  Created on: 09/10/2016
 *      Author: eduda
 */

#include "Librerias.h"

#define HIGH 1
#define LOW 0

sHX711 gsHX711;

void begin(unsigned char gain)
{
	gsHX711.OFFSET;
	gsHX711.SCALE;
	set_gain(gain);
}

unsigned char is_ready()
{
	return (DOUT_GetVal() == LOW);
}

void set_gain(unsigned char gain)
{
	switch (gain)
	{
		case 128:		// channel A, gain factor 128
			gsHX711.GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			gsHX711.GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			gsHX711.GAIN = 2;
			break;
	}
	PD_SCK_PutVal(LOW);
	read();
}

long read()
{
unsigned long value = 0;
unsigned char data[3] = { 0 };
unsigned char filler = 0x00;
unsigned int i = 0;

	// wait for the chip to become ready
	while (!is_ready())
	{
		// Will do nothing on Arduino but prevent resets of ESP8266 (Watchdog Issue)
		// yield();
	}
	// pulse the clock pin 24 times to read the data
	data[2] = shiftIn();
	data[1] = shiftIn();
	data[0] = shiftIn();
	// set the channel and the gain factor for the next reading using the clock pin
	for (i = 0; i < gsHX711.GAIN; i++)
	{
		PD_SCK_PutVal(HIGH);
		PD_SCK_PutVal(LOW);
	}

	// Datasheet indicates the value is returned as a two's complement value
	    // Flip all the bits
	    data[2] = ~data[2];
	    data[1] = ~data[1];
	    data[0] = ~data[0];

	    // Replicate the most significant bit to pad out a 32-bit signed integer
	    if ( data[2] & 0x80 ) {
	        filler = 0xFF;
	    } else if ((0x7F == data[2]) && (0xFF == data[1]) && (0xFF == data[0])) {
	        filler = 0xFF;
	    } else {
	        filler = 0x00;
	    }

//	// Replicate the most significant bit to pad out a 32-bit signed integer
//	if (data[2] & 0x80) {
//		filler = 0xFF;
//	} else {
//		filler = 0x00;
//	}

	// Construct a 32-bit signed integer
	value = ( (unsigned long)(filler) << 24
			| (unsigned long)(data[2]) << 16
			| (unsigned long)(data[1]) << 8
			| (unsigned long)(data[0]) );

	return (long)(value);
}

long read_average(unsigned char times)
{
unsigned char i = 0;
long sum = 0;

	for (i = 0; i < times; i++)
	{
		sum += read();
		//yield();
	}
	return sum / times;
}

double get_value(unsigned char times)
{
	return read_average(times) - gsHX711.OFFSET;
}

float get_units(unsigned char times)
{
	return get_value(times) / gsHX711.SCALE;
}

void tare(unsigned char times)
{
	long sum = read_average(times);
	set_offset(sum);
}

void set_scale(float scale)
{
	gsHX711.SCALE = scale;
}

float get_scale()
{
	return gsHX711.SCALE;
}

void set_offset(long offset)
{
	gsHX711.OFFSET = offset;
}

long get_offset()
{
	return gsHX711.OFFSET;
}

void power_down()
{
	PD_SCK_PutVal(LOW);
	PD_SCK_PutVal(HIGH);
}

void power_up()
{
	PD_SCK_PutVal(LOW);
}

unsigned char shiftIn (void)
{
unsigned char data = 0;
unsigned int i = 0;

	for (i = 0; i < 8; i++)
	{
		PD_SCK_PutVal(HIGH);
		data = data << 1;
		if(DOUT_GetVal())data++;
		PD_SCK_PutVal(LOW);
	}
	return (data);
}
