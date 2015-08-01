// Send a simple web request
#include <SIM900.h>

SIM900 gsm;

void setup()
{
  Serial.begin(9600);
  
  gsm.begin("1234");// 1234 is your pin
  
  gsm.beginGPRS(); // start the gprs and don't forget to change the APN if you need
}

void loop()
{
  String response = gsm.web("ip_or_name", "/adress"); // 1. your ip or hostname | 2. your adress with the "/" before, without the ip, like : gsm.web("127.0.0.1", "/hello.php?id=5&arduino=Mega2560&pin=8");

  delay(900000); // send a web request every 15 minutes
}