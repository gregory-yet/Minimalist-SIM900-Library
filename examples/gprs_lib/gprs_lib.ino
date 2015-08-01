#include <SIM900.h>

SIM900 gsm;

void setup()
{
  Serial.begin(9600);
  
  gsm.begin("1234");
  
  gsm.beginGPRS();
}

void loop()
{
  String response = gsm.web("ip_or_name", "/adress");

  delay(900000);
}
