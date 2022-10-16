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
#include "Menu.h"
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
    Menu menu;

    bool SW1_state = false;
    bool SW2_state = false;
    bool SW3_state = false;

    menu.print();

    while(1) {
        if(SW1.read()) {
            SW1_state = true;
        }
        else if(SW1_state){
            menu.move_up();
            menu.print();
            SW1_state = false;
        }
        if(SW2.read()) {
            SW2_state = true;
        }
        else if(SW2_state){
            menu.switch_led();
            menu.print();
            SW2_state = false;
        }
        if(SW3.read()) {
            SW3_state = true;
        }
        else if(SW3_state){
            menu.move_down();
            menu.print();
            SW3_state = false;
        }


    }
}













