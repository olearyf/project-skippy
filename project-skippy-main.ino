/*
 * Frances O'Leary 8/8/2020 - position tracking removed because a gyroscope is needed
 * 
 * This is preliminary code for project
 * skippy, a homemade model rocket flight
 * computer. Assuming the other tests (look in
 * the repo you found this code in) go well,
 * this should work. Emphasis on should.
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
float baseZ; //used to account for acceleration due to gravity
float baseAlt; //used to get altitude relative to the altitude the user is at

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Project Skippy Flight Computer Starting. . .");
  
  // set pins
  pinMode(redLED, OUTPUT);
  pinMode(loggingLED, OUTPUT);
  digitalWrite(loggingLED, LOW);
  digitalWrite(redLED, LOW);

  // see if card can be initialized
  if (!SD.begin(cardSelect)) {
    Serial.println("Card not found.");
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
    Serial.print("Couldn't create the file: "); 
    Serial.println(filename);
    return;
  }
  Serial.print("Writing to the file: "); 
  Serial.println(filename);
  // write data schema on top line of file
  logfile.println("time(sec),pressure(pa),altitude(m),temperature(C),xAcceleration(m/s^2),yAcceleration(m/s^2),zAcceleration(m/s^2)");

  Serial.println("Initializing sensors now. . . ");

  // attempt to connect to acceleromter at I2C address 0x18
  if (! acceleromter.begin(0x18)) { // if fails, try 0x19 as an alternative, or use address debugger
    digitalWrite(redLED, HIGH);
    Serial.println("Could not initialize accelerometer.");
    return;
  }
  Serial.println("Successfully connected to accelerometer!");

  
  if (!pressureSensor.begin()) {
    digitalWrite(redLED, HIGH);
    Serial.println("Altimeter could not be intialized.");
    return;
  }
  Serial.println("Successfully connected to altimeter!");

  // options: 2, 4, 8, 16, read up on model rockets
  acceleromter.setRange(LIS3DH_RANGE_8_G);
  Serial.print("Accelerometer Range = "); Serial.print(2 << acceleromter.getRange());
  Serial.println("G");

  acceleromter.setDataRate(LIS3DH_DATARATE_50_HZ);
  Serial.println("Accelerometer data rate set to 50 Hz.");

  // get base measurements
  sensors_event_t event;
  acceleromter.getEvent(&event);
  baseZ = event.acceleration.z;
  baseAlt = pressureSensor.getAltitude();
  dataLoggingStartTime = millis();

  // set pins
  pinMode(redLED, OUTPUT);
  digitalWrite(loggingLED, LOW);
  
  Serial.println("Project Skippy is initialized and ready!");
  digitalWrite(loggingLED, HIGH);
}

void loop() {
  time = (float)(millis() - dataLoggingStartTime) / 1000.0; // convert to seconds
  pressure = pressureSensor.getPressure();
  altitude = pressureSensor.getAltitude() - baseAlt;
  temperature = pressureSensor.getTemperature();
  sensors_event_t event;
  acceleromter.getEvent(&event);
  xAcceleration = event.acceleration.x;
  yAcceleration = event.acceleration.y;
  zAcceleration = event.acceleration.z - baseZ;

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
    exit(0);
  }
  delay(100);
}
