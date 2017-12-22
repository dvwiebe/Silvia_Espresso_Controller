/*
 * File: silvia_utility.c
 * Author: David Wiebe
 * Description: Process related functions required for the Silvia PID Controller PIC Program 
 * Revision History: Rev 0 - Sept 19, 2017
 */

#include "silvia_process.h"

static double activeDouble = 0;
static uint16_t activeUint16 = 0;
static long int activeTimeOut = 0;

void Update_Temperature() {

    //temporary char array to hold set point double as text
    char doubleText [6] = {0};

    //call function to read ADS1220 chip and update temperature variable
    readRTDTemperatureC(0);
    //apply user set RTD temperature Offset Value (zero by default)
    rtdTemperatureC += rtdOffset.d;

    //convert temperature double to char array
    sprintf(doubleText, "%.1f", rtdTemperatureC);
    
    //Calculate difference between actual and setpoint temperature for use in
    //this function  and PID function
    deltaTemperatureC = rtdTemperatureC - pidSetPoint;

    //check if temperature is within tolerance of user setting and update
    //Status box on LCD accordingly
    if ((deltaTemperatureC < TEMPERATURE_VARIANCE) && (deltaTemperatureC > ((-1.0) * TEMPERATURE_VARIANCE))) {
        draw_filled_rectangle(91, 3, 126, 34, 1);
        draw_text("Ready", 96, 13, Tahoma7, 1, 0);

    } else if (deltaTemperatureC < 0) {
        draw_filled_rectangle(91, 3, 126, 34, 0);
        draw_text("Heating", 93, 8, Tahoma7, 1, 1);
        draw_text("Up", 103, 19, Tahoma7, 1, 1);

    } else {
        draw_filled_rectangle(91, 3, 126, 34, 0);
        draw_text("TOO", 100, 8, Tahoma7, 1, 1);
        draw_text("HOT!", 99, 19, Tahoma7, 1, 1);
    }

    //clear previous temperature reading from LCD and write new reading   
    draw_filled_rectangle(26, 1, 74, 23, 0);
    draw_text(doubleText, 30, 4, Tahoma14, 1, 1);
    glcd_refresh();
}

void Change_Set_Point() {

    //temporary char array to hold set point double as text
    char doubleText [6] = {};

    draw_filled_rectangle(1, 36, 71, 46, 0); // Clear Set Point Title and Number

    //check position of steam switch
    if (!STM_Input_GetValue()) // if pin low, steam switch active
    {

        pidSetPoint = steamSetPoint.d;
        draw_text("Steam: ", 12, 36, Tahoma7, 1, 1);
        if (steamSetPoint.d < 100) sprintf(doubleText, " %.1f", steamSetPoint.d);
        else sprintf(doubleText, "%.1f", steamSetPoint.d);

    } else // if pin high, brew active
    {
        pidSetPoint = brewSetPoint.d;
        draw_text("Brew : ", 12, 36, Tahoma7, 1, 1);
        if (brewSetPoint.d < 100) sprintf(doubleText, " %.1f", brewSetPoint.d);
        else sprintf(doubleText, "%.1f", brewSetPoint.d);
    }

    //Update Screen with new Setpoint
    draw_text(doubleText, 47, 36, Tahoma7, 1, 1);
    glcd_refresh();
}

void Silvia_PID_Function(PID *pidPntr) {

    static uint8_t pidAggressive = 0;

    if (deltaTemperatureC > AGGRESSIVE_LIMIT || (deltaTemperatureC < ((-1.0) * AGGRESSIVE_LIMIT))) {
        //if temperature difference > than limit (10C), use aggressive tuning
        //check to see if aggressive tuning already in use
        if (!pidAggressive) {
            SetTunings(pidPntr, (pidKp.uint16 * 2), 0, 0); //set aggressive tuning
            pidAggressive = 1; //flag to identify aggressive tuning in use
        }
    } else {
        //if temperature difference within limit (10C), use normal tuning
        //check to see if normal tuning already in use
        if (pidAggressive) {
            SetTunings(pidPntr, pidKp.uint16, pidKi.uint16, pidKd.uint16); //set normal tuning
            ZeroIntegral(pidPntr); //reset Integral Cumulative error to zero
            pidAggressive = 0; //flag to identify aggressive tuning NOT in use
        }
    }

    //call PID compute function; only called once at the start of each period
    //time check performed internal to Compute function
    Compute(pidPntr);
}

void Run_Output() {
    //variable to identify period start;
    static uint32_t periodStart = 0;

    //if period is beyond set PID_PERIOD, start new time period
    if ((runTime - periodStart) > PID_PERIOD) periodStart = runTime;

    //if pidOutput is higher than time elapsed in current period, set SSR pin high
    //else turn off SSR pin
    if (pidOutput > (runTime - periodStart)) SSR_SetHigh();
    else SSR_SetLow();

}

