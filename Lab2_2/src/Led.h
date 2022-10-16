/*
 * Led.h
 *
 *  Created on: 9 Sep 2022
 *      Author: DBY
 */

#ifndef LED_H_
#define LED_H_

#include "DigitalIoPin.h"

class Led {
public:
	Led();
	virtual ~Led();
	bool get_red_state();
	bool get_grn_state();
	bool get_blu_state();
	void switch_led(int led);
private:
	DigitalIoPin led_red;
	DigitalIoPin led_grn;
	DigitalIoPin led_blu;
};


#endif /* LED_H_ */
