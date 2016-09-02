#include <SD.h>
#include <Wire.h>
#include "Rtc.h"

char time[20];
char date[20];

Rtc rtc;
volatile int NbTopsFan; //measuring the rising edges of the signal
volatile byte seconds;
int seconds1;
int seconds2;
int overfl;
int overfl1;
int Calc;
long tiempo1=0;
long tiempo2=0;
long seconds8=0;
int minutos = 0;
int horas = 0;
int hallsensor = 2;    //The pin location of the sensor
const int chipSelect = 8;
void rpm ()     //This is the function that the interupt calls
{
  NbTopsFan++;  //This function measures the rising and falling edge of the
}

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("FAILED");
    // don't do anything more:
    return;
  }
}

void loop()
{
  NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
  delay (1000);
  Calc = (NbTopsFan * 60 / 7.5);
  Serial.println(Calc);
  String dataString = "";
  rtc.GetDate();
  rtc.Time(time);
  rtc.Date(date);
  dataString += String(date);
  dataString += "     ";
  dataString += String(time);
  if (Calc > 50) {
    seconds++;
    seconds1 = seconds;
  }
  else {
    minutos = 0;
    horas = 0;
    seconds = 0;
    overfl = 0;
  }
  if (seconds1 == seconds && seconds1 == 0) {
    tiempo1 = millis();
  }
  if (seconds1 != seconds && seconds1 != 0) {
    File dataFile = SD.open("AGUA2.csv", FILE_WRITE);
    tiempo2 = millis();
    if (seconds == 255) {
      overfl++;
      seconds = 0;
    }
    seconds2 = seconds1 + (overfl1 * 255);

    if (seconds2 != 0) {
      seconds8=((tiempo2-tiempo1)-1000)*0.001;
      horas = seconds8 / 3600;
      seconds8 = seconds8 % 3600;
      minutos = seconds8 / 60;
      seconds8 = seconds8 % 60;
      Serial.print("Se detecto un flujo con una duracion de = ");
      dataFile.print("Se detecto un flujo con una duracion de = ");
      if (horas < 10) {
        Serial.print("0");
        dataFile.print("0");
      }
      Serial.print(horas);
      dataFile.print(horas);
      Serial.print(":");
      dataFile.print(":");
      if (minutos < 10) {
        Serial.print("0");
        dataFile.print("0");
      }
      Serial.print(minutos);
      dataFile.print(minutos);
      Serial.print(":");
      dataFile.print(":");
      if (seconds8 < 10) {
        Serial.print("0");
        dataFile.print("0");
      }
      Serial.print(seconds8);
      dataFile.print(seconds8);
      seconds1 = 0;
      Serial.print("               Fecha y Hora =  ");
      dataFile.print("               Fecha y Hora =  ");
      Serial.println(dataString);
      dataFile.println(dataString);
      dataFile.close();
      delay (500);
    }
  }
}


