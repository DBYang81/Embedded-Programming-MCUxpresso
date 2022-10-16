/*
 * PrintItm.h
 *
 *  Created on: 8 Sep 2022
 *      Author: DBY
 */

#ifndef PRINTITM_H_
#define PRINTITM_H_

#include "ITM_write.h"
#include <string>


class PrintItm {
public:
	PrintItm();
	virtual ~PrintItm();
	void print(int);
	void print(const char *);
	void print(std::string);
};

#endif /* PRINTITM_H_ */
