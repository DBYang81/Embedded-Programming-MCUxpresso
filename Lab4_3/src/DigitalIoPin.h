/*
 * DigitalIoPin.h
 *
 *  Created on: Sep 3, 2022
 *      Author: DBY
 */

#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_

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
	bool input;
	bool pullup;
	bool invert;
};




#endif /* DIGITALIOPIN_H_ */
