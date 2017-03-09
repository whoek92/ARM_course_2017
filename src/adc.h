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

void adc_init();
void adc_start();
uint16_t adc_read();
void ADC_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif /* _ADC_H */
