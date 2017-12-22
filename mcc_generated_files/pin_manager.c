/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information : 
        Product Revision  :  MPLAB(c) Code Configurator - 4.26
        Device            :  PIC24FJ256GA704
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


/**
    Section: Includes
*/
#include <xc.h>
#include "pin_manager.h"
#include "../silvia_utility.h"

/**
    void PIN_MANAGER_Initialize(void)
*/
void PIN_MANAGER_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0480;
    LATB = 0x4000;
    LATC = 0x0018;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x000F;
    TRISB = 0x8FDF;
    TRISC = 0x03C7;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    IOCPDA = 0x0000;
    IOCPDB = 0x0000;
    IOCPDC = 0x0000;
    IOCPUA = 0x0000;
    IOCPUB = 0x0000;
    IOCPUC = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSA = 0x000F;
    ANSB = 0xF000;
    ANSC = 0x0000;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPINR0bits.INT1R = 0x0010;   //RC0->EXT_INT:INT1;
    RPINR22bits.SDI2R = 0x0006;   //RB6->SPI2:SDI2;
    RPINR1bits.INT3R = 0x0012;   //RC2->EXT_INT:INT3;
    RPOR6bits.RP12R = 0x0008;   //RB12->SPI1:SCK1OUT;
    RPOR2bits.RP5R = 0x000A;   //RB5->SPI2:SDO2;
    RPINR1bits.INT2R = 0x0002;   //RB2->EXT_INT:INT2;
    RPOR6bits.RP13R = 0x0007;   //RB13->SPI1:SDO1;
    RPINR2bits.INT4R = 0x0004;   //RB4->EXT_INT:INT4;
    RPOR10bits.RP21R = 0x000B;   //RC5->SPI2:SCK2OUT;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    /****************************************************************************
     * Interrupt On Change for group IOCFC - flag
     ***************************************************************************/
	IOCFCbits.IOCFC1 = 0; // Pin : RC1

    /****************************************************************************
     * Interrupt On Change for group IOCNC - negative
     ***************************************************************************/
	IOCNCbits.IOCNC1 = 1; // Pin : RC1

    /****************************************************************************
     * Interrupt On Change for group IOCPC - positive
     ***************************************************************************/
	IOCPCbits.IOCPC1 = 1; // Pin : RC1

    /****************************************************************************
     * Interrupt On Change for group PADCON - config
     ***************************************************************************/
	PADCONbits.IOCON = 1; 

    IEC1bits.IOCIE = 1; // Enable IOCI interrupt 
}

/* Interrupt service routine for the IOCI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _IOCInterrupt ( void )
{
    if(IFS1bits.IOCIF == 1)
    {
        // Clear the flag
        IFS1bits.IOCIF = 0;
        // interrupt on change for group IOCFC
        if(IOCFCbits.IOCFC1 == 1)
        {
            IOCFCbits.IOCFC1 = 0;
            // Add handler code here for Pin - RC1
            steamFlag = 1;            
        }
    }
}
