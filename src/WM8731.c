#include "WM8731.h"
#include <stm32f4xx.h>
#include "gpio.h"
#include "mydefines.h"

//function prototypes
void WM8731_spi_init(void);
void WM8731_i2s_dac_init(void);
void WM8731_i2s_adc_init(void);
void WM8731_config_i2s_init(void);
void WM8731_config_i2s_start(void);

void WM8731_init(void){
  //initialize the command interface to the codec
  WM8731_spi_init();
  //reset the codec
  WM8731_config_reset();
  //configure codec for I2S communication
  WM8731_config_i2s_init();
  //initialize the I2S interface to the codec
  WM8731_i2s_dac_init();
  WM8731_i2s_adc_init();
  //start the I2S communication
  WM8731_config_i2s_start();
  //wait for a rising edge of WS
  while ( !(GPIOB->IDR & GPIO_IDR_IDR_12) );
  while (   GPIOB->IDR & GPIO_IDR_IDR_12  );
  //enable I2S
  SPI2->I2SCFGR |= SPI_I2SCFGR_I2SE;
  SPI1->I2SCFGR |= SPI_I2SCFGR_I2SE;
}

void WM8731_spi_init(){
  //initialize GPIO clocks for GPIOB and GPIOC
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

  //initialize MODE pin	MCU pin PB6
  //set PB6 as output
  GPIOB->MODER |= GPIO_MODER_MODER6_0;
  //set the slave select line high
  GPIOB->ODR |= GPIO_ODR_ODR_6;

  //initialize MOSI		MCU pin: PB2 (SPI3_MOSI)
  //set PB2 as high speed
  GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
  //set PB2 as alternate function
  GPIOB->MODER |= GPIO_MODER_MODER2_1;
  //set the alternate function of PB2 as SPI3
  GPIOB->AFR[0] |= (GPIO_AF7_SPI3 << (4*2));

  //initialize SCLK		MCU pin: PC10 (SPI3_SCK)
  //set PA5 as alternate function
  GPIOC->MODER |= GPIO_MODER_MODER10_1;
  //set the alternate function of PC10 as SPI3
  GPIOC->AFR[1] |= (GPIO_AF6_SPI3 << (4*(10-8)));

  //initialize CS 		MCU pin: PB1
  //set PB1 as output function
  GPIOB->MODER |= GPIO_MODER_MODER1_0;
  //set PB1 high
  GPIOB->BSRR |= GPIO_BSRR_BS_1;

  //initialize SPI3 clock
  RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
  //set SPI to transmit only communication
  SPI3->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
  //set the SPI bus to 16-bit operation
  SPI3->CR1 |= SPI_CR1_DFF;
  //set the baud rate to f_PCLK/256
  SPI3->CR1 |= SPI_CR1_BR;
  //set the SPI to master mode
  SPI3->CR1 |= SPI_CR1_MSTR;
  //set the SPI to software slave management
  SPI3->CR1 |= SPI_CR1_SSM;
  //tell SS is low
  SPI3->CR1 |= SPI_CR1_SSI;
  //set clock phase to 1
  SPI3->CR1 |= SPI_CR1_CPHA;
  //enable SPI
  SPI3->CR1 |= SPI_CR1_SPE;
}

//set up the outgoing I2S audio interface
void WM8731_i2s_dac_init(void){
  //initialize GPIO clocks for GPIOB
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  //I2S2_CK - PB13 - clock
  //set PB13 as alternate function
  GPIOB->MODER |= GPIO_MODER_MODER13_1;
  //set the alternate function of PB13 as I2S2
  GPIOB->AFR[1] |= GPIO_AF5_SPI2 << (4*(13-8));

  //I2S2_SD - PB15 - serial data
  //set PB15 as alternate function
  GPIOB->MODER |= GPIO_MODER_MODER15_1;
  //set the alternate function of PB15 as I2S2
  GPIOB->AFR[1] |= GPIO_AF5_SPI2 << (4*(15-8));

  //I2S2_WS - PB12 - word select
  //set PB12 as alternate function
  GPIOB->MODER |= GPIO_MODER_MODER12_1;
  //set the alternate function of PB12 as I2S2
  GPIOB->AFR[1] |= GPIO_AF5_SPI2 << (4*(12-8));

  //initialize SPI2/I2S2 clock
  RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
  //enable TXE interrupt
  SPI2->CR2 |= SPI_CR2_TXEIE;
  //enable interrupt using CMSIS
  //NVIC_EnableIRQ(SPI2_IRQn);
  //select I2S mode
  SPI2->I2SCFGR |= SPI_I2SCFGR_I2SMOD;
  //set to "slave transmit mode"
  //already correct by default
  //set to left justified mode
  SPI2->I2SCFGR |= SPI_I2SCFGR_I2SSTD_1;
  //set to 16-bit operation
  //already correct by default
  //load initial data
  SPI2->DR = 0x0000;
}

