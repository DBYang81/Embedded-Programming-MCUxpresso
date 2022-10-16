/*
===============================================================================
 Name        : main.c
 Author      : $(Dongbin Yang)
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
#include <atomic>
#include <ctype.h>
#include "DigitalIoPin.h"

// TODO: insert other include files here
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

// TODO: insert other definitions and declarations here
#define TICKRATE_HZ (1000)

int main(void) {

	uint32_t sysTickRate;

	Chip_Clock_SetSysTickClockDiv(1);

	sysTickRate = Chip_Clock_GetSysTickClockRate();

	SysTick_Config(sysTickRate / TICKRATE_HZ);


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

    DigitalIoPin SW(0,17,true,true,true);
    DigitalIoPin OUT_g(0,3,false);


    // TODO: insert code here

    bool mode = false;

    int c = 0;

    while(1){// echo back what receive
    	if(mode == false){
    		OUT_g.write(true);
    		c = Board_UARTGetChar();
    		if(c!= EOF){
    			if(c=='\n')Board_UARTPutChar('\r');
    			Board_UARTPutChar(toupper(c));
    			if(c=='\r')Board_UARTPutChar('\n');
    		}
    	}else if(mode == true){
    		OUT_g.write(false);
    		c = Board_UARTGetChar();
    		if(c!= EOF){
    			if(c=='\n')Board_UARTPutChar('\r');
    			Board_UARTPutChar(tolower(c));
    			if(c=='\r')Board_UARTPutChar('\n');
    		}
    	}
    	if(SW.read()) {
    		mode = !mode;
    	}
    }
    return 0;
}


