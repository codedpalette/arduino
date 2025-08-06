#include "Arduino.h"

int switchState = HIGH;
unsigned long timer = 0;

void setup()
{
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  switchState = digitalRead(2);
  if (switchState == HIGH)
  {
    // pressed
    timer = 0;
    digitalWrite(3, HIGH); // green
    digitalWrite(4, LOW);  // red
    digitalWrite(5, LOW);  // red
  }
  else
  {
    // not pressed
    digitalWrite(3, LOW);
    if (timer == 0)
    {
      timer = millis();
    }
    if (millis() - timer < 250)
    {
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    }
    else if (millis() - timer < 500)
    {
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    }
    else
    {
      timer = 0;
    }
  }
}
