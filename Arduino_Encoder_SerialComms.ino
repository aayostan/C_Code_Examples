// Include the encoder library and maps
#include "ACE128.h"  // Absolute Contact Encoder
#include <ACE128map12345678.h> // mapping for pin order 23456789
#include <Wire.h> // I2C bus communication library - required to support ACE128

// Constants
const double DEG_PER_VAL = 360.0 / 128.0;
const int MAGNET = 13;

// Globals
ACE128 encoder(2,3,4,5,6,7,8,9, (uint8_t*)encoderMap_12345678);

uint8_t pinPos = 0; 
uint8_t oldPos = 255;
int16_t mpos;
uint8_t seen = 0;

void setup() {
  encoder.begin();                  // this is required for each instance, initializes the pins
  pinPos = encoder.acePins();       // get IO expander pins
  oldPos = pinPos;                  // remember where we are

  pinMode(MAGNET, OUTPUT);
  digitalWrite(MAGNET, LOW);       // Magnet default is off
  
  Serial.begin(9600);
}


void loop() {
  pinPos = encoder.acePins();      // get IO expander pins
  mpos = encoder.mpos();            // get multiturn position - signed

  // This block of code handles changes in the encoder position
  if (pinPos != oldPos) {           // did we move?
    seen |= pinPos ^ oldPos;        // what changed?
    oldPos = pinPos;                // remember where we are
    if (seen < 255) {
      Serial.print('l');            // Searching for pins..
    } else {
      Serial.print('p');            // Indicate we are sending position
      Serial.println(mpos);         // Send absolute position
    }
  }
}

void serialEvent()
{
  char input = Serial.read();

  // This block of code handles incoming serial communications
  switch(input) {
    case 'f':
      encoder.setMpos(0);           // set logical multiturn zero to current position
      oldPos = 255;                 // force display update
      break;
    case 'd':
      digitalWrite(MAGNET, LOW);    // Turn off electromagnet
      break;
    case 'l':
      digitalWrite(MAGNET, HIGH);   // Turn on electromagnet
      break;
    case 'c':                       // Change unit
      oldPos = 255;
      break;
    case 's':                       // Stop
      while(1); // Infinite loop doing nothing until program restart
      break;
    default:                        // Error
      Serial.print('e');
      break;
  }  
}
