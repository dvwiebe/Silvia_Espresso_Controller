/**
  EXT_INT Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    ext_int.c

  @Summary
    This is the generated driver implementation file for the EXT_INT 
    driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for driver APIs for EXT_INT. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC24FJ256GA704
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60
*/

/**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
#include "mcc.h"
#include "../silvia_utility.h"

//***User Area Begin->code: Add External Interrupt handler specific headers 

//***User Area End->code: Add External Interrupt handler specific headers

/**
   Section: External Interrupt Handlers
 */
/**
  Interrupt Handler for EX_INT1 - INT1
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
{
    //***User Area Begin->code: INT1 - External Interrupt 1***
    
    /***************Encoder Interrupt Code***********/
    
    //if ENCB pin is low, rotation is Clockwise, else it's CCW
    if(!ENCB_GetValue()) encFlag = 1;
    else encFlag = 2;
    
    //toggle interrupt edge detect to opposite mode - Toggle if encoder not
    //responsive enough and change if statement above to ENB == ENCA pin is CW
    //INTCON2bits.INT1EP ^= 1;
    
    //***User Area End->code: INT1 - External Interrupt 1***
    EX_INT1_InterruptFlagClear();
}
/**
  Interrupt Handler for EX_INT2 - INT2
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT2Interrupt(void)
{
    //***User Area Begin->code: INT2 - External Interrupt 2***
    /***************Encoder Button Interrupt Code***********/
    btnFlag = 1;
    
    //***User Area End->code: INT2 - External Interrupt 2***
    EX_INT2_InterruptFlagClear();
}
/**
  Interrupt Handler for EX_INT0 - INT0
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
{
    //***User Area Begin->code: INT0 - External Interrupt 0***
    /***************RTD Interrupt Code***********/
    rtdFlag = 1;
    //***User Area End->code: INT0 - External Interrupt 0***
    EX_INT0_InterruptFlagClear();
}
/**
  Interrupt Handler for EX_INT3 - INT3
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT3Interrupt(void)
{
    //***User Area Begin->code: INT3 - External Interrupt 3***
    /***************Brew 120V Interrupt Code***********/
    //if waterFlag not active do the following
    if(!waterFlag)
    {        
        //if pin state high, Brew switch has been switched off.
        if(_RC2)
        {
            brewFlag = 0;
            //close 3-way valve and turn off pump
            VLV_RLY_SetLow();
            PMP_RLY_SetLow();
        }
        else
        {
            brewFlag = 1;
            brewFirstPassFlag = 1;
        }           
        
        //Toggle Interrupt to detect opposite edge
        INTCON2bits.INT3EP ^= 1;        
    }

    //***User Area End->code: INT3 - External Interrupt 3***
    EX_INT3_InterruptFlagClear();
}
/**
  Interrupt Handler for EX_INT4 - INT4
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT4Interrupt(void)
{
    //***User Area Begin->code: INT4 - External Interrupt 4***
    /*************Hot Water 120V Interrupt Code**************/    
    //if brewFlag not active do the following
    if(!brewFlag)
    {
        //if pin state high, water switch has been switched off 
        if(_RB4)
        {
            waterFlag = 0;
            //turn off pump
            PMP_RLY_SetLow();
        }
        else
        {
            waterFlag = 1;
            //turn on pump
            PMP_RLY_SetHigh();
        }
        
        //Toggle Interrupt to detect opposite edge
        INTCON2bits.INT4EP ^= 1;
    }
        
    //***User Area End->code: INT4 - External Interrupt 4***
    EX_INT4_InterruptFlagClear();
}
/**
    Section: External Interrupt Initializers
 */
/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT1
    INT2
    INT0
    INT3
    INT4
*/
void EXT_INT_Initialize(void)
{
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT1_InterruptFlagClear();   
    EX_INT1_NegativeEdgeSet();
    EX_INT1_InterruptEnable();
    /*******
     * INT2
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT2_InterruptFlagClear();   
    EX_INT2_NegativeEdgeSet();
    EX_INT2_InterruptEnable();
    /*******
     * INT0
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT0_InterruptFlagClear();   
    EX_INT0_NegativeEdgeSet();
    EX_INT0_InterruptEnable();
    /*******
     * INT3
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT3_InterruptFlagClear();   
    EX_INT3_NegativeEdgeSet();
    EX_INT3_InterruptEnable();
    /*******
     * INT4
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT4_InterruptFlagClear();   
    EX_INT4_NegativeEdgeSet();
    EX_INT4_InterruptEnable();
}
