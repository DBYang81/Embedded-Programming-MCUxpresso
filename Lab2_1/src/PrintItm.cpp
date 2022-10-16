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

void PrintItm::print(const char *c){
	ITM_write(c);
}

void PrintItm::print(int i){
	std::string str = std::to_string(i);
	ITM_write(str.c_str());
}

void PrintItm::print(std::string s){
	ITM_write(s.c_str());
}
