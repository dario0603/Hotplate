#ifndef PID_HOTPLATE_CONTROL_H
#define PID_HOTPLATE_CONTROL_H

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

double Setpoint, Input, Output;

//Link the extern reflow function
extern Reflow_function myfunction;

//Link the extern setup Tuning Parameters
extern PID mytermo(&Input, &Output, &Setpoint, consKp, consKd, consKi, DIRECT);

//Link the extern PWM instance
extern RP2040_PWM* PWM_Instance;

//Link the extern Thermistor istance
extern Thermistor* therm;

//Control the output of the PID controller
void PID_control(double cKp, double cKd, double cKi, double aKp, double aKd, double aKi){

  double gap = abs(Setpoint-Input); //distance away from setpoint

  if (gap < 10)  
    //We're close to setpoint, use conservative tuning parameters
    mytermo.SetTunings(cKp, cKi, cKd);
  else
    //We're far from setpoint, use aggressive tuning parameters
    mytermo.SetTunings(aKp, aKi, aKd);
  
  mytermo.Compute();

  //Set the PWM frequency and duty cycle of the output signal
  PWM_Instance -> setPWM(HOTPLATE_OUT, PWM_FREQ, Output);
}

//Start to heat the hotplate following the right reflow function
bool heat_hotplate(double cKp, double cKd, double cKi, double aKp, double aKd, double aKi){
  bool exit = false;

  Setpoint = myfunction.value(time(false), exit);

  //The dafault Reflow function is in °C, for °K reset the reflow function and rewrite this function whit
  //
  //Fahreneit measures: therm.readFahrenheit()
  //Kelvin measures: therm.readKelivn()
  
  Input = therm.readCelsius();
  
  PID_control(cKp ,cKd ,cKi ,aKp ,aKd ,aKi );

  Serial.print(Input);
  Serial.print(" ");
  Serial.print(Output);
  Serial.print(" ");
  Serial.println(Setpoint);
  
  return exit;
}

#endif