/** @file gpio.h
* 
* @brief Provides an abstraction layer to the LED(s) and Buttons.
*
* @par       
* 
*/ 

#include <stdint.h>

#ifndef _GPIO_H
#define _GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

void gpio_led_red_init();	// Initialise the red LED
void gpio_led_red_on();		// Sets the red LED
void gpio_led_red_off();	// Disables the red LED
void gpio_led_red_toggle();	// Toggle the red LED
void gpio_led_init();		// Initialise the RGB led output
void gpio_led_set(uint32_t);	// ORs PC0, PC1 and PC2 with the passed input
void gpio_led_toggle(uint32_t);	// XORs PC0, PC1 and PC2 with the passed input

void gpio_button_init();	// Initialise the buttons
uint8_t gpio_button_0_read();	// returns button 0 state
uint8_t gpio_button_1_read();	// Returns button 1 state
void EXTI0_IRQHandler();	// EXTI channel 0 ISR
void EXTI1_IRQHandler();	// EXTI channel 1 ISR


#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H */
