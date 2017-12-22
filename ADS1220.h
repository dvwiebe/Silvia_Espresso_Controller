/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   ADS1220.H
 * Author: DAVID WIEBE
 * Comments:
 * Revision history:
 * Created on November 6, 2016, 2:11 PM
 * Aug 5, 2017 - Modified for use with Silvia Controller and XC16 compiler 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADS1220_H
#define	ADS1220_H

//////////////////////////////////////////////////////////////////////////////
/***********************Program Constants************************************/

#define ADS1220_RESET       0x06    //Reset ADS1220 registry to default
#define ADS1220_WRITE_REG   0x43    //Write 4 bytes starting @ address 0
#define ADS1220_START       0x08    //Start taking temperature readings
#define ADS1220_READ        0x10    //Read temperature data on command
#define ADS1220_PWRDWN      0x02    //Enter power-down mode
//3 Wire RTD Registry Settings
#define ADS1220_3W_REG_0    0x60    //0110-Input Multiplex, XXX - User Set Gain 
                                    //0-PGA Enabled
#define ADS1220_3W_REG_1    0x04    //XXXXX- User Set SPS, 1- Continuous, 
                                    //0-Int Temp Disabled, 0-Burnout sensor off
#define ADS1220_3W_REG_2_FLTR   0x55//01-Ext Ref inputs, 01-50Hz&60Hz Filter, 
                                    //0-Low side power switch, 101-0.5mA IDAC
#define ADS1220_3W_REG_2_NOFLTR 0x45//01-Ext Ref inputs, 00-Filter Disabled, 
                                    //0-Low side power switch, 101-0.5mA IDAC
#define ADS1220_3W_REG_3    0x70    //011-IDAC1 to AIN2, 100-IDAC2 to AIN3, 
                                    //0-DRDY pin used for data ready, 
                                    //0-Always write zero for chip
//ADS1220 Internal Offset Calibration Registry Settings
#define ADS1220_ICOFFSET_REG_0  0xE0    //1110-Short Multiplex for calibration, 
                                        //XXX- User Set Gain, 0-PGA Enabled  
#define ADS1220_ICOFFSET_REG_1  0X30    //00110 - 90SPS Turbo
                                        //0- Single Sample, 0-Int Temp 
                                        //Disabled, 0-Burnout sensor off
#define ADS1220_ICOFFSET_REG_2  0X45    //01-Ext Ref inputs, 00-Filter Disabled, 
                                        //0-Low side power switch, 101-0.5mA IDAC
#define ADS1220_ICOFFSET_REG_3  0X70    //011-IDAC1 to AIN2, 100-IDAC2 to AIN3, 
                                        //0-DRDY pin used for data ready, 
                                        //0-Always write zero for chip
//Available Gain Options
#define ADS1220_GAIN_1      0x0
#define ADS1220_GAIN_2      0x02
#define ADS1220_GAIN_4      0x04
#define ADS1220_GAIN_8      0x06
#define ADS1220_GAIN_16     0x08
#define ADS1220_GAIN_32     0xA
#define ADS1220_GAIN_64     0xC
#define ADS1220_GAIN_128    0xE

//Available Samples Per Second Options 
#define ADS1220_SPS_20      0x00
#define ADS1220_SPS_40      0x10
#define ADS1220_SPS_90      0x30
#define ADS1220_SPS_180     0x50
#define ADS1220_SPS_350     0x70
#define ADS1220_SPS_660     0x90
#define ADS1220_SPS_1200    0xB0
#define ADS1220_SPS_2000    0xD0

//Value used for Errors
#define ADS1220_ERROR       0x7F

//Constants used to calculate resistance and temperature from Bytes read
#define ADS1220_rZero       100             //PT100 resistance at 0C
#define ADS1220_FSR         (((uint32_t)1<<23)-1) //Full scale for signed 24 bit
#define ADS1220_VREF        1.65            //1.65 Based on Board Design and selected Vref
#define ADS1220_A_PARAM     0.0039083        
#define ADS1220_B_PARAM     (-0.0000005775)

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////
/*******************ADS1220 Chip Command Functions****************************/

void ADS1220Command(uint8_t command);
//functions to set gainRegisteryValue and 
//SPS and Gain RegistryValue based on user inputs.  Need to call 
//initializeThreeWireRTD() after to update chip registry. NOTE: spsValue is 
//actual SPS value divided by 10 (ie for 20 SPS, spsValue passed should be 2)
void setGain(uint8_t gain);       
void setSPS (uint8_t spsValue);
//performs internal calibration of ADS1220; called automatically by 
//initializeThreeWireRTD())
void performInternalOffset( void ); 
//calls performInternalOffset and Writes settings to register for 3wire RTD
//make sure to call setGain and setSPS before initializing RTD
int initializeThreeWireRTD( void ); 
void readRTDBytes(uint8_t rtd); //reads temperatures from ADS1220
void readRTDResistance(uint8_t rtd);
void readRTDTemperatureC(uint8_t rtd);
void readRTDTemperatureF(uint8_t rtd);

///////////////////////////////////////////////////////////////////////////////
/***************************Global Variables**********************************/

//Program written for 16-bit PIC (PIC24FJ256GA704)

extern uint8_t rtdBytes [2][3]; //includes icOffset value (if used)
extern double rtdTemperatureC;
extern double rtdTemperatureF;
extern double rtdResistance;
extern uint8_t gainRegisterValue;
extern uint8_t spsRegisterValue;
extern uint32_t offset32;
extern uint8_t garbage; //use to record values returned use when transmitting SPI info



// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* ADS1220_H */

