#include "Arduino.h"

int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  while (millis() < 5000)
  {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh)
    {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow)
    {
      sensorLow = sensorValue;
    }
  }
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  Serial.print("High: ");
  Serial.print(sensorHigh);
  Serial.print(" Low: ");
  Serial.println(sensorLow);
}

void loop()
{
  sensorValue = analogRead(A0);
  int pitch = map(sensorValue, 0, 1023, 50, 4000);
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" Pitch: ");
  Serial.println(pitch);
  tone(8, pitch, 10);
  delay(10);
}