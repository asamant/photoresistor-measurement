/********************
 * 
 * Light intensity measurement using a simple Arduino setup
 * PHOTO_PIN: Define the pin where the photoresistor's resistance value is to be measured. The default is A0
 * Use a program like minicom with the right port (/dev/ttyACM*) to get the light intensity values
 * 
 * Moving average reference: https://www.arduino.cc/en/Tutorial/Smoothing
 * 
 ********************/

#include "Plotter.h"

#define PHOTO_PIN A0
#define MOV_AVG_WINDOW_SIZE 5

Plotter p;

int photoPin = PHOTO_PIN;

int val = 0; // light intensity

int readings[MOV_AVG_WINDOW_SIZE];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
    // Change the baud rate if desired
  Serial.begin(9600);

  //p.Begin();
  //p.AddTimeGraph("Light intensity (voltage)", 500, "Samples", average); 
}

void loop() {
  // read analog input
  int rawVal = analogRead(photoPin);
  
  // subtract the last reading:
  total = total - readings[readIndex];
  
  // read from the sensor:
  readings[readIndex] = rawVal;
  
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= MOV_AVG_WINDOW_SIZE) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / MOV_AVG_WINDOW_SIZE; 
  
  //p.Plot();
  // Serial.print("val=")
  Serial.println(average);
}
