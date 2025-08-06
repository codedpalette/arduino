#include "Arduino.h"
#include <Servo.h>

Servo myServo;

int const potPin = A0;
int potVal;
int angle;

void setup()
{
  myServo.attach(9);
  Serial.begin(9600);
}

void loop()
{
  potVal = analogRead(potPin);
  angle = map(potVal, 0, 1023, 0, 180);
  myServo.write(angle);
  Serial.print("Potentiometer Value: ");
  Serial.print(potVal);
  Serial.print(" - Angle: ");
  Serial.println(angle);
  delay(15);
}