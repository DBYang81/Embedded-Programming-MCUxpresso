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
#include "LiquidCrystal.h"
#include "DigitalIoPin.h"
#include <string>

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
    // initialize the RIT
    Chip_RIT_Init(LPC_RITIMER);

    //LCD pins setup as output
    DigitalIoPin rs(0, 8, false, true, false);
	DigitalIoPin en(1, 6, false, true, false);
	DigitalIoPin d4(1, 8, false, true, false);
	DigitalIoPin d5(0, 5, false, true, false);
	DigitalIoPin d6(0, 6, false, true, false);
	DigitalIoPin d7(0, 7, false, true, false);

	//button pins on LPC setup as input
	DigitalIoPin sw1(0,17,true,true,true);
	DigitalIoPin sw2(1,11,true,true,true);
	DigitalIoPin sw3(1,9,true,true,true);

	//create lcd object
    LiquidCrystal lcd (&rs, &en, &d4, &d5, &d6, &d7);

    lcd.clear(); //clear the LCD
    lcd.setCursor(0, 0); //set the posiiton of cursor
    lcd.begin(16,2);

    char buff[33];

    while(1){
        std::string s1 = "UP  ";
        std::string s2 = "UP  ";
        std::string s3 = "UP  ";

    	if(sw1.read()) s1="DOWN";
    	else s1;
    	if(sw2.read()) s2="DOWN";
    	else s2;
    	if(sw3.read()) s3="DOWN";
    	else s3;
    	snprintf(buff, 33, "B1    B2    B3  %s  %s  %s", s1.c_str(), s2.c_str(), s3.c_str());
    	lcd.print(buff);
    }



    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	i++;
        __asm volatile ("nop");
    }
    return 0 ;
}
