/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include "i2c.h"
#include "DigitalIoPin.h"
#include "lpcUart.h"
#include "PrintItm.h"
#include "TC74R.h"
#include <atomic>
#include <cr_section_macros.h>
#include "json.hpp"

static volatile std::atomic_int counter;

#ifdef __cplusplus
extern "C"{
#endif

void SysTick_Handler(void){
	if(counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif

void Sleep(int ms){
	counter = ms;
	while(counter > 0){
		__WFI();
	}
}


#define STANDBY_TIMEOUT 5000
#define TICKRATE_HZ  1000

int main(void) {

	uint32_t sysTickRate;

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();

#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, false);
#endif
#endif

    Chip_Clock_SetSysTickClockDiv(1);
    sysTickRate = Chip_Clock_GetSysTickClockRate();
    SysTick_Config(sysTickRate / TICKRATE_HZ);

	LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig U_cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
	LpcUart lpcUart(U_cfg); //create lpcUart object in order to read or write pins directly

	I2C_config cfg;
	I2C i2c(cfg);
	PrintItm itm;
	DigitalIoPin sw3(1,9,true,true,true);

	TC74_R tc74(i2c, lpcUart, 0x4A); //initialize the TC74 sensor object

	unsigned long long timeStamp = 0; //timeStamp for JSON
	unsigned sampleId = 0;//sample id for JSON
	unsigned int standbyTimer = 0;


	while(1){
		if(sw3.read()){
			if(tc74.checkMode()){
				tc74.switchNormalMode();
			}
			timeStamp += 5; //accumulate time by 5ms
			while(sw3.read()); //assure the button is released
			//check status and read the temperature data
			if(tc74.getStatus()){
				Sleep(5);
				timeStamp += 5;
				char msg[128];
				sampleId++;
				int8_t temp = tc74.getTemp();
				snprintf(msg, 128, "{\r\n\t\"samplenr\": %d, \r\n\t\"timestamp\": %llu, \r\n\t\"temperature\" :%d\r\n}\r\n", sampleId, timeStamp, temp);
				lpcUart.write(msg);
			}else{
				lpcUart.write("data is not ready for reading");
			}
		}
		if(standbyTimer >= STANDBY_TIMEOUT){
			if(!tc74.checkMode()){
				tc74.setIdle();
			}
		}

		//sleep between button transaction
		Sleep(5);
		timeStamp += 5;
		standbyTimer += 5;

	}

	return 0 ;
}





