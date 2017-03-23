/*
 * adc.c
 *
 *  Created on: Mar 8, 2017
 *      Author: Wim
 */

#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include <stm32f4xx.h>
#include "WM8731.h"

uint32_t colorCount;
uint8_t mode, rgb;
uint8_t resetPin;
uint16_t volume = 0;

void adc_init()
{
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		// Enable ADC1 peripheral clock
  GPIOC->MODER |= GPIO_MODER_MODER4;		// Set PC4 to alternate function
  ADC1->SQR3 |= 14;				// Select channel 14 for the first conversion
  ADC1->SMPR2 |= 0b111;				// Sample time = 3 cycles (000)
  ADC1->CR1 |= ADC_CR1_EOCIE;			// Enable end-of-conversion interrupt
  ADC1->CR2 |= ADC_CR2_ADON 			// Enable ADC
	     + ADC_CR2_CONT 			// Set continuous conversion mode
	     + ADC_CR2_EOCS;			// Set EOC at end of every regular conversion
  ADC->CCR |= ADC_CCR_ADCPRE;			// Set PCLK2 / 8
}

void adc_start()
{
  ADC1->SR &= ~(ADC_SR_EOC);			// Reset EOC IFG
  ADC1->CR2 |= ADC_CR2_SWSTART;			// Start ADC
  NVIC_EnableIRQ(ADC_IRQn);			// Enable ADC IRQ
}

uint16_t adc_read()
{
  while((ADC1->SR & ADC_SR_EOC) == 0);		// Wait till conversion has finished
  return (ADC1->DR & 0xFFFF);			// Return the last 16 bits of the output
}

void ADC_IRQHandler(void)
{
  colorCount += (ADC1->DR);			// Increment the color counter
  rgb = ((colorCount >> 18) & 0b111);		// Display counter value bits
#ifndef DEBUGGINGADC
  if((mode & 0b111) < 3)			// IF mode is lower than 3
  {
    gpio_led_set(rgb);
  }
  else						// ELSE
    gpio_led_set((ADC1->DR >> 6) & 0b111);	// Display output value bits
#endif /*DEBUGGING*/
#ifdef DEBUGGINGADC
  //GPIOC->BSRR = ((rgb & 0b111) << 16) + (rgb ^ 0b111);
#endif /*DEBUGGING*/

}
