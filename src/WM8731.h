#define WM8731_LLI              0x00    //LEFT LINE IN REGISTER
#define WM8731_LLI_LINVOL_0     0x01    //line input volume, bit 0
#define WM8731_LLI_LINVOL_1     0x02    //line input volume, bit 1
#define WM8731_LLI_LINVOL_2     0x04    //line input volume, bit 2
#define WM8731_LLI_LINVOL_3     0x08    //line input volume, bit 3
#define WM8731_LLI_LINVOL_4     0x10    //line input volume, bit 4
#define WM8731_LLI_LINMUTE      0x80    //line input mute
#define WM8731_LLI_LRINBOTH     0x100   //left/right simultaneous load

#define WM8731_RLI              0x01    //RIGHT LINE IN REGISTER
#define WM8731_RLI_LINVOL_0     0x01    //line input volume, bit 0
#define WM8731_RLI_LINVOL_1     0x02    //line input volume, bit 1
#define WM8731_RLI_LINVOL_2     0x04    //line input volume, bit 2
#define WM8731_RLI_LINVOL_3     0x08    //line input volume, bit 3
#define WM8731_RLI_LINVOL_4     0x10    //line input volume, bit 4
#define WM8731_RLI_RINMUTE      0x80    //line input mute
#define WM8731_RLI_RLINBOTH     0x100   //left/right simultaneous load

#define WM8731_LHPO             0x02    //LEFT HEADPHONE OUT REGISTER
#define WM8731_LHPO_LHPVOL_0    0x01    //headphone volume, bit 0
#define WM8731_LHPO_LHPVOL_1    0x02    //headphone volume, bit 1
#define WM8731_LHPO_LHPVOL_2    0x04    //headphone volume, bit 2
#define WM8731_LHPO_LHPVOL_3    0x08    //headphone volume, bit 3
#define WM8731_LHPO_LHPVOL_4    0x10    //headphone volume, bit 4
#define WM8731_LHPO_LHPVOL_5    0x20    //headphone volume, bit 5
#define WM8731_LHPO_LHPVOL_6    0x40    //headphone volume, bit 6
#define WM8731_LHPO_LZCEN       0x80    //zero cross detect enable
#define WM8731_LHPO_LRHPBOTH    0x100   //left/right simultaneous load

#define WM8731_RHPO             0x03    //RIGHT HEADPHONE OUT REGISTER
#define WM8731_RHPO_RHPVOL_0    0x01    //headphone volume, bit 0
#define WM8731_RHPO_RHPVOL_1    0x02    //headphone volume, bit 1
#define WM8731_RHPO_RHPVOL_2    0x04    //headphone volume, bit 2
#define WM8731_RHPO_RHPVOL_3    0x08    //headphone volume, bit 3
#define WM8731_RHPO_RHPVOL_4    0x10    //headphone volume, bit 4
#define WM8731_RHPO_RHPVOL_5    0x20    //headphone volume, bit 5
#define WM8731_RHPO_RHPVOL_6    0x40    //headphone volume, bit 6
#define WM8731_RHPO_RZCEN       0x80    //zero cross detect enable
#define WM8731_RHPO_RLHPBOTH    0x100   //left/right simultaneous load

#define WM8731_AAPC             0x04    //ANALOG AUDIO PATH CONTROL REGISTER
#define WM8731_AAPC_MICBOOST    0x01    //microphone input level boost
#define WM8731_AAPC_MUTEMIC     0x02    //microphone input mute to ADC
#define WM8731_AAPC_INSEL       0x04    //microphone/line input select to ADC
#define WM8731_AAPC_BYPASS      0x08    //bypass switch
#define WM8731_AAPC_DACSEL      0x10    //DAC select
#define WM8731_AAPC_SIDETONE    0x20    //side tone switch
#define WM8731_AAPC_SIDEATT_0   0x40    //side tone attenuation, bit 0
#define WM8731_AAPC_SIDEATT_1   0x80    //side tone attenuation, bit 1

#define WM8731_DAPC             0x05    //DIGITAL AUDIO PATH CONTROL REGISTER
#define WM8731_DAPC_ADCHPD      0x01    //ADC high pass filter enable
#define WM8731_DAPC_DEEMP_0     0x02    //de-emphasis control, bit 0
#define WM8731_DAPC_DEEMP_1     0x04    //de-emphasis control, bit 1
#define WM8731_DAPC_DACMU       0x08    //DAC soft mute control
#define WM8731_DAPC_HPOR        0x10    //store DC offset when high pass filter disabled

#define WM8731_PDC              0x06    //POWER DOWN CONTROL REGISTER
#define WM8731_PDC_LINEINPD     0x01    //line input power down
#define WM8731_PDC_MICPD        0x02    //microphone power down
#define WM8731_PDC_ADCPD        0x04    //ADC power down
#define WM8731_PDC_DACPD        0x08    //DAC input power down
#define WM8731_PDC_OUTPD        0x10    //line/headphone outputs power down
#define WM8731_PDC_OSCPD        0x20    //oscillator power down
#define WM8731_PDC_CLKOUTPD     0x40    //clock out power down
#define WM8731_PDC_POWEROFF     0x80    //power off device

#define WM8731_DAIF             0x07    //DIGITAL AUDIO INTERFACE FORMAT REGISTER
#define WM8731_DAIF_FORMAT_0    0x01    //audio data format select, bit 0
#define WM8731_DAIF_FORMAT_1    0x02    //audio data format select, bit 1
#define WM8731_DAIF_IWL_0       0x04    //input audio data bit length select, bit 0
#define WM8731_DAIF_IWL_1       0x08    //input audio data bit length select, bit 1
#define WM8731_DAIF_LRP         0x10    //DACLRC phase control
#define WM8731_DAIF_LRSWAP      0x20    //DAC left right clock swap
#define WM8731_DAIF_MS          0x40    //master/slave mode control
#define WM8731_DAIF_BCLKIN      0x80    //bit clock invert

#define WM8731_SC               0x08    //SAMPLING CONTROL REGISTER
#define WM8731_SC_USB_NORMAL    0x01    //mode select
#define WM8731_SC_BOSR          0x02    //base over-sampling rate
#define WM8731_SC_SR_0          0x04    //sample rate control, bit 0
#define WM8731_SC_SR_1          0x08    //sample rate control, bit 1
#define WM8731_SC_SR_2          0x10    //sample rate control, bit 2
#define WM8731_SC_SR_3          0x20    //sample rate control, bit 3
#define WM8731_SC_CLKDIV2       0x40    //clock divider select

#define WM8731_AC               0x09    //ACTIVE CONTOL REGISTER
#define WM8731_AC_ACTIVE        0x01    //activate I2S interface

#define WM8731_RR               0x0F    //RESET REGISTER
#define WM8731_RR_RST           0x00    //reset device

#ifndef WM8731_H_
#define WM8731_H_

#define WM8731_fs_8kHz		//choose a 8kHz sampling frequency
//#define WM8731_fs_48kHz	//choose a 48kHz sampling frequency

#include <stdint.h>	//contains integer data types such as the uint16_t

void WM8731_init(void);				//initialize pins and SPI to the WM8731
void WM8731_config_reset(void);			//send a reset to the WM8731
void WM8731_config_micbypass(void);		//configure the WM8731 to bypass the microphone input directly to the headphone output
void WM8731_config_volume(uint16_t volume);	//set the output volume. Max 127, min 48. Values under 48 result in a muted output


#endif /* WM8731_H_ */
