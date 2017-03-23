//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

// definitions for compilation
#define DEBUGGINGADC

#include <stdio.h>
#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include <stm32f4xx.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "WM8731.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.

  // Infinite loop
	RCC->CFGR = 0;		// Set system clock to HSI (16MHz internal RC-oscillator)
	gpio_button_init();	// Initialise the registers for button 0 and 1
	gpio_led_init();	// Initialise the leds
	//timer_init();		// Initialise TIM2
	//adc_init();		// Initialise ADC1
	//adc_start();		// Start ADC1
	WM8731_init();		// Initialise SPI
	while(1){};
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
