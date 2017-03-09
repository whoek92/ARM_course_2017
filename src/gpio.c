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
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER0_0;
	GPIOC->OTYPER |= GPIO_OTYPER_OT_0;
}

void gpio_led_red_on()
{
	GPIOC->BSRR |= GPIO_BSRR_BR_0;
}

void gpio_led_red_off()
{
	GPIOC->BSRR |= GPIO_BSRR_BS_0;
}

void gpio_led_red_toggle()
{
	GPIOC->ODR ^= GPIO_ODR_ODR_0;
}

void gpio_led_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER0_0 + GPIO_MODER_MODER1_0 + GPIO_MODER_MODER2_0;
	GPIOC->OTYPER |= GPIO_OTYPER_OT_0 + GPIO_OTYPER_OT_1 + GPIO_OTYPER_OT_2;
	GPIOC->BSRR |= (0x07) << 16;
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
			GPIOC->BSRR = ((0b100 & 0b000) << 16) + (0b000 ^ 0x07);
			EXTI->IMR |= 0b11;
			break;
	}
}

void gpio_led_toggle(uint32_t rgb)
{
	GPIOC->ODR ^= (rgb & 0b111);
}

void gpio_button_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->PUPDR |= (0b0101);
	EXTI->IMR |= 0b11;
	EXTI->FTSR |= 0b11;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
}

uint8_t gpio_button_0_read()
{
	return (GPIOA->IDR) & (1<<0);
}

uint8_t gpio_button_1_read()
{
	return (GPIOA->IDR) & (1<<1);
}

void EXTI1_IRQHandler(void)	// PA1 interrupt service routine
{
	mode--;
	EXTI->IMR &= ~0b01;
	EXTI->PR ^= EXTI_PR_PR0;
	colorCount = 0;
}

void EXTI0_IRQHandler(void)	// PA0 interrupt service routine
{
	mode++;
	EXTI->IMR &= ~0b10;
	EXTI->PR ^= EXTI_PR_PR1;
	colorCount = 0;
}
