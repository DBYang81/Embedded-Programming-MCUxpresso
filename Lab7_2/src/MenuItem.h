/*
 * MenuItem.h
 *
 *  Created on: 1.2.2016
 *      Author: krl
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "PropertyEdit.h"


class MenuItem {
public:
	enum menuEvent {
		up,
		down,
		ok,
		back,
		show,
		debug
	};
	MenuItem(PropertyEdit *property);
	virtual ~MenuItem();
	virtual bool event(menuEvent e);
	bool getDebugCnt();
private:
	PropertyEdit *pe;
	bool okBtnPressed;
};

#endif /* MENUITEM_H_ */
