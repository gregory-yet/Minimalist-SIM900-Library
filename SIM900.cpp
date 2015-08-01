/* 
	* @title			SIM900
	* @description		Minimalist library for SIM900
	* @author 			Grégory G. & Laurent T.
	* @date				31/07/2015 (dd/mm/yyyy) 09:33
*/

#include "Arduino.h"
#include "SIM900.h"

/* PUBLIC FUNCTIONS */

void SIM900::begin(String pin)
{
	Serial1.begin(9600);

	simpleAT("ATE0");
	sendAT("ATZ", "OK", 500);
	sendAT("AT", "OK", 1000);
	if(testPin() == 0){
		sendAT("AT+CPIN="+pin, "OK", 2000);
	}

	sendAT("AT+CGREG?", "+CGREG: 0,5", 1000);
	sendAT("AT+IFC=1,1","OK", 500);
	sendAT("AT+CMGF=1", "OK", 500);
	sendAT("AT+CLIP=1", "OK", 500);
	sendAT("AT+COLP=1", "OK", 2000);
}

void SIM900::beginGPRS()
{
	sendAT("AT+CGATT=1", "OK", 500);
	sendAT("AT+CGDCONT=1,\"IP\",\"APN\"", "OK", 500);
	sendAT("AT+CSTT=\"free\",\"\",\"\"", "OK", 500);
	simpleAT("AT+CIICR");
	delay(2000);
	simpleAT("AT+CIFSR");
	delay(1000);
	sendAT("AT+CIPHEAD=1", "OK", 1000);
}

void SIM900::sms(String number, String msg)
{
	simpleAT("AT+CMGS=\""+number+"\"");
	delay(1000);
	simpleAT(msg);
	delay(1000);
	sendCTR(false);
}

String SIM900::web(String ip, String adress)
{
	sendAT("AT+CIPSTART=\"TCP\",\""+ip+"\",\"80\"", "OK", 1000);
	simpleAT("AT+CIPSEND");
	delay(2000);
	simpleAT("GET "+adress);
	simpleAT(" HTTP/1.1");
	simpleAT(" HOST: "+ip);
	simpleAT(" Connection: close");

	return sendCTR(true);
}

/* SEND AT COMMAND */

String SIM900::sendAT(String cmd, String wait, int time)
{
	unsigned int timeout = 10000;
	boolean isTimeout = false;
	unsigned int waiting_at = millis();

	char buffer;
	String response;

	Serial.println("--------------------------");
	Serial.println(cmd);
	Serial1.println(cmd);

	while(!strstr(&response[0], &wait[0]) && !isTimeout) {

		if(millis() - waiting_at < timeout){
			if(Serial1.available()){
				buffer = Serial1.read();
				response += buffer;
			}
		}
		else {
			isTimeout = true;
		}
	}


	Serial.println(response);

	Serial.println();

	delay(time);

	return response;
}

void SIM900::simpleAT(String cmd)
{
	Serial.println(cmd);
	Serial1.println(cmd);
}

String SIM900::simpleRead()
{
	String response;
	char buffer;
	
	while(Serial1.available()){
		buffer = Serial1.read();
		response += buffer;
	}

	return response;
}

String SIM900::sendCTR(boolean gprs)
{
	serialFlush();
	Serial1.println((char)26);

	if(gprs){
		unsigned int timeout = 10000;
		boolean isTimeout = false;
		unsigned int waiting_at = millis();

		char buffer;
		String response;

		while(!strstr(&response[0], "</S>") && !isTimeout) {

			if(millis() - waiting_at < timeout){
				if(Serial1.available()){
					buffer = Serial1.read();
					response += buffer;
				}
			}
			else {
				isTimeout = true;
				response = "timeout";
			}
		}

		Serial.println(response);

		return response;
	}

	delay(500);
}

void SIM900::serialFlush()
{
	char buf;
	while(Serial1.available()){
		buf = Serial1.read(); 
	}
}

/* FUNC */

boolean SIM900::testPin()
{
	simpleAT("AT+CPIN?");
	delay(500);
	String value = simpleRead();
	Serial.println(value);
	boolean pin = false;

	if (strstr(&value[0], "+CPIN: READY"))
	{
		pin = true;
	}
	else 
	{
		pin = false;
	}

	return pin;
}

/*  Rechercher une valeur dans s
		@param String s                 Chaine dans laquelle on cherche des valeurs
		@param String search            Valeur qu'on recherche
		@return String cRetourValeur    Chaine entre la valeur cherchée
*/
String SIM900::parse(String s, String search)
{
	String cRetourValeur = "";

	int TagR1Debut = s.indexOf("<"+search+">");
	int TagR1Fin = s.indexOf("</"+search+">");

	cRetourValeur = s.substring(TagR1Debut + 2 + search.length(), TagR1Fin );

	return cRetourValeur;
}