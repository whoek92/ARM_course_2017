/*
 * timer.c
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
uint16_t volume;

void timer_init()
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->CFGR = RCC_CFGR_PPRE1_DIV16;	// APB1 prescaler (16/2, 16 MHz -> 2 MHz)
  TIM2->PSC = 1999;			// TIM2 prescaler (1999+1 prescaler -> 2 MHz -> 1 kHz)
  TIM2->ARR = 3999; 			// TIM2 final value (999+1 cycles per update, 1 kHz -> 1 Hz)
  TIM2->EGR |= TIM_EGR_UG;		// Update TIM2 counters
  TIM2->SR &= ~TIM_SR_UIF;		// Reset TIM2 update interrupt flag
  TIM2->DIER = TIM_DIER_UIE;		// Update Interrupt enable
  NVIC_EnableIRQ(TIM2_IRQn);		// IRQ enabled
  TIM2->CR1 = TIM_CR1_CEN;		// TIM2 enable
}

void TIM2_IRQHandler()
{
  if(TIM2->SR & TIM_SR_UIF)
  {
    //gpio_led_toggle(0b111);
      //WM8731_CW(WM8731_AAPC,WM8731_AAPC_INSEL + WM8731_AAPC_MICBOOST + WM8731_AAPC_SIDETONE + WM8731_AAPC_BYPASS + ((volume>>4)&0xC0));
      gpio_led_set((volume>>4)&0x3);
  }
  TIM2->SR = 0;						// Reset all TIM2 IFGs
}
