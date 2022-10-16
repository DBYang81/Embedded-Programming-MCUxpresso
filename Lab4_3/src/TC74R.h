/*
 * TC74R.h
 *
 *  Created on: 30 Sep 2022
 *      Author: DBY
 */

#ifndef TC74R_H_
#define TC74R_H_

#include "DigitalIoPin.h"
#include "I2C.h"
#include "LpcUart.h"
#include "stdio.h"


class TC74_R {
public:
	TC74_R(I2C &i2c, LpcUart &lpcUart, uint8_t Addr);
	virtual ~TC74_R();
	uint8_t getTemp();
	bool getStatus();
	bool checkMode();
	void switchNormalMode();
	void setIdle();


private:
	I2C* _i2c;
	LpcUart* _lpcUart;
	uint8_t slaveAdd;
	uint8_t regCtrl = 0x01; //control register command for configuring
	uint8_t regTemp = 0x00; //control register command for values

};

#endif /* TC74R_H_ */
