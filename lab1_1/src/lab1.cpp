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
static volatile std::atomic_int counter;

#ifdef __cplusplus
extern "C" {
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
//    Board_LED_Set(0, false);
#endif
#endif

    // TODO: insert code here
    Chip_Clock_SetSysTickClockDiv(1);

    sysTickRate = Chip_Clock_GetSysTickClockRate();

    SysTick_Config(sysTickRate / TICKRATE_HZ);

    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 17, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 17);

    while(1){
//    	bool SW1= Chip_GPIO_GetPinState(LPC_GPIO, 0, 17);
//    	if(SW1){
//    		Chip_GPIO_SetPinState(LPC_GPIO, 0, 25, false);
//    		Sleep(1000);
//    		Chip_GPIO_SetPinState(LPC_GPIO, 0, 25, true);
//    		Sleep(1000);
//    		Chip_GPIO_SetPinState(LPC_GPIO, 0, 3, false);
//    		Sleep(1000);
//    		Chip_GPIO_SetPinState(LPC_GPIO, 0, 3, true);
//    		Sleep(1000);
//    		Chip_GPIO_SetPinState(LPC_GPIO, 1, 1, false);
//    		Sleep(1000);
//    		Chip_GPIO_SetPinState(LPC_GPIO, 1, 1, true);
//    		Sleep(1000);
//    	}
    	if(Chip_GPIO_GetPinState(LPC_GPIO, 0,17)){
    		Board_LED_Set(0, true);
    		Sleep(1000);
    		Board_LED_Set(0, false);
    		Sleep(1000);
    		Board_LED_Set(1, true);
    		Sleep(1000);
    		Board_LED_Set(1, false);
    		Sleep(1000);
    		Board_LED_Set(2, true);
    		Sleep(1000);
    		Board_LED_Set(2, false);
    		Sleep(1000);
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
