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
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include <string>
#include "LpcUart.h"
#include "DecimalEdit.h"
#include "stateMachine.h"

// TODO: insert other include files here
static volatile std::atomic_int counter;
//static volatile std::atomic_int tick;
#ifdef __cplusplus
extern "C"{
#endif

/*
 * @brief Handle system ticker timer
 * @return nothing
 */

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
#define BACK_EVENT_INTERVAL 10000//10s timeout for BACK event

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
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here

    Chip_Clock_SetSysTickClockDiv(1);
    sysTickRate = Chip_Clock_GetSysTickClockRate();
    SysTick_Config(sysTickRate / TICKRATE_HZ);


    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
    LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
    LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
    LpcUartConfig cfg = {LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
    LpcUart lpcUart(cfg); //create lpcUart object in order to read or write pins directly


    //button setup
    DigitalIoPin sw1_up(0,17,true,true,true); //upward button
    DigitalIoPin sw2_down(1,11,true,true,true);//downward button
    DigitalIoPin sw3_ok(1,9,true,true,true);//mode changes to focus button

    //LCD pins setup
    DigitalIoPin rs(0, 8, false, true, false);
    DigitalIoPin en(1, 6, false, true, false);
    DigitalIoPin d4(1, 8, false, true, false);
    DigitalIoPin d5(0, 5, false, true, false);
    DigitalIoPin d6(0, 6, false, true, false);
    DigitalIoPin d7(0, 7, false, true, false);






    Chip_RIT_Init(LPC_RITIMER);
    //    NVIC_EnableIRQ(RITIMER_IRQn);
    LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);
    lcd->begin(16, 2);
    lcd->setCursor(0,0);

    SimpleMenu menu;

    DecimalEdit *time = new DecimalEdit(lcd,  std::string("Time"), 200, 0, 20, &lpcUart);
    DecimalEdit *blank = new DecimalEdit(lcd, std::string("Blank"), 1, 0, 0.1, &lpcUart);
    IntegerEdit *light = new IntegerEdit(lcd, &lpcUart, std::string("Light"), 3, 0, 1);


    menu.addItem(new MenuItem(time));
    menu.addItem(new MenuItem(blank));
    menu.addItem(new MenuItem(light));
    unsigned int timeout = 0;

    time->setValue(100);
    blank->setValue(0.5);
    light->setValue(0);

    stateMachine fsm;

    while(1) {
    	Sleep(1);
    	timeout++;
    	if(sw1_up.read()){
    		timeout = 0;
    		menu.event(MenuItem::up);
    		while(sw1_up.read());
    	}

    	if(sw2_down.read()){
    		timeout = 0;
    		menu.event(MenuItem::down);
    		while(sw2_down.read());
    	}

    	if(sw3_ok.read()){
    		timeout = 0;
    		menu.event(MenuItem::ok);
    		while(sw3_ok.read());
    	}

    	if(timeout >= BACK_EVENT_INTERVAL){ //10s Back Event while no button-pressed
    		timeout = 0;
    		menu.event(MenuItem::back);
    		while(sw3_ok.read());
    	}

    	fsm.HandleState(
    			Event(Event::eTick, light->getValue(),
    					(int)(time->getValue()),
						(int)(blank->getValue()*1000)));

    }
    return 0 ;
}


