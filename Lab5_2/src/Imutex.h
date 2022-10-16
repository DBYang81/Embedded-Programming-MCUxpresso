/*
 * Imutex.h
 *
 *  Created on: 13 Oct 2022
 *      Author: DBY
 */

#ifndef IMUTEX_H_
#define IMUTEX_H_

class Imutex {
public:
	Imutex();
	virtual ~Imutex();
	void lock();
	void unlock();
private:
	bool enable;
};

#endif /* IMUTEX_H_ */
