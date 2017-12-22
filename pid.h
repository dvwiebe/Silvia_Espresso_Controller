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
 * File: pid.h   
 * Author: David Wiebe
 * Comments: Adapted from Brett Beauregard's original Arduino PID library
 *              <br3ttb@gmail.com> brettbeauregard.com
 * Revision history: 
 *  Aug 5, 2017 - Rev 0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PID_V1_H
#define	PID_V1_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "silvia_utility.h"

//#define __cplusplus     1
#define AUTOMATIC       1
#define MANUAL          0
#define DIRECT          0
#define REVERSE         1


// TODO Insert appropriate #include <>


// TODO Insert C++ class definitions if appropriate
typedef struct PIDstruct{
        double dispKp;				// * we'll hold on to the tuning parameters in user-entered 
        double dispKi;				//   format for display purposes
        double dispKd;				//
    
        double kp;                  // * (P)roportional Tuning Parameter
        double ki;                  // * (I)ntegral Tuning Parameter
        double kd;                  // * (D)erivative Tuning Parameter

        int controllerDirection;

        double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
        double *myOutput;             //   This creates a hard link between the variables and the 
        double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                      //   what these values are.  with pointers we'll just know.

        unsigned long lastTime;
        double ITerm, lastInput;

        unsigned long SampleTime;
        double outMin, outMax;
        bool inAuto;
    }PID;

//commonly used functions **************************************************************************
void Construct_PID(PID* pid, double* Input, double* Output, double* Setpoint, 
        double Kp, double Ki, double Kd, int ControllerDirection);          

void Initialize_PID(PID* pid);                                  //Initialize PID instance

void SetMode(PID* pid, int Mode);                   // * sets PID to either Manual (0) or Auto (non-0)

bool Compute(PID* pid);                             // * performs the PID calculation.  it should be
                                                    //   called every time loop() cycles. ON/OFF and
                                                    //   calculation frequency can be set using SetMode
                                                    //   SetSampleTime respectively
void SetOutputLimits(PID* pid, double Min, double Max);       //clamps the output to a specific range. 0-255 by default, but
                                                    //it's likely the user will want to change this depending on
                                                    //the application

//available but not commonly used functions ********************************************************
void SetTunings(PID* pid, double Kp, double Ki, double Kd);   // * While most users will set the tunings once in the 
                                                    //constructor, this function gives the user the option
                                                    //of changing tunings during runtime for Adaptive control
void ZeroIntegral(PID* pid);                        //DW * Allows users to zero integral term. This may be desired
                                                    //DW   in some systems when changing setpoints to prevent cumulated
                                                    //DW   error being carried forward.

void SetControllerDirection(PID* pid, int Direction);          // * Sets the Direction, or "Action" of the controller. DIRECT
                                                    //   means the output will increase when error is positive. REVERSE
                                                    //   means the opposite.  it's very unlikely that this will be needed
                                                    //   once it is set in the constructor.
void SetSampleTime(PID* pid, int NewSampleTime);    // * sets the frequency, in Milliseconds, with which 
                                                    //   the PID calculation is performed.  default is 100
//Display functions ****************************************************************
double GetKp(PID* pid);                                  // These functions query the pid for interal values.
double GetKi(PID* pid);                                  //  they were created mainly for the pid front-end,
double GetKd(PID* pid);                                  // where it's important to know what is actually 
int GetMode(PID* pid);                                   //  inside the PID.
int GetDirection(PID* pid);					  







// TODO Insert declarations

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
#endif /*__cplusplus */
    
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
    
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

