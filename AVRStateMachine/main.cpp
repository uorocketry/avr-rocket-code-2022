/*
 * main.cpp
 *
 * Created: 1/13/2022 7:23:45 PM
 */ 

#include "Rocket.h"
#include "stdafx.h"
#include "usart.h"
#include "Pwm.h"

int main(void)
{
	/* Peripherals */
	Pwm servo();
	PORTC.DIRSET = PIN6_bm; // Configure LED0 as output
    PORTC.DIRCLR = PIN7_bm; // Configure SW0 as input
    /* Enable the internal pull-up for PC7 */
    PORTC.PIN7CTRL |= PORT_PULLUPEN_bm; 
	/* State Machine */
	Rocket rocket;
// 	RocketData* data = (RocketData*)malloc(sizeof(RocketData)); // Without helper operators 
	RocketData* data = new RocketData();
	data->speed = 100;
	rocket.setSpeed(data);	// Leaves the state in start
	rocket.Halt();
    while (1) {
		if (!(PORTC.IN & (PIN7_bm))) {
			data->speed = 100;
			rocket.setSpeed(data);
		}
		else {
			rocket.Halt();
		}
	}
}

