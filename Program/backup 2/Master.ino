
//External libraries---------------------------------------

//I2C Comunication library
#include <Wire.h>

//Internal libraries---------------------------------------

//Contains all the parameters of the hotplate
#include "config.h"

//Actual time functions (in seconds)
#include "actual_time.h"

//PID controller functions
#include "PID_hotplate_control.h"

//Internal var---------------------------------------

//Create the actions that can be performed by the hotplate
enum Action{MANUAL_MOD, MODIFY, TURN_ON, TURN_OFF, NONE};
Action operation = TURN_ON;  //set the default action to nothing

//Is needed during the heating to memorize if the time need to be set to zero
bool flag_set_time_to_zero = true;

//Setup function---------------------------------------

void setup() {

  //Setup all the PID_HOTPLATE_CONTROL Library variables
  //(see PID_hotplate_control.h)
  PID_hotplate_setup();

}

//Loop function---------------------------------------

void loop() {
  
  switch(operation){

      case MANUAL_MOD:
        break;

      case MODIFY:
        break;

      case TURN_ON:     //Heat the hotplates that needs to be heated

        if(flag_set_time_to_zero){
          myfunction.set_zero(time(true));
          flag_set_time_to_zero = false;
        }
        if(!heat_hotplate(consKp , consKd, consKi, aggKp, aggKd, aggKi))
          delay(10);
        else{
          operation = NONE;
          flag_set_time_to_zero = true;
        }
        
        break;

      case TURN_OFF:

        flag_set_time_to_zero = true;

        break;

      default:
        break;
      
  }
  
}
