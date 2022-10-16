/*
 * PrintItm.h
 *
 *  Created on: 8 Sep 2022
 *      Author: DBY
 */

#ifndef PRINTITM_H_
#define PRINTITM_H_

#include "ITM_write.h"
#include <cstdio>
#include <cstdarg>
#include <string>


class PrintItm {
public:
	PrintItm();
	virtual ~PrintItm();
	int print(int);
	int print(const char * format, ...);
	int print(std::string);
};

#endif /* PRINTITM_H_ */
