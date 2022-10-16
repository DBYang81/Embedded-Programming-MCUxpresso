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
#include <atomic>
#include "PrintItm.h"
#include "DigitalIoPin.h"
#include <vector>
#include <numeric>
#include <algorithm>


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
    Board_LED_Set(0, true);
#endif
#endif

    DigitalIoPin SW1(0,17,true,true,true);
    PrintItm itm;

    CoreDebug ->DEMCR |= 1 << 24;
    DWT->CTRL |= 1;

    std::vector<uint32_t> vec;

    while(1){
    	if(SW1.read() && vec.size() < 50){
    		uint32_t init_v = DWT-> CYCCNT;
    		Sleep(1);
    		uint32_t final_v = DWT-> CYCCNT;
    		vec.push_back(final_v - init_v);
    	}
    	while(SW1.read());
    	if(vec.size() == 50){
    		std::sort(vec.begin(), vec.end());
    		double averg_st = std::accumulate(vec.begin(), vec.end(), 0.0) / 50;
    		itm.print("average sleep time in counter cycle: %f\n", averg_st);
    		itm.print("average sleep time in ms: %f\n", (averg_st*1000000/72000000));
    		itm.print("*******************************************************************************\n");
    		for(uint32_t i = 0; i < vec.size(); ++i){
    			itm.print("No." + std::to_string(i + 1) + ":\t" + std::to_string(vec[i]) + "\n");
    		}
    		vec.clear();
    	}
    }






    return 0 ;
}
