#ifndef _ROCKET_H
#define _ROCKET_H
#include "AVRStateMachine.h"
#include "stdafx.h"

struct RocketData : public EventData
{
	int speed;	

};

class Rocket : public StateMachine
{
public:
	Rocket() : StateMachine(ST_MAX_STATES) {}
	void Halt();
	void setSpeed(RocketData*);
private:
	void ST_Idle(EventData*);
	void ST_Stop(EventData*);
	void ST_Start(RocketData*);
	void ST_ChangeSpeed(RocketData*);
	
	BEGIN_STATE_MAP
				STATE_MAP_ENTRY(&Rocket::ST_Idle)
		STATE_MAP_ENTRY(&Rocket::ST_Stop)
		STATE_MAP_ENTRY(&Rocket::ST_Start)
		STATE_MAP_ENTRY(&Rocket::ST_ChangeSpeed)
	END_STATE_MAP
	
	enum E_States {
		ST_IDLE = 0,
		ST_STOP,
		ST_START,
		ST_CHANGE_SPEED,
		ST_MAX_STATES	
	};
	
	Bluetooth blueT1;
	Pwm servo1;	
// 	enum E_States {
//         ST_INIT,
//         ST_WAIT_FOR_INIT,
//         ST_WAIT_FOR_READY,
//         ST_WAIT_FOR_FILLING,
//         ST_FILLING,
//         ST_WAIT_FOR_IGNITION,
//         ST_IGNITION,
//         ST_FULL_BURN,
//         ST_FINAL_VENTING,
//         ST_DONE,
//         ST_ABORT_FILLING,
//         ST_ABORT_BURN,
//         ST_SERVO_CONTROL, // Debugging state
//         ST_MAX_STATES
// 	};
};

#endif