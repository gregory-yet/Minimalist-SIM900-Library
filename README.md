# Minimalist-SIM900-Library
Send SMS and web request with a minimalist SIM900 library

## Informations
Only a small library who will allow you to send an SMS or a web request in seconds very easily. No need to add a library too full for your project, simply send messages or retrieve data from a web page!

It is a library who shouldn't be on Github, but I don't found a simple library so I hope it right for you!

You can use this code to test your SIM900 shield / module before using my library.
```Arduino
void setup()
{
 Serial1.begin(9600);               // the GPRS baud rate   
 Serial.begin(9600);                 // the GPRS baud rate   
}

void loop()
{
 if (Serial1.available())
   Serial.write(Serial1.read());
 if (Serial.available())
   Serial1.write(Serial.read());  

}
```
With this program, you just have to open your Serial Monitor at 9600 bauds and send an AT command (you can send a simple command like "AT" without quotes, and see if there is a response from the SIM900).

My library use the MEGA 2560 with RX1 and TX1 (```Serial1.begin(9600);``` ...), so you must have a MEGA 2560, but you also can use the [SoftwareSerial](https://www.arduino.cc/en/Reference/SoftwareSerial) library i think i don't run test with this library.

With my SIM900 library and the good SIM900 module, I can send a SMS very quickly in seconds, same for the web request !

## Requirements
- An Arduino (MEGA2560 or other but with the SoftwareSerial lib)
- A SIM900 module / shied, I use [this SIM900 from SainSmart](http://www.sainsmart.com/sim900-gprs-gsm-board-quad-band-module-kit-for-arduino-high-quality-new.html)
- A **powerful** alimentation who can follow the requirements of the SIM900 module (5V / 2A)
- With the SIM900 from SainSmart i need to connect RX on TX, and TX on RX.

## Modifications
You need to specify your APN at SIM900.cpp:35 (because like i say, it just a library for a personnal project, so I don't need to change my APN...)

## Examples
You can find this examples in the "examples" folder !
```Arduino
// Send a simple SMS
#include <SIM900.h>

SIM900 gsm;

void setup()
{
  Serial.begin(9600);
  
  gsm.begin("1234"); // 1234 is your PIN
}

void loop()
{
  gsm.sms("0666666666", "Library test"); // 1. your number | 2. the text message
  
  do { } while (1); // send only one SMS
}
```

```Arduino
// Send a simple web request
#include <SIM900.h>

SIM900 gsm;

void setup()
{
  Serial.begin(9600);
  
  gsm.begin("1234");// 1234 is your pin
  
  gsm.beginGPRS(); // start the gprs
}

void loop()
{
  String response = gsm.web("ip_or_name", "/adress"); // 1. your ip or hostname | 2. your adress with the "/" before, without the ip, like : gsm.web("127.0.0.1", "/hello.php?id=5&arduino=Mega2560&pin=8");

  delay(900000); // send a web request every 15 minutes
}
```

## Author
Grégory G. & Laurent T.
