/*
 * StateMachine.cpp
 *
 *  Created on: 6 Oct 2022
 *      Author: DBY
 */

#include "StateMachine.h"

StateMachine::StateMachine(TC74_R &tc, LpcUart &lpcUart):sensor(&tc),lpcUart(&lpcUart),ledJack {0,27,false,true,false},ledDiner {1,0,false,true,false},ledBar {0,24,false,true,false}{
	timeOut = 2000;
	coldLimit = 20;
	lunch = false;
	night = false;
	cold = false;
	ledJack.write(false);
	ledDiner.write(false);
	ledBar.write(false);
	currentState = &StateMachine::Init;
	(this->*currentState)(Event(Event::eEnter));

}
StateMachine::~StateMachine() {
	// TODO Auto-generated destructor stub
}

void StateMachine::handlestate(const Event& e){
	(this->*currentState)(e);
}



void StateMachine::setState(state_ptr newState){
	(this->*currentState)(Event(Event::eExit));
	currentState = newState;
	(this->*currentState)(Event(Event::eEnter));

}


void StateMachine::Init(const Event &e){
	switch (e.type){
	case Event::eEnter:
		lpcUart->write("Initial State\r\n");
		timer = 0;
		break;
	case Event::eExit:
		lpcUart->write("Exit Initial\r\n");
		break;
	case Event::eLunch:
		lunch = !lunch;
		break;
	case Event::eTick:
		timer++;
		if(timer >= timeOut) setState(&StateMachine::Jack);
		break;
	case Event::eNight:
		night = !night;
		break;
	case Event::eCriticalError:
		break;
	}
}

void StateMachine::Jack(const Event &e){
	switch (e.type){
		case Event::eEnter:
			lpcUart->write("Enter Jack's\r\n");
			ledOn(&ledJack);
			timer = 0;
			break;
		case Event::eExit:
			if(lunch) ledOff(&ledJack);
			lpcUart->write("Exit Jack's\r\n");
			break;
		case Event::eLunch:
			lunch = !lunch;
			break;
		case Event::eTick:
			timer++;
			if(timer >= timeOut){
				if(lunch) setState(&StateMachine::Diner);
				else setState(&StateMachine::jackBar);
			}
			break;
		case Event::eNight:
			night = !night;
			break;
		case Event::eCriticalError:
			break;
		}
}

void StateMachine::Diner(const Event &e){
	switch (e.type){
		case Event::eEnter:
			lpcUart->write("Enter Diner\r\n");
			ledOn(&ledDiner);
			timer = 0;
			break;
		case Event::eExit:
			lpcUart->write("Exit Diner\r\n");
			break;
		case Event::eLunch:
			lunch = !lunch;
			break;
		case Event::eTick:
			timer++;
			if(timer >= timeOut) {
				setState(&StateMachine::jackDiner);
			}
			break;
		case Event::eNight:
			night = !night;
			break;
		case Event::eCriticalError:
			break;
		}
}

void StateMachine::jackDiner(const Event &e){
	switch (e.type){
		case Event::eEnter:
			lpcUart->write("Enter Jack's Diner\r\n");
			ledOn(&ledJack);
			timer = 0;
			break;
		case Event::eExit:
			lpcUart->write("Exit Initial\r\n");
			ledOff(&ledDiner);
			if(!cold) ledOff(&ledJack);
			break;
		case Event::eLunch:
			lunch =!lunch;
			break;
		case Event::eTick:
			timer++;
			if(timer >= timeOut) {
				cold = isCold();
				if(cold) setState(&StateMachine::Jack);
				else setState(&StateMachine::Init);
			}
			break;
		case Event::eNight:
			night = !night;
			break;
		case Event::eCriticalError:
			break;
		}
}

void StateMachine::jackBar(const Event &e){
	switch (e.type){
		case Event::eEnter:
			lpcUart->write("Enter Jack's Bar\r\n");
			ledOn(&ledBar);
			timer = 0;
			break;
		case Event::eExit:
			lpcUart->write("Exit Jack's Bar\r\n");
			break;
		case Event::eLunch:
			lunch = !lunch;
			break;
		case Event::eTick:
			timer++;
			if(timer >= timeOut) setState(&StateMachine::jackBarDiner);
			break;
		case Event::eNight:
			night = !night;
			break;
		case Event::eCriticalError:
			break;
		}
}

void StateMachine::jackBarDiner(const Event &e){
	switch (e.type){
		case Event::eEnter:
			lpcUart->write("Enter Jack's Bar Diner\r\n");
			ledOn(&ledDiner);
			timer = 0;
			break;
		case Event::eExit:
			ledOff(&ledBar);
			ledOff(&ledDiner);
			if(!cold) ledOff(&ledJack);
			lpcUart->write("Exit Jack's Bar Diner\r\n");
			break;
		case Event::eLunch:
			lunch = !lunch;
			break;
		case Event::eTick:
			if(!night){
				timer++;
				if(timer >= timeOut){
					cold = isCold();
					if(cold) setState(&StateMachine::Jack);
					else setState(&StateMachine::Init);
				}
			}
			break;
		case Event::eNight:
			night = !night;
			break;
		case Event::eCriticalError:
			break;
		}
}


void StateMachine::ledOn(DigitalIoPin *on){
	on->write(true);

}
void StateMachine::ledOff(DigitalIoPin *off){
	off->write(false);
}

bool StateMachine::isCold(){
	//check the mode
	if(sensor->checkMode()){
		sensor->switchNormalMode();
	}
	//check data status and get temp
	if(sensor->getStatus()){
		char msg[128];
		int8_t temp = sensor->getTemp();
		snprintf(msg, 128, "{\r\n\t\"temperature\" :%d\r\n}\r\n", (int8_t) temp);
		lpcUart->write(msg);
		if(temp <= coldLimit) return true;
	}
	return false;
}
