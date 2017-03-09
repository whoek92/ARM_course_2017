/*
 * adc.c
 *
 *  Created on: Mar 8, 2017
 *      Author: Wim
 */

#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "spi.h"

#include <stm32f4xx.h>

uint32_t colorCount;
uint8_t mode;
uint8_t resetPin;

void adc_init()
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	GPIOC->MODER |= GPIO_MODER_MODER4;
	ADC1->SQR3 |= 14;				// Select channel 14 for the first conversion
	ADC1->SMPR2 |= 0b000;
	ADC1->CR1 |= ADC_CR1_EOCIE;
	ADC1->CR2 |= ADC_CR2_ADON + ADC_CR2_CONT + ADC_CR2_EOCS;
	ADC->CCR |= ADC_CCR_ADCPRE;
}

void adc_start()
{
	ADC1->SR &= ~(ADC_SR_EOC);
	ADC1->CR2 |= ADC_CR2_SWSTART;
	NVIC_EnableIRQ(ADC_IRQn);
}

uint16_t adc_read()
{
	while((ADC1->SR & ADC_SR_EOC) == 0);
	return (ADC1->DR & 0xFFFF);
}

void ADC_IRQHandler(void)
{
	colorCount += (ADC1->DR);
	if((mode & 0b111) < 3)
		gpio_led_set((colorCount >> 23) & 0b111);
	else
		gpio_led_set((ADC1->DR >> 6) & 0b111);
}
