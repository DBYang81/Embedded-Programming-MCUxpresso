/*
 * Event.h
 *
 *  Created on: 14 Oct 2022
 *      Author: DBY
 */

#ifndef EVENT_H_
#define EVENT_H_

class Event{
public:
	enum eventType{ eEnter, eExit, eKey, eTick};
	Event(eventType e = eTick, int led_ = 0, int time_= 0, int blank_ = 0):type(e), led(led_), time(time_), blank(blank_){};
	eventType type;
	int led;
	int time;
	int blank;
};

#endif /* EVENT_H_ */
