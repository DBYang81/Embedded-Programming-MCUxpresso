/*
===============================================================================
 Name        : main.c
 Author      : $(Dongbin yang)
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
#include "DigitalIoPin.h"

// TODO: insert other include files here
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

// TODO: insert other definitions and declarations here

#define TICKRATE_HZ (1000)


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
//    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    Chip_Clock_SetSysTickClockDiv(1);

    sysTickRate = Chip_Clock_GetSysTickClockRate();

    SysTick_Config(sysTickRate / TICKRATE_HZ);

    DigitalIoPin SW1(0,17,true,true,false);
    DigitalIoPin SW2(1,11,true,true,false);
    DigitalIoPin SW3(1,9,true,true,false);


    DigitalIoPin OUT1(0,25,false);
    DigitalIoPin OUT2(0,3,false);
    DigitalIoPin OUT3(1,1,false);

    while(1){
    	if(SW1.read()){
    		OUT1.write(true);
    	}else{
    		OUT1.write(false);
    		Sleep(1000);
    		OUT1.write(true);
    	}

    	if(SW2.read()){
    		OUT2.write(true);
    	}else{
    		OUT2.write(false);
    		Sleep(1000);
    		OUT2.write(true);
    	}

    	if(SW3.read()){
    		OUT3.write(true);
    	}else{
    		OUT3.write(false);
    		Sleep(1000);
    		OUT3.write(true);
    	}
    	Sleep(10);
    }



    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
