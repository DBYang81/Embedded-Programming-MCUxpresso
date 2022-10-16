/*
 * EventQueue.cpp
 *
 *  Created on: 6 Oct 2022
 *      Author: DBY
 */

#include "EventQueue.h"

EventQueue::EventQueue() {
	// TODO Auto-generated constructor stub

}

EventQueue::~EventQueue() {
	// TODO Auto-generated destructor stub
}

void EventQueue::publish(const Event &e){
	eq.push(e);
}

Event EventQueue::consume(){
	if(eq.empty()){
		return Event(Event::eCriticalError, 0);
	}
	Event e(eq.front());
	eq.pop();
	return e;
}

bool EventQueue::pending(){
	return !eq.empty();
}
