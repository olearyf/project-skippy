/*
 * Frances O'Leary, 8/1/2020
 * 
 * This file is a sanity check for your 32u4 Adalogger. It
 * makes the LED blink on and off.
 */

 // set up the pin to write to
void setup() {
  Serial.begin(115200);
  Serial.println("Test beginning!");
  pinMode(13, OUTPUT);
}
 
// blink a lot
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("LED on.");
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("LED off.");
  delay(1000);              // wait for a second
}
