/********************
 * 
 * Light intensity measurement using a simple Arduino setup
 * PHOTO_PIN: Define the pin where the photoresistor's resistance value is to be measured. The default is A0
 * Use a program like minicom with the right port (/dev/ttyACM*) to get the light intensity values
 * 
 ********************/

#define PHOTO_PIN A0


int photoPin = PHOTO_PIN;

int val = 0; // light intensity

void setup() {
  // Change the baud rate if desired
  Serial.begin(9600);
}

void loop() {
  // read and print on the serial mon. Can be stored in a log file from there.
  val = analogRead(photoPin);
  Serial.println(val);
}
