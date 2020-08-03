/*
 * Frances O'Leary 8/2/2020
 * 
 * This is preliminary code for project
 * skippy, a homemade model rocket flight
 * computer. Assuming the other tests (look in
 * the repo you found this code in) go well,
 * this should work. Emphasis on should.
 * 
 * Flow:
 *  - turn on device
 *  - turn on logging (green LED is on)
 *  - device logs data
 *  - turn off logging (green LED off)
 *  - turn off data
 *  - turn on again to log new file if you wish
 */
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_acceleromter3DH.h>
#include <Adafruit_Sensor.h>
#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <Adafruit_MPL3115A2.h>

#define cardSelect 4
#define dataLoggingPin 5
#define loggingLED 11


Adafruit_acceleromter3DH acceleromter = Adafruit_acceleromter3DH();
Adafruit_MPL3115A2 pressureSensor = Adafruit_MPL3115A2();
boolean isFinishedLogging = false;
boolean isLogging = false;
File logfile;
char filename[20];
unsigned long dataLoggingStartTime;
// data definitions
unsigned long time;
float pressure; // inches Hg
float altitude; // meters
float temperature; // degrees c
float xAcceleration; // m/s^2
float yAcceleration; // m/s^2
float zAcceleration; // m/s^2
// loosely calculated
float xPosition; // meters
float yPosition; // meters
float zPosition; // meters

void setup() {
  Serial.begin(115200);
  Serial.println("Project Skippy Flight Computer Starting. . .");

  // see if card can be initialized
  if (!SD.begin(cardSelect)) {
    Serial.println("Card not found.");
    error(2);
  }

  // create filename that will not overwrite other flight data
  strcpy(filename, "/flightdata00.txt");
  for (uint8_t i = 0; i < 100; i++) {
    filename[11] = '0' + i/10;
    filename[12] = '0' + i%10;
    if (! SD.exists(filename)) {
      break;
    }
  }

  // attempt to open the file
  logfile = SD.open(filename, FILE_WRITE);
  if(!logfile) {
    Serial.print("Couldn't create the file: "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to the file: "); 
  Serial.println(filename);
  // write data schema on top line of file
  logfile.println("time(ms)#pressure(in Hg)#altitude(m)#temperature(C)#xAcceleration(m/s^2)#yAcceleration(m/s^2)#zAcceleration(m/s^2)#xposition(m)#yposition(m)#zposition(m)");

  Serial.println("Initializing sensors now. . . ");

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
  acceleromter.setRange(acceleromter3DH_RANGE_8_G);
  Serial.print("Accelerometer Range = "); Serial.print(2 << acceleromter.getRange());
  Serial.println("G");

  acceleromter.setDataRate(acceleromter3DH_DATARATE_50_HZ);
  Serial.print("Accelerometer data rate set to 50 Hz.");

  // set pins
  pinMode(13, OUTPUT);
  pinMode(loggingLED, OUTPUT);
  pinMode(dataLoggingPin, INPUT);
  
  Serial.println("Project Skippy is initialized and ready!");
}

uint8_t i=0;
void loop() {
  /*
   * If it is logging but the logging switch has been moved to 'off',
   * close the file and end the program.
   */
  if (digitalRead(dataLoggingPin == 0 && isLogging = true) {
    isFinishedLogging = true;
    isLogging = false;
    digitalWrite(loggingLED, LOW);
    logfile.close();
    return;
  }

  /*
   * If logging switch is on, write th data to the file.
   */
  if (digitalRead(dataLoggingPin) == 1) {
    if (isLogging == false) {
      isLogging = true;
      // set logging LED to 'on'
      digitalWrite(loggingLED, HIGH);
      dataLoggingStartTime = millis();
    }
    // get data to log
    time = millis() - dataLoggingStartTime;
    pressure = pressureSensor.getPressure() / 3377;
    altitude = pressureSensor.getAltitude();
    temperature = pressureSensor.getTemperature();
    sensors_event_t event;
    acceleromter.getEvent(&event);
    xAcceleration = event.acceleration.x;
    yAcceleration = event.acceleration.y;
    zAcceleration = event.acceleration.z;
    /*
     * Calculate position, converting time to seconds
     * and assuming initial velocity and position
     * components to all be 0.
     */
    xPosition = 0.5 * xAcceleration * (time / 1000);
    yPosition = 0.5 * yAcceleration * (time / 1000);
    zPosition = 0.5 * zAcceleration * (time / 1000);

    // print data to file in predefined data schema
    logfile.print(time);
    logfile.print("#");
    logfile.print(pressure);
    logfile.print("#");
    logfile.print(altitude);
    logfile.print("#");
    logfile.print(temperature);
    logfile.print("#");
    logfile.print(xAcceleration);
    logfile.print("#");
    logfile.print(yAcceleration);
    logfile.print("#");
    logfile.print(zAcceleration);
    logfile.print("#");
    logfile.print(xPosition);
    logfile.print("#");
    logfile.print(yPosition);
    logfile.print("#");
    logfile.print(zPosition);
    logfile.print('\n');

    delay(100);
  }
}

// blink out an error code if one occurs
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}
