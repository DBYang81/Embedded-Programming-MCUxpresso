/*
 * KillerEdit.cpp
 *
 *  Created on: 15 Oct 2022
 *      Author: DBY
 */

#include "KillerEdit.h"
#include <cstdio>

KillerEdit::KillerEdit(LiquidCrystal *lcd_, LpcUart *uart_, std::string editTitle, int max, int min):
lcd(lcd_), uart(uart_), title(editTitle),upper_lim(max), lower_lim(min) {
	// TODO Auto-generated constructor stub
	value = 0;
	edit = 0;
	focus = false;
}

KillerEdit::~KillerEdit() {
	// TODO Auto-generated destructor stub
}



void KillerEdit::increment() {
	if(edit >= upper_lim) edit = upper_lim;
	else edit++;
}

void KillerEdit::decrement() {
	if(edit <= lower_lim) edit = lower_lim;
	else edit-- ;
}

void KillerEdit::accept() {
	save();
	LPC_WWDT->FEED = 0x00;
	LPC_WWDT->FEED = 0x11;
}

void KillerEdit::cancel() {
	edit = value;
}


void KillerEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool KillerEdit::getFocus() {
	return this->focus;
}

void KillerEdit::display() {
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

void KillerEdit::debugDisplay(){
	char buff[128];
	snprintf(buff, 128, "%s	  %4d \r\n", title.c_str(), edit);
	uart->write(buff);
}


void KillerEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage

}

int KillerEdit::getValue() {
	return value;
}
void KillerEdit::setValue(int value) {
	edit = value;
	save();
}
