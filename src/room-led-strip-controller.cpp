#include <Arduino.h>
const int redPotenciometer = A0;
const int greenPotenciometer = A1;
const int blueInput = A2;   
const int brightnessPotenciometer = A3;

const int button = 2;
//bananaaaaaaaaaaa
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

int ledSpeed = 80;

void setup()
{
  Serial.begin(9600); 

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(redPotenciometer, INPUT);
  pinMode(blueInput, INPUT);
  pinMode(greenPotenciometer, INPUT);
  pinMode(brightnessPotenciometer, INPUT);
}



void LedStatic(float r, float g, float b, float brightness)
{
  brightness = brightness / 100;
  analogWrite(redPin, r * brightness);
  analogWrite(greenPin, g * brightness);
  analogWrite(bluePin, b * brightness);
}


void LedWhite(int brightness)
{
  analogWrite(redPin, 1 * brightness);
  analogWrite(greenPin, 1 * brightness);
  analogWrite(bluePin, 1 * brightness);
}

void loop()
{
  //LedStatic(139, 0, 139, 50);
  float red = analogRead(redPotenciometer);
  red = map(red, 0, 1023, 0, 255);

  float blue = analogRead(blueInput);
  blue = map(blue, 0, 1023, 0, 255);

  float green = analogRead(greenPotenciometer);
  green = map(green, 0, 1023, 0, 255);

  float brightness = analogRead(brightnessPotenciometer);
  brightness = map(brightness, 0, 1023, 0, 100);

  Serial.println(red);
  Serial.println(blue);
  Serial.println(green);
  Serial.println(brightness);

  //analogWrite(RED, 255);

  LedStatic(red, green, blue, brightness);    

}