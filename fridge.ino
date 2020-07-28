#include "Arduino.h"
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

//initialize thermometer
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//var definitions
int hist=2; //hysteresis
int setTemp=8; //default set temperature after startup


//pin definitions
int coolPin=10;
int tempPin=8;
int plusButton=6;
int minusButton=7;

void coolMe(){
	digitalWrite(coolPin,0);
}
void stopCooling(){
	digitalWrite(coolPin,1);
}
int measureTemp(){
	sensors.requestTemperatures();
	float tempC = sensors.getTempCByIndex(0);
	return tempC;
}

void setup()
{
	sensors.begin();
//define in/out pins

}


void loop()
{
//measure temperature
//display on the lcd
if ((measureTemp()+hist)>setTemp){
coolMe();
}
if ((measureTemp()+hist)<setTemp){
	stopCooling();
}

}
