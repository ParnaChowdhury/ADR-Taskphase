
#include <math.h>
#include <Wire.h>

const float ROLL_PID_KP=2;                                     //set PID gains for roll
const float ROLL_PID_KD=1;
const float ROLL_PID_KI=0.5;

const float PITCH_PID_KP=2;                                    //set PID gains for Pitch
const float PITCH_PID_KD=1;
const float PITCH_PID_KI=0.5;

float computeRollPID(float setPoint){
 
  
  static unsigned long lastTime;                                 //define necessary variables
  static float lastErr, errSum;
  float error;
  static float P, I, D;

  int SampleTime = 1000;                                         // define PID Sampling Time
  
  unsigned long now = millis();
  int dt = (int)(now - lastTime);
  
  if(dt >= SampleTime){                                           // unless dt is large enough not calculated
    error   = angle_roll_output - setpoint;
    errSum += error*dt;
    
    P = ROLL_PID_KP * error;
    
    
    if(dt > 10*SampleTime) {                                       // dt is significantly large so system should be prevented from becoming unstable
      D = 0;                                                       // set d term to 0,  it could cause a large output spike
      errSum = 0;                                                  // also reset the errSum value to zero the I term
    }
    else{
      D = ROLL_PID_KD * (error - lastErr)/dt;
    }
    
    I = ROLL_PID_KI * errSum;
    
    I = constrain(I, -I_MAX, I_MAX);                              // constrain I term to max setting to keep the system stable 
 
    
    lastErr = error;
    lastTime = now;
  }
  return (P + I + D);
}


float computePitchPID(float setPoint){
  
  
  static unsigned long lastTime;                                //define parameters
  static float lastErr, errSum;
  float error;
  static float P, I, D;

  int SampleTime = 1000; 
  
  unsigned long now = millis();
  int dt = (int)(now - lastTime);
  
  if(dt >= SampleTime){
    error   = angle_pitch_output - setpoint;
    errSum += error*dt;
    
    P = PITCH_PID_KP * error;
    
    if(dt >= 10*SampleTime){                      //elapsed time is too high
      D = 0;                                      // d term made 0 to reduce overshoots
      errSum = 0;                                 // error sum 0 to 0 the i term
    }
    else{
      D = PITCH_PID_KD * (error - lastErr)/dt;
    }
    
    I = PITCH_PID_KI * errSum;
    
    I = constrain(I, -I_MAX, I_MAX);               // constrain I term to max setting   
    
    
    lastErr = error;
    lastTime = now;
  }
  return (P + I + D);
}

void setup(){
  Serial.begin(115200);
  looptimeNow=micros();

}

void loop(){
  computeRollPID();
  computePitchPID();
}
