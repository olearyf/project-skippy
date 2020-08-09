/*
 * Frances O'Leary, 8/8/2020
 * 
 * This is a battery test to see the voltage
 * of your Skippy Flight Computer battery.
 */
 
#define VBATPIN A9

void setup(){
  Serial.begin(9600);
  while(!Serial);
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024.0; // convert to voltage
  Serial.print("VBat: " ); Serial.println(measuredvbat);
}

void loop() {
  // do nothing
}
