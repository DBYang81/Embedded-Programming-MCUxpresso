/*
 * stateMachine.cpp
 *
 *  Created on: 14 Oct 2022
 *      Author: DBY
 */

#include "stateMachine.h"

stateMachine::stateMachine() {
	// TODO Auto-generated constructor stub
	currentState = &stateMachine::stateDefault;
	(this->*currentState) (Event (Event::eEnter));

}

stateMachine::~stateMachine() {
	// TODO Auto-generated destructor stub
}

void stateMachine::HandleState(const Event &e){
	(this->*currentState) (e);
}

void stateMachine::stateDefault(const Event &e){
	switch(e.type){
	case Event::eEnter:
		timer = 0;
		for(auto &p : leds){
			p.write(false);
		}
		break;
	case Event::eExit:
		break;
	case Event::eKey:
		break;
	case Event::eTick:
		this->led = e.led;
		this->time = e.time;
		this->blank = e.blank;
		if(this->led && this->time){
			setState(&stateMachine::stateOn);
		}
		break;
	}

}

void stateMachine::stateOn(const Event &e){
	switch(e.type){
	case Event::eEnter:
		timer = 0;
		leds[this->led - 1].write(true);
		break;
	case Event::eExit:
		break;
	case Event::eKey:
		break;
	case Event::eTick:
		timer++;
		if(timer >= this->time){
			if(e.blank || !e.time){
				setState(&stateMachine::stateOff);
			}else{
				timer = 0;
			}
		}
		if(e.led != this->led){
			if(e.led == 0) setState(&stateMachine::stateOff);
			leds[this->led - 1].write(false);
			leds[e.led - 1].write(true);
			this->led = e.led;
		}
		break;
	}
}

void stateMachine::stateOff(const Event &e){
	switch(e.type){
	case Event::eEnter:
		leds[this->led -1].write(false);
		timer = 0;
		break;
	case Event::eExit:
		break;
	case Event::eKey:
		break;
	case Event::eTick:
		timer++;
		if(timer >= this->blank){
			setState(&stateMachine::stateDefault);
		}
		break;
	}

}

void stateMachine::setState(state_ptr newState){
	(this->*currentState)(Event(Event::eExit));
	currentState = newState;
	(this->*currentState)(Event(Event::eEnter));
}
