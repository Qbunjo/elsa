#include "Arduino.h"
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#define ONE_WIRE_BUS 2

//initialize thermometer
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

//var definitions
int hist = 2; //hysteresis
int setTemp = 10; //default set temperature after startup
int mTemp;

//pin definitions
int coolPin = 4;
int plusButton = 9;
int minusButton = 10;



void TurnOn() {
  lcd.display();
  lcd.backlight();
}
void TurnOff() {
  lcd.noDisplay();
  lcd.noBacklight();
}

void coolMe() {
  digitalWrite(coolPin, 0);
}
void stopCooling() {
  digitalWrite(coolPin, 1);
}
int measureTemp() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  return tempC;
}

boolean ifPressed() {
  if (digitalRead(plusButton) == true or digitalRead(minusButton) == true)
    return true;
  else
    return false;
}

void setTempChange() {
}

void displayInfo() {
  TurnOn();
  //display on the lcd
  for (int i = 0; i < 30; i++) {
    lcd.setCursor(0, 1);
    lcd.print("Set Temp:");
    lcd.setCursor(9, 1);
    if (setTemp<10){
      lcd.print("    ");
      lcd.setCursor(9,1);}
    lcd.print(setTemp);
    lcd.print((char)223);
    lcd.setCursor(0, 0);
    lcd.print("Cur Temp:");
    lcd.setCursor(9, 0);
    if (mTemp<10){
      lcd.print("    ");
       lcd.setCursor(9,0);}
    lcd.print(mTemp);
    lcd.print((char)223);
    
    if (digitalRead(plusButton) == true) {
      setTemp++;
      lcd.setCursor(9, 1);
      lcd.print(setTemp);
      i=0;
    }
    if (digitalRead(minusButton) == true) {
      setTemp--;
      lcd.setCursor(9, 1);
      lcd.print(setTemp);
      i=0;
    }
    delay(400);
  }

  TurnOff();
}


void setup()
{
  sensors.begin();
  //define in/out pins
  pinMode(coolPin, OUTPUT);
  pinMode(plusButton, INPUT);
  pinMode(minusButton, INPUT);
  lcd.init();

  // start lcd
    mTemp=measureTemp();
  displayInfo();
}


void loop()
{
  mTemp=measureTemp();
  //measure temperature (main fridge process)
  if ((mTemp + hist) > setTemp) {
    coolMe();
  }
  if ((mTemp + hist) < setTemp) {
    stopCooling();
  }
  if (ifPressed() == true) {
    displayInfo();
  }
}
