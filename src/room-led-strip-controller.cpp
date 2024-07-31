#include <Arduino.h>

const int redPotenciometer = A5;
const int greenPotenciometer = A2;
const int bluePotenciometer = A1;   
const int brightnessPotenciometer = A0;

const int buttonPin = 2;
//bananaaaaaaaaaaa
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

//controle do botão

int buttonState = 0;
int lastButtonState = 0;
unsigned long buttonPressTime = 0;
bool pressedFor2Seconds = false;
bool buttonAction = false;

bool toggleReading = false;
bool readingSpeed = false;

//controladores gerais

int ledState = 0;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;
float brightnessValue = 0;
int ledDelayValue = 0;

int hueValue = 0;

// pisca pisca
float blinkTime = 0;
int ledBlinkState = 0;
int r = 0;
int g = 0;
int b = 0;


// fade

int redFadeValue = 0;
int greenFadeValue = 0;
int blueFadeValue = 0;
unsigned long previousMillis = 0;

float myFabs(float x) {
    return (x < 0) ? -x : x;
}

// Função para converter HSB para RGB
void HSBtoRGB(float hue, float sat, float bright, int& r, int& g, int& b) {
    float c = bright * sat; // Chroma
    float x = c * (1 - myFabs(fmod(hue / 60.0, 2) - 1));
    float m = bright - c;

    float r_prime, g_prime, b_prime;

    if (0 <= hue && hue < 60) {
        r_prime = c;
        g_prime = x;
        b_prime = 0;
    } else if (60 <= hue && hue < 120) {
        r_prime = x;
        g_prime = c;
        b_prime = 0;
    } else if (120 <= hue && hue < 180) {
        r_prime = 0;
        g_prime = c;
        b_prime = x;
    } else if (180 <= hue && hue < 240) {
        r_prime = 0;
        g_prime = x;
        b_prime = c;
    } else if (240 <= hue && hue < 300) {
        r_prime = x;
        g_prime = 0;
        b_prime = c;
    } else if (300 <= hue && hue < 360) {
        r_prime = c;
        g_prime = 0;
        b_prime = x;
    } else {
        r_prime = 0;
        g_prime = 0;
        b_prime = 0;
    }

    r = static_cast<int>((r_prime + m) * 255);
    g = static_cast<int>((g_prime + m) * 255);
    b = static_cast<int>((b_prime + m) * 255);
}


void setup()
{
  Serial.begin(9600); 

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(redPotenciometer, INPUT);
  pinMode(bluePotenciometer, INPUT);
  pinMode(greenPotenciometer, INPUT);
  pinMode(brightnessPotenciometer, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);
}



void LedStatic(int r, int g, int b, float brightness)
{
  analogWrite(redPin, r * brightness);
  analogWrite(greenPin, g * brightness);
  analogWrite(bluePin, b * brightness);
}

void LedBoringBlink(float brightness, int delay) 
{

  switch (ledBlinkState)
  {
  case 0:
    LedStatic(255, 0, 0, brightness);
    break;
  
  case 1:
    LedStatic(0, 255, 0, brightness);
    break;

  case 2: 
    LedStatic(0, 0, 255, brightness);
    break;

  default:
    break;
  }



  if (millis() - blinkTime >= delay)
  {
    ledBlinkState ++;
    if (ledBlinkState > 2) ledBlinkState = 0;
    blinkTime = millis();
  }

}

void LedRealBlink(float brightness, int delay)
{
  if (millis() - blinkTime >= delay)
  {
    blinkTime = millis();

    int hueValue = random(0, 360);
    int saturationValue = 1;
    int brightnessValue = 1;

    HSBtoRGB(hueValue, saturationValue, brightnessValue, r, g, b);
  }

  //random hue 0 and 360


  LedStatic(r, g, b, brightness);
}


int map(int x, int in_min, int in_max, int out_min, int out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapValueToFloat(int x, int in_min, int in_max) {
    return static_cast<float>(x - in_min) / (in_max - in_min);
}

void Read()
{
  redValue = analogRead(redPotenciometer);
  //blueValue = analogRead(bluePotenciometer);
  //greenValue = analogRead(greenPotenciometer);

  buttonState = digitalRead(buttonPin);
}

void loop()
{

  Read();

  if (buttonState == 0) {

      buttonAction = false;

      if (lastButtonState == 1) buttonPressTime = millis();

      if (millis() - buttonPressTime >= 2000 && !pressedFor2Seconds) // liga/desliga se pressionado por 2 segundos.
      {
        
        buttonAction = true;
        pressedFor2Seconds = true;

        if (ledState == 0) ledState = 1;
        else ledState = 0;
      }

      if (millis() - buttonPressTime >= 500 && !toggleReading) // muda para velocidade se pressionado por 2 segundos.
      {
        buttonAction = true;
        toggleReading = true;
        readingSpeed = !readingSpeed;
      }

      if(lastButtonState == 1 && ledState != 0) // muda o estado do led se pressionado uma vez.
      {
        buttonAction = true;
        ledState ++;
        if (ledState > 4) ledState = 1;
      }
  }

  else 

  {
    buttonAction = false;
    toggleReading = false;
    buttonPressTime = 0;
    pressedFor2Seconds = false;
  }

  lastButtonState = buttonState;

  Serial.println(redValue);

  //USANDO VERMELHO PQ TODOS OS POTENCIOMETROS QUEIMARÃO

  float tempValue = mapValueToFloat(redValue, 0, 1023);
  Serial.println(tempValue);
  
  switch (ledState)
  {
    case 0:
      LedStatic(0, 0, 0, tempValue);
      break;
    
    case 1:
      LedStatic(255, 255, 255, tempValue);
      break;

    case 2:
      LedStatic(255, 75, 0, tempValue);
      break;

    case 3:
      LedBoringBlink(tempValue, 300);
      break;
    
    case 4:
      LedRealBlink(tempValue, 75);
      break;
  }
}