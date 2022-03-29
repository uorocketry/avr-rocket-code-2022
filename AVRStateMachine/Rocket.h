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
// 	void Halt();
// 	void setSpeed(RocketData*);
	void Launch(void);
	void MotorBurnout(void);
	void Apogee(void);
	void Touchdown(void);
private:	
	// Might need to change some to a pointer of type EventData
	void ST_Init(RocketData*);
	void ST_Wait_for_init(RocketData*);
	void ST_Wait_for_launch(RocketData*);
	void ST_Powered_flight(RocketData*);
	void ST_Coast(RocketData*);
	void ST_Descent_phase_1(RocketData*);
	void ST_Descent_phase_2(RocketData*);
	void ST_Ground(RocketData*);
	
	BEGIN_STATE_MAP
		STATE_MAP_ENTRY(&Rocket::ST_Init)
		STATE_MAP_ENTRY(&Rocket::ST_Wait_for_init)
		STATE_MAP_ENTRY(&Rocket::ST_Wait_for_launch)
		STATE_MAP_ENTRY(&Rocket::ST_Powered_flight)
		STATE_MAP_ENTRY(&Rocket::ST_Coast)
		STATE_MAP_ENTRY(&Rocket::ST_Descent_phase_1)
		STATE_MAP_ENTRY(&Rocket::ST_Descent_phase_2)
		STATE_MAP_ENTRY(&Rocket::ST_Ground)
	END_STATE_MAP
	
    enum E_States
    {
	    ST_INIT = 0,
	    ST_WAIT_FOR_INIT,
	    ST_WAIT_FOR_LAUNCH,
	    ST_POWERED_FLIGHT,
	    ST_COAST,
	    ST_DESCENT_PHASE_1,
	    ST_DESCENT_PHASE_2,
	    ST_GROUND,
	    ST_MAX_STATES
    };
	
	Usart usart = Usart(1);
	Bluetooth blueT1;
// 	void ST_Idle(EventData*);
// 	void ST_Stop(EventData*);
// 	void ST_Start(RocketData*);
// 	void ST_ChangeSpeed(RocketData*);

// 	BEGIN_STATE_MAP
// 				STATE_MAP_ENTRY(&Rocket::ST_Idle)
// 		STATE_MAP_ENTRY(&Rocket::ST_Stop)
// 		STATE_MAP_ENTRY(&Rocket::ST_Start)
// 		STATE_MAP_ENTRY(&Rocket::ST_ChangeSpeed)
// 	END_STATE_MAP

// 	enum E_States {
// 		ST_IDLE = 0,
// 		ST_STOP,
// 		ST_START,
// 		ST_CHANGE_SPEED,
// 		ST_MAX_STATES
// 	};
// 	enum E_States {
//         ST_INIT = 0,
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