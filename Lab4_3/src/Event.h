/*
 * Event.h
 *
 *  Created on: 6 Oct 2022
 *      Author: DBY
 */

#ifndef EVENT_H_
#define EVENT_H_

class Event {
public:
	enum eventType{eEnter, eExit, eLunch, eNight, eTick, eCriticalError};
	Event(eventType e =eTick, int v = 0);
	virtual ~Event();
	eventType type;
	int value;
};

#endif /* EVENT_H_ */
