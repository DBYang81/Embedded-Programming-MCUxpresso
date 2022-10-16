/*
 * IntegerEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef INTEGEREDIT_H_
#define INTEGEREDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include "LpcUart.h"
#include <string>

class IntegerEdit: public PropertyEdit {
public:
	IntegerEdit(LiquidCrystal *lcd_, LpcUart *uart, std::string editTitle, int max, int min);
	virtual ~IntegerEdit();
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

#endif /* INTEGEREDIT_H_ */