void Brewing() {
    //static variables for use within this function only
    static uint32_t startTime = 0;
    static uint8_t brewStartFlag = 0;
    static uint8_t preInfInProcFlag = 0;
    static uint8_t preInfDelayFlag = 0;

    uint16_t timerValue;
    char timerText[5] = {0}; //array to hold timer value for LCD


    //if first pass through brew function, set variables as follows
    if (brewFirstPassFlag) {
        startTime = runTime; //start of time period
        brewFirstPassFlag = 0;
        brewStartFlag = 1;

        //during first pass through, check if user has toggled pre-infusion
        if (preInfToggle) {
            preInfInProcFlag = 1;
            preInfDelayFlag = 1;

            //Update timer area to read "PRE" to denote Pre-Infusion in process
            draw_filled_rectangle(90, 48, 128, 64, 0); //clear Timer Area            
            draw_text("PRE", 94, 49, Tahoma12, 1, 1);
            glcd_refresh();

            //Toggle 3-way Valve and Pump to start pre-infusion
            VLV_RLY_SetHigh();
            PMP_RLY_SetHigh();

            //return to main
            return;
        }
    }

    if (preInfInProcFlag) {
        //check if pre-infusion has run for user defined period
        //if time remaining, return to main
        if ((runTime - startTime) < preInfPump.uint16) return;
        else //else shut off pump and valve
        {
            //shut off pump and toggle valve
            PMP_RLY_SetLow();
            VLV_RLY_SetLow();

            preInfInProcFlag = 0; //update preInfusion in process flag                        
            startTime = runTime; //reset startTime for next activity to "now"

            return;
        }
    }

    if (preInfDelayFlag) {
        //check if preinfusion delay has reach user defined period
        //if time remaining, return to main
        if ((runTime - startTime) < preInfDelay.uint16) return;
        else {
            preInfDelayFlag = 0; //updated preInfusion Delay Flag
            startTime = runTime; //reset startTime for next activity to "now"
        }
    }

    //if first time through this code for brew cycle, turn on pump and valve
    if (brewStartFlag) {
        brewStartFlag = 0; //toggle flag
        VLV_RLY_SetHigh();
        PMP_RLY_SetHigh();
    }

    //Calculate current brew run time and assign to timerValue
    timerValue = runTime - startTime;
    //timerValue in ms, convert to xx.y precision in seconds
    // decimal = y; integer math used to reduce CPU usage
    uint8_t decimal = (timerValue % 1000) / 100;
    sprintf(timerText, "%2u.%u", timerValue / 1000, decimal);

    //Update timer area with the brew run time
    draw_filled_rectangle(90, 48, 128, 64, 0); //clear Timer Area
    draw_text(timerText, 94, 49, Tahoma12, 1, 1);
    glcd_refresh();

    //check if user has brew timer active
    if (brewTimeToggle) {
        //check if current timerValue >= user set brew timer
        if (timerValue >= brewTime.uint16) {
            //turn off pump and valve
            PMP_RLY_SetLow();
            VLV_RLY_SetLow();
            brewFlag = 0; //reset flag            
        }
    }

}

