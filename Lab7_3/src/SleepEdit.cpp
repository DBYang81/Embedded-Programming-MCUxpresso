/*
 * SleepEdit.cpp
 *
 *  Created on: 15 Oct 2022
 *      Author: DBY
 */

#include "SleepEdit.h"
#include "systick.h"
#include <cstdio>


SleepEdit::SleepEdit(LiquidCrystal *lcd_, LpcUart *uart_, std::string editTitle, int max, int min):
lcd(lcd_), uart(uart_), title(editTitle), upper_lim(max), lower_lim(min) {
	// TODO Auto-generated constructor stub
	value = 0;
	edit  = 0;
	focus = false;
}

SleepEdit::~SleepEdit() {
	// TODO Auto-generated destructor stub
}


void SleepEdit::increment() {
	if(edit >= upper_lim) edit = upper_lim;
	else edit++;
}

void SleepEdit::decrement() {
	if(edit <= lower_lim) edit = lower_lim;
	else edit-- ;
}

void SleepEdit::accept() {
	save();
	uart -> write("Set 10s sleeps\r\n");
	Sleep(10000);
}

void SleepEdit::cancel() {
	edit = value;
}


void SleepEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool SleepEdit::getFocus() {
	return this->focus;
}

void SleepEdit::display() {
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

void SleepEdit::debugDisplay(){
	char buff[128];
	snprintf(buff, 128, "%s	  %4d \r\n", title.c_str(), edit);
	uart->write(buff);
}


void SleepEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage

}

int SleepEdit::getValue() {
	return value;
}

void SleepEdit::setValue(int value) {
	edit = value;
	save();
}
