/*
 * Frances O'Leary, 8/1/2020
 * 
 * This is a sanity check to make sure
 * you can write data to a text file on
 * the micro sd card that is inserted into your
 * 32u4 Adalogger.
 */
 
#include <SPI.h>
#include <SD.h>

#define cardSelect 4
File outputFile;
char filename[15];
char fileContent[][] = {
  "Hello! This is the Adalogger SD card test!",
  "I hope you're having a great day!",
  "What are you making with your Adalogger?"
  "More precisely, what data are you logging?",
  "It's cool, you don't have to tell me if you don't want to.",
  "Hopefully this test works!",
  "Because then you'll be on your merry way with your project.",
  ":)"
};

void setup() {
  Serial.begin(115200);
  Serial.println("Beginning data logging test. . .");

  // for the onboard LED
  pinMode(13, OUTPUT);

  // check if the card is there:
  if (!SD.begin(cardSelect)) {
    Serial.println("Micro SD card could not be located.");
    error(2);
  }

  // open or make the file
  strcpy(filename, "testdata.txt");
  outputFile = SD.open(filename, FILE_WRITE);
  if(!outputFile) {
    Serial.print("Couldn't create the file with name: "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to the file: "); 
  Serial.println(filename);

  pinMode(13, OUTPUT);
  Serial.println("Ready to write to the file!");
}

/*
 * Code to write to the file. Note there is currently
 * not error handling as this is a basic sanity check.
 * Writing to the file = success.
 */
void loop() {
  for (int i = 0; i < 8; i++) {
    outputFile.println(fileContent[i]);
  }
  Serial.println("Done writing to file.");
  return;
}
