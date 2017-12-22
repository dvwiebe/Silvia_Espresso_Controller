/*
 * File:   ADS1220.c
 * Author: David Wiebe
 *
 * Created on November 6, 2016, 2:11 PM
 * Modified on Aug 5,2017 for use with Silvia Controller and XC16 compiler
 */


#include <xc.h>
#include "ADS1220.h"
#include "silvia_utility.h"
#include "mcc_generated_files/mcc.h"

///////////////////////////////////////////////////////////////////////////////
/***********************ADS1220 Global Variables******************************/

double rtdTemperatureC = 0;
double rtdTemperatureF = 0;
double rtdResistance = 0;
uint8_t rtdBytes [2][3] = {{0}}; //includes icOffset value (if used)
uint8_t gainRegisterValue;
uint8_t spsRegisterValue;
uint8_t gainValue;
uint8_t spsValue;
uint32_t offset32 = 0;
uint8_t garbage; //use to record values returned use when transmitting SPI info

//issue command
void ADS1220Command(uint8_t command )
{
    ADSCS_SetLow();
    delayms(1);
    
    garbage = SPI2_Exchange8bit(command);    
    
    delayms(1);
    ADSCS_SetHigh();
}

void setGain(uint8_t gain){
    //sets gain Register value based on user input; 
    //this sets value but does not write to ADS1220 register
    
    switch(gain){
        case 0x01:
            gainRegisterValue = ADS1220_GAIN_1;
            gainValue = 1;
            break;
        case 0x02:
            gainRegisterValue = ADS1220_GAIN_2;
            gainValue = 2;
            break;
        case 0x04:
            gainRegisterValue = ADS1220_GAIN_4;
            gainValue = 4;
            break;
        case 0x08:
            gainRegisterValue = ADS1220_GAIN_8;
            gainValue = 8;
            break;
        case 0x10:
            gainRegisterValue = ADS1220_GAIN_16;
            gainValue = 16;
            break;
        case 0x20:
            gainRegisterValue = ADS1220_GAIN_32;
            gainValue = 32;
            break;
        case 0x40:
            gainRegisterValue = ADS1220_GAIN_64;
            gainValue = 64;
            break;
        case 0x80:
            gainRegisterValue = ADS1220_GAIN_128;
            gainValue = 128;
        default:
            gainRegisterValue = ADS1220_ERROR;
            //don't allow the program to proceed with an incorrect Gain value
            while(gainRegisterValue == ADS1220_ERROR);
            break;
    }
}

void setSPS(uint8_t spsValue) {
    //sets sps Register value based on user input sps value; this sets value 
    //but does not write to ADS1220 register
    switch(spsValue){
        case 0x02:
            spsRegisterValue = ADS1220_SPS_20;
            break;
        case 0x04:           
            spsRegisterValue = ADS1220_SPS_40;
            break;
        case 0x09:
            spsRegisterValue = ADS1220_SPS_90;
            break;
        case 0x12:
            spsRegisterValue = ADS1220_SPS_180;
            break;
        case 0x23:
            spsRegisterValue = ADS1220_SPS_350;
            break;
        case 0x42:
            spsRegisterValue = ADS1220_SPS_660;
            break;
        case 0x78: 
            spsRegisterValue = ADS1220_SPS_1200;
            break;
        case 0xC8:
            spsRegisterValue = ADS1220_SPS_2000;
        default:
            spsRegisterValue = ADS1220_ERROR;
            //don't allow the program to proceed with an incorrect sps value
            while(spsRegisterValue == ADS1220_ERROR);
            break;
    }
}

//performs internal calibration of ADS1220 - code needs re-write
//void performInternalOffset( void ){
//    //performInternalOffset should only be called from within
//    //initializeThreeWireRTD to ensure interrupts disabled for process
//    //and to ensure proper RTD settings are put back in place for readings   
//    
//    //create local variables to read and sum data        
//    uint32_t tempBit32;
//    uint8_t numSamples = 8;
//    
//    offset32 = 0;       
//    
//    //Tell the chip to write to register and send 4 bytes
//    garbage = SPI2_Exchange8bit(ADS1220_WRITE_REG);
//    garbage = SPI2_Exchange8bit(gainRegisterValue | ADS1220_ICOFFSET_REG_0);
//    garbage = SPI2_Exchange8bit(ADS1220_ICOFFSET_REG_1); //incorporate user set sps        
//    garbage = SPI2_Exchange8bit(ADS1220_ICOFFSET_REG_2);
//    garbage = SPI2_Exchange8bit(ADS1220_ICOFFSET_REG_3);
//    
//    //use for loop to collect average readings to use for rtdBytes[4]
//    for (uint8_t i = 0; i < numSamples; i++){
//        garbage = SPI2_Exchange8bit(ADS1220_START); //tell the chip to take a reading
//        __delay_us(1);                 
//    
//        while(!LCDA0_GetValue() == 0); //wait for reading to be available
//        tempBit32 = SPI2_Exchange8bit(0x0); //read byte0
//        tempBit32 = (tempBit32 << 8) | SPI2_Exchange8bit(0x0); //read byte1
//        tempBit32 = (tempBit32 << 8) | SPI2_Exchange8bit(0x0); //read byte2      
//        
//        //internal Offset could be negative; data sent as Twos Compliment so
//        //bit shift answer left and then right to carry forward negative sign
//        //if applicable
//        tempBit32 = tempBit32 << 8;
//        tempBit32 = tempBit32 >> 8;
//        
//        offset32 += tempBit32;        
//                
//    }  
//       
//    //average at end of for loop to minimize process effort
//    //offset number small enough that for loop won't exceed 4 bytes
//    offset32 /= numSamples;
//    
//    //transfer to the 8 bit array; only for users if they request.  Only 24bits
//    //stored; offset32 used for internal PIC calculations
//    rtdBytes[4][0] = (offset32 >> 16) & 0xff;
//    rtdBytes[4][1] = (offset32 >> 8) & 0xff;
//    rtdBytes[4][2] = offset32 & 0xff;        
//    
//}

