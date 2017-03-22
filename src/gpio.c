/*
 * gpio.c
 *
 *  Created on: Feb 15, 2017
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

void gpio_led_red_init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	// Enable GPIO C
  GPIOC->MODER |= GPIO_MODER_MODER0_0;	// Set PC0 to output
  GPIOC->OTYPER |= GPIO_OTYPER_OT_0;	// Set output to open-drain
}

void gpio_led_red_on()
{
  GPIOC->BSRR |= GPIO_BSRR_BR_0;	// Reset PC0
}

void gpio_led_red_off()
{
  GPIOC->BSRR |= GPIO_BSRR_BS_0;	// Set PC0
}

void gpio_led_red_toggle()
{
  GPIOC->ODR ^= GPIO_ODR_ODR_0;		// Toggle PC0
}

void gpio_led_init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	// Enable GPIO C
  GPIOC->MODER |= GPIO_MODER_MODER0_0 	// Set PC0, PC1 and PC2 to output
	        + GPIO_MODER_MODER1_0 	//
		+ GPIO_MODER_MODER2_0;	//
  GPIOC->OTYPER |= GPIO_OTYPER_OT_0 	// Set PC0, PC1 and PC2 to open-drain
		 + GPIO_OTYPER_OT_1 	//
		 + GPIO_OTYPER_OT_2;	//
  GPIOC->BSRR |= (0x07) << 16;		// Set PC0, PC1 and PC2 to '1'
}

void gpio_led_set(uint32_t rgb)
{
  switch(mode & 0b11)
  {
    case 0:
      switch(rgb & 0b111)
      {
	case 0:
	  GPIOC->BSRR = ((0b000 & 0x07) << 16) + (0b000 ^ 0x07);
	  break;
	case 1:
	  GPIOC->BSRR = ((0b001 & 0x07) << 16) + (0b001 ^ 0x07);
	  break;
	case 2:
	  GPIOC->BSRR = ((0b011 & 0x07) << 16) + (0b011 ^ 0x07);
	  break;
	case 3:
	  GPIOC->BSRR = ((0b010 & 0x07) << 16) + (0b010 ^ 0x07);
	  break;
	case 4:
	  GPIOC->BSRR = ((0b110 & 0x07) << 16) + (0b110 ^ 0x07);
	  break;
	case 5:
	  GPIOC->BSRR = ((0b100 & 0x07) << 16) + (0b100 ^ 0x07);
	  break;
	case 6:
	  GPIOC->BSRR = ((0b101 & 0x07) << 16) + (0b101 ^ 0x07);
	  break;
	case 7:
	  GPIOC->BSRR = ((0b111 & 0x07) << 16) + (0b11 ^ 0x07);
	  EXTI->IMR |= 0b11;
	  break;
      }
      break;

    case 1:
      switch(rgb & 0b1)
      {
	case 0:
	  GPIOC->BSRR = ((0b001 & 0x07) << 16) + (0b001 ^ 0x07);
	  break;
	case 1:
	  GPIOC->BSRR = ((0b100 & 0x07) << 16) + (0b100 ^ 0x07);
	  EXTI->IMR |= 0b11;
	    break;
      }
      break;

    case 2:
      switch(rgb & 0b11)
      {
	case 0:
	  GPIOC->BSRR = ((0b001 & 0x07) << 16) + (0b001 ^ 0x07);
	  break;
	case 1:
	  GPIOC->BSRR = ((0b010 & 0x07) << 16) + (0b010 ^ 0x07);
	  break;
	case 2:
	  GPIOC->BSRR = ((0b100 & 0x07) << 16) + (0b100 ^ 0x07);
	  break;
	case 3:
	  GPIOC->BSRR = ((0b111 & 0x07) << 16) + (0b111 ^ 0x07);
	  EXTI->IMR |= 0b11;
	  break;
      }
      break;

    default:
      GPIOC->BSRR = ((rgb & 0b000) << 16) + (0b000 ^ 0x07);
      EXTI->IMR |= 0b11;
      break;
  }
}

void gpio_led_toggle(uint32_t rgb)
{
  GPIOC->ODR ^= (rgb & 0b111);	// Toggle PC0, PC1 and PC2 based
				// on the rgb value passed
}

void gpio_button_init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// Enable GPIO A
  GPIOA->PUPDR |= (0b0101);		// Enable pull-up on PA0 and PA2
  EXTI->IMR |= 0b11;			// Unmask EXTI channel 0 and 1 interrupt
  EXTI->FTSR |= 0b11;			// Set interrupt on high-low transition
  NVIC_EnableIRQ(EXTI0_IRQn);		// Enable EXTI channel 0 and 1 interrupt
  NVIC_EnableIRQ(EXTI1_IRQn);		//
}

uint8_t gpio_button_0_read()
{
  return (GPIOA->IDR) & (1<<0);	// Return button 0 state
}

uint8_t gpio_button_1_read()
{
  return (GPIOA->IDR) & (1<<1);	// Return button 1 state
}

void EXTI1_IRQHandler(void)	// PA1 interrupt service routine
{
  mode--;			// Decrement the mode variable
  EXTI->IMR &= ~0b01;		// Mask the interrupt of channel 0 (debouncing)
  EXTI->PR ^= EXTI_PR_PR0;	// Reset EXTI channel 1 IFG
  colorCount = 0;		// Reset color counter
}

void EXTI0_IRQHandler(void)	// PA0 interrupt service routine
{
  mode++;			// Increment the mode variable
  EXTI->IMR &= ~0b10;		// Mask the interrupt of channel 1 (debouncing)
  EXTI->PR ^= EXTI_PR_PR1;	// Reset EXTI channel 0 IFG
  colorCount = 0;		// Reset color counter
}
