/*
 * MoreSender.h
 *
 *  Created on: 15 Sep 2022
 *      Author: DBY
 */

#include "MorseCode.h"
#include "DigitalIoPin.h"
#include "Board.h"
#include "chip.h"

#include <cstdarg>
#include <cstring>
#include <atomic>
#include <string>


#ifndef MORSESENDER_H_
#define MORSESENDER_H_


class MorseSender {
public:
	MorseSender(DigitalIoPin &led_pt, DigitalIoPin &decoder_pt);
	virtual ~MorseSender();
	void convertedToMorse(char *input_str);
	void convertedToMorse(std::string s);

private:
	DigitalIoPin *led_ptr;
	DigitalIoPin *decode_ptr;
};

#endif /* MORSESENDER_H_ */
