# photoresistor-measurement

Code for a very simple Arduino setup involving light intensity measurement using a photoresistor. Makes use of a voltage divider circuit in which the reading of the voltage is directly proportional to the intensity of light incident on the photoresistor.

Needs 
- the Arduino IDE, and 
- minicom
to be installed. Make sure that the following are correctly specified:
- The Arduino board type (Uno, Mega 2560, etc.)
- Baud rate (Default = 9600 bps)
- Serial port (Default: /dev/ttyACM0)

To log the values, either use minicom's inbuilt logging system or install pySerial.

See [this](https://www.instructables.com/id/How-to-use-a-photoresistor-or-photocell-Arduino-Tu/) link for reference.
