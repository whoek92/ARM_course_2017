/*
*
* @brief Provides an abstraction layer to the ADC.
*
* @par
*
*/


#include <stdint.h>

#ifndef _ADC_H
#define _ADC_H

#ifdef __cplusplus
extern "C" {
#endif

void adc_init();	// Initialises the ADC registers
void adc_start();	// Starts the continuous or single conversion
uint16_t adc_read();	// Read the most recent conversion
void ADC_IRQHandler();	// ADC interrupt service routine

#ifdef __cplusplus
}
#endif

#endif /* _ADC_H */
