#include <Wire.h>
#include <PinChangeInt.h>
#include <math.h>


#define RX_PIN_CH0 A0                                                      //Define Pins
#define RX_PIN_CH1 A1
#define RX_PIN_CH2 A2
#define RX_PIN_CH3 A3


volatile byte updateFlagsShared;                                           // Declare variables shared b/w interrupts & program as volatile
volatile int rxValShared[NUMBER_CHANNELS];

unsigned long rxStart[NUMBER_CHANNELS];                                    // define timer variables for interrupts (not volatile b/c not shared)

int rxVal[NUMBER_CHANNELS];                                                // define global Rx value variable

float rxThro, rxRoll, rxPitch, rxYaw;                                      // variables for Rx desired setpoints


void rxInit(){                                                             // initialize interface with Rx by attaching interrupts

  PCintPort::attachInterrupt(RX_PIN_CH0, chan0, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH1, chan1, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH2, chan2, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH3, chan3, CHANGE);
}

void rxGetNewVals(){                                                     // updates values in rxVal with any new RX signals that have been recieved
  
  noInterrupts();                                                        // turn off interrupts while interacting with volatile vars
  
  byte updateFlags = updateFlagsShared;                                  // take local copy of update flags. while taking copy, disable inturupts, so that values don't get changed.
   
                                                 
  for (int i=0; i<4; i++){                                              // copy the value of each channel into the buffer if it has been updated
   
    if (updateFlagsShared & 1<<i){                                      // use bitshift to check if the flag has been raised
      
      if(600 < rxValShared[i] && rxValShared[i] < 2200){                // check if value is reasonable. 
        rxVal[i] = rxValShared[i];                                      // Reject values greater than 2200 micros, these mean an interrupt was missed
      }
    }
  }
    
  // now we have a copy of each changed variable. We have to copy them as Serial.print() is not supported by inturrupt routine.
  updateFlagsShared = 0;                                                 //Reset the flag variable and turn interrupts on
                                                                 
  interrupts();
  
  rxMapping(updateFlags);
}


// Measure pulse lengths of input servo signals.


void chan0()                                                               // Function attached to RX_PIN_CH0 interrupt.

{

  if (digitalRead(RX_PIN_CH0) == HIGH)                                      // if pin is high, new pulse. Record time
  {
    rxStart[0] = micros();
  }
  else                                                                      // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxValShared[0] = micros() - rxStart[0];
    rxStart[0] = 0;
    updateFlagsShared |= RX_FLAG_CH0;
  }
}

void chan1()                                                                // Function attached to RX_PIN_CH1 interrupt.
// Function attached to RX_PIN_CH1 interrupt.

{
  if (digitalRead(RX_PIN_CH1) == HIGH)                                     // if pin is high, new pulse. Record time
  {
    rxStart[1] = micros();
  }
  else                                                                     // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxValShared[1] = micros() - rxStart[1];
    rxStart[1] = 0;
    updateFlagsShared |= RX_FLAG_CH1;
  }
}

void chan2()                                                                // Function attached to RX_PIN_CH2 interrupt.                                                   
// Function attached to RX_PIN_CH2 interrupt.

{
  
  if (digitalRead(RX_PIN_CH2) == HIGH)                                      // if pin is high, new pulse. Record time
  {
    rxStart[2] = micros();
  }
  else                                                                       // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxValShared[2] = micros() - rxStart[2];
    rxStart[2] = 0;
    updateFlagsShared |= RX_FLAG_CH2;
  }
}

void chan3()                                                                // Function attached to RX_PIN_CH3 interrupt.
{
  
  if (digitalRead(RX_PIN_CH3) == HIGH)                                       // if pin is high, new pulse. Record time
  {
    rxStart[3] = micros();
  }

  else                                                                      // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxValShared[3] = micros() - rxStart[3];
    rxStart[3] = 0;
    updateFlagsShared |= RX_FLAG_CH3;
  }
}
void rxMapping(byte updateFlags){
  
  /* 
  Converts any new Rx values into angle setpoints to be used by the PIDs.
  Only calculates for values that have been updated since last time, indicated
  by the updateFlags parameter. 
  
  For roll/pitch/yaw, uses floating point math instead of the map() function
  because it runs faster and the values are constrained to the limits.
  */
  
  if(updateFlags & 1<<CHANNEL_THROTTLE){                                                                        // New throttle value
                                                                                                                 
    rxThro = map(rxVal[CHANNEL_THROTTLE], THROTTLE_CUTOFF, THROTTLE_RMAX, THROTTLE_WMIN, THROTTLE_WMAX);        // map throttle values directly 
  }
  if(updateFlags & 1<<CHANNEL_ROLL){                                                                            // New roll caliberated and set under a max-min limit
    rxRoll  = (float)rxVal[CHANNEL_ROLL]*ROLL_RX_MULT - ROLL_RX_SUB;
    rxRoll  = constrain(rxRoll, -ROLL_A_MAX, ROLL_A_MAX);
  }
  if(updateFlags & 1<<CHANNEL_PITCH){                                                                            // New pitch caliberated and set under a max-min limit
    rxPitch = (float)rxVal[CHANNEL_PITCH]*PITCH_RX_MULT - PITCH_RX_SUB;
    rxPitch = constrain(rxPitch, -PITCH_A_MAX, PITCH_A_MAX);
  }
  if(updateFlags & 1<<CHANNEL_YAW){                                                                              // New yaw caliberated and set under a max min limit
    rxYaw   = (float)rxVal[CHANNEL_YAW]*YAW_RX_MULT - YAW_RX_SUB;
    rxYaw   = constrain(rxYaw, -YAW_A_MAX, YAW_A_MAX);
  }
}

void setup(){
  Serial.begin(115200);
  rxinit();
  delay(200);
}

void loop(){
  looptimeNow= micros();
}
}
