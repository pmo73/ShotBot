#include <AccelStepper.h>
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int tasterPin = 8;
void setup() {  
  
  stepper.setMaxSpeed(200);
  stepper.setSpeed(200);
  stepper.setAcceleration(20);
  stepper.moveTo(-50);
  Serial.begin(115200);
  Serial.print("\n");
  pinMode(tasterPin, INPUT_PULLUP);
}

void loop() {
    stepper.runSpeedToPosition();
    if (digitalRead(tasterPin) == LOW) { 
      Serial.print("Pressed ");
      Serial.flush();
      stepper.moveTo(20);
    }
}

/*#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  servo1.attach(3);
  servo2.attac
  h(5);
  servo3.attach(6);
  servo4.attach(9);
}

void loop() {
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  delay(1000);
  servo1.write(30);
  delay(1000);
  servo1.write(60);
  delay(1000);
  servo1.write(90);
  delay(1000);
  servo1.write(120);
  delay(1000);
  servo1.write(150);
  delay(1000);
  servo1.write(180);
  delay(1000);
  servo1.write(210);
  delay(1000);
  servo1.write(240);
  delay(1000);
  servo1.write(270);
  delay(1000);
  servo1.write(300);
  delay(1000);
  servo1.write(330);
  delay(1000);
  servo1.write(360);
  delay(1000);
}*/