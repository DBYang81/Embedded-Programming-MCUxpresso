/*
 * Led.cpp
 *
 *  Created on: 9 Sep 2022
 *      Author: DBY
 */

#include "Led.h"

Led::Led():led_red{0, 25 ,false ,true, true}, led_grn{0, 3 ,false ,true, true}, led_blu{1, 1 ,false ,true, true}{

	led_red.write(false);
	led_grn.write(false);
	led_blu.write(false);
}


Led::~Led(){
	// TODO Auto-generated destructor stub
}


bool Led::get_red_state() {
	return this->led_red.read();
}

bool Led::get_grn_state() {
	return this->led_grn.read();
}

bool Led::get_blu_state() {
	return this->led_blu.read();
}

void Led::switch_led(int led) {
	switch (led)
	{
	case 0:
		if(this->get_red_state()){
			this->led_red.write(false);
		}else{
			this->led_red.write(true);
		}
		break;
	case 1:
		if(this->get_grn_state()){
			this->led_grn.write(false);
		}else{
			this->led_grn.write(true);
		}
		break;
	case 2:
		if(this->get_blu_state()){
			this->led_blu.write(false);
		}else{
			this->led_blu.write(true);
		}
		break;
	default:
		break;
	}
}
