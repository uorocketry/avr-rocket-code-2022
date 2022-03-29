#include <assert.h>
#include "Rocket.h"

// void Rocket::Halt(void)
// {
// 	BEGIN_TRANSITION_MAP
// 		TRANSITION_MAP_ENTRY (EVENT_IGNORED)
// 		TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)
// 		TRANSITION_MAP_ENTRY (ST_STOP)
// 		TRANSITION_MAP_ENTRY (ST_STOP)
// 	END_TRANSITION_MAP(NULL)
// }
// 
// void Rocket::setSpeed(RocketData* pData)
// {
// 	BEGIN_TRANSITION_MAP
// 		TRANSITION_MAP_ENTRY (ST_START)
// 		TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)
// 		TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)
// 		TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)
// 	END_TRANSITION_MAP(pData)
// }
// 
// void Rocket::ST_Idle(EventData* pData)
// {
// 	// turn led on
// 	PORTC.OUTSET = PIN6_bm;
// 	_delay_ms(DELAY_TIME);	
// 	/* This message is transmitted over both usart ports, one to the CDC and the other to the HC-06 */
// 	this->usart.sendString("Idle State"); 
// 	_delay_ms(2000);
// }
// 
// void Rocket::ST_Stop(EventData* pData) 
// {
// 	InternalEvent(ST_IDLE);
// 	this->usart.sendString("Stop State");
// 	_delay_ms(2000);
// }
// 
// void Rocket::ST_Start(RocketData* pData) 
// {
// 	PORTC.OUTCLR = PIN6_bm;
// 	_delay_ms(DELAY_TIME);
// 	this->usart.sendString("Start State");
// }
// 
// void Rocket::ST_ChangeSpeed(RocketData* pData) 
// {
// 	this->usart.sendString("Change Speed State");
// }

// mappings
void Rocket::Launch(void) {
	// Might need to declare EventData eventData;
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_INIT)		// init -> normally ignored, but open for testing purposes to allow an in.
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// wait for init
		TRANSITION_MAP_ENTRY(ST_POWERED_FLIGHT) // wait for launch
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// powered flight
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// coast
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// decent phase 1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// decent phase 2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ground
	END_TRANSITION_MAP(NULL)
}

void Rocket::MotorBurnout(void) {
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) 
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(ST_COAST)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
	END_TRANSITION_MAP(NULL)
}

void Rocket::Apogee(void) {
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(ST_DESCENT_PHASE_1)
		TRANSITION_MAP_ENTRY(ST_DESCENT_PHASE_2)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
	END_TRANSITION_MAP(NULL)
}

void Rocket::Touchdown(void) {
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(ST_GROUND)
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
	END_TRANSITION_MAP(NULL)
}

// Define what the states do
void Rocket::ST_Init(RocketData* pData) {
	// initialize peripherials and establish link to main computer
	this->usart.sendString("Init");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_WAIT_FOR_INIT);
}

void Rocket::ST_Wait_for_init(RocketData* pData) {
	// if initialized switch states
	this->usart.sendString("Wait for init");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_WAIT_FOR_LAUNCH); 
}

void Rocket::ST_Wait_for_launch(RocketData* pData) {
	// external event to detect launch, for now force it
	this->usart.sendString("Wait for launch");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_POWERED_FLIGHT);
}

void Rocket::ST_Powered_flight(RocketData* pData) {
	// external events to detect apogee or motor burnout, for now force it
	this->usart.sendString("Powered flight");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_COAST);
}

void Rocket::ST_Coast(RocketData* pData) {
	// external event to detect apogee, for now force it
	this->usart.sendString("Coast");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_DESCENT_PHASE_1); 
}

void Rocket::ST_Descent_phase_1(RocketData* pData) {
	// Read barometer, if <= 100, then trigger descent phase 2, for now force it
	this->usart.sendString("Descent phase 1");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_DESCENT_PHASE_2);
}

void Rocket::ST_Descent_phase_2(RocketData* pData) {
	// external event to detect touchdown, for now force it
	this->usart.sendString("Descent phase 2");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_GROUND);
}

void Rocket::ST_Ground(RocketData* pData) {
	// update outputs.
	this->usart.sendString("Done");
	_delay_ms(DELAY_TIME);
	InternalEvent(ST_INIT);
}