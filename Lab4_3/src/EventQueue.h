/*
 * EventQueue.h
 *
 *  Created on: 6 Oct 2022
 *      Author: DBY
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <queue>
#include "Event.h"


class EventQueue {
public:
	EventQueue();
	virtual ~EventQueue();
	void publish(const Event &e);
	Event consume();
	bool pending();

private:
	std::queue<Event> eq;
};

#endif /* EVENTQUEUE_H_ */
