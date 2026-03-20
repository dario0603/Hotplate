#ifndef I2C_COMMUNICATION_H
#define I2C_COMMUNICATION_H

//External libraries---------------------------------------

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

//I2C function library
#include <Wire.h>

//Internal var---------------------------------------

int slave_num = 0;

//Functions---------------------------------------

void I2C_communication_setup(){
  Wire.begin();
}



#endif