/*
 * Frances O'Leary, 8/2/2020
 * 
 * This is a sanity check for reading data
 * from an accelerometer and an altimeter at
 * the same time using 1 I2C bus. It prints out data
 * from both sensors.
 */

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_LIS3DH acceleromter = Adafruit_LIS3DH();
Adafruit_MPL3115A2 pressureSensor = Adafruit_MPL3115A2();
float pressurePascals;
float altitude;
float temperature;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Beginning combined accelerometer/altimeter diagnostic test. . . ");

 // attempt to connect to acceleromter at I2C address 0x18
  if (! acceleromter.begin(0x18)) { // if fails, try 0x19 as an alternative, or use address debugger
    Serial.println("Could not initialize accelerometer.");
    return;
  }
  Serial.println("Successfully connected to accelerometer!");

  
  if (!pressureSensor.begin()) {
    Serial.println("Altimeter could not be intialized.");
    return;
  }
  Serial.println("Successfully connected to altimeter!");

  // options: 2, 4, 8, 16, read up on model rockets
  acceleromter.setRange(LIS3DH_RANGE_4_G);
  Serial.print("Accelerometer Range = "); Serial.print(2 << acceleromter.getRange());
  Serial.println("G");

  acceleromter.setDataRate(LIS3DH_DATARATE_50_HZ);
  Serial.print("Accelerometer data rate set to 50 Hz.");

  Serial.println("Done with setup!");
}

void loop() {
  Serial.println("Accelerometer Data: ");
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

  Serial.println();
  Serial.println("Altimeter data: ");
  
  // get pressure
  pressurePascals = pressureSensor.getPressure();
  Serial.print("Pressure: ");
  Serial.print(pressurePascals / 3377);
  Serial.println(" Inches (Hg) ");

  //get altitude
  altitude = pressureSensor.getAltitude();
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" meters");

  // get temperature
  temperature = pressureSensor.getTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("*C");

  Serial.println("-----------------------------------------------");
  delay(200);
}
