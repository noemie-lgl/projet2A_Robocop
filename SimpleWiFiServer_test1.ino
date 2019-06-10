/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>

const char* ssid     = "AndroidAP7271";
const char* password = "nononono";

// Robot 1 - Motor A
int motor1Pin1 = 4; 
int motor1Pin2 = 5; 
int motor1EnablePin = 25; 

// Robot 1 - Motor B
int motor2Pin1 = 12; 
int motor2Pin2 = 13; 
int motor2EnablePin = 26;


// Setting PWM properties
const int freq = 30000;
const int motor1PwmChannel = 1;
const int motor2PwmChannel = 2;
const int resolution = 8;
int dutyCycle = 200;


WiFiServer server(80);

void setup()
{
    // sets the pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor1EnablePin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(motor2EnablePin, OUTPUT);
  
  // configure LED PWM functionalitites
    ledcSetup(motor1PwmChannel, freq, resolution);
    ledcSetup(motor2PwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
    ledcAttachPin(motor1EnablePin, motor1PwmChannel);
    ledcAttachPin(motor2EnablePin, motor2PwmChannel);

    Serial.begin(115200);
       // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to move forward.<br>");
            client.print("Click <a href=\"/L\">here</a> to move backwards.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          Serial.println("Moving Forward");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, HIGH); 
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, HIGH); 
          ledcWrite(1, 255);  
          ledcWrite(2, 255); 
          delay(2000);
          
           // Stop the DC motor
          Serial.println("Motor stopped");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
    
        }
        if (currentLine.endsWith("GET /L")) {
          Serial.println("Moving Backwards");
          digitalWrite(motor1Pin1, HIGH);
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, HIGH);
          digitalWrite(motor2Pin2, LOW);
          ledcWrite(1, 255);  
          ledcWrite(2, 255);    
          delay(2000); 

          // Stop the DC motor
          Serial.println("Motor stopped");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          
        }
       
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
