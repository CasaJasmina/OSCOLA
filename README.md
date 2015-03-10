# OSCOLA
Open Source COnnected LAmp

Oscola is a open source connected lamp designed for the first Casa Jasmina workshop by Jesse Howard, Stefano Paradiso and Lorenzo Romagnoli. 

<img src="https://raw.githubusercontent.com/CasaJasmina/OSCOLA/master/oscola-small.jpg" width="600"/>

Coherently with the Open-Design philosophy, the lamp can be easily reinterpreted and modified according to specific needs. 
The Structure of the lamp is meant to be laser-cutted, and his kept together with screws and bolts; no glue is needed.

The electronic of the lamp is based on Arduino YUN, hence it allows it to connect to the Internet. Via a web-interface the user can change the color of the light.
 
During the workshop participants, made their derivative design. Their codes and cutting files can be found in the "ws projects" folder.

<img src="https://farm9.staticflickr.com/8590/16525701260_4364515a04_z.jpg" width="600"/>

The Arduino code uses MQTT and the [Easy-Arduino-Yun-MQTT-Client](https://github.com/bobbytech/Easy-Arduino-Yun-MQTT-Client) library. In order to control the addressable leds remember to download and install also the [Neopixel library](https://github.com/adafruit/Adafruit_NeoPixel) 

more pics from the workshop [here](https://www.flickr.com/photos/arduino_cc/sets/72157650751710580) 
