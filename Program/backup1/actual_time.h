#ifndef ACTUAL_TIME_H
#define ACTUAL_TIME_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

//Internal millis() function values
const unsigned long MAX_MILLIS = 4294967295;     //this is the max millis value (17179868 for earlier versions of Arduino)
const unsigned long HALF_MILLIS = 2147483647;     //this is halfway to the max millis value (17179868 for earlier versions of Arduino)

//Count every time the millis() function reache the maximum value
int millisRollover(){
   static int numRollovers = 0;                  //variable that permanently holds the number of rollovers since startup
   static bool readyToRoll = false;              //tracks whether we've made it halfway to rollover
   unsigned long now = millis();                 //the time right now

   if (now > HALF_MILLIS)   //as long as the value is greater than halfway to the max
      readyToRoll = true;     //you are ready to roll over

   if (readyToRoll == true && now < HALF_MILLIS){
      numRollovers++;         //if we've previously made it to halfway and the current millis() 
      readyToRoll = false;    //value is now _less_ than the halfway mark then we have rolled over
   } 

   return numRollovers;
}

//Return the elapsed time (in seconds) since the function has been set considering that millis() function have a maximum value
double time(bool set){
  static double time_0 = 0;
  static int lastRollover = 0;

  if(set){                                //the function time is set to 0
    time_0 = millis();                    //set time_0 to actual time
    lastRollover = millisRollover();      //read the number of rollovers for the function millis()
    return 0;
  }
  
  int numRollovers = millisRollover();          //read the actual number of rollovers
  if(lastRollover == numRollovers)              //and compare it to the last number of rollovers
    return (millis()-time_0)/1000;              //return the elapsed time (in seconds) since the function has been set
  
  lastRollover = numRollovers;                  //set the last rollover function to actual rollover 
                                                //if the millis function has rotated

  return ((MAX_MILLIS-time_0)+millis())/1000;   //return the elapsed time (in seconds) since the function has been set
}

#endif