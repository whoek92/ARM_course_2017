/** @file gpio.h
* 
* @brief Provides an abstraction layer to the LED(s) and Buttons.
*
* @par       
* 
*/ 

#ifndef _GPIO_H
#define _GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

void gpio_led_red_init();
void gpio_led_red_on();
void gpio_led_red_off();
void gpio_led_red_toggle();

void gpio_button_init();
uint8_t gpio_button_0_read();
uint8_t gpio_button_1_read();


#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H */
