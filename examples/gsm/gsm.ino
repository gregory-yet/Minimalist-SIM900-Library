#include <SIM900.h>

SIM900 gsm;

void setup()
{
  Serial.begin(9600);
  
  gsm.begin("1234");
}

void loop()
{
  gsm.sms("0666666666", "Library test");
  
  do { } while (1);
}
