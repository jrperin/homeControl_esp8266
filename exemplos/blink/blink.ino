/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

/*
GPIO0   = 0
GPIOTXD = 1
GPIO2   = 2
GPIORXD = 3
*/

#define pinOut 3


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pinOut as an output.
  pinMode(pinOut, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pinOut, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(pinOut, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
