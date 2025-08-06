#include "Arduino.h"

const int sensorPin = A0;

float baselineTemp = 0.0;
int calibrationCount = 0;

void calibrate();
float readTemperature(bool print);

void setup()
{
  Serial.begin(9600);
  for (int pinNumber = 2; pinNumber < 5; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  calibrate();
}

void calibrate()
{
  Serial.println("Calibrating temperature sensor...");
  // calibrate during the first five seconds
  while (millis() < 5000)
  {
    baselineTemp += readTemperature(false);
    calibrationCount++;
  }
  baselineTemp /= calibrationCount;
  Serial.print("Finished calibrating, baselineTemp = ");
  Serial.println(baselineTemp);
}

float readTemperature(bool print)
{
  int sensorVal = analogRead(sensorPin);
  if (print)
  {
    Serial.print(" Sensor value: ");
    Serial.print(sensorVal);
  }

  float voltage = (sensorVal / 1024.0) * 5.0;
  if (print)
  {
    Serial.print(", Volts: ");
    Serial.print(voltage);
  }

  float temperature = (voltage - 0.5) * 100;
  if (print)
  {
    Serial.print(", degrees C: ");
    Serial.println(temperature);
  }
  return temperature;
}

void loop()
{
  float temperature = readTemperature(true);
  digitalWrite(2, temperature >= baselineTemp + 2 ? HIGH : LOW);
  digitalWrite(3, temperature >= baselineTemp + 4 ? HIGH : LOW);
  digitalWrite(4, temperature >= baselineTemp + 6 ? HIGH : LOW);
  delay(1);
}
