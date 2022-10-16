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
#include "LpcUart.h"
#include <stdlib.h>

// TODO: insert other include files here



// TODO: insert other definitions and declarations here
#define TICKRATE_HZ (1000)


void clean_buff(char *str, int length);
void tolower(char *str);

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
	LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
	LpcUart lpcUart(cfg); //create lpcUart object in order to read or write pins directly

	char input[81];
	unsigned int i = 0;
	char ch; // char read from lpcUart

	while(1){
		if(lpcUart.read(ch)){
			if(ch == '\n') lpcUart.write('\r'); //precede linefeed with carriage return
			lpcUart.write(ch);
			if(ch == '\r') lpcUart.write('\n'); //precede linefeed with carriage return



			if(i < 80 && ch != '\0'){
				input[i] = ch;
				i++;
			}

			//receive input after '\n' with certain input
			if(ch == '\r' && strlen(input) != 0){
				char tmp[81];
				char cmd[10];
				strcpy(tmp, input);
				clean_buff(input, 81);
				i = 0;
				//split the string into [command] [value] by delimit :
//				char *cmd = strtok(tmp, ":");
				sscanf(tmp, "%s", cmd);
				strcpy(tmp, tmp + strlen(cmd) + 1);


				tolower(cmd);
				if(strcmp(cmd, "wpm") ==  0){
					int wpm = atoi(tmp);
					//setup the range from 1 to 100 and unit time min as 10ms
					if(wpm > 0 && wpm < 301) ms.set_wpm(wpm);
					else lpcUart.write("\r\n invalid and range between 1 to 300\r\n");
				}
				else if(strcmp(cmd, "send") == 0){
					if (strlen(tmp) > 0) {
						for(unsigned int j = 0; j < strlen(tmp); j++){
							tmp[j] = toupper(tmp[j]);
						}
						ms.convertedToMorse(tmp);
					}
					else lpcUart.write("\r\n No text to be sent!");
				}
				else if(strcmp(cmd, "set") == 0){
					char str[5];
					int wpm = ms.get_wpm();
					sprintf(str, "%d", wpm);
					lpcUart.write("\r\n WPM :");
					lpcUart.write(str);
					int dot_time = ms.get_dot_duration();
					sprintf(str, "%d", dot_time);
					lpcUart.write("\r\n The dot length :");
					lpcUart.write(str);
					lpcUart.write("\r\n");

				}else{
					lpcUart.write("\r\n invalid commands\r\n");
					lpcUart.write("Commands As wpm : [number], send : [text], set\r\n");
				}
			}

			if(input[0] == '\r'){
				//keep the empty input
				input[0] = '\0';
				i = 0;
			}


		}

	}

	return 0 ;
}

void clean_buff(char *str, int length){
	for(int i = 0; i < length; i++){
		str[i] = 0;
	}
}

void tolower(char *str){
	for(unsigned int i = 0; i < strlen(str); i++){
		str[i] = tolower(str[i]);
	}
}
