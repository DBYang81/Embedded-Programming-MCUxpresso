/*
 * KillerEdit.h
 *
 *  Created on: 15 Oct 2022
 *      Author: DBY
 */

#ifndef KILLEREDIT_H_
#define KILLEREDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include "LpcUart.h"
#include <string>



class KillerEdit: public PropertyEdit {
public:
	KillerEdit(LiquidCrystal *lcd_, LpcUart *uart, std::string editTitle, int max, int min);
	virtual ~KillerEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	bool getFocus();
	void display();
	int  getValue();
	void setValue(int value);
	void debugDisplay();
private:
	void save();
	void displayEditValue();
	LiquidCrystal *lcd;
	LpcUart *uart;
	std::string title;
	int value;
	int edit;
	bool focus;
	int upper_lim;
	int lower_lim;
};

#endif /* KILLEREDIT_H_ */
