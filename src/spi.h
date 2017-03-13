/*
*
* @brief Provides an abstraction layer to the SPI communication.
*
* @par
*
*/


#include <stdint.h>

#ifndef _SPI_H
#define _SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#define _BV(A)	(1 << A)	//Bit vector definition

//Definitions for the Control Words
#define WM8731_LLI		0x00	//LEFT LINE IN REGISTER
#define WM8731_LLI_LINVOL_0	_BV(0)	//line input volume, bit 0
#define WM8731_LLI_LINVOL_1	_BV(1)	//line input volume, bit 1
#define WM8731_LLI_LINVOL_2	_BV(2)	//line input volume, bit 2
#define WM8731_LLI_LINVOL_3	_BV(3)	//line input volume, bit 3
#define WM8731_LLI_LINVOL_4	_BV(4)	//line input volume, bit 4
#define WM8731_LLI_LINMUTE	_BV(7)	//line input mute
#define WM8731_LLI_LRINBOTH	_BV(8)	//left/right simultaneous load

#define WM8731_RLI		0x01	//RIGHT LINE IN REGISTER
#define WM8731_RLI_LINVOL_0	_BV(0)	//line input volume, bit 0
#define WM8731_RLI_LINVOL_1	_BV(1)	//line input volume, bit 1
#define WM8731_RLI_LINVOL_2	_BV(2)	//line input volume, bit 2
#define WM8731_RLI_LINVOL_3	_BV(3)	//line input volume, bit 3
#define WM8731_RLI_LINVOL_4	_BV(4)	//line input volume, bit 4
#define WM8731_RLI_RINMUTE	_BV(7)	//line input mute
#define WM8731_RLI_RLINBOTH	_BV(8)	//left/right simultaneous load

#define WM8731_LHPO		0x02	//LEFT HEADPHONE OUT REGISTER
#define WM8731_LHPO_LHPVOL_0	_BV(0)	//headphone volume, bit 0
#define WM8731_LHPO_LHPVOL_1	_BV(1)	//headphone volume, bit 1
#define WM8731_LHPO_LHPVOL_2	_BV(2)	//headphone volume, bit 2
#define WM8731_LHPO_LHPVOL_3	_BV(3)	//headphone volume, bit 3
#define WM8731_LHPO_LHPVOL_4	_BV(4)	//headphone volume, bit 4
#define WM8731_LHPO_LHPVOL_5	_BV(5)	//headphone volume, bit 5
#define WM8731_LHPO_LHPVOL_6	_BV(6)	//headphone volume, bit 6
#define WM8731_LHPO_LZCEN	_BV(7)	//zero cross detect enable
#define WM8731_LHPO_LRHPBOTH	_BV(8)	//left/right simultaneous load

#define WM8731_RHPO		0x03	//RIGHT HEADPHONE OUT REGISTER
#define WM8731_RHPO_RHPVOL_0	_BV(0)	//headphone volume, bit 0
#define WM8731_RHPO_RHPVOL_1	_BV(1)	//headphone volume, bit 1
#define WM8731_RHPO_RHPVOL_2	_BV(2)	//headphone volume, bit 2
#define WM8731_RHPO_RHPVOL_3	_BV(3)	//headphone volume, bit 3
#define WM8731_RHPO_RHPVOL_4	_BV(4)	//headphone volume, bit 4
#define WM8731_RHPO_RHPVOL_5	_BV(5)	//headphone volume, bit 5
#define WM8731_RHPO_RHPVOL_6	_BV(6)	//headphone volume, bit 6
#define WM8731_RHPO_RZCEN	_BV(7)	//zero cross detect enable
#define WM8731_RHPO_RLHPBOTH	_BV(8)	//left/right simultaneous load