//write settings to register for 3wire RTD

int initializeThreeWireRTD( void ){             
    
    ADSCS_SetLow(); //slave select pin low    
    delayms(1);
    
    //performInternalOffset();        
       
    //Interrupts_Disabled();//turn off interrupts during initialization
    //tell the chip to write to register and send 4 bytes for register settings
    garbage = SPI2_Exchange8bit(ADS1220_WRITE_REG);
    garbage = SPI2_Exchange8bit(gainRegisterValue | ADS1220_3W_REG_0); //incorporate user set gain
    garbage = SPI2_Exchange8bit(spsRegisterValue | ADS1220_3W_REG_1); //incorporate user set sps
    if(spsRegisterValue == ADS1220_SPS_20)
        garbage = SPI2_Exchange8bit(ADS1220_3W_REG_2_FLTR);
    else
        garbage = SPI2_Exchange8bit(ADS1220_3W_REG_2_NOFLTR);    
    garbage = SPI2_Exchange8bit(ADS1220_3W_REG_3);    
    
    //for(int i = 0; i < 50; i++) //delay function won't work when interrupts off
   
    garbage = SPI2_Exchange8bit(ADS1220_START); //start continuous conversion    
    //Interrupts_Enabled(); //turn interrupts back on
    
    delayms(1);
    ADSCS_SetHigh();

    return 1; //return 1 to confirm initialization complete
}
//reads temperatures from ADS1220
void readRTDBytes(uint8_t rtd){
            
    ADSCS_SetLow();
    delayms(1);
    //start new reading IF in single shot mode
    //garbage = SPI2_Exchange8bit(ADS1220_START);    
    
    Interrupts_Disabled();//turn off interrupts during reading
    
    //save temperature readings from ADS1220 chip to array
    rtdBytes[rtd][0] = SPI2_Exchange8bit(0x0); //read byte0
    rtdBytes[rtd][1] = SPI2_Exchange8bit(0x0); //read byte1
    rtdBytes[rtd][2] = SPI2_Exchange8bit(0x0); //read byte2
        
    //note that these numbers dont have icoffset subtracted from them
    Interrupts_Enabled();//turn off interrupts during initialization;
    delayms(1);
    ADSCS_SetHigh();
    
}

void readRTDResistance(uint8_t rtd){
        
    uint32_t tempBit32;
    
    if(rtd < 1) //don't call readRTDBytes function if looking for Offset value
        readRTDBytes(rtd);    
    
    tempBit32 = rtdBytes[rtd][0];
    tempBit32 = (tempBit32 << 8) | rtdBytes[rtd][1];
    tempBit32 = (tempBit32 << 8) | rtdBytes[rtd][2];
    
    //ADS1220 Output format is Binary Two's Compliment; RTD readings will always
    //be positive as voltage is always higher upstream of RTD; however icOffset
    //may be negative.  Ratio the input code read to 8,388,607 (7F FFFF in HEX)
    tempBit32 = tempBit32 << 8;
    tempBit32 = tempBit32 >> 8;
    
    //subtract offset (offset default is zero unless calculated otherwise)
    tempBit32 = tempBit32 - offset32;            
    
    rtdResistance = ((double)tempBit32 * 2 * (1000.0 * ADS1220_VREF)) / (ADS1220_FSR * (double)gainValue);          
    
}

void readRTDTemperatureC(uint8_t rtd){ 
    
    readRTDResistance(rtd);
    //Using Callendar-Van Dusen formula
    //Formula also works for temperature <= 0C but error increases exponentially as temperature gets more negative.  
    //(Following Errors are from formula only and do not include other errors from sensor, etc) 
    //At -20C Error ~= 0.008C; At -50C Error ~= 0.01C;  At -75C Error ~= 0.08C; At -100C Error ~= 0.2C;   
    
    rtdTemperatureC = (-1 * ADS1220_rZero * ADS1220_A_PARAM + sqrt(
          pow(( ADS1220_rZero * ADS1220_A_PARAM),2) - (4.0 * ADS1220_rZero * 
          ADS1220_B_PARAM * (ADS1220_rZero - rtdResistance)))) / 
          (2.0 * ADS1220_rZero * ADS1220_B_PARAM);  
    
   
}

void readRTDTemperatureF(uint8_t rtd){    
    
    readRTDTemperatureC(rtd);
    rtdTemperatureF = rtdTemperatureC * (9.0 / 5.0) + 32;      
    
}
