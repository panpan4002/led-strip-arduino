#include <Arduino.h>
const int redPotenciometer = A0;
const int greenPotenciometer = A1;
const int bluePotenciometer = A2;   
const int brightnessPotenciometer = A3;

const int buttonPin = 2;
//bananaaaaaaaaaaa
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

int buttonState = 0;
unsigned long buttonPressTime = 0;
int lastButtonState = 1;

bool power = false;
int state = 0;

int ledSpeed = 1000;
int ledColorState = 0;
unsigned long previousMillis = 0;

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

void LedBlink(int brightness, int speed) {
  unsigned long currentMillis = millis(); // Pega o tempo atual

  if (currentMillis - previousMillis >= speed) { // Verifica se já passou o tempo de 'speed'
    previousMillis = currentMillis; // Atualiza a última vez que o LED foi atualizado

    ledColorState++;
    if (ledColorState >= 2) {
      ledColorState = 0;
    }
  }

    // Alterna entre os diferentes estados do LED
    switch (ledColorState) {
      case 0:
        LedStatic(255, 0, 0, brightness);
        state = 1;
        break;
      case 1:
        LedStatic(0, 255, 0, brightness);
        state = 2;
        break;
      case 2:
        LedStatic(0, 0, 255, brightness);
        state = 0;
        break;
    }
  }

void loop()
{
  //LedStatic(139, 0, 139, 50);
  float red = analogRead(redPotenciometer);
  red = map(red, 0, 1023, 0, 255);

  float blue = analogRead(bluePotenciometer);
  blue = map(blue, 0, 1023, 0, 255);

  float green = analogRead(greenPotenciometer);
  green = map(green, 0, 1023, 0, 255);

  float brightness = analogRead(brightnessPotenciometer);
  brightness = map(brightness, 0, 1023, 0, 100);

  buttonState = digitalRead(buttonPin);

  /*Serial.print(red);
  Serial.print(" ");
  Serial.print(blue);
  Serial.print(" ");
  Serial.print(green);
  Serial.print(" ");
  Serial.print(brightness);
  Serial.print(" ");
  Serial.println(buttonState);
  */


  //analogWrite(RED, 255);

  if (buttonState == 0) {
    // Se o botão acabou de ser pressionado, armazene o tempo atual
    if (buttonPressTime == 0 && lastButtonState == 1 && state != 0) {
      buttonPressTime = millis();
      state ++;

      Serial.println("aperto");
    }
    // Se o botão foi pressionado por 2 segundos, execute uma ação
    else if (millis() - buttonPressTime >= 2000) {

      if (state == 0) {
        state = 1;
        }

      else state = 0;
      buttonPressTime = 0;
    }
  }
  // Se o botão não está pressionado, reset o tempo de pressionamento do botão
  else {
    buttonPressTime = 0;
  }

  if (state > 4) {
    state = 1;
  }

  lastButtonState = buttonState;

  Serial.println(state);

  switch (state)
    {
    case 0:
      LedStatic(0, 0, 0, 0);
      break;
    
    case 1:
      LedWhite(brightness);
      break;

    case 2:
      LedStatic(red, green, blue, brightness);
      break;

    case 3:
      LedBlink(brightness, ledSpeed);
      break;

    default:
      break;
    }  

}