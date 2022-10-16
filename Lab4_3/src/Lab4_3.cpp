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

#include <cr_section_macros.h>
#include "I2C.h"
#include "DigitalIoPin.h"
#include "LpcUart.h"
#include "StateMachine.h"
#include "Event.h"
#include "TC74R.h"
#include "EventQueue.h"
#include <atomic>

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

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
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

    // TODO: insert code here
    Chip_Clock_SetSysTickClockDiv(1);

    sysTickRate = Chip_Clock_GetSysTickClockRate();

    SysTick_Config(sysTickRate / TICKRATE_HZ);


    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
    LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
    LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
    LpcUartConfig U_cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
    LpcUart lpcUart(U_cfg); //create lpcUart object in order to read or write pins directly


    DigitalIoPin sw1(0,17,true,true,true);
    DigitalIoPin sw3(1,9,true,true,true);

    I2C_config cfg;
    I2C i2c (cfg);

    TC74_R tc74(i2c, lpcUart, 0x4A);

    StateMachine fsm(tc74, lpcUart);

    EventQueue events;

    while(1) {
    	Sleep(1);
    	if(sw1.read()) {
    		Sleep(1);
    		events.publish(Event(Event::eLunch, 0));
    	}

    	if(sw3.read()) {
    		Sleep(1);
    		events.publish(Event(Event::eNight, 0));
    	}

    	events.publish(Event(Event::eTick, 0));
    	while (events.pending()) {
    		fsm.handlestate(events.consume());
    	}
    }
    return 0;
}




















