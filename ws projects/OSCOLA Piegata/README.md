# OSCOLA Piegata

CC BY-SA [tamberg](https://twitter.com/tamberg)

Derivative of [https://github.com/CasaJasmina/OSCOLA](https://github.com/CasaJasmina/OSCOLA) licensed CC BY-SA Jesse Howard, Stefano Paradiso and Lorenzo Romagnoli, developed at FabLab Torino and Officine Arduino.

<img src="http://thingiverse-production-new.s3.amazonaws.com/renders/05/20/54/91/cd/16626711215_f3ddda509a_z_preview_featured.jpg" width="600"/>

## Arduino Yun Mailbox HTTP API

The OSCOLA Piegata Arduino code is based on the Arduino Yun [Mailbox HTTP API](https://www.arduino.cc/en/Tutorial/MailboxReadMessage), which is simpler than MQTT.

## Testing the API with Curl

Download and install the Curl command line tool from [http://curl.haxx.se/](http://curl.haxx.se/), then type

`$ curl -vX POST http://arduino.local/mailbox/{rrggbb}` e.g.

`$ curl -vX POST http://arduino.local/mailbox/ee6600`

## Using a DIY 3D Tilt Sensor Controller

This project includes a Web page with JS glue code for a [DIY 3D Tilt Sensor](http://www.instructables.com/id/DIY-3D-Tilt-Sensor/) controller - here's a [short video](https://www.youtube.com/v/HGzyO5u3bwg?start=170&end=186&version=3).

## Connecting to the IFTTT Maker Channel

Thanks to the HTTP API, the OSCOLA Piegata can receive Webhook calls from the [IFTTT Maker Channel](blog.ifttt.com/post/121786069098/introducing-the-maker-channel).

To make the Arduino Yun accessible from IFTTT follow the steps in [https://yaler.net/arduino-yun](https://yaler.net/arduino-yun)

Then [clone](https://ifttt.com/recipes/search?q=OSCOLA) or [create a new recipe](https://ifttt.com/myrecipes/personal/new) or [Do app](https://ifttt.com/products/do/button) button using your relay domain in the URL

`http://{RELAY_DOMAIN}.try.yaler.net/mailbox/{rrggbb}` e.g.

`http://gsiot-ffmq-ttd5.try.yaler.net/mailbox/ee6600`

Use *Method* `POST` and *Content Type* `application/x-www-form-urlencoded`, leave *Body* empty.

Here's an example recipe to [light up OSCOLA on sunset](https://ifttt.com/recipes/310542-light-up-oscola-on-sunset) at your location, and one to [switch off OSCOLA on sunrise](https://ifttt.com/recipes/310547-switch-off-oscola-on-sunrise).

<img src="https://farm1.staticflickr.com/425/19973201441_055150e15e_z.jpg"/>

IFTTT does not yet allow to publish Do app recpies, so you'll have to create one from scratch.

<img src="https://farm4.staticflickr.com/3793/19345435314_0eacae5181.jpg"/>&nbsp;
<img src="https://farm1.staticflickr.com/398/19968022555_b079d7db66.jpg"/>

# HTTP APIs and Webhooks for an open IoT

Note that OSCOLA, the DIY controller and the IFTTT platform do not know anything about each other.

[HTTP](http://tools.ietf.org/html/rfc2616)(S) [REST](https://de.wikipedia.org/wiki/Representational_State_Transfer) APIs and [Webhooks](https://en.wikipedia.org/wiki/Webhook) enable a loosely coupled, more open Internet of Things.
