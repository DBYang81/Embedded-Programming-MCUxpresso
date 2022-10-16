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
#include <atomic>
#include <cr_section_macros.h>

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



int main(void) {

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

    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
    LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
    LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
    LpcUartConfig U_cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
    LpcUart lpcUart(U_cfg); //create lpcUart object in order to read or write pins directly

    I2C_config cfg;
    I2C i2c(cfg);
    PrintItm itm;

    DigitalIoPin sw3(1,9,true,true,true);
    uint8_t busAdd = 0x4A;
    uint8_t txBufferPtr[2] = {0x01, 0x00};
    uint16_t txSize = 2;
    uint8_t rxBufferPtr;
    uint16_t rxSize = 1;



    while(1){
    	if(sw3.read()){
    		i2c.transaction(busAdd, txBufferPtr, txSize, &rxBufferPtr, rxSize);
    		while(sw3.read());
    		if((rxBufferPtr & 0x40)){
    			lpcUart.write("\r\nReading Status succeeds\r\n");

    			bool ret = i2c.transaction(busAdd, &txBufferPtr[1], txSize, &rxBufferPtr, rxSize);
    			if(ret){
    				char printed_str[50];
    				itm.print(rxBufferPtr);
    				itm.print("\n");

    				snprintf(printed_str, 50, "\r\nTemperature on I2C is %x degree.", (int8_t) rxBufferPtr);
    				lpcUart.write(printed_str);
    				lpcUart.write("\r\n");
    			}else{
    				lpcUart.write("reading fails!");
    			}
    		}
    	}
    }

    return 0 ;
}
