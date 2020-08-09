# project-skippy
A cheap DIY rocket flight computer that tracks time from launch, pressure, altitude, temperature, acceleration.

![](https://github.com/olearyf/project-skippy/blob/master/project-skippy-logo.jpg)

## About

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
- [small cheap camera](https://www.amazon.com/gp/product/B07X8LDZ9M/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1) (optional)

## Assembly (no BIC or TEQ 😉)
Below are some schematics made with Fritzing that detail how to wire it up. I recommend you visit the [tests](https://github.com/olearyf/project-skippy/blob/master/tests/about.md) folder and start with those, and then work your way up to the full code and full wiring below:

![](https://github.com/olearyf/project-skippy/blob/master/images/project%20skippy%20PCB_bb.jpg)

![](https://github.com/olearyf/project-skippy/blob/master/images/project%20skippy_schem.jpg)

Once it's all wired up you're ready to load the code!

## Loading the Code 💻

To load the code, use the  [Arduino IDE](https://www.arduino.cc/en/main/software). Download [project-skippy-main.ino](https://github.com/olearyf/project-skippy/blob/master/project-skippy-main.ino) and open it in the IDE. From here, connect your Adalogger using a micro usb cable. Then, click upload. From the terminal, you should see it compile, and then flash the sketch to the board. If everything goes well, once it's done flashing you should see the LED turn on and log data for 10 minutes. If you encounter an error at compile time, it is most likely due to you either lacking the necessary libraries(defined at the top), or your board may possibly be connected to the wrong port. If it is the latter, try hitting the reset button after pressing upload, or restarting your computer.

## Attaching to Rocket 🚀

make sure to put 3d printer files so people can make it themselves. -> rocket, nose cone, bottom joint, the works

## Launch 💥

## Analysis 📝

To use SkippyParser.py, install pandas and plotly using pip if you havent't already. Additionally, install Python if you need to. Then, from the command line, run the following:
```
python SkippyParser.py "path/to/your/flight/data/from/the/computer.csv"
```
This will parse your data and launch an html file that contains your data plots! Analyze to your heart's content; below is a readout from one of my launches:

insert jpg
  
### Important Notes (aka don't make the mistakes I did)

You may be wondering by some data values are read twice(such as temperature, pressure, and altitude). There isn't really any rhyme or reason to this; I just found that if I didn't do it I would get crazy values like <600 pascals. Reading it twice allows for some time for the sensor to really get the value(at least I think) so that's why it's in there.
