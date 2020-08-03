# About
This folder, known as Tests houses all the test code I ran to devlope my flight computer, known as Project Skippy. Descriptions of each file are below, and comments within the code can further explain what is going on.
## adalogger-blink-test
This file is a sanity check for when you get your 32u4 Adalogger. It just makes the onboard LED blink. 
Note: no aditional wiring needed. Simply plug it in and upload your sketch.
## adalogger-sd-card-test
This file is a sanity check for writing to a micro sd card that is inserted into your 32u4. It writes some stuff to a .txt file on the sd card.
Note: no aditional wiring needed. Simply plug it in and upload your sketch.
## altimeter-test
This file is a sanity check for using your Adafruit MPL3115A2 pressure sensor. It is hooked up to the 32u4 using I2C(this sensor requires it), and this program prints out some basic stats.
Below is the wired setup and expected program output:
<insert here>
