/*
 * spi.c
 *
 *  Created on: Mar 8, 2017
 *      Author: Wim
 */


#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "spi.h"
#include <stm32f4xx.h>

#define NSS 0b10

uint32_t colorCount;
uint8_t mode;
uint8_t resetPin;

void spi_init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN	// Make sure that GPIOB and C are enabled
	        | RCC_AHB1ENR_GPIOCEN;	//
  GPIOB->MODER |= GPIO_MODER_MODER2_1	// Set PB6 to output and logic high,
	        | GPIO_MODER_MODER1_0   // PB2 to SPI3_MOSI and PB1 as NSS (out)
		| GPIO_MODER_MODER6_0;	//
  GPIOB->BSRR = GPIO_BSRR_BS_6
	      | GPIO_BSRR_BS_1;		// PB6 and PB1 high
  GPIOB->AFR[0] = (7<<(4*2));		//
  GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;

  GPIOC->MODER |= GPIO_MODER_MODER11_1	// Set PC11 to SPI3_MISO
		| GPIO_MODER_MODER10_1;	// and PC10 to SPI3_SCK

  GPIOC->AFR[1] |= (6<<((10-8)*4)) 	//
	         | (6<<((11-8)*4));	//

  RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;	// Enable SPI clock
  SPI3->CR1 |= SPI_CR1_BIDIOE		// Set the SPI to Output enable in bi-dir
	     | SPI_CR1_DFF		// 16-bit data frame
	     | SPI_CR1_SSM		// Software slave select
	     | SPI_CR1_SSI		// Slave select high
	     | SPI_CR1_BR		// Lowest baudrate (f/256)
	     | SPI_CR1_CPHA		// Clock Phases set to 1
	     | SPI_CR1_MSTR;		// Master mode
  SPI3->CR1 |= SPI_CR1_SPE;		// SPI enable

  WM8731_config_reset();		// Reset the codec
}

void spi_out(uint16_t spi_out_data)
{
  SPI3->DR = spi_out_data;			// Fill the data register
  while(SPI3->SR & SPI_SR_BSY);			// Wait till the transmission is finished (not busy).
  GPIOB->BSRR |= (NSS << 16);			// Send one NSS pulse
  for(volatile int i = 16000; i > 0; i--);	//
  GPIOB->BSRR |= NSS;				//
}

//write a control word to the WM8731
void WM8731_CW(uint16_t reg, uint16_t data)
{
  //write outputCode to SPI register (data is transmitted directly after)
  spi_out( (reg << 9) | data );
}

//reset the WM8731
void WM8731_config_reset(void)
{
  //write 0x00 to the reset register to reset the device
  WM8731_CW(WM8731_RR, WM8731_RR_RST);
}

void WM8731_forward_mic(void)
{
  WM8731_CW(WM8731_PDC,WM8731_PDC_DACPD + WM8731_PDC_OSCPD + WM8731_PDC_ADCPD + WM8731_PDC_LINEINPD);
  WM8731_CW(WM8731_AAPC,WM8731_AAPC_INSEL + WM8731_AAPC_MICBOOST + WM8731_AAPC_SIDETONE + WM8731_AAPC_BYPASS);
}
