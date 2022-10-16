/*
 * StateMachine.h
 *
 *  Created on: 6 Oct 2022
 *      Author: DBY
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "TC74R.h"
#include "Event.h"
#include "DigitalIoPin.h"
#include "LpcUart.h"


class StateMachine;
typedef void(StateMachine::*state_ptr)(const Event &);

class StateMachine {
public:
	StateMachine(TC74_R &tc74, LpcUart &lpcUart);
	virtual ~StateMachine();
	void handlestate(const Event &e);

private:
	//states
	state_ptr currentState;
	void Init(const Event &e);
	void Jack(const Event &e);
	void Diner(const Event &e);
	void jackDiner(const Event &e);
	void jackBar(const Event &e);
	void jackBarDiner(const Event &e);

	//behavior
	void setState(state_ptr newState);
	void ledOn(DigitalIoPin *on);
	void ledOff(DigitalIoPin *off);

	//verification
	bool isCold();

	//variables
	TC74_R *sensor;
	LpcUart *lpcUart;
	DigitalIoPin ledJack;
	DigitalIoPin ledDiner;
	DigitalIoPin ledBar;
	int timer; //count for each state;
	int timeOut; //limit each state;
	bool lunch;
	bool night;
	bool cold;
	int coldLimit;//set cold limit for temperature in order to test sensor
};

#endif /* STATEMACHINE_H_ */
