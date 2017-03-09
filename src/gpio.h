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

void gpio_led_red_init();
void gpio_led_red_on();
void gpio_led_red_off();
void gpio_led_red_toggle();
void gpio_led_init();
void gpio_led_set(uint32_t);
void gpio_led_toggle(uint32_t);

void gpio_button_init();
uint8_t gpio_button_0_read();
uint8_t gpio_button_1_read();
void EXTI0_IRQHandler();
void EXTI1_IRQHandler();


#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H */
