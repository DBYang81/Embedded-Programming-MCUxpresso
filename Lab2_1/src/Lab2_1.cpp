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
//#include "ITM_write.h"
#include "DigitalIoPin.h"
#include "PrintItm.h"
#include <atomic>
static volatile std::atomic_int counter;

// TODO: insert other include files here
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

    DigitalIoPin SW1(0,17,true,true,true);
    DigitalIoPin SW2(1,11,true,true,true);
    DigitalIoPin SW3(1,9,true,true,true);

    PrintItm itm;
    int cnt1 = 0;
    int cnt2 = 0;
    int cnt3 = 0;

    while(1){
    	if(SW1.read()){
    		++cnt1;
    	}else if(cnt1 != 0){
    		itm.print("SW1 pressed for ");
    		itm.print(cnt1);
    		itm.print(" ms.\n");
    		cnt1 = 0;
    	}

    	if(SW2.read()){
    		++cnt2;
    	}else if(cnt2 != 0){
    		itm.print("SW2 pressed for ");
    		itm.print(cnt2);
    		itm.print(" ms.\n");
    		cnt2 = 0;
    	}

    	if(SW3.read()){
    		++cnt3;
    	}else if(cnt3 != 0){
    		itm.print("SW3 pressed for ");
    		itm.print(cnt3);
    		itm.print(" ms.\n");
    		cnt3 = 0;
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
