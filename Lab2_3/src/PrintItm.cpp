/*
 * PrintItm.cpp
 *
 *  Created on: 8 Sep 2022
 *      Author: DBY
 */

#include "PrintItm.h"

PrintItm::PrintItm() {
	// TODO Auto-generated constructor stub
	ITM_init();
}

PrintItm::~PrintItm() {
	// TODO Auto-generated destructor stub
}

int PrintItm::print(const char* format, ...){
	char buf[501];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);
	return ITM_write(buf);
}

int PrintItm::print(int i){
	std::string str = std::to_string(i);
	ITM_write(str.c_str());
	ITM_write("\t");
	return 0;
}

int PrintItm::print(std::string s){
	ITM_write(s.c_str());
	return 0;
}
