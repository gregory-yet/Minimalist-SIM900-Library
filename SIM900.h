/* 
	* @title			SIM900
	* @description		Minimalist library for SIM900
	* @author 			Grégory G. & Laurent T.
	* @date				31/07/2015 (dd/mm/yyyy) 09:03
*/

#ifndef SIM900_h
#define SIM900_h

#include "Arduino.h"

class SIM900 {

public:
	void begin(String pin);
	void beginGPRS();
	void sms(String number, String msg);
	String web(String ip, String adress);
	String sendAT(String cmd, String wait, int time);
	void simpleAT(String cmd);
	String simpleRead();
	String parse(String s, String search);
private:
	boolean testPin();
	String sendCTR(boolean gprs);
	void serialFlush();
};

#endif