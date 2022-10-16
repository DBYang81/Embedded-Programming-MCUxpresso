/*
 * IntegerEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "IntegerEdit.h"
#include <cstdio>

IntegerEdit::IntegerEdit(LiquidCrystal *lcd_, LpcUart *uart_, std::string editTitle, int max, int min):
lcd(lcd_), uart(uart_), title(editTitle),upper_lim(max), lower_lim(min){
	value = 0;
	edit  = 0;
	focus = false;
}

IntegerEdit::~IntegerEdit() {
}

void IntegerEdit::increment() {
	if(edit >= upper_lim) edit = upper_lim;
	else edit++;
}

void IntegerEdit::decrement() {
	if(edit <= lower_lim) edit = lower_lim;
	else edit-- ;
}

void IntegerEdit::accept() {
	save();
}

void IntegerEdit::cancel() {
	edit = value;
}


void IntegerEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool IntegerEdit::getFocus() {
	return this->focus;
}

void IntegerEdit::display() {
	lcd->clear();
	lcd->setCursor(0,0);
	lcd->print(title);
	lcd->setCursor(0,1);
	char s[17];
	if(focus) {
		snprintf(s, 17, "     [%4d]     ", edit);
	}
	else {
		snprintf(s, 17, "      %4d      ", edit);
	}
	lcd->print(s);
}

void IntegerEdit::debugDisplay(){
	char buff[128];
	snprintf(buff, 128, "%s	  %4d \r\n", title.c_str(), edit);
	uart->write(buff);
}


void IntegerEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage

}

int IntegerEdit::getValue() {
	return value;
}
void IntegerEdit::setValue(int value) {
	edit = value;
	save();
}
