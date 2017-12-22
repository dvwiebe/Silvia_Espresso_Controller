#include "pid.h"

void Construct_PID(PID* pid, double* Input, double* Output, double* Setpoint,        
        double Kp, double Ki, double Kd, int ControllerDirection)
{
    pid->myOutput = Output;
    pid->myInput = Input;
    pid->mySetpoint = Setpoint;
	pid->inAuto = false;
	
	SetOutputLimits(pid, 0, 255);				//default output limit corresponds to 
												//the arduino pwm limits
    pid->SampleTime = 100;							//default Controller Sample Time is 0.1 seconds

    SetControllerDirection(pid, ControllerDirection);
    SetTunings(pid, Kp, Ki, Kd);

    pid->lastTime = runTime - pid->SampleTime; 
}

void Initialize_PID(PID *pid)
{    
    pid->ITerm = *(pid->myOutput);
    pid->lastInput = *(pid->myInput);
    if(pid->ITerm > pid->outMax) pid->ITerm = pid->outMax;
    else if(pid->ITerm < pid->outMin) pid->ITerm = pid->outMin;
}

void SetMode(PID* pid, int Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if(newAuto == !(pid->inAuto))
    {  /*we just went from manual to auto*/
        Initialize_PID(pid);
    }
    pid->inAuto = newAuto; 
}

bool Compute(PID* pid)
{
   if(!(pid->inAuto)) return false;
   unsigned long now = runTime;
   unsigned long timeChange = (now - pid->lastTime);
   if(timeChange >= pid->SampleTime)
   {
      /*Compute all the working error variables*/
	  double input = *(pid->myInput);
      double error = *(pid->mySetpoint) - input;
      pid->ITerm += (pid->ki * error);
      if(pid->ITerm > pid->outMax) pid->ITerm = pid->outMax;
      else if(pid->ITerm < pid->outMin) pid->ITerm = pid->outMin;
      double dInput = (input - pid->lastInput);
 
      /*Compute PID Output*/
      double output = pid->kp * error + pid->ITerm - pid->kd * dInput;
      
	  if(output > pid->outMax) output = pid->outMax;
      else if(output < pid->outMin) output = pid->outMin;
	  *(pid->myOutput) = output;
	  
      /*Remember some variables for next time*/
      pid->lastInput = input;
      pid->lastTime = now;
	  return true;
   }
   else return false; 
}
void SetOutputLimits(PID* pid, double Min, double Max)
{
   if(Min >= Max) return;
   pid->outMin = Min;
   pid->outMax = Max;
 
   if(pid->inAuto)
   {
	   if(*(pid->myOutput) > pid->outMax) *(pid->myOutput) = pid->outMax;
	   else if(*(pid->myOutput) < pid->outMin) *(pid->myOutput) = pid->outMin;
	 
	   if(pid->ITerm > pid->outMax) pid->ITerm = pid->outMax;
	   else if(pid->ITerm < pid->outMin) pid->ITerm = pid->outMin;
   } 
}

//available but not commonly used functions ********************************************************
void SetTunings(PID* pid, double Kp, double Ki, double Kd)
{
    if (Kp<0 || Ki<0 || Kd<0) return;
 
    pid->dispKp = Kp; pid->dispKi = Ki; pid->dispKd = Kd;

    double SampleTimeInSec = ((double)pid->SampleTime)/1000;  
    pid->kp = Kp;
    pid->ki = Ki * SampleTimeInSec;
    pid->kd = Kd / SampleTimeInSec;

   if(pid->controllerDirection ==REVERSE)
    {
       pid->kp = (0 - pid->kp);
       pid->ki = (0 - pid->ki);
       pid->kd = (0 - pid->kd);
    }
}
void ZeroIntegral(PID* pid)
{
    pid->ITerm = 0;
}

void SetControllerDirection(PID* pid, int Direction)
{
   if(pid->inAuto && Direction != pid->controllerDirection)
   {
	  pid->kp = (0 - pid->kp);
      pid->ki = (0 - pid->ki);
      pid->kd = (0 - pid->kd);
   }   
   pid->controllerDirection = Direction; 
}

void SetSampleTime(PID* pid, int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime
                      / (double)pid->SampleTime;
      pid->ki *= ratio;
      pid->kd /= ratio;
      pid->SampleTime = (unsigned long)NewSampleTime;
   } 
}
//Display functions ****************************************************************
   double GetKp(PID* pid)
   {
       return pid->dispKp;
   }
   double GetKi(PID* pid)
   {
       return pid->dispKi;
   }
   double GetKd(PID* pid)
   {
       return pid->dispKd;
   }
   int GetMode(PID* pid)
   {
       return pid->inAuto ? AUTOMATIC : MANUAL;
   }
   int GetDirection(PID* pid)
   {
       return pid->controllerDirection;
   }