void Button_Pushed() {

    btnFlag = 0;        //clear button pushed flag
    btnActiveFlag ^= 1; //toggle button active flag
        
    draw_filled_rectangle(5, 48, 88, 64, 0); //clear LCD Setting Area

    //if button just turned active, user has selected to change a value
    if (btnActiveFlag) {
        char valueText [8] = {0}; //temporary array to hold setting text

        switch (menuIndex) {
            case 0: //Brew Set Point
                activeDouble = brewSetPoint.d;
                Update_Double(0, valueText);
                break;
            case 1: // Steam Set Point
                activeDouble = steamSetPoint.d;
                Update_Double(0, valueText);
                break;
            case 2: // Brew Timer Toggle
                Update_Toggle(brewTimeToggle, valueText);
                break;
            case 3: // Brew Timer Value
                activeUint16 = brewTime.uint16;
                Update_Uint16(0, valueText, 1);
                break;
            case 4: // Pre-Infusion Toggle
                Update_Toggle(preInfToggle, valueText);
                break;
            case 5: // Pre-Infusion Timer
                activeUint16 = preInfPump.uint16;
                Update_Uint16(0, valueText, 1);
                break;
            case 6: // Pre-Infusion Delay
                activeUint16 = preInfDelay.uint16;
                Update_Uint16(0, valueText, 1);
                break;
            case 7: // RTD Offset
                activeDouble = rtdOffset.d;
                Update_Double(0, valueText);
                break;
            case 8: // Auto Off Timer
                activeTimeOut = timeOut.lInt;
                Update_Auto_Off(0, valueText);
                break;
            case 9: // kp
                activeUint16 = pidKp.uint16;
                Update_Uint16(0, valueText, 0);
                break;
            case 10: // ki
                activeUint16 = pidKi.uint16;
                Update_Uint16(0, valueText, 0);
                break;
            case 11: // kd
                activeUint16 = pidKd.uint16;
                Update_Uint16(0, valueText, 0);
                break;
        }
        
        draw_text(valueText, 10, 51, Tahoma7, 1, 1); //write new value to LCD
        
    } 
    else //if button just changed inactive it means the user has updated a value
    {
        uint8_t trueFlag = 1; // temporary flag as EEPROM function requires value address        
        
        // Update appropriate value and save in EEPROM based on menu Index position
        switch (menuIndex) {
            case 0: //Brew Set Point
                brewSetPoint.d = activeDouble;
                EEPROM_Write(&trueFlag, 3, 1); //set brew SP flag as true in EEPROM
                EEPROM_Write(brewSetPoint.uint8, 18, 4); // save new setpoint
                steamFlag = 1; //flag so LCD displayed set point is updated
                break;
            case 1: // Steam Set Point
                steamSetPoint.d = activeDouble;
                EEPROM_Write(&trueFlag, 4, 1); //set steam SP flag as true in EEPROM
                EEPROM_Write(steamSetPoint.uint8, 24, 4); // save new setpoint
                steamFlag = 1; //flag so LCD displayed set point is updated
                break;
            case 2: // Brew Timer Toggle
                EEPROM_Write(&brewTimeToggle, 11, 1); // set brew time toggle flag in EEPROM
                break;
            case 3: // Brew Timer Value
                brewTime.uint16 = activeUint16;
                EEPROM_Write(&trueFlag, 5, 1); //set brew Timer value flag as true in EEPROM
                EEPROM_Write(brewTime.uint8, 28, 2); // save new timer value
                break;
            case 4: // Pre-Infusion Toggle
                EEPROM_Write(&preInfToggle, 10, 1); // set pre-Inf toggle flag in EEPROM
                break;
            case 5: // Pre-Infusion Timer
                preInfPump.uint16 = activeUint16;
                EEPROM_Write(&trueFlag, 7, 1); //set pre-Infusion On Time value flag as true in EEPROM
                EEPROM_Write(preInfPump.uint8, 22, 2); // save new timer value
                break;
            case 6: // Pre-Infusion Delay
                preInfDelay.uint16 = activeUint16;
                EEPROM_Write(&trueFlag, 6, 1); //set pre-Infusion Delay flag as true in EEPROM
                EEPROM_Write(preInfDelay.uint8, 30, 2); // save new timer value
                break;
            case 7: // RTD Offset
                rtdOffset.d = activeDouble;
                EEPROM_Write(&trueFlag, 8, 1); //set RTD Offset flag as true in EEPROM
                EEPROM_Write(rtdOffset.uint8, 32, 4); // save new offset value
                break;
            case 8: // Auto Off Timer
                timeOut.lInt = activeTimeOut;
                EEPROM_Write(&trueFlag, 9, 1); // set time out value flag as true in EEPROM
                EEPROM_Write(timeOut.uint8, 36, 4); // save auto off value
                break;
            case 9: // kp
                pidKp.uint16 = activeUint16;
                EEPROM_Write(&trueFlag, 0, 1); //set Kp Flag as true in EEPROM
                EEPROM_Write(pidKp.uint8, 12, 2); // save new value
                break;
            case 10: // ki
                pidKi.uint16 = activeUint16;
                EEPROM_Write(&trueFlag, 1, 1); //set Ki Flag as true in EEPROM
                EEPROM_Write(pidKi.uint8, 14, 2); // save new value
                break;
            case 11: // kd
                pidKd.uint16 = activeUint16;
                EEPROM_Write(&trueFlag, 2, 1); //set Kd Flag as true in EEPROM
                EEPROM_Write(pidKd.uint8, 16, 2); // save new value
                break;
        }
        //write setting title to LCD
        draw_text(settingNames[menuIndex], 10, 51, Tahoma7, 1, 1); 
    }
    
    //update LCD Screen
    glcd_refresh();

}

