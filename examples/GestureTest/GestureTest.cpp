/****************************************************************
GestureTest.ino
APDS-9960 RGB and Gesture Sensor
Shawn Hymel @ SparkFun Electronics
May 30, 2014
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor

Tests the gesture sensing abilities of the APDS-9960. Configures
APDS-9960 over I2C and waits for gesture events. Calculates the
direction of the swipe (up, down, left, right) and displays it
on a serial console. 

To perform a NEAR gesture, hold your hand
far above the sensor and move it close to the sensor (within 2
inches). Hold your hand there for at least 1 second and move it
away.

To perform a FAR gesture, hold your hand within 2 inches of the
sensor for at least 1 second and then move it above (out of
range) of the sensor.

Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt

Resources:
Include Wire.h and SparkFun_APDS-9960.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

//#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void setup() {

  // Set interrupt pin as input
  //pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  //Serial.begin(9600);
  printf("\n");
  printf("--------------------------------\n");
  printf("SparkFun APDS-9960 - GestureTest\n");
  printf("--------------------------------\n");
  
  // Initialize interrupt service routine
  //attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    printf("APDS-9960 initialization complete\n");
  } else {
    printf("Something went wrong during APDS-9960 init!\n");
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    printf("Gesture sensor is now running\n");
  } else {
    printf("Something went wrong during gesture sensor init!\n");
  }
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        printf("************** UP ***************\n");
        break;
      case DIR_DOWN:
        printf("************** DOWN **************\n");
        break;
      case DIR_LEFT:
        printf("************** LEFT **************\n");
        break;
      case DIR_RIGHT:
        printf("************** RIGHT **************\n");
        break;
      case DIR_NEAR:
        printf("************** NEAR **************\n");
        break;
      case DIR_FAR:
        printf("************** FAR **************\n");
        break;
      default:
        printf("************** NONE **************\n");
    }
  }
}

int main(int argc, char **argv) {
    setup();
    for(;;) {
        handleGesture();
        usleep(100000);
    }
    return 0;
}

