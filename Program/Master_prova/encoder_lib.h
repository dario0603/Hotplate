#ifndef ENCODER_LIB_H
#define ENCODER_LIB_H

//External libraries---------------------------------------

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

//Internal libraries---------------------------------------

//Contains all the parameters of the hotplate
#include "config.h"

//Internal var---------------------------------------

//Actual button state
//If the actual button state is different from the past button state
//the button has been pressed
bool actual_button_state = false;

//Past button state
bool past_button_state = false;

//Set the direction of rotation
//false --> clockwise decrease, counterclockwise increase
//true --> counterclockwise decrease, clockwise increase
bool direction = false;

//Counter for the encoder value
int cont = MIN_CONT_VALUE;

//Functions---------------------------------------

// rotary encoder pin change interrupt handler
void modify_encoder_value(){

  //Read the actual value of the encoder B pin
  bool B_value = digitalRead(ENC_B_PIN);

  //Check the direction of rotation
  if(B_value == direction)

    if(cont < MAX_CONT_VALUE)
      cont++;
    else
      cont = MIN_CONT_VALUE;
  else

    if(cont > MIN_CONT_VALUE)
      cont--;
    else
      cont = MAX_CONT_VALUE;

}

void encoder_button(){

  //Change the actual state of the button (PRESSED, UNPRESSED)
  actual_button_state = !actual_button_state;

}

// rotary encoder initialization
void encoder_setup(){

  //Set the encoder pin as input pin
  pinMode(ENC_A_PIN, INPUT);
  pinMode(ENC_B_PIN, INPUT);
  pinMode(ENC_BUTTON_PIN, INPUT);

  //Set the encoder button pin and the encoder A pin as interrupt pin
  attachInterrupt(ENC_A_PIN, modify_encoder_value, RISING);
  attachInterrupt(ENC_BUTTON_PIN, encoder_button, RISING);

  //set the initial value of button state
  actual_button_state = false;
  
}

//Verify if the button has been pressed
//If so reset the state of the button
bool button_pressed(){

  if(past_button_state == actual_button_state)
    return false;
  
  past_button_state = actual_button_state;
  return true;

}

#endif
