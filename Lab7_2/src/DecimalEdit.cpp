/*
 * DecimalEdit.cpp
 *
 *  Created on: 14 Oct 2022
 *      Author: DBY
 */

#include "DecimalEdit.h"


DecimalEdit::DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, float max, float min, float step_, LpcUart *uart_):
lcd(lcd_), title(editTitle), upper_lim(max), lower_lim(min), step(step_), uart(uart_){
	value = 0;
	edit  = 0;
	focus = false;
}

DecimalEdit::~DecimalEdit() {
	// TODO Auto-generated destructor stub
}

void DecimalEdit::increment() {
	if(edit + step <= upper_lim) edit += step;
	else edit = upper_lim;
}

void DecimalEdit::decrement() {
	if(edit - step >= lower_lim) edit -= step;
	else edit = lower_lim;
}

void DecimalEdit::accept() {
	save();
}

void DecimalEdit::cancel() {
	edit = value;
}


void DecimalEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool DecimalEdit::getFocus() {
	return this->focus;
}

void DecimalEdit::display() {
	lcd->clear();
	lcd->setCursor(0,0);
	lcd->print(title);
	lcd->setCursor(0,1);
	char s[17];
	if(focus) {
		snprintf(s, 17, "     [%3.1f]     ", edit);
	}
	else {
		snprintf(s, 17, "      %3.1f      ", edit);
	}
	lcd->print(s);
}

void DecimalEdit::debugDisplay(){
	char buff[128];
	snprintf(buff, 128, "%s	  %3.1f \r\n", title.c_str(), edit);
	uart->write(buff);
}


void DecimalEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


float DecimalEdit::getValue() {
	return value;
}
void DecimalEdit::setValue(int value) {
	edit = value;
	save();
}