#define WM8731_AAPC		0x04	//ANALOG AUDIO PATH CONTROL REGISTER
#define WM8731_AAPC_MICBOOST	_BV(0)	//microphone input level boost
#define WM8731_AAPC_MUTEMIC	_BV(1)	//microphone input mute to ADC
#define WM8731_AAPC_INSEL	_BV(2)	//microphone/line input select to ADC
#define WM8731_AAPC_BYPASS	_BV(3)	//bypass switch
#define WM8731_AAPC_DACSEL	_BV(4)	//DAC select
#define WM8731_AAPC_SIDETONE	_BV(5)	//side tone switch
#define WM8731_AAPC_SIDEATT_0	_BV(6)	//side tone attenuation, bit 0
#define WM8731_AAPC_SIDEATT_1	_BV(7)	//side tone attenuation, bit 1

#define WM8731_DAPC		0x05	//DIGITAL AUDIO PATH CONTROL REGISTER
#define WM8731_DAPC_ADCHPD	_BV(0)	//ADC high pass filter enable
#define WM8731_DAPC_DEEMP_0	_BV(1)	//de-emphasis control, bit 0
#define WM8731_DAPC_DEEMP_1	_BV(2)	//de-emphasis control, bit 1
#define WM8731_DAPC_DACMU	_BV(3)	//DAC soft mute control
#define WM8731_DAPC_HPOR	_BV(4)	//store DC offset when high pass filter disabled

#define WM8731_PDC		0x06	//POWER DOWN CONTROL REGISTER
#define WM8731_PDC_LINEINPD	_BV(0)	//line input power down
#define WM8731_PDC_MICPD	_BV(1)	//microphone power down
#define WM8731_PDC_ADCPD	_BV(2)	//ADC power down
#define WM8731_PDC_DACPD	_BV(3)	//DAC input power down
#define WM8731_PDC_OUTPD	_BV(4)	//line/headphone outputs power down
#define WM8731_PDC_OSCPD	_BV(5)	//oscillator power down
#define WM8731_PDC_CLKOUTPD	_BV(6)	//clock out power down
#define WM8731_PDC_POWEROFF	_BV(7)	//power off device

#define WM8731_DAIF		0x07	//DIGITAL AUDIO INTERFACE FORMAT REGISTER
#define WM8731_DAIF_FORMAT_0	_BV(0)	//audio data format select, bit 0
#define WM8731_DAIF_FORMAT_1	_BV(1)	//audio data format select, bit 1
#define WM8731_DAIF_IWL_0	_BV(2)	//input audio data bit length select, bit 0
#define WM8731_DAIF_IWL_1	_BV(3)	//input audio data bit length select, bit 1
#define WM8731_DAIF_LRP		_BV(4)	//DACLRC phase control
#define WM8731_DAIF_LRSWAP	_BV(5)	//DAC left right clock swap
#define WM8731_DAIF_MS		_BV(6)	//master/slave mode control
#define WM8731_DAIF_BCLKIN	_BV(7)	//bit clock invert

#define WM8731_SC		0x08	//SAMPLING CONTROL REGISTER
#define WM8731_SC_USB_NORMAL	_BV(0)	//mode select
#define WM8731_SC_BOSR		_BV(1)	//base over-sampling rate
#define WM8731_SC_SR_0		_BV(2)	//sample rate control, bit 0
#define WM8731_SC_SR_1		_BV(3)	//sample rate control, bit 1
#define WM8731_SC_SR_2		_BV(4)	//sample rate control, bit 2
#define WM8731_SC_SR_3		_BV(5)	//sample rate control, bit 3
#define WM8731_SC_CLKDIV2	_BV(6)	//clock divider select

#define WM8731_AC		0x09	//ACTIVE CONTOL REGISTER
#define WM8731_AC_ACTIVE	_BV(0)	//activate I2S interface

#define WM8731_RR		0x0F	//RESET REGISTER
#define WM8731_RR_RST		0x00	//reset device

void spi_init();			// Initialise the SPI registers
void spi_out(uint16_t);			// Transmit a 16-bit SPI frame
void WM8731_CW(uint16_t,uint16_t);	// Transmit a control word
void WM8731_config_reset(void);		// Transmit the reset control word
void WM8731_forward_mic(void);		// Forward the mic to the output

#ifdef __cplusplus
}
#endif

#endif /* _SPI_H */
