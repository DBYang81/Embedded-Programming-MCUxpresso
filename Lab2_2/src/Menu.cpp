/*
 * Menu.cpp
 *
 *  Created on: 9 Sep 2022
 *      Author: DBY
 */

#include "Menu.h"

Menu::Menu() {
	// TODO Auto-generated constructor stub
	this -> selected_led = 0;
}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

int Menu::print(){
	bool p_flag = true;
	itm.print("Select Led:\n\n");
	p_flag = p_flag && this->itm.print("RED		%s	%s", led.get_red_state() ? "NO" : "OFF", selected_led == 0 ? "<--\n":"\n");
	p_flag = p_flag && this->itm.print("Green	%s	%s", led.get_grn_state()? "NO" : "OFF", selected_led == 1 ? "<--\n":"\n");
	p_flag = p_flag && this->itm.print("Blue	%s	%s", led.get_blu_state()? "NO" : "OFF", selected_led == 2 ? "<--\n":"\n");
	return p_flag;
}

bool Menu::move_up() {
	if(this->selected_led > 0) {
		--(this->selected_led);
		return true;
	}
	else {
		this->selected_led = 2;
		return false;
	}
}

bool Menu::move_down() {
	if(this->selected_led < 2) {
		++(this->selected_led);
		return true;
	}
	else {
		this->selected_led = 0;
		return false;
	}
}

void Menu::switch_led() {
	this->led.switch_led(this->selected_led);
}
