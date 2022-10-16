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
#include "MorseSender.h"
#include "MorseCode.h"

// TODO: insert other include files here
#define INDEX 81


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


    // TODO: insert code here
	DigitalIoPin led(0,25,false);
	DigitalIoPin decoder(0,8,false);

	MorseSender ms(led, decoder);
	char input[INDEX];
	unsigned int i = 0;
	int ch =0;


	while(1){
		//get char through UART
		ch = Board_UARTGetChar();
		if(ch != EOF){
			if(ch == '\n') Board_UARTPutChar('\r');
			Board_UARTPutChar(ch); //print the char out in the terminal
			if(ch == '\r') Board_UARTPutChar('\n');

			if(i < INDEX - 1){
				if(ch != '\n' && ch != '\r'){ //add the char when it is not a linefeed
					input[i] = toupper(ch);
					++i;
				}else{
					input[i] = '\n'; // linefeed add it to array, then add terminating sign
					input[i + 1] = '\0';
					ms.convertedToMorse(input);
					i = 0;
				}
			}else{
				input[i + 1] = '\0';
				ms.convertedToMorse(input);
				i = 0;
			}
		}
	}


//    // Force the counter to be placed into memory
//    volatile static int i = 0 ;
//    // Enter an infinite loop, just incrementing a counter
//    while(1) {
//        i++ ;
//        // "Dummy" NOP to allow source level single
//        // stepping of tight while() loop
//        __asm volatile ("nop");
//    }
    return 0 ;
}
