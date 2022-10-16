/*
 * DecimalEdit.h
 *
 *  Created on: 14 Oct 2022
 *      Author: DBY
 */

#ifndef DECIMALEDIT_H_
#define DECIMALEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include "LpcUart.h"
#include <string>


class DecimalEdit : public PropertyEdit{
public:
	DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, float max, float min, float step_, LpcUart *uart_=nullptr);
	virtual ~DecimalEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	bool getFocus();
	void display();
	float getValue();
	void setValue(int value);
	void debugDisplay();

private:
	void save();
	void displayEditValue();
	LiquidCrystal *lcd;
	LpcUart *uart;
	std::string title;
	float value;
	float edit;
	bool focus;
	float upper_lim;
	float lower_lim;
	float step;
};

#endif /* DECIMALEDIT_H_ */
