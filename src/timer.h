/*
*
* @brief Provides an abstraction layer to the timer functions and controls.
*
* @par
*
*/


#include <stdint.h>

#ifndef _TIMER_H
#define _TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

void timer_init();
void TIM2_IRQHandler();


#ifdef __cplusplus
}
#endif

#endif /* _TIMER_H */
