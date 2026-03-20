#ifndef PID_HOTPLATE_CONTROL_H
#define PID_HOTPLATE_CONTROL_H

//External libraries---------------------------------------

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

//Reflow function library
#include <Reflow_function.h>

//PID library
#include <PID_v1.h>

//PWM signal generator library
#include <RP2040_PWM.h>

//Thermistor library
#include <Thermistor.h>
#include <NTC_Thermistor.h>

//Internal libraries---------------------------------------

//Contains all the parameters of the hotplate
#include "config.h"

//Actual time functions (in seconds)
#include "actual_time.h"

//Internal var---------------------------------------

//Create the extern Variables we'll be connecting to whit our PID controller
double Setpoint, Input, Output;

//Create the extern setup Tuning Parameters
PID mytermo(&Input, &Output, &Setpoint, 0, 0, 0, DIRECT);

//Link the extern reflow function
Reflow_function myfunction;

//Link the extern PWM instance
RP2040_PWM* PWM_Instance;

//Link the extern Thermistor istance
Thermistor* therm;

//Functions---------------------------------------

//Setup all the internal variables for the PID_HOTPLATE_CONTROL library
void PID_hotplate_setup(){

  //Set the baud rate for serial comunication
  Serial.begin(9600);

  //assigns the pin, with a fixed frequency and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(HOTPLATE_PIN, PWM_FREQ, 0);

  //Assign the pin, whit all the sensor parameters
  therm = new NTC_Thermistor(THERMISTOR_PIN, REFERENCE_RESISTANCE, NOMINAL_RESISTANCE, NOMINAL_TEMPERATURE, B_VALUE, ADC_RESOLUTION);

  //Set the right output limits for the PWM signal
  mytermo.SetOutputLimits(0, 100);

}

//Control the output of the PID controller
void PID_control(double cKp, double cKd, double cKi, double aKp, double aKd, double aKi){

  double gap = abs(Setpoint-Input);   //distance away from setpoint
  mytermo.SetMode(AUTOMATIC);         //Turn the PID on

  if (gap < 10)  
    //We're close to setpoint, use conservative tuning parameters
    mytermo.SetTunings(cKp, cKi, cKd);
  else
    //We're far from setpoint, use aggressive tuning parameters
    mytermo.SetTunings(aKp, aKi, aKd);
  
  mytermo.Compute();

  //Set the PWM frequency and duty cycle of the output signal
  PWM_Instance -> setPWM(HOTPLATE_PIN, PWM_FREQ, Output);

}

//Start to heat the hotplate following the right reflow function
bool heat_hotplate(double cKp, double cKd, double cKi, double aKp, double aKd, double aKi){

  bool exit = false;

  Setpoint = myfunction.value(time(false), exit);

  //The dafault Reflow function is in °C, for °K reset the reflow function and rewrite this function whit
  //
  //Fahreneit measures: therm.readFahrenheit()
  //Kelvin measures: therm.readKelivn()
  
  Input = therm -> readCelsius();
  
  PID_control(cKp, cKd, cKi, aKp, aKd, aKi);

  Serial.print(Input);
  Serial.print(" ");
  Serial.print(Output);
  Serial.print(" ");
  Serial.println(Setpoint);
  
  return exit;

}

void turn_off_hotplate(){

  mytermo.SetMode(MANUAL);         //Turn the PID off
  PWM_Instance -> setPWM(HOTPLATE_PIN, PWM_FREQ, 0);   //Set the duty cycle of the output signal to 0%

}

#endif