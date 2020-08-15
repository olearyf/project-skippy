# project-skippy
**NOTE: this project is still underway!**

A cheap DIY rocket flight computer that tracks time from launch, pressure, altitude, temperature, acceleration.

![](https://github.com/olearyf/project-skippy/blob/master/project-skippy-logo.jpg)

## About

While there are some neat physics tricks when it comes to approximating flight data for your model rockets, and while there are online weather apps and things to get such information such as local pressure and temperature, I thought it would be much more fun to get all this data myself. In addition to this, I can adjust the granularity to my preferences and make some sweet plots of some sweet data! Thus, Project Skippy is born; named because I started real work on the idea across from a jar of Skippy peanut butter while working in my kitchen. It's easy to use and implement, and in addition to this I supplied the 3D files for everything you need so you can print your own! All rockets use C Estes motors. 

Anyways, the idea is this: you print a rocket, make a flight computer, launch the rocket(with my super technical and complicated(jokes) remote ignition system), log the data during the flight, analyze it, and just have a good time. If that seems like something you're interested in, heres how:

## Parts List 💡
- [Adafruit Lithium Ion Polymer Battery - 3.7v 500mAh](https://www.adafruit.com/product/1578)
- [Adafruit Feather 32u4 Adalogger](https://www.adafruit.com/product/2795)
- [8 GB Micro SD Card](https://www.adafruit.com/product/1294)
- [MPL3115A2 - I2C Barometric Pressure/Altitude/Temperature Sensor](https://www.adafruit.com/product/1893)
- [Adafruit LIS3DH Triple-Axis Accelerometer](https://www.adafruit.com/product/2809)
- LED
- 220 ohm resistor (or whatever resistor you need to limit the appropriate current your LED can handle)
- some wires
- soldering iron (optional, depending on how you want to hook it up
- 3D printer (optional, you can strap this thing to any rocket your heart desires)
- M2 screws
- [small cheap camera](https://www.amazon.com/gp/product/B07X8LDZ9M/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1) (optional)

## Assembly (no BIC or TEQ 😉)
Below are some schematics made with Fritzing that detail how to wire it up. I recommend you visit the [tests](https://github.com/olearyf/project-skippy/blob/master/tests/about.md) folder and start with those, and then work your way up to the full code and full wiring below:

![](https://github.com/olearyf/project-skippy/blob/master/images/project%20skippy%20PCB_bb.jpg)

![](https://github.com/olearyf/project-skippy/blob/master/images/project%20skippy_schem.jpg)

Once it's all wired up you're ready to load the code!

Note: not shown in the schematic is the 3.7v 500mAh battery - I soldered a slide switch to break the positive terminal to act as a way to turn the computer on and off. Note, to initiate the program you may need to hit the reset button on the board.

Below is my set up while I was prototyping:

![](https://github.com/olearyf/project-skippy/blob/master/images/IMG_5326.jpg)

## Loading the Code 💻

To load the code, use the  [Arduino IDE](https://www.arduino.cc/en/main/software). Download [project-skippy-main.ino](https://github.com/olearyf/project-skippy/blob/master/project-skippy-main.ino) and open it in the IDE. From here, connect your Adalogger using a micro usb cable. Then, click upload. From the terminal, you should see it compile, and then flash the sketch to the board. If everything goes well, once it's done flashing you should see the LED turn on and log data for 10 minutes. If you encounter an error at compile time, it is most likely due to you either lacking the necessary libraries(defined at the top), or your board may possibly be connected to the wrong port. If it is the latter, try hitting the reset button after pressing upload, or restarting your computer.

## Attaching to Rocket 🚀

For my first launch I used an Estes C-11-0 rocket motor, since the camera and flight computer are fairly heavy. Below are pictures of the 3D files I made and printed that can be found [here](https://github.com/olearyf/project-skippy/tree/master/3D-files). They include a basic rocket body with a space for the motor, and a nose cone that fits via friction fit. The nose cone has a loop at the end that I recommend attaching a plastic bag streamer to, as when I launched it popped off and this addition helped slow its fall. If the motor is too loose for the base, wrap it in a layer of masking tape.

![](https://github.com/olearyf/project-skippy/blob/master/images/light%20c11%20v1.png)

![](https://github.com/olearyf/project-skippy/blob/master/images/project%20skippy%20nose%20cone%203%20v4.png)

Below is the finished rocket. You can see the LED and slide switch from the flight computer poking out, as well as the onboard camera. This one was named the EFun 3 X-PLORE because I launched it with one of my managers from my summer internship at Microsoft who came to Purdue and launched some rockets with me! (Skippy for scale).

![](https://github.com/olearyf/project-skippy/blob/master/images/IMG_5454.jpg)

## Launch 💥

Unfortunately my camera was not recording the launch :(. However I'll launch again and upload a video soon! Data from the first launch with the rocket pictured above is found below.

## Analysis 📝

To use SkippyParser.py, install pandas and plotly using pip if you havent't already. Additionally, install Python if you need to. Then, from the command line, run the following:
```
python SkippyParser.py "path/to/your/flight/data/from/the/computer.csv"
```
This will parse your data and launch an html file that contains your data plots! Analyze to your heart's content; below is a readout from one of my launches:

![](https://github.com/olearyf/project-skippy/blob/master/images/newplot%20(2).png)

While not the best data to recieve. . . it works! Now I just need to work on the items below to get my rocket to go higher. The full raw data can be found [here](https://github.com/olearyf/project-skippy/blob/master/data/FLIGHT32.CSV). Note that Project Skippy takes data for 10 minutes and a model rocket launch is usually far shorter than that ;).

## Things I'm Working On

- better housing! Right now it's all screwed into a box that gets taped in
- data filter
- better rocket design overall - I want to go higher!
  
### Important Notes (aka don't make the mistakes I did)

You may be wondering by some data values are read twice(such as temperature, pressure, and altitude). There isn't really any rhyme or reason to this; I just found that if I didn't do it I would get crazy values like <600 pascals. Reading it twice allows for some time for the sensor to really get the value(at least I think) so that's why it's in there.

UPDATE: I need to add a data filter! And I should be reading the values a lot more than just once.
