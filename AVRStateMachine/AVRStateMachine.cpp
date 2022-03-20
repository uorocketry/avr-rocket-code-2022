#include "AVRStateMachine.h"
#include <assert.h>

extern "C" void __cxa_pure_virtual() { while (1); } // Very important. If virtual function fails, then the program is trapped in a super loop. Change to flashing LED.
/* This is a Member Initializer List */
StateMachine::StateMachine(unsigned char maxStates) :
	_maxStates(maxStates),
	currentState(0),
	_eventGenerated(false),
	_pEventData(NULL)
{
}


void StateMachine::ExternalEvent(unsigned char newState,
								 EventData* pData)
{
	if (newState == EVENT_IGNORED) {
		if (pData)
			delete pData;
	}
	else {
		// TODO - capture software lock here
		InternalEvent(newState, pData);
		StateEngine();
		// TODO - release software lock here
	}
}

void StateMachine::InternalEvent(unsigned char newState,
								 EventData* pData)
{
	if (pData == NULL)
		pData = new EventData();
	_pEventData = pData;
	_eventGenerated = true;
	currentState = newState;
}

void StateMachine::StateEngine(void)
{
	EventData* pDataTemp = NULL;
	while (_eventGenerated) {
		pDataTemp = _pEventData;
		_pEventData = NULL;
		_eventGenerated = false;
		
		assert(currentState < _maxStates);
		
		const StateStruct* pStateMap = GetStateMap();
		(this->*pStateMap[currentState].pStateFunc)(pDataTemp);
		if (pDataTemp) {
// 			free(pDataTemp);
			delete pDataTemp;
			pDataTemp = NULL;
		}
	}
}