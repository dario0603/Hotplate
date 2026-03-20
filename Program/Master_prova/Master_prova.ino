
//External libraries---------------------------------------

//I2C Comunication library
#include <Wire.h>

//Internal libraries---------------------------------------

//Contains all the parameters of the hotplate
#include "config.h"

//PID controller functions
#include "PID_hotplate_control.h"

//Encoder functions
#include "encoder_lib.h"

//Actual time functions (in seconds)
#include "actual_time.h"

//Internal var---------------------------------------

//Create the actions that can be performed by the hotplate
enum Action{MANUAL_MOD, MODIFY, HEAT, TURN_ON, TURN_OFF, NONE};
Action operation = TURN_ON;  //set the default action to nothing

//Is needed during the heating to memorize if the time need to be set to zero
bool flag_set_time_to_zero = true;

//Setup function---------------------------------------

void setup(){

  //Set the serial comunication baud rate
  Serial.begin(BAUD_RATE);

  //Setup all the PID_HOTPLATE_CONTROL Library variables
  //(see PID_hotplate_control.h)
  PID_hotplate_setup();

  //Setup all the ENCODER Library variables
  //(see encoder_lib.h)
  encoder_setup();

}

//Loop function---------------------------------------

void loop(){
  
  while(true){

    Serial.print("encoder value:");
    Serial.println(cont);

    if(button_pressed()){
      conversion_enum_int(operation, cont);
      break;
    }

  }

  while(true){

    switch(operation){

        case MANUAL_MOD:
          operation = NONE;
          break;

        case MODIFY:
          operation = NONE;
          break;

        case HEAT:     //Heat the hotplates that needs to be heated

          if(flag_set_time_to_zero){
            myfunction.set_zero(time(true));
            flag_set_time_to_zero = false;
          }

          if(!heat_reflow_profile(consKp , consKd, consKi, aggKp, aggKd, aggKi))
            delay(10);
          else{
            operation = TURN_OFF;
            flag_set_time_to_zero = true;
          }

          if(button_pressed()){
            turn_off_hotplate();
            operation = NONE;
          }
          
          break;

        case TURN_ON:

          flag_set_time_to_zero = true;
          turn_on_hotplate();
          //set_temp(consKp , consKd, consKi, aggKp, aggKd, aggKi, 40);

          if(button_pressed()){
            turn_off_hotplate();
            operation = NONE;
          }

          break;

        case TURN_OFF:

          flag_set_time_to_zero = true;
          turn_off_hotplate();
          operation = NONE;

          break;

        default:
          operation = NONE;
          break;
        
    }

    if(operation == NONE)
      break;
    
  }
}

//Functions---------------------------------------

void conversion_enum_int(Action &op_enum, int op_int){
  switch(op_int){

    case 0:
      op_enum = MANUAL_MOD;
      break;
    
    case 1:
      op_enum = MODIFY;
      break;
    
    case 2:
      op_enum = HEAT;
      break;
    
    case 3:
      op_enum = TURN_ON;
      break;
    
    case 4:
      op_enum = TURN_OFF;
      break;
    
    default:
      op_enum = NONE;
      break;
  }
}
