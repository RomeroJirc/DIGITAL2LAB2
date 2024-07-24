/*
 * ADC.h
 *
 * Created: 13/05/2024 01:10:21 p. m.
 *  Author: josei
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>
	
void initADC(void);
uint8_t ADC_CHANEL_SELECT(uint8_t chanel);

#endif /* ADC_H_ */