//set up the incoming I2S audio interface
void WM8731_i2s_adc_init(void){
  //initialize GPIO clocks for GPIOA
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  //I2S1_CK - PA5 - clock
  //set PA5 as alternate function
  GPIOA->MODER |= GPIO_MODER_MODER5_1;
  //set the alternate function of PA5 as I2S1
  GPIOA->AFR[0] |= GPIO_AF5_SPI1 << (4*5);

  //I2S1_SD - PA7 - serial data
  //set PA7 as alternate function
  GPIOA->MODER |= GPIO_MODER_MODER7_1;
  //set the alternate function of PA7 as I2S1
  GPIOA->AFR[0] |= GPIO_AF5_SPI1 << (4*7);

  //I2S1_WS - PA4 - word select
  //set PA4 as alternate function
  GPIOA->MODER |= GPIO_MODER_MODER4_1;
  //set the alternate function of PA4 as I2S1
  GPIOA->AFR[0] |= GPIO_AF5_SPI1 << (4*4);

  //initialize SPI1/I2S1 clock
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  //select I2S mode
  SPI1->I2SCFGR |= SPI_I2SCFGR_I2SMOD;
  //set to "slave receive mode"
  SPI1->I2SCFGR |= SPI_I2SCFGR_I2SCFG_0;
  //set to left justified mode
  SPI1->I2SCFGR |= SPI_I2SCFGR_I2SSTD_1;
  //set to 16-bit operation
  //already correct by default
}

//write a control word to the WM8731
static void WM8731_control_word(uint16_t reg, uint16_t data){
  //write outputCode to SPI register (data is transmitted directly after)
  SPI3->DR = (reg << 9) | data;
  //wait until the transmit buffer is empty
  while( !(SPI3->SR & SPI_SR_TXE) );
  //wait until SPI is not busy anymore
  while(   SPI3->SR & SPI_SR_BSY );
  //send a sync pulse
  GPIOB->BSRR = GPIO_BSRR_BR_1;
  for(volatile uint32_t i = 0; i<100; i++){/*do nothing in the for loop, just keep counting to 100*/}
  GPIOB->BSRR = GPIO_BSRR_BS_1;
}

//reset the WM8731
void WM8731_config_reset(void){
  //write 0x00 to the reset register to reset the device
  WM8731_control_word(WM8731_RR, WM8731_RR_RST);
}

//configure the WM8731 to bypass the microphone directly to the output
void WM8731_config_micbypass(void){
  //set the headphone output to maximum volume
  WM8731_control_word(WM8731_LHPO, 0b1111111 | WM8731_LHPO_LRHPBOTH);
  //configure the MICBOOST (extra microphone volume) and SIDETONE (bypass microphone to the output)
  WM8731_control_word(WM8731_AAPC, WM8731_AAPC_MICBOOST | WM8731_AAPC_SIDETONE);
  //power UP: microphone input, outputs, device. power DOWN: line input, ADC, DAC, oscillator, clock output.
  WM8731_control_word(WM8731_PDC, WM8731_PDC_LINEINPD | WM8731_PDC_ADCPD | WM8731_PDC_DACPD | WM8731_PDC_OSCPD | WM8731_PDC_CLKOUTPD);
}

//configure the WM8731 headphone output volume,
//@param volume - output volume. Maximum 127, values under 48 result in muted output
void WM8731_config_volume(uint16_t volume){
  volume = volume & 0b1111111;										//mask the last 7 bits as extra safety mechanism
  WM8731_control_word(WM8731_LHPO, (volume | WM8731_LHPO_LRHPBOTH) );	//set the left and right volume at once
}

#ifdef WM8731_fs_48kHz
//configure the WM8731 to use the I2S interface for data communication
void WM8731_config_i2s_init(void){
  //configure analog audio path: MICBOOST enabled, microphone as input, DAC as output,
  WM8731_control_word(WM8731_AAPC, WM8731_AAPC_MICBOOST | WM8731_AAPC_INSEL | WM8731_AAPC_DACSEL);
  //set the digital audio path control: de-emphasis to 48kHz
  WM8731_control_word(WM8731_DAPC, WM8731_DAPC_DEEMP_1 | WM8731_DAPC_DEEMP_0);
  //power up: microphone, ADC, DAC, outputs, oscillator, device. Power down: line input, clock out,
  WM8731_control_word(WM8731_PDC, WM8731_PDC_LINEINPD | WM8731_PDC_CLKOUTPD);
  //set codec to I2S mode, master
  WM8731_control_word(WM8731_DAIF, WM8731_DAIF_FORMAT_1 | WM8731_DAIF_MS);
  //set the sampling rate for ADC and DAC to 48kHz: BOSR=1, SR[3:0]=0b0000 (refer to table 18 in codec datasheet)
  WM8731_control_word(WM8731_SC, WM8731_SC_BOSR );
}
#endif

#ifdef WM8731_fs_8kHz
//configure the WM8731 to use the I2S interface for data communication
void WM8731_config_i2s_init(void){
  //configure analog audio path: MICBOOST enabled, microphone as input, DAC as output,
  WM8731_control_word(WM8731_AAPC, WM8731_AAPC_MICBOOST | WM8731_AAPC_INSEL | WM8731_AAPC_DACSEL);
  //set the digital audio path control: de-emphasis to 48kHz
  WM8731_control_word(WM8731_DAPC, WM8731_DAPC_DEEMP_1 | WM8731_DAPC_DEEMP_0);
  //power up: microphone, ADC, DAC, outputs, oscillator, device. Power down: line input, clock out,
  WM8731_control_word(WM8731_PDC, WM8731_PDC_LINEINPD | WM8731_PDC_CLKOUTPD);
  //set codec to I2S mode, master
  WM8731_control_word(WM8731_DAIF, WM8731_DAIF_FORMAT_1 | WM8731_DAIF_MS);
  //set the sampling rate for ADC and DAC to 8kHz: BOSR=1, SR[3:0]=0b0011 (refer to table 18 in codec datasheet)
  WM8731_control_word(WM8731_SC, WM8731_SC_BOSR | WM8731_SC_SR_1 | WM8731_SC_SR_0);
}
#endif

void WM8731_config_i2s_start(void){
  //activate I2S interface
  WM8731_control_word(WM8731_AC, WM8731_AC_ACTIVE);
}
