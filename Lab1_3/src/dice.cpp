/*
 * dice.cpp
 *
 *  Created on: 2 Sep 2022
 *      Author: dbyang
 */

#include "dice.h"


Dice::Dice(){
	for(int i = 0; i < 7; ++i){
		ledPin[i].write(false);
	}
}

void Dice::Show(int number){
	if(number < 0) number = 0;
	switch(number){
		case 0:
			for(int j = 0; j < 7; ++j){
				ledPin[j].write(false);
			}
			break;
		case 1:
			ledPin[3].write(true);
			break;
		case 2:
			ledPin[2].write(true);
			ledPin[6].write(true);
			break;
		case 3:
			ledPin[2].write(true);
			ledPin[3].write(true);
			ledPin[6].write(true);
			break;
		case 4:
			ledPin[0].write(true);
			ledPin[2].write(true);
			ledPin[4].write(true);
			ledPin[6].write(true);
			break;
		case 5:
			ledPin[0].write(true);
			ledPin[2].write(true);
			ledPin[3].write(true);
			ledPin[4].write(true);
			ledPin[6].write(true);
			break;
		case 6:
			ledPin[0].write(true);
			ledPin[1].write(true);
			ledPin[2].write(true);
			ledPin[4].write(true);
			ledPin[5].write(true);
			ledPin[6].write(true);
			break;
		default:
			for(int i = 0; i < 7; ++i){
				ledPin[i].write(true);
			}
			break;
	}
}




/*
DigitalIoPin PD1(1, 9, false);
 DigitalIoPin PD2(0, 29, false);
 DigitalIoPin PD3(0, 9, false);
 DigitalIoPin PD4(0, 10, false);
 DigitalIoPin PD5(0, 16, false);
 DigitalIoPin PD6(1, 3, false);
 DigitalIoPin PD7(0, 0, false);*/
