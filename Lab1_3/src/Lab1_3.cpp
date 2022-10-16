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

// TODO: insert other include files here
#include <atomic>
#include <ctime>
#include <cstdlib>
#include "DigitalIoPin.h"
#include "dice.h"


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

    //Input buttons
    DigitalIoPin testBtn(0, 8, true, true, true);
    DigitalIoPin oprtBtn(1, 6, true, true, true);

    Dice dice;
    uint32_t counter = 0;

    while(1){
    	if(testBtn.read()){
    		dice.Show(7);
    		while(testBtn.read());
    		dice.Show(0);
            counter = 0;
    	}
    	if(oprtBtn.read()){
    		dice.Show(0);
    		while(oprtBtn.read()){
                ++counter;
//                if(counter > 6) counter = 1;//use a counter as random number
//    			std::srand(time(0)); // do not set fix seed because mcu does not clock
    			counter = (std::rand() % 6) + 1; //possible to use rand() by default time seed
    		}
    		dice.Show(counter);
    	}
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
