#include "EmonLib.h"
#include <SD.h>
#include <Wire.h>
#include "Rtc.h"

EnergyMonitor emon1;
char time[20];
char date[20];

Rtc rtc;
volatile byte seconds;
int seconds1;
int seconds2;
int overfl;
int overfl1;
long tiempo1 = 0;
long tiempo2 = 0;
long seconds8 = 0;
double Irms;
int minutos = 0;
int horas = 0;
const int chipSelect = 8;
boolean paso = true;
double medicion;
int i = 0;

int valor[20];

void setup()
{
  Serial.begin(9600);
  emon1.current(1, 111.1);
    pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("FAILED");
    return;
  }
}

void loop()
{
  double Irms = emon1.calcIrms(1480);
 // Serial.println(Irms);

if (paso = true){
    i++;
    if (i > 5 && i < 50){
    if (medicion > Irms){
    medicion=medicion;
  }
  else{
    medicion = Irms;
  }
  Serial.println(medicion);
    Serial.println(i);
  delay(250);
  }
 if (i > 50){
  String dataString = "";
  rtc.GetDate();
  rtc.Time(time);
  rtc.Date(date);
  dataString += String(date);
  dataString += "     ";
  dataString += String(time);
  if (Irms > (medicion + 0.03)) {
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
    File dataFile = SD.open("FLUJO3.csv", FILE_WRITE);
    tiempo2 = millis();
    if (seconds == 255) {
      overfl++;
      seconds = 0;
    }
    seconds2 = seconds1 + (overfl1 * 255);

    if (seconds2 != 0) {
      seconds8 = (tiempo2 - tiempo1) * 0.001;
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
}
}


