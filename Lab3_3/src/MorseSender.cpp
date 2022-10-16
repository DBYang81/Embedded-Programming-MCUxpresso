/*
 * MoreSender.cpp
 *
 *  Created on: 15 Sep 2022
 *      Author: DBY
 */

#include "MorseSender.h"
static volatile std::atomic_int counter;
#ifdef __cplusplus
extern "C"{
#endif

void SysTick_Handler(void){
	if(counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif

void Sleep(int ms){
	counter = ms;
	while(counter > 0){
		__WFI();
	}
}



MorseSender::MorseSender(DigitalIoPin &led_pt, DigitalIoPin &decoder_pt)
	:led_ptr(&led_pt), decode_ptr(&decoder_pt){}

MorseSender::~MorseSender() {
	// TODO Auto-generated destructor stub
}

void MorseSender::convertedToMorse(char* input_str){
	unsigned int unit_length = 10;

	for(int t = 0; input_str[t] != '\0'; t++){

		bool is_morse = false;
		if(input_str[t] == ' '){
			is_morse = true;
			led_ptr -> write(false);
			decode_ptr -> write(true);
			Sleep(unit_length * 4);
		}else{
			for(int j = 0; ITU_morse[j].symbol != 0; j++){

				if(input_str[t] == ITU_morse[j].symbol){

					is_morse = true;

					//int len = *(&ITU_morse[j].code + 1) - ITU_morse[j].code;//len = *(&arr+1)-arr;

					for(int i = 0; ITU_morse[j].code[i] != 0; ++i){

						led_ptr -> write(true);
						decode_ptr -> write(false); //UART high pin to write (not inverted like lpc)
						Sleep(ITU_morse[j].code[i] * unit_length);
						decode_ptr -> write(true);
						led_ptr -> write(false);
						Sleep(unit_length);

					}
					Sleep(unit_length * 2);
				}
			}
		}

		if(is_morse == false){

			for(int x = 0; x < 4; ++x){

				led_ptr -> write(true);
				decode_ptr -> write(false);
				Sleep(ITU_morse[23].code[x] * unit_length);
				decode_ptr -> write(true);
				led_ptr -> write(false);
				Sleep(unit_length);

			}
			Sleep(unit_length * 2);
		}

	}
}

void MorseSender::convertedToMorse(std::string s){
	convertedToMorse(s.c_str());
}

void MorseSender::set_wpm(int wpm){
	// average word length is 60 * unit time
	// 1 min = 60s = 60000 ms
	//wpm = 60 * unit-time in 60000 ms
	this -> unit_length = 60000 / (60 * wpm);

}

unsigned int MorseSender::get_wpm(){
	return 60000 / (this->unit_length * 60);
}

unsigned int MorseSender::get_dot_duration(){
	return this->unit_length;
}









