/*
 * DigitalIoPin.cpp
 *
 *  Created on: 2 Sep 2022
 *      Author: dbyang
 */

#ifndef DIGITALIOPIN_CPP_
#define DIGITALIOPIN_CPP_

#include "DigitalIoPin.h"

DigitalIoPin::DigitalIoPin(int port, int pin, bool input, bool pullup, bool invert): _port(port), _pin(pin){

	if(input){
		if(pullup){
			if(invert){
				Chip_IOCON_PinMuxSet(LPC_IOCON, _port, _pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
			}else{
				Chip_IOCON_PinMuxSet(LPC_IOCON, _port, _pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));
			}
		}else{
			if(invert){
				Chip_IOCON_PinMuxSet(LPC_IOCON, _port, _pin, (IOCON_MODE_PULLDOWN | IOCON_DIGMODE_EN | IOCON_INV_EN));
			}else{
				Chip_IOCON_PinMuxSet(LPC_IOCON, _port, _pin, (IOCON_MODE_PULLDOWN | IOCON_DIGMODE_EN));
			}
		}
		Chip_GPIO_SetPinDIRInput(LPC_GPIO,_port,_pin);
	}else{
		Chip_GPIO_SetPinDIROutput(LPC_GPIO,_port,_pin);
	}
}

bool DigitalIoPin::read(){
	return Chip_GPIO_GetPinState(LPC_GPIO,_port,_pin);
}

void DigitalIoPin::write(bool value){
	Chip_GPIO_SetPinState(LPC_GPIO, _port, _pin, value);
}

#endif /* DIGITALIOPIN_CPP_ */
