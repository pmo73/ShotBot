#include <AccelStepper.h>
#include <Servo.h> 


#define dirPin 2
#define stepPin 3
#define FINGER_MIN_POS 13
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
Servo servo_under_arm;
Servo servo_finger;
Servo servo_arm;
int tasterPin = 8;
bool calibrated = false;
void setup() {  
  
    stepper.setMaxSpeed(100);
    stepper.setAcceleration(100);
    stepper.move(-1000);
    pinMode(tasterPin, INPUT_PULLUP);

    servo_finger.attach(5);
    servo_under_arm.attach(6);
    servo_arm.attach(9);
    servo_finger.write(FINGER_MIN_POS);
    servo_under_arm.write(0);
    servo_arm.write(0);
}

void loop() {
  
    //servo_arm.write(37);
    //servo_under_arm.write(17);
    servo_finger.write(14);
    stepper.runSpeedToPosition();
    if (!calibrated && digitalRead(tasterPin) == LOW) { 
      stepper.setCurrentPosition(0);
      stepper.moveTo(1);
      calibrated = true;
      delay(500);
    }
    
    if(calibrated) {
      for(int i = 0; i < 12; ++i) {
        if(stepper.distanceToGo() == 0) {
          stepper.runToNewPosition(30 + i * 40 * 1.07);  
          delay(1000);
        }
      }            
    }
}
