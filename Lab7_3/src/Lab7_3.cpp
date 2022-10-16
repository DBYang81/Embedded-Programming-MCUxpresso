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
#include "SimpleMenu.h"
#include "integerEdit.h"
#include <string>
#include "LiquidCrystal.h"
#include "LpcUart.h"
#include "KillerEdit.h"
#include "SleepEdit.h"
#include <atomic>

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
//	tick++;
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
#define BACK_EVENT_INTERVAL 10000//10s timeout for BACK event

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

    Chip_Clock_SetSysTickClockDiv(1);
    uint32_t sysTickRate = Chip_Clock_GetSysTickClockRate();
    SysTick_Config(sysTickRate / 1000);

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

   	//LED Initialize

   	DigitalIoPin rled (0, 25, false, true, true);
   	DigitalIoPin gled (0, 3, false, true, true);
   	DigitalIoPin bled (1, 1, false, true, true);


    Chip_RIT_Init(LPC_RITIMER);
//    NVIC_EnableIRQ(RITIMER_IRQn);
    LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);
    lcd->begin(16, 2);
    lcd->setCursor(0,0);

    SimpleMenu menu;

    IntegerEdit *time = new IntegerEdit(lcd, &lpcUart ,std::string("Time"), 10, 0);
    KillerEdit *blank = new KillerEdit(lcd, &lpcUart ,std::string("Blank"), 200, 100); //when accept(), generate invalid feed sequence
    SleepEdit *light = new SleepEdit(lcd, &lpcUart ,std::string("Light"), 2, 0);//after accept(), sleep for 10s


    menu.addItem(new MenuItem(time));
    menu.addItem(new MenuItem(blank));
    menu.addItem(new MenuItem(light));


    time->setValue(5);
    blank->setValue(150);
    light->setValue(0);


    //check WDT reset
    if(Chip_WWDT_GetStatus(LPC_WWDT) & WWDT_WDMOD_WDTOF){
    	lpcUart.write("Watchdog timeout\r\n");
    	rled.write(true);
//    	Board_LED_Set(0,true);
    }else{
//    	Board_LED_Set(1,true);
    	gled.write(true);
    	lpcUart.write("Reset\r\n");
    }


    //enable WDT Oscillator
    Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_WDTOSC_PD);

    /*Initialize WWDT clock */
    Chip_WWDT_Init(LPC_WWDT);


    //The WDT divides the input frequency into it by 4

   uint32_t wdtFreq = Chip_Clock_GetWDTOSCRate() / 4 ;
//   lpcUart.write(wdtFreq);

    //Feed time constant to approximately 2s.
    //Worst case delay is considered to be 6ms, due to the main loop Sleep(1) and several delays in LCD

    Chip_WWDT_SetTimeOut(LPC_WWDT, wdtFreq * 2);

    /* Configure WWDT to reset on timeout */
    Chip_WWDT_SetOption(LPC_WWDT, WWDT_WDMOD_WDRESET);

    /* Clear watchdog warning and timeout interrupts */
    Chip_WWDT_ClearStatusFlag(LPC_WWDT, WWDT_WDMOD_WDTOF | WWDT_WDMOD_WDINT);

    /* Start watchdog */
    Chip_WWDT_Start(LPC_WWDT);


    unsigned int timeout = 0;
    while(1) {
    	Chip_WWDT_Feed(LPC_WWDT); //Feed watchdog.
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
     	}
    }
    return 0 ;

}
