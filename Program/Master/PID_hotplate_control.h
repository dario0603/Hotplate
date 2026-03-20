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
#include <AverageThermistor.h>
#include <SmoothThermistor.h>

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
Thermistor* therm = NULL;

//Set the average thermistor reading or the smooth thermistor reading
bool smooth = true;

//Functions---------------------------------------

//Setup all the internal variables for the PID_HOTPLATE_CONTROL library
void PID_hotplate_setup(){

  //Set the baud rate for serial comunication
  Serial.begin(BAUD_RATE);

  //assigns the pin, with a fixed frequency and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(HOTPLATE_PIN, PWM_FREQ, 0);

  //Assign the pin, whit all the sensor parameters
  Thermistor* origin_therm = new NTC_Thermistor(THERMISTOR_PIN, REFERENCE_RESISTANCE, NOMINAL_RESISTANCE, NOMINAL_TEMPERATURE, B_VALUE, ADC_RESOLUTION);

  if(smooth)
    therm = new SmoothThermistor(origin_therm, SMOOTHING_FACTOR);
  else
    therm = new AverageThermistor(origin_therm, READINGS_NUMBER, DELAY_TIME);

  //Set the right output limits for the PWM signal
  mytermo.SetOutputLimits(MIN_OUTPUT_LIMIT, MAX_OUTPUT_LIMIT);

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
bool heat_reflow_profile(double cKp, double cKd, double cKi, double aKp, double aKd, double aKi){

  bool exit = false;

  Setpoint = myfunction.value(time(false), exit);

  //The dafault Reflow function is in °C, for °K reset the reflow function and rewrite this function whit
  //
  //Fahreneit measures: therm.readFahrenheit()
  //Kelvin measures: therm.readKelivn()
  
  Input = therm -> readCelsius();
  
  if(!exit){
    
    PID_control(cKp, cKd, cKi, aKp, aKd, aKi);

    Serial.print("Input:");
    Serial.print(Input);
    Serial.print(" ");

    Serial.print("Output:");
    Serial.print(Output);
    Serial.print(" ");

    Serial.print("Setpoint:");
    Serial.println(Setpoint);

  }
  
  return exit;

}

//Function to turn off the hotplate
void turn_off_hotplate(){

  mytermo.SetMode(MANUAL);         //Turn the PID off
  PWM_Instance -> setPWM(HOTPLATE_PIN, PWM_FREQ, 0);   //Set the duty cycle of the output signal to 0%

}

//Function to turn on the hotplate
void turn_on_hotplate(){

  mytermo.SetMode(MANUAL);         //Turn the PID off
  PWM_Instance -> setPWM(HOTPLATE_PIN, PWM_FREQ, 100);   //Set the duty cycle of the output signal to 100%

  Serial.print("Temperature:");                          //Read the actual temperature in °C
  Serial.println(therm -> readCelsius());

}

//Function to set a constant temperature as setpoint
void set_temp(double cKp, double cKd, double cKi, double aKp, double aKd, double aKi, int temperature){

  Setpoint = temperature;

  //The dafault Reflow function is in °C, for °K reset the reflow function and rewrite this function whit
  //
  //Fahreneit measures: therm.readFahrenheit()
  //Kelvin measures: therm.readKelivn()
  
  Input = therm -> readCelsius();
  
  PID_control(cKp, cKd, cKi, aKp, aKd, aKi);

  Serial.print("Input:");
  Serial.print(Input);
  Serial.print(" ");

  Serial.print("Output:");
  Serial.print(Output);
  Serial.print(" ");

  Serial.print("Setpoint:");
  Serial.println(Setpoint);

}

#endif
