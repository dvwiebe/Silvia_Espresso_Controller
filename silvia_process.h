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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SILVIA_PROCESS_H
#define	SILVIA_PROCESS_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "silvia_utility.h"
#include "pid.h"
#include "ADS1220.h"



#define TEMPERATURE_VARIANCE    (0.5)   //Considered acceptable tempterature
                                        //difference from user setpoint
#define AGGRESSIVE_LIMIT        10      //Temperature difference at which   
                                        //aggressive PID tuning used
#define PID_PERIOD              1000    //PID time period in milliseconds

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star

/**
 * @summary - Function calls ADS functions to read RTD and then updates the 
 * LCD with the updated temperature and updates the "Ready" field
 */
void Update_Temperature();

/**
 * @summary - Function changes between Brew and Steam Set Points based on 
 * steam switch position; steamFlag set and this function is called from Main
 */
void Change_Set_Point();

/**
 * @summary - Function sets aggressive / normal tuning based on set and actual
 * temperatures and calls PID compute function
 * 
 * @param -  pointer to PID "object"
 */
void Silvia_PID_Function(PID* pidPntr);

/**
 * @summary - Function turns SSR pin on/off based on PID output value and 
 * time period
 */
void Run_Output();

/**
 * @summary - controls espresso brewing function; when brew switch flipped
 * it sets the brewFlag = 1 which then calls this function from Main
 * 
 * **/
void Brewing();

/**
 * @summary - toggles between editing and saving user settings; when button 
 * pushed it sets the btnFlag = 1 and this function is called from Main
 */
void Button_Pushed();

/**
 * @summary - when user turns encoder it sets the encFlag = 1 and this function
 * is called from main to change menu selection or change parameter values as
 * applicable
 */
void Encoder_Turned();

/**
 * @summary - called from encoder and button functions to update value to 
 * text for active double parameter; active parameter set by Button_Pushed()
 * @param x - passed through values dictates if value is incremented or decremented
 * @param string - pass char array to write value text to
 */
void Update_Double(int x, char *string);

/**
 * @summary - called from encoder and button functions to update value to 
 * text for toggle parameter passed through
 * @param toggle - toggle value to update text for; 1 = On, 0 = Off
 * @param string - char array to write On or Off to
 */
void Update_Toggle(uint8_t toggle, char *string);

/**
 * @summary - called from encoder and button functions to update value to 
 * text for active 16 bit parameter; active parameter set by Button_Pushed()
 * @param x - passed through values dictates if value is incremented or decremented
 * @param string - pass char array to write value text to
 * @param timerBool - True or False.  If true active value treated as a timer value
 */
void Update_Uint16(int x, char *string, uint8_t timerBool);

/**
 * @summary - called from encoder and button functions to update value text for
 * Auto Off timer value
 * @param x - passed through values dictates if value is incremented or decremented
 * @param string - pass char array to write value text to
 */
void Update_Auto_Off(int x, char *string);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

