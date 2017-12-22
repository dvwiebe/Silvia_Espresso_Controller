/**
 * Template MCC generated comments for main file:
  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC24FJ256GA704
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60
 */

/*************EsspressI/O Controller V1.0************************
 *  Summary:
 *      Main file for Silvia Espresso controller
 *  
 * Author: David Wiebe <dvwiebe@gmail.com>
 * Date: Dec 22, 2017
 * Version: 1.0
 * Released under GNU V3.0 License
 */

#include "silvia_utility.h"
#include "silvia_process.h"


/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    

    /*Initialize LCD*/
    glcd_init();                //Initialize the screen, turning it on    
    glcd_blank();               //Clear the screen's internal memory     
    glcd_logo(espresso_logo);   //Print Logo for Startup
    
    delayms(1000); //delay to allow ADS1220 startup
    
    //Create PID object for program
    PID boilerPID;
    
    /*EEPROM - check for user saved settings*/
    Read_User_Settings();
    
    /*PID - Initialize PID Controller*/
    pidSetPoint = brewSetPoint.d; //default, set point is brew temp        
    Construct_PID(&boilerPID, &rtdTemperatureC, &pidOutput, &pidSetPoint,        
        pidKp.uint16, pidKi.uint16, pidKd.uint16, DIRECT);    
    SetOutputLimits(&boilerPID, 0, PID_PERIOD);
    SetSampleTime(&boilerPID, PID_PERIOD);
    SetMode(&boilerPID, AUTOMATIC); //sets PID to automatic and initializes it

    /*RTD*/
    ADS1220Command(ADS1220_RESET); //reset ADS1220
    delayms(1000);              //delay to allow for proper reset
    setGain(16);              //set the gain to 16
    setSPS(0x02);               //set the SPS to 20    
    uint8_t rtdCheck = initializeThreeWireRTD();   //Initialize ADS for 3-wire RTD
    
    if(rtdCheck != 1)       //check if rtd initialization failed
    {
        glcd_blank();
        draw_text("RTD Init Failed",2,2,Tahoma12,1,1);
        glcd_refresh();
        delayms(10000); //Delay for 10s to allow message to be read
        Sleep_Mode();
    }

    delayms(2000); //delay additional 2 seconds for logo visibility
    
    LCD_Draw_Borders(); //Draw borders for operation  
    

    while (1) {
        //check runtime; if > time out period, power down unit
        if (timeOut.lInt == 0); //do nothing as time out disabled by user
        else if (runTime > timeOut.lInt) Sleep_Mode();
        
        //if steam switch has been switched, flag == 1 and setpoint function called
        if(steamFlag) 
        {
            steamFlag = 0;
            Change_Set_Point();
        }
        
        //if RTD flag == 1, reading is available from ADS chip, call RTD read function
        if(rtdFlag)
        {
            rtdFlag = 0; //reset flag
            Update_Temperature();
        }

        
        //Call PID Function to calculate output, and then run the output 
        Silvia_PID_Function(&boilerPID);
        Run_Output();
        
        //if brew flag == 1, brew switch has been toggled by user; flag cleared
        //within Brewing() function
        if(brewFlag) Brewing();
        
        //check for encoder turned flag
        if(encFlag) Encoder_Turned();
        
        //check for button pressed flag
        if(btnFlag) Button_Pushed();
    }

    return -1;
}
/**
 End of File
 */