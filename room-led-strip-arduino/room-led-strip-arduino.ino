int BLUE = 6;
int RED = 5;
int GREEN = 3;
int ledSpeed = 80;
int brightness = 255;
int sexo = 2;
int r, g, b;
int staticR = 100
, staticG = 50, staticB = 20;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  
  
  //analogWrite(RED, 255);
  //analogWrite(BLUE, 225);
  //analogWrite(GREEN, 80);  
  //branco();
  //penis();   
  //piscaRGB();
  //dormir();

  /*switch(sexo)
 {
  case 1: branco();
  break;

  case 2: piscaRGB();
  break;

  case 3: penis();
  break;

  case 4: estatico();
  break;
 }*/
}

void estatico()
{
  analogWrite(RED, 1 * staticR);
  analogWrite(GREEN, 1 * staticG);
  analogWrite(BLUE, 1 * staticB);
}

void dormir()
{
  analogWrite(RED, 10);
  analogWrite(GREEN, 50);
  analogWrite(BLUE, 105);
}

void branco()
{
  analogWrite(RED, 1 * brightness);
  analogWrite(GREEN, 1 * brightness);
  analogWrite(BLUE, 1 * brightness);
}

void piscaRGB()
{
  analogWrite(RED, 1 * brightness);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(ledSpeed);
  analogWrite(RED, 0);
  analogWrite(GREEN, 1 * brightness);
  analogWrite(BLUE, 0);
  delay(ledSpeed);
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 1 * brightness);
  delay(ledSpeed);
}

void penis()
{
 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(RED, r);
    delay(ledSpeed);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUE, b);
    delay(ledSpeed);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREEN, g);
    delay(ledSpeed);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(RED, r);
    delay(ledSpeed);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUE, b);
    delay(ledSpeed);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREEN, g);
    delay(ledSpeed);
  } 
}
