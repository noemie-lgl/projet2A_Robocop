    /*  Arduino DC Motor Control - PWM | H-Bridge | L298N
             Example 02 - Arduino Robot Car Control
        by Dejan Nedelkovski, www.HowToMechatronics.com
    */
    #define enA 3 //PWM
    #define in1 2
    #define in2 4
    #define enB 9 //PWM
    #define in3 5
    #define in4 6

    #define enA_2 10 //PWM
    #define enB_2 11 //PWM
    #define in1_2 7
    #define in2_2 8
    #define in3_2 12
    #define in4_2 13



    float coeff = 0.8;    
    int motorSpeedA = 0;
    int motorSpeedB = 0;
    int motorSpeedA_2 = 0;
    int motorSpeedB_2 = 0;
    
    void setup() {
      pinMode(enA, OUTPUT);
      pinMode(enB, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT);
      pinMode(enA_2, OUTPUT);
      pinMode(enB_2, OUTPUT);
      pinMode(in1_2, OUTPUT);
      pinMode(in2_2, OUTPUT);
      pinMode(in3_2, OUTPUT);
      pinMode(in4_2, OUTPUT);
      Serial.begin(9600);
    }
    void loop() {
      int xAxis = analogRead(A0); // Read Joysticks X-axis
      int yAxis = analogRead(A1); // Read Joysticks Y-axis
      // Y-axis used for forward and backward control
      if (yAxis < 470) {
        // Set Motor A backward
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1_2, HIGH);
        digitalWrite(in2_2, LOW);
        // Set Motor B backward
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        digitalWrite(in3_2, HIGH);
        digitalWrite(in4_2, LOW);
        // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
        motorSpeedA = map(yAxis, 470, 0, 0, 255);
        motorSpeedB = map(yAxis, 470, 0, 0, 255);
        motorSpeedA_2 = (int)((float)motorSpeedA*coeff);
        motorSpeedB_2 = (int)((float)motorSpeedB*coeff);
      }
      else if (yAxis > 550) {
        // Set Motor A forward
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in1_2, LOW);
        digitalWrite(in2_2, HIGH);
        // Set Motor B forward
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        digitalWrite(in3_2, LOW);
        digitalWrite(in4_2, HIGH);
        // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
        motorSpeedA = map(yAxis, 550, 1023, 0, 255);
        motorSpeedB = map(yAxis, 550, 1023, 0, 255);
        motorSpeedA_2 = (int)((float)motorSpeedA*coeff);
        motorSpeedB_2 = (int)((float)motorSpeedB*coeff);
      }
      // If joystick stays in middle the motors are not moving
      else {
        motorSpeedA = 0;
        motorSpeedB = 0;
        motorSpeedA_2 = 0;
        motorSpeedB_2 = 0;
      }
      // X-axis used for left and right control
      if (xAxis < 470) {
        // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
        int xMapped = map(xAxis, 470, 0, 0, 255);
        // Move to left - decrease left motor speed, increase right motor speed
        motorSpeedA = motorSpeedA - xMapped;
        motorSpeedB = motorSpeedB + xMapped;
        motorSpeedA_2 = (int)((float)motorSpeedA*coeff);
        motorSpeedB_2 = (int)((float)motorSpeedB*coeff);
        // Confine the range from 0 to 255
        if (motorSpeedA < 0) {
          motorSpeedA = 0;
          motorSpeedA_2 = 0;
        }
        if (motorSpeedB > 255) {
          motorSpeedB = 255;
          motorSpeedB_2 = (int)((float)255*coeff);
        }
      }
      if (xAxis > 550) {
        // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
        int xMapped = map(xAxis, 550, 1023, 0, 255);
        // Move right - decrease right motor speed, increase left motor speed
        motorSpeedA = motorSpeedA + xMapped;
        motorSpeedB = motorSpeedB - xMapped;
        motorSpeedA_2 = (int)((float)motorSpeedA*coeff);
        motorSpeedB_2 = (int)((float)motorSpeedB*coeff);
        // Confine the range from 0 to 255
        if (motorSpeedA > 255) {
          motorSpeedA = 255;
          motorSpeedA_2 = (int)((float)255*coeff);
        }
        if (motorSpeedB < 0) {
          motorSpeedB = 0;
          motorSpeedB_2 = 0;
        }
      }
      // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
      if (motorSpeedA < 70) {
        motorSpeedA = 0;
        motorSpeedA_2 = 0;
      }
      if (motorSpeedB < 70) {
        motorSpeedB = 0;
        motorSpeedB_2 = 0;
      }
      analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
      analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
      analogWrite(enA_2, motorSpeedA_2); // Send PWM signal to motor A
      analogWrite(enB_2, motorSpeedB_2); // Send PWM signal to motor B
      Serial.println(motorSpeedA_2);
      Serial.println(motorSpeedB_2);
      //delay(250);
    }
