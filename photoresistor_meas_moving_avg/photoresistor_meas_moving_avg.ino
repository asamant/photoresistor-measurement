/********************
 * 
 * Light intensity measurement using a simple Arduino setup
 * PHOTO_PINx: Define the pins where the photoresistor's resistance values are to be measured. The defaults are A0, A1, and A2
 * Use a program like minicom with the right port (/dev/ttyACMx) to get the light intensity values
 * 
 * Moving average reference: https://www.arduino.cc/en/Tutorial/Smoothing
 * We use a moving average filter because light intensity measurements from the photoresistor are quite noisy in general.
 * 
 ********************/

#include "Plotter.h" // Optional

#define NUM_PHOTO_PINS 3
#define PHOTO_PIN_0 A0
#define PHOTO_PIN_1 A1
#define PHOTO_PIN_2 A2
#define MOV_AVG_WINDOW_SIZE 10

// ***************** VARIABLES *********************************

Plotter p;

int photoPin0 = PHOTO_PIN_0;
int photoPin1 = PHOTO_PIN_1;
int photoPin2 = PHOTO_PIN_2;

int rawVals[NUM_PHOTO_PINS]; // Array holding the raw intensity values from the pins

int readings[NUM_PHOTO_PINS][MOV_AVG_WINDOW_SIZE];      // the readings from the analog input pins
int readIndex = 0;              // the index of the current reading
int total[NUM_PHOTO_PINS];                  // the running totals 
int average[NUM_PHOTO_PINS];                // the average values


// ******************* SETUP *******************************

void setup() {
    // Change the baud rate if desired
  Serial.begin(9600);

  //p.Begin();
  //p.AddTimeGraph("Light intensity (voltage)", 500, "Samples", average); 
}


// ****************** RUNNING (MAIN) LOOP ***********************

void loop() {
  // read analog input
  rawVals[0] = analogRead(photoPin0);
  rawVals[1] = analogRead(photoPin1);
  rawVals[2] = analogRead(photoPin2);
  
  // If more pins are added, add analogRead(photoPinX) statements here accordingly.

  for (int pinIndex = 0; pinIndex < NUM_PHOTO_PINS; ++pinIndex){
      
      // subtract the last reading:
      total[pinIndex] = total[pinIndex] - readings[pinIndex][readIndex];

      // read from the sensor:
      readings[pinIndex][readIndex] = rawVals[pinIndex];
      
      // add the reading to the total:
      total[pinIndex] = total[pinIndex] + readings[pinIndex][readIndex];
  
      // advance to the next position in the array:
      readIndex = readIndex + 1;

      // if we're at the end of the array...
      if (readIndex >= MOV_AVG_WINDOW_SIZE) {
        // ...wrap around to the beginning:
        readIndex = 0;
      }

      // calculate the average:
      average[pinIndex] = total[pinIndex] / MOV_AVG_WINDOW_SIZE; 
  }
  
  //p.Plot();
  // Serial.print("val=")

  /*SUPER HACK - refer to https://forum.arduino.cc/index.php?topic=448426.0; it's for setting the upper and lower limits on the serial plotter
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1000);  // To freeze the upper limit
  Serial.print(" ");
  */

  Serial.print(average[0]);
  Serial.print(" ");
  Serial.print(average[1]);
  Serial.print(" ");
  Serial.println(average[2]);
}
