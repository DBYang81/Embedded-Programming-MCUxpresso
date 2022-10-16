/*
 * digitalIoPin.h
 *
 *  Created on: 2 Sep 2022
 *      Author: dbyang
 */

#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_

#include "chip.h"
#include "board.h"

class DigitalIoPin{
public:
	DigitalIoPin(int port, int pin, bool input= true, bool pullup = true, bool invert = false);
	DigitalIoPin(const DigitalIoPin &) = delete;
	virtual ~DigitalIoPin(){};
	bool read();
	void write(bool value);
private:
	int _port;
	int _pin;
};

#endif /* DIGITALIOPIN_H_ */
