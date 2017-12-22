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
 * File:   silvia_utility.h
 * Author: David Wiebe
 * Comments: For the Silvia PIC Controller 
 * Revision history: Rev 0 July 31, 2017
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SILVIA_UTILITY_H
#define	SILVIA_UTILITY_H

// TODO Insert appropriate #include <>
#include <xc.h> // include processor files - each processor file is guarded.  
#include "stdio.h"
#include "mcc_generated_files/mcc.h"
#include "ADS1220.h"
#include "st7565.h"
#include "font_tahoma.h"
#include "graphics.h"


#define Interrupts_Enabled()    INTCON2bits.GIE = 1;
#define Interrupts_Disabled()   INTCON2bits.GIE = 0;
#define EEPROM_ADDRESS          0x50
#define EEPROM_TIMEOUT          2000
 
/**************Union Definitions***************/

extern union Four_Bytes {
    double d;
    long lInt;
    uint8_t uint8[4];
}brewSetPoint, steamSetPoint, rtdOffset, timeOut;

extern union Two_Bytes {
    uint16_t uint16;
    uint8_t uint8[2];
}pidKp, pidKi, pidKd, brewTime, preInfDelay, preInfPump;

/**
 * @Summary Delay function
 * @param delay - delay in milliseconds
 */
void delayms(uint16_t delay);

/**
 * @Summary - Function called to write data to EEPROM
 * 
 * @param dPointer - pointer to data that will be written to EEPROM
 * @param dAddress - EEPROM data address where data will start being written
 * @param bytesToWrite - Number of bytes to be written; not to exceed 8
 */
void EEPROM_Write(uint8_t *dPointer, uint8_t dAddress, uint8_t bytesToWrite);

/**
 * @Summary - Function called to read data from EEPROM (random access read)
 * 
 * @param dPointer - pointer to where read data will be stored 
 * @param dAddress - EEPROM data address where data will start to be read
 * @param bytesToRead - Number of bytes to be read and saved
 */
void EEPROM_Read(uint8_t *dPointer, uint8_t dAddress, uint8_t bytesToRead);

/**
 * @Summary - Functions checks EEPROM at startup for user saved settings and 
 * recalls them as applicable
 */
void Read_User_Settings();

/**
 * @Summary - Function places PIC and peripherals in a sleep mode when the 
 * program reaches its timeOut period or an error occurs
 */
void Sleep_Mode();

/**
 * @Summary - Function draws borders / template for LCD operating screen
 */
void LCD_Draw_Borders();

/*
 *Define Variables
 */

//PID parameters
extern double pidSetPoint;
extern double pidOutput;
    
//Brew and Steam Setpoints in degC
extern double deltaTemperatureC;
    
//Brew Toggle and Time
extern uint8_t brewTimeToggle;
    
//Pre-Infusion Settings
extern uint8_t preInfToggle;  

//Program runTime Parameter
extern uint32_t runTime;

//Interrupt Flags
extern volatile uint8_t steamFlag;
extern volatile uint8_t rtdFlag;
extern volatile uint8_t brewFlag;
extern volatile uint8_t brewFirstPassFlag;
extern volatile uint8_t btnFlag;
extern volatile uint8_t encFlag;
extern volatile uint8_t waterFlag;
extern volatile uint8_t btnActiveFlag;

extern int menuIndex;
extern char *settingNames[];

//LCD Startup Logo
extern const unsigned char espresso_logo[];


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* SILVIA_H */

