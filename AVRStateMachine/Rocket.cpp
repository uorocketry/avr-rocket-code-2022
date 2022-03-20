#include <assert.h>
#include "Rocket.h"

void Rocket::Halt()
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)
		TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)
		TRANSITION_MAP_ENTRY (ST_STOP)
		TRANSITION_MAP_ENTRY (ST_STOP)
	END_TRANSITION_MAP(NULL)
}

void Rocket::setSpeed(RocketData* pData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY (ST_START)
		TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)
		TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)
		TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)
	END_TRANSITION_MAP(pData)
}

void Rocket::ST_Idle(EventData* pData)
{
	// turn led on
	PORTC.OUTSET = PIN6_bm;
	_delay_ms(DELAY_TIME);	
	/* This message is transmitted over both usart ports, one to the CDC and the other to the HC-06 */
	this->blueT1.sendString("Idle State"); 
	this->servo1.changePosition(0x0039);
	_delay_ms(2000);
}

void Rocket::ST_Stop(EventData* pData) 
{
	InternalEvent(ST_IDLE);
	this->blueT1.sendString("Stop State");
	this->servo1.changePosition(0x0019);
	_delay_ms(2000);
}

void Rocket::ST_Start(RocketData* pData) 
{
	PORTC.OUTCLR = PIN6_bm;
	_delay_ms(DELAY_TIME);
	this->blueT1.sendString("Start State");
}

void Rocket::ST_ChangeSpeed(RocketData* pData) 
{
	this->blueT1.sendString("Change Speed State");
}

