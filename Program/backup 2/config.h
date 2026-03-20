#ifndef CONFIG_H
#define CONFIG_H



// Microcontroller pinout
#define HOTPLATE_PIN 22           //Hotplate mosfet pin
#define THERMISTOR_PIN 26         //NTC sensor pin
#define SDA_PIN
#define SCL_PIN



//NTC settings
#define REFERENCE_RESISTANCE    8000    //the pullup resistor to which the NTC is connected
#define NOMINAL_RESISTANCE      100000  //The nominal resistance of the NTC
#define NOMINAL_TEMPERATURE     25      //the temperature (in °C) of the NTC when the resistance is nominal
#define B_VALUE                 3950    //The beta value of the NTC thermistor
#define V_REFERENCE             3300    //Usually 3300mV for RP2040 and 5000mV for esp32
#define ADC_RESOLUTION          4095    //If you use the STM32 board, you must calibrate your thermistor, since the
                                        //analogRead(*) function return 0..4095 versus 0..1023 for Arduino.



//PWM settings
#define PWM_FREQ 2000       //the frequency of duty cicle is written in hertz



//Slave property
#define SLAVE_NUM 4                                 //The number of the slaves
const int SLAVE_ADDR[] {0x01, 0x02, 0x03, 0x04};        //The address of the slaves



//Define the aggressive and conservative Tuning Parameters for PID controller
const double aggKp = 4, aggKi = 0.2, aggKd = 1;
const double consKp = 1, consKi = 0.05, consKd = 0.25;



#endif