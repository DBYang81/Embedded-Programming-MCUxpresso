/*
 * Menu.h
 *
 *  Created on: 9 Sep 2022
 *      Author: DBY
 */

#ifndef MENU_H_
#define MENU_H_
#include "PrintItm.h"
#include "Led.h"


class Menu {
public:
	Menu();
	virtual ~Menu();
	int print();
	bool move_up();
	bool move_down();
	void switch_led();
private:
	uint8_t selected_led;
	PrintItm itm;
	Led led;
};

#endif /* MENU_H_ */
