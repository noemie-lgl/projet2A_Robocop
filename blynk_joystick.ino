/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include "WiFi.h"

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
char auth[] = "209fe14af13f4c01b247e105d743e093"; //YourToken

// Your WiFi credentials.
char ssid[] = "AndroidAP7271"; //YourNetworkName
char pass[] = "nononono"; //YourPassword



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



void motor(int left, int right) {
   digitalWrite(motor1Pin1, (left < 0) ? LOW : HIGH);
  digitalWrite(motor2Pin1, (left > 0) ? LOW : HIGH);
  digitalWrite(motor1Pin2, (right < 0) ? LOW : HIGH);
  digitalWrite(motor2Pin2, (right > 0) ? LOW : HIGH);
  ledcWrite(1, 255);  
  ledcWrite(2, 255);   
}




void setup() {
  
 
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

  Blynk.begin(auth, ssid, pass);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {

  Blynk.run();

  /*
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);
  */
  
  
  //Blynk.run();
 // Move the DC motor forward at maximum speed
  /*Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed  INVERSE?? 
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  while (dutyCycle <= 255){
    ledcWrite(motor1PwmChannel, dutyCycle);   
    ledcWrite(motor2PwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;*/
}


BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();

  if (y < 512) {
          if (x < 512) {
            // left forward
            motor(0, 1);
          } else if (x > 512) {
            // left backward
            motor(0, -1);
          } else {
            // turn anti-clockwise
            motor(-1, 1);
          }
        } else if (y > 512) {
          if (y < 80) {
            // right forward
            motor(1, 0);
          } else if (x > 176) {
            // right backward
            motor(-1, 0);
          } else {
            // turn anti-clockwise
            motor(1, -1);
          }
        } else {
          if (y < 80) {
            // forward
            motor(1, 1);
          } else if (y > 176) {
            // backward
            motor(-1, -1);
          } else {
            // stop
            motor(0, 0);
          }
        }*/

  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed  INVERSE?? 
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  while (dutyCycle <= 255){
    ledcWrite(motor1PwmChannel, dutyCycle);   
    ledcWrite(motor2PwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;      

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

}
