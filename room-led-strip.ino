#include <WiFi.h>
#include <esp_http_server.h>

//WIFI SETTINGS

const char* ssid = "SMITHREENS 2.4G";
const char* password = "40028922";

WiFiServer server(80);

String httpHeader;

int RED = 5;
int GREEN = 18;
int BLUE = 19;

int ledSpeed = 80;
int brightness = 255;
int sexo = 0;
int r, g, b;
int staticR = 100 , staticG = 50, staticB = 20; 

void setup()
{
  Serial.begin(115200);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop()
{
  WiFiClient client = server.available();   // Listen for incoming clients

  delay(1000);

  if(client) {
    Serial.println("New Client.");
    Serial.println("client ip: ");
    Serial.println(client.remoteIP());
  }

}

void LedStatic()
{
  analogWrite(RED, 1 * staticR);
  analogWrite(GREEN, 1 * staticG);
  analogWrite(BLUE, 1 * staticB);
}


void LedWhite()
{
  analogWrite(RED, 1 * brightness);
  analogWrite(GREEN, 1 * brightness);
  analogWrite(BLUE, 1 * brightness);
}

void LedBlink()
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

void LedMem1()
{
  analogWrite(RED, 10);
  analogWrite(GREEN, 50);
  analogWrite(BLUE, 105);
}

// Current time
//unsigned long currentTime = millis();
// Previous time
//unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
//const long timeoutTime = 2000;

/*void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        httpHeader += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP httpHeaders always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (httpHeader.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (httpHeader.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (httpHeader.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (httpHeader.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } 
            else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
          }
        }
      }
    }
  }
}*/