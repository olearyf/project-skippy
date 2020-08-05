/*
 * Frances O'Leary, 8/2/2020
 * 
 * This is a sanity check for reading data
 * from a acceleromter3DH acceleromter from a 32u4 Adalogger.
 * It prints out general data to the serial monitor using I2C.
 */
 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3DH acceleromter = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(115200);
  Serial.println("Beginning the LIS3DH Accelerometer test!");

 // attempt to connect to sensor at I2C address 0x18
  if (! acceleromter.begin(0x18)) { // when trying multiple sensors on our I2C pin set up, try 0x19 as an alternative
    Serial.println("Could not initialize sensor.");
    return;
  }
  Serial.println("Successfully connected to sensor!");

  // options: 2, 4, 8, 16, read up on model rockets
  acceleromter.setRange(LIS3DH_RANGE_4_G);
  Serial.print("Sensor Range = "); Serial.print(2 << acceleromter.getRange());
  Serial.println("G");

  acceleromter.setDataRate(LIS3DH_DATARATE_50_HZ);
  Serial.print("Data rate set to 50 Hz.");

  Serial.println("Done with setup!");
}

void loop() {
  // testing group data collection
  acceleromter.read();
  Serial.print("X:  "); 
  Serial.println(acceleromter.x);
  Serial.print("Y:  ");
  Serial.println(acceleromter.y);
  Serial.print("Z:  ");
  Serial.println(acceleromter.z);

  // testing event data collection
  sensors_event_t event;
  acceleromter.getEvent(&event);
  Serial.println("Event data (m/2^2): ");
  Serial.print("X: "); 
  Serial.println(event.acceleration.x);
  Serial.print("Y: ");
  Serial.println(event.acceleration.y);
  Serial.print("Z: ");
  Serial.println(event.acceleration.z);

  Serial.println("-----------------------------------------------");
  delay(200);
}
