/*
 * Imutex.cpp
 *
 *  Created on: 13 Oct 2022
 *      Author: DBY
 */

#include "Imutex.h"
#include "chip.h"

Imutex::Imutex():enable(false) {
	// TODO Auto-generated constructor stub

}

Imutex::~Imutex() {
	// TODO Auto-generated destructor stub
}

void Imutex::lock(){
	enable = (__get_PRIMASK() & 1) == 0;
	__disable_irq();
}

void Imutex::unlock(){
	if(enable) __enable_irq();
}
