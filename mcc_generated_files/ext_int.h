/**
  EXT_INT Generated Driver API Header File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    ext_int.h

  @Summary:
    This is the generated header file for the EXT_INT driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides APIs for driver for EXT_INT. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC24FJ256GA704
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _EXT_INT_H
#define _EXT_INT_H

/**
    Section: Includes
*/
#include <xc.h>

// Provide C++ Compatibility
#ifdef __cplusplus  

extern "C" {

#endif

/**
    Section: Macros
*/
/**
  @Summary
    Clears the interrupt flag for INT1

  @Description
    This routine clears the interrupt flag for the external interrupt, INT1.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
    {
        // User Area Begin->code: INT1 - External Interrupt 1

        // User Area End->code: INT1 - External Interrupt 1
        EX_INT1_InterruptFlagClear();
    }
    </code>

*/
#define EX_INT1_InterruptFlagClear()       (IFS1bits.INT1IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT1

  @Description
    This routine clears the interrupt enable for the external interrupt, INT1.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT1Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    EX_INT1_InterruptDisable();
    // change the edge
    EX_INT1_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_InterruptDisable()     (IEC1bits.INT1IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT1

  @Description
    This routine clears the interrupt enable for the external interrupt, INT1.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT1Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT1_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_InterruptEnable()       (IEC1bits.INT1IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    EX_INT1_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_NegativeEdgeSet()          (INTCON2bits.INT1EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT1_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_PositiveEdgeSet()          (INTCON2bits.INT1EP = 0)
/**
  @Summary
    Clears the interrupt flag for INT2

  @Description
    This routine clears the interrupt flag for the external interrupt, INT2.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT2Interrupt(void)
    {
        // User Area Begin->code: INT2 - External Interrupt 2

        // User Area End->code: INT2 - External Interrupt 2
        EX_INT2_InterruptFlagClear();
    }
    </code>

*/
#define EX_INT2_InterruptFlagClear()       (IFS1bits.INT2IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT2

  @Description
    This routine clears the interrupt enable for the external interrupt, INT2.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT2Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    EX_INT2_InterruptDisable();
    // change the edge
    EX_INT2_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    EX_INT2_InterruptFlagClear();
    EX_INT2_InterruptEnable();
    </code>

*/
#define EX_INT2_InterruptDisable()     (IEC1bits.INT2IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT2

  @Description
    This routine clears the interrupt enable for the external interrupt, INT2.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT2Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT2_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT2_InterruptFlagClear();
    EX_INT2_InterruptEnable();
    </code>

*/
#define EX_INT2_InterruptEnable()       (IEC1bits.INT2IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    EX_INT2_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT2_InterruptFlagClear();
    EX_INT2_InterruptEnable();
    </code>

*/
#define EX_INT2_NegativeEdgeSet()          (INTCON2bits.INT2EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT2_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT2_InterruptFlagClear();
    EX_INT2_InterruptEnable();
    </code>

*/
#define EX_INT2_PositiveEdgeSet()          (INTCON2bits.INT2EP = 0)
/**
  @Summary
    Clears the interrupt flag for INT0

  @Description
    This routine clears the interrupt flag for the external interrupt, INT0.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
    {
        // User Area Begin->code: INT0 - External Interrupt 0

        // User Area End->code: INT0 - External Interrupt 0
        EX_INT0_InterruptFlagClear();
    }
    </code>

*/
#define EX_INT0_InterruptFlagClear()       (IFS0bits.INT0IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT0

  @Description
    This routine clears the interrupt enable for the external interrupt, INT0.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT0Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    EX_INT0_InterruptDisable();
    // change the edge
    EX_INT0_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    EX_INT0_InterruptFlagClear();
    EX_INT0_InterruptEnable();
    </code>

*/
#define EX_INT0_InterruptDisable()     (IEC0bits.INT0IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT0

  @Description
    This routine clears the interrupt enable for the external interrupt, INT0.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT0Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT0_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT0_InterruptFlagClear();
    EX_INT0_InterruptEnable();
    </code>

*/
#define EX_INT0_InterruptEnable()       (IEC0bits.INT0IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    EX_INT0_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT0_InterruptFlagClear();
    EX_INT0_InterruptEnable();
    </code>

*/
#define EX_INT0_NegativeEdgeSet()          (INTCON2bits.INT0EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT0_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT0_InterruptFlagClear();
    EX_INT0_InterruptEnable();
    </code>

*/
#define EX_INT0_PositiveEdgeSet()          (INTCON2bits.INT0EP = 0)
/**
  @Summary
    Clears the interrupt flag for INT3

  @Description
    This routine clears the interrupt flag for the external interrupt, INT3.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT3Interrupt(void)
    {
        // User Area Begin->code: INT3 - External Interrupt 3

        // User Area End->code: INT3 - External Interrupt 3
        EX_INT3_InterruptFlagClear();
    }
    </code>

*/
#define EX_INT3_InterruptFlagClear()       (IFS3bits.INT3IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT3

  @Description
    This routine clears the interrupt enable for the external interrupt, INT3.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT3Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    EX_INT3_InterruptDisable();
    // change the edge
    EX_INT3_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    EX_INT3_InterruptFlagClear();
    EX_INT3_InterruptEnable();
    </code>

*/
#define EX_INT3_InterruptDisable()     (IEC3bits.INT3IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT3

  @Description
    This routine clears the interrupt enable for the external interrupt, INT3.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT3Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT3_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT3_InterruptFlagClear();
    EX_INT3_InterruptEnable();
    </code>

*/
#define EX_INT3_InterruptEnable()       (IEC3bits.INT3IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    EX_INT3_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT3_InterruptFlagClear();
    EX_INT3_InterruptEnable();
    </code>

*/
#define EX_INT3_NegativeEdgeSet()          (INTCON2bits.INT3EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT3_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT3_InterruptFlagClear();
    EX_INT3_InterruptEnable();
    </code>

*/
#define EX_INT3_PositiveEdgeSet()          (INTCON2bits.INT3EP = 0)
/**
  @Summary
    Clears the interrupt flag for INT4

  @Description
    This routine clears the interrupt flag for the external interrupt, INT4.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT4Interrupt(void)
    {
        // User Area Begin->code: INT4 - External Interrupt 4

        // User Area End->code: INT4 - External Interrupt 4
        EX_INT4_InterruptFlagClear();
    }
    </code>

*/
#define EX_INT4_InterruptFlagClear()       (IFS3bits.INT4IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT4

  @Description
    This routine clears the interrupt enable for the external interrupt, INT4.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT4Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    EX_INT4_InterruptDisable();
    // change the edge
    EX_INT4_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    EX_INT4_InterruptFlagClear();
    EX_INT4_InterruptEnable();
    </code>

*/
#define EX_INT4_InterruptDisable()     (IEC3bits.INT4IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT4

  @Description
    This routine clears the interrupt enable for the external interrupt, INT4.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT4Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT4_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT4_InterruptFlagClear();
    EX_INT4_InterruptEnable();
    </code>

*/
#define EX_INT4_InterruptEnable()       (IEC3bits.INT4IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    EX_INT4_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT4_InterruptFlagClear();
    EX_INT4_InterruptEnable();
    </code>

*/
#define EX_INT4_NegativeEdgeSet()          (INTCON2bits.INT4EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT4_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT4_InterruptFlagClear();
    EX_INT4_InterruptEnable();
    </code>

*/
#define EX_INT4_PositiveEdgeSet()          (INTCON2bits.INT4EP = 0)

/**
    Section: External Interrupt Initializers
 */
/**
  @Summary
    Initializes the external interrupt pins

  @Description
    This routine initializes the EXT_INT driver to detect the configured edge, clear
    the interrupt flag and enable the interrupt.

    The following external interrupts will be initialized:
    INT1 - EX_INT1
    INT2 - EX_INT2
    INT0 - EX_INT0
    INT3 - EX_INT3
    INT4 - EX_INT4
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Initialize the external interrupt pins
    <code>
    // 
    EXT_INT_Initialize();
    </code>

*/
void EXT_INT_Initialize(void);

// Provide C++ Compatibility
#ifdef __cplusplus  

}

#endif
#endif
