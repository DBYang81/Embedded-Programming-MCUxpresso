/*
 * stateMachine.h
 *
 *  Created on: 14 Oct 2022
 *      Author: DBY
 */

#include "Event.h"
#include "DigitalIoPin.h"


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

class stateMachine;
typedef void (stateMachine::*state_ptr)(const Event &);

class stateMachine {
public:
	stateMachine();
	virtual ~stateMachine();
	void HandleState(const Event &e);
private:
	state_ptr currentState;
	void stateDefault (const Event &e);
	void stateOn (const Event &e);
	void stateOff(const Event &e);
	void setState(state_ptr newState);
	int timer;
	int time;
	int blank;
	int led;
    //LEDs Initializing
	DigitalIoPin leds[3] = {
			{0, 25, false, true, true},
			{0, 3, false, true, true},
			{1, 1, false, true, true}
	};

};

#endif /* STATEMACHINE_H_ */
