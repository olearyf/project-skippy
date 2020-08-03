/*
 * Frances O'Leary, 8/1/2020
 * 
 * This program is a sanity check for a 32u4 Adalogger
 * and a MPL3115A2 pressure sensor. The objective is
 * to hook up the sensor and read some basic data.
 */
 
#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 pressureSensor = Adafruit_MPL3115A2();
float pressurePascals;
float altitude;
float temperature;

void setup() {
  Serial.begin(115200);
  Serial.println("Beginning MPL3115A2 diagnostic test. . . ");
}

void loop() {
  if (!pressureSensor.begin()) {
    Serial.println("Sensor could not be intialized.");
    return;
  }

  // get pressure
  pressurePascals = pressureSensor.getPressure();
  Serial.print("Pressure: ");
  Serial.print(pressurePascals / 3377);
  Serial.println(" Inches (Hg) ";

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
  
  delay(250);
}
