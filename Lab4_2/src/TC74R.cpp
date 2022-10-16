/*
 * TC74R.cpp
 *
 *  Created on: 30 Sep 2022
 *      Author: DBY
 */

#include "TC74R.h"




TC74_R::TC74_R(I2C &i2c, LpcUart &lpcUart, uint8_t addr) : _i2c(&i2c), _lpcUart(&lpcUart), slaveAdd(addr){
	// TODO Auto-generated constructor stub
}

TC74_R::~TC74_R() {
	// TODO Auto-generated destructor stub
}

uint8_t TC74_R::getTemp(){
	uint8_t temperature;
	_i2c->transaction(slaveAdd, &regTemp, 1, &temperature, 1);
	return temperature;
};

bool TC74_R::getStatus(){
	uint8_t regCtrl = 0x01; //control register command byte;
	uint8_t status;
	if(_i2c->transaction(slaveAdd, &regCtrl, 1, &status, 1)){
		if((status & 0x40) && !(status & 0x80)){ //0x40 ready bit in control register, test if it is ready using mask 0x40
			_lpcUart->write("data ready.\r\n\r\n");
			return true;
		}else {
			return false;
		}
	}
}

bool TC74_R::checkMode(){
	uint8_t mode = 0;
	if(_i2c->transaction(slaveAdd, &regCtrl, 1, &mode, 1)){
		if(mode & 0x80){ //0x80 standby mask in control register
			return true;
		}else {
			return false;
		}
	}else _lpcUart->write("unable to connect to sensor.\r\n");
	return false;
}



void TC74_R::switchNormalMode(){
	uint8_t mode;
	uint8_t normalMode = 0x00;
	uint8_t comCode [2] = {regCtrl, normalMode}; //I2C write data into register, take first data as command register, the following is as real data
	//I2C tells to write control register normal mode value into it.
	if(_i2c->transaction(slaveAdd, comCode, 2, &mode, 1)){
		_lpcUart->write("switch to normal mode\r\n\r\n");
	}else _lpcUart->write("unable to connect to sensorTC-74\r\n");
}

void TC74_R::setIdle(){
	uint8_t idle;
	uint8_t comdCode[2] = {0x01, 0x80};
	//I2C tells to write control register standby value into it in order to standby the sensor
	if(_i2c->transaction(slaveAdd, comdCode, 2, &idle,1)){
		_lpcUart->write("\r\n On idle mode!\r\n\r\n");
	}else _lpcUart->write("error occurs\r\n");

}
