/*
 * dice.h
 *
 *  Created on: 2 Sep 2022
 *      Author: dbyang
 */

#ifndef DICE_H_
#define DICE_H_

#include "DigitalIoPin.h"

class Dice{
public:
	Dice();
	virtual ~Dice(){};
	void Show(int number);
private:
	DigitalIoPin ledPin[7] = {{1, 9, false}, {0, 29, false}, {0, 9, false}, {0, 10, false}, {0, 16, false}, {1, 3, false}, {0, 0, false}};
};


#endif /* DICE_H_ */

/*
DigitalIoPin PD1(1, 9, false);
 DigitalIoPin PD2(0, 29, false);
 DigitalIoPin PD3(0, 9, false);
 DigitalIoPin PD4(0, 10, false);
 DigitalIoPin PD5(0, 16, false);
 DigitalIoPin PD6(1, 3, false);
 DigitalIoPin PD7(0, 0, false);*/