void Encoder_Turned() {
    //temporary variable with encoder increment or decrement
    int x = 0;

    //if encFlag == 2, encoder rotated forward, else encoder rotated backward
    if (encFlag == 2) x = 1;
    else if (encFlag == 1) x = -1;

    encFlag = 0; //clear flag
    
    draw_filled_rectangle(5, 48, 88, 64, 0); //clear LCD Setting Area

    if (btnActiveFlag) //if button active, update selected value
    {

        char valueText [8] = {0}; //temporary array to hold setting text
        switch (menuIndex) {
            case 0: //Brew Set Point
                Update_Double(x, valueText);
                break;
            case 1: //Steam Set Point
                Update_Double(x, valueText);
                break;
            case 2: //Brew Timer Toggle
                brewTimeToggle ^= 1;
                Update_Toggle(brewTimeToggle, valueText);
                break;
            case 3: //Brew Timer Value
                Update_Uint16(x, valueText, 1);
                break;
            case 4: //Pre-Infusion Toggle
                preInfToggle ^= 1;
                Update_Toggle(preInfToggle, valueText);
                break;
            case 5: //Pre-Infusion Timer
                Update_Uint16(x, valueText, 1);
                break;
            case 6: //Pre-Infusion Delay Timer
                Update_Uint16(x, valueText, 1);
                break;
            case 7: //RTD Offset
                Update_Double(x, valueText);
                break;
            case 8: //Auto Off Timer
                Update_Auto_Off(x, valueText);
                break;
            case 9: //kp
                Update_Uint16(x, valueText, 0);
                break;
            case 10: //ki
                Update_Uint16(x, valueText, 0);
                break;
            case 11: //kd
                Update_Uint16(x, valueText, 0);
                break;
        }
        
        draw_text(valueText, 10, 51, Tahoma7, 1, 1); //write new value to LCD

    } else //if button not active, cycle through setting menu
    {
        //fill in previous indicator line
        draw_filled_rectangle(1, (50 + menuIndex), 4, (50 + menuIndex), 1);

        //update menu index
        menuIndex += x;
        //check if menuIndex within range and adjust as needed
        if (menuIndex > 11) menuIndex = 0;
        else if (menuIndex < 0) menuIndex = 11;

        //Update LCD with new indicator and new title 
        draw_filled_rectangle(1, (50 + menuIndex), 4, (50 + menuIndex), 0); //update indicator line        
        draw_text(settingNames[menuIndex], 10, 51, Tahoma7, 1, 1);
    }
    //refresh LCD
    glcd_refresh();

}

void Update_Double(int x, char *string) {
    //increment by x / 10 or (0.1)
    activeDouble += (double)x / 10.0;
    
    //update string with double value
    sprintf(string, "%.1f C", activeDouble);
}

void Update_Toggle(uint8_t toggle, char *string) {

    string[0] = ' ';
    string[1] = ' ';
    string[2] = 'O';

    //if toggle ==1, write "ON", else write "OFF"
    if (toggle) {
        string[3] = 'N';
        string[4] = '\0';
    } else {
        string[3] = 'F';
        string[4] = 'F';
        string[5] = '\0';
    }
}

void Update_Uint16(int x, char *string, uint8_t timerBool) {
    //if a timer value, increment as uint16 but display as double
    if (timerBool) {
        //increment in 0.1 seconds only;
        activeUint16 += (x * 100);
        uint16_t tempUint16 = activeUint16 / 100;
        //convert timer to be viewed as a double and update string
        sprintf(string, "%u.%u s", tempUint16 / 10, tempUint16 % 10);
    } else {
        //increment or decrement uint16 by x 
        activeUint16 += x;
        //update string with 16bit value
        sprintf(string, "%u", activeUint16);
    }
}

void Update_Auto_Off(int x, char *string) {
    //increment in units of 30 minutes only which is 1,800,000 ms
    activeTimeOut += (x * 1800000);

    //check if timeOut in range
    if (activeTimeOut < 0) activeTimeOut = 14400000;
    else if (activeTimeOut > 14400000 || activeTimeOut == 0) {
        activeTimeOut = 0;
        string[0] = 'D';
        string[1] = 'i';
        string[2] = 's';
        string[3] = 'a';
        string[4] = 'b';
        string[5] = 'l';
        string[6] = 'e';
        string[7] = '\0';
    } else {
        //Display in Hours
        //create temporary timeout variable and convert ms to s; no loss of
        //digits as we're incrementing by 1,800,000ms
        uint16_t timeOut16bit = activeTimeOut / 1000;
        
        //if there is remainder, then the value in hrs is u.5 where u is determined below
        if(timeOut16bit % 3600) 
            sprintf(string, "%u.5 hrs", (timeOut16bit /3600));
        else
            sprintf(string, "%u hrs", (timeOut16bit /3600));       
        
    }

}