#ifndef CONFIG_H
#define CONFIG_H

// Microcontroller pinout
#define PWM_OUT 3
#define THERMISTOR A0

//Select if the microcontrollore is Master or Slave
#define SLAVE_NUM 4                                 //The number of the slaves
const int SLAVE_ADDR {0x01, 0x02, 0x03, 0x04}        //The address of the slaves

//Define the aggressive and conservative Tuning Parameters
const double aggKp = 4, aggKi = 0.2, aggKd = 1;
const double consKp = 1, consKi = 0.05, consKd = 0.25;

#endif