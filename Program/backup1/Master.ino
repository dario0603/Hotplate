
//I2C Comunication library
#include <Wire.h>

//PID library
#include <PID_v1.h>

//PWM signal generator library
#include <RP2040_PWM.h>

//Thermistor library
#include <Thermistor.h>
#include <NTC_Thermistor.h>

//Reflow function library
#include <Reflow_function.h>

//Internal libraries
#include "actual_time.h"
#include "config.h"
#include "PID_hotplate_control.h"

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the setup Tuning Parameters
PID mytermo(&Input, &Output, &Setpoint, consKp, consKd, consKi, DIRECT);

//Creates PWM instance
RP2040_PWM* PWM_Instance;

//Creates Thermistor istance
Thermistor* therm;

//Create the dafeault reflow function
Reflow_function myfunction;

//Create the actions that can be performed by the hotplate
enum Action{MANUAL_MOD, MODIFY, TURN_ON, TURN_OFF, NONE};
Action operation = TURN_ON;  //set the default action to nothing

void setup() {
  //Set the baud rate for serial comunication
  Serial.begin(9600);

  //assigns the pin, with a fixed frequency and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(HOTPLATE_PIN, PWM_FREQ, 0);

  //Assign the pin, whit all the sensor parameters
  therm = new NTC_Thermistor(THERMISTOR_PIN, REFERENCE_RESISTANCE, NOMINAL_RESISTANCE, NOMINAL_TEMPERATURE, B_VALUE, ADC_RESOLUTION);

  //Turn the PID on
  mytermo.SetMode(AUTOMATIC);
  //Set the right output limits for the PWM signal
  mytermo.SetOutputLimits(0, 100);
}

void loop() {
  
  switch(operation){

      case MANUAL_MOD:
        break;

      case MODIFY:
        break;

      case TURN_ON:
        myfunction.set_zero(time(true));
        if(!heat_hotplate(consKp , consKd, consKi, aggKp, aggKd, aggKi))
          delay(10);
        else
          operation = NONE;
        break;

      case TURN_OFF:
        break;

      default:
        break;
      
  }
  
}
