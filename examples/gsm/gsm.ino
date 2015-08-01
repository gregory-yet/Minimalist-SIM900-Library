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