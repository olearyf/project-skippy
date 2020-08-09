/*
 * Frances O'Leary 8/9/2020
 * 
 * This is code for project
 * skippy(V1), a homemade model rocket flight
 * computer. It logs data such as time since it
 * started logging, pressure, altitude, temperature, and xyz
 * accelertation in a csv file. It is intended to be used in conjunction
 * with SkippyParser.py, which plots the data.
 * 
 * Flow:
 *  - turn on device
 *  - if all goes well, green LED will turn on
 *  - device logs data for 10 minutes
 *  - logging stops (green LED off)
 *  - file closed
 *  - sketch terminates
 */

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <Adafruit_MPL3115A2.h>

#define cardSelect 4
#define loggingLED 11
#define redLED 13


Adafruit_LIS3DH acceleromter = Adafruit_LIS3DH();
Adafruit_MPL3115A2 pressureSensor = Adafruit_MPL3115A2();
File logfile;
char filename[20];
float dataLoggingStartTime;
// data definitions
float time; // seconds
float pressure; // pascals
float altitude; // meters
float temperature; // degrees c
float xAcceleration; // m/s^2
float yAcceleration; // m/s^2
float zAcceleration; // m/s^2
float baseX; // to account for position of accelerometer
float baseY; // to account for position of accelerometer
float baseZ; //used to account for acceleration due to gravity

void setup() {
  
  // set pins
  delay(500);
  pinMode(redLED, OUTPUT);
  pinMode(loggingLED, OUTPUT);
  digitalWrite(loggingLED, LOW);
  digitalWrite(redLED, LOW);

  // see if card can be initialized
  if (!SD.begin(cardSelect)) {
    digitalWrite(redLED, HIGH);
    return;
  }

  // create filename that will not overwrite other flight data
  strcpy(filename, "/FLIGHT00.csv");
  for (uint8_t i = 0; i < 100; i++) {
    filename[7] = '0' + i/10;
    filename[8] = '0' + i%10;
    if (! SD.exists(filename)) {
      break;
    }
  }

  // attempt to open the file
  logfile = SD.open(filename, FILE_WRITE);
  if(!logfile) {
    digitalWrite(redLED, HIGH);
    return;
  }
  
  // write data schema on top line of file
  logfile.println("time(sec),pressure(pa),altitude(m),temperature(C),xAcceleration(m/s^2),yAcceleration(m/s^2),zAcceleration(m/s^2)");
  
  // attempt to connect to acceleromter at I2C address 0x18
  if (! acceleromter.begin(0x18)) { // if fails, try 0x19 as an alternative, or use address debugger
    digitalWrite(redLED, HIGH);
    return;
  }
  
  // options: 2, 4, 8, 16
  acceleromter.setRange(LIS3DH_RANGE_8_G);

  acceleromter.setDataRate(LIS3DH_DATARATE_50_HZ);

  // attempt to connect to pressure sensor
  if (!pressureSensor.begin()) {
    digitalWrite(redLED, HIGH);
    return;
  }

  // get base measurements
  sensors_event_t event;
  acceleromter.getEvent(&event);
  baseX = event.acceleration.x;
  baseY = event.acceleration.y;
  baseZ = event.acceleration.z;
  dataLoggingStartTime = millis();

  // set pins
  pinMode(redLED, OUTPUT);
  digitalWrite(loggingLED, LOW);

  // set LED to 'logging mode' (aka on)
  digitalWrite(loggingLED, HIGH);
}

void loop() {
  // get data
  time = (float)(millis() - dataLoggingStartTime) / 1000.0; // convert to seconds
  pressure = pressureSensor.getPressure();
  pressure = pressureSensor.getPressure();
  altitude = pressureSensor.getAltitude();
  altitude = pressureSensor.getAltitude();
  temperature = pressureSensor.getTemperature();
  temperature = pressureSensor.getTemperature();
  sensors_event_t event;
  acceleromter.getEvent(&event);
  xAcceleration = event.acceleration.x - baseX; // adjust for base measurements
  yAcceleration = event.acceleration.y - baseY; // adjust for base measurements
  zAcceleration = event.acceleration.z - baseZ; // adjust for base measurements

  // print data to file in predefined data schema
  logfile.print(time);
  logfile.print(",");
  logfile.print(pressure);
  logfile.print(",");
  logfile.print(altitude);
  logfile.print(",");
  logfile.print(temperature);
  logfile.print(",");
  logfile.print(xAcceleration);
  logfile.print(",");
  logfile.print(yAcceleration);
  logfile.print(",");
  logfile.print(zAcceleration);
  logfile.print('\n');
  if (time >= 600.0) {
    logfile.close();
    digitalWrite(loggingLED, LOW);
    return;
  }
  delay(100);
}
