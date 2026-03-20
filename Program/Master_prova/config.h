#ifndef CONFIG_H
#define CONFIG_H



//Serial comunication
#define BAUD_RATE 9600                //Baud rate for the serial comunication



//Microcontroller pinout
#define HOTPLATE_PIN 17               //Hotplate mosfet pin
#define THERMISTOR_PIN 27             //NTC sensor pin
#define ENC_A_PIN 18                  //Pin data A of the encoder
#define ENC_B_PIN 19                  //Pin data B of the encoder
#define ENC_BUTTON_PIN 20             //Button pin of the encoder
#define SDA_PIN
#define SCL_PIN



//NTC settings
#define REFERENCE_RESISTANCE    1005   //the pullup resistor to which the NTC is connected
#define NOMINAL_RESISTANCE      100000  //The nominal resistance of the NTC
#define NOMINAL_TEMPERATURE     25      //the temperature (in °C) of the NTC when the resistance is nominal
#define B_VALUE                 3950    //The beta value of the NTC thermistor
#define V_REFERENCE             3300    //Usually 3300mV for RP2040 and 5000mV for esp32
#define ADC_RESOLUTION          1023    //If you use the STM32 board, you must calibrate your thermistor, since the
                                        //analogRead(*) function return 0..4095 versus 0..1023 for Arduino.

#define READINGS_NUMBER 15               //How many readings are taken to determine a mean temperature.
                                        //The more values, the longer a calibration is performed,
                                        //but the readings will be more accurate.

#define DELAY_TIME 10                   //Delay time between a temperature readings
                                        //from the temperature sensor (ms).

#define SMOOTHING_FACTOR 5              //Smoothing factor of a temperature value.



//PWM settings
#define PWM_FREQ 1000       //the frequency of duty cicle is written in hertz
#define MIN_OUTPUT_LIMIT 0   //the minimum percentage value of output limit
#define MAX_OUTPUT_LIMIT 90   //the maximum percentage value of output limit



//Slave property
#define SLAVE_NUM 4                                 //The number of the slaves
const int SLAVE_ADDR[] {0x01, 0x02, 0x03, 0x04};        //The address of the slaves



//Encoder library constant
#define MAX_CONT_VALUE 5          //Max value that the encoder can count
#define MIN_CONT_VALUE 0          //Min value that the encoder can count



//PID library constant
bool smooth = false;               //Set the average thermistor reading (false) or the smooth thermistor reading (true)
#define DATA_GRAPH_TIME 100        //Set the time for sending data to plot temperature

//this is the max millis value (17179868 for earlier versions of Arduino)
const unsigned long int MAX_MILLIS = 4294967295;

//this is halfway to the max millis value (17179868 for earlier versions of Arduino)
const unsigned long int HALF_MILLIS = 2147483647;   

//Define the aggressive and conservative Tuning Parameters for PID controller
const double aggKp = 2.0, aggKi = 0.2, aggKd = 1.0;
const double consKp = 1.0, consKi = 0.5, consKd = 0.3;



#endif
