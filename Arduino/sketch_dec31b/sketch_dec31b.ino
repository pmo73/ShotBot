#include <AccelStepper.h>
#include <Servo.h> 


void grab_pipe();
void fill_shot(long position);


#define dirPin 2
#define stepPin 3
#define FINGER_MIN_POS 12
#define motorInterfaceType 1

#define SHOT_POSITION_0 80
#define SHOT_POSITION_1 250
#define SHOT_POSITION_2 430
#define SHOT_POSITION_3 610
#define SHOT_POSITION_4 780
#define SHOT_POSITION_5 940
#define SHOT_POSITION_6 1110
#define SHOT_POSITION_7 1280
#define SHOT_POSITION_8 1460
#define SHOT_POSITION_9 1620
#define SHOT_POSITION_10 1800
#define SHOT_POSITION_11 1980
#define SHOT_POSITION_12 160
#define SHOT_POSITION_13 340
#define SHOT_POSITION_14 520
#define SHOT_POSITION_15 690
#define SHOT_POSITION_16 860
#define SHOT_POSITION_17 1020
#define SHOT_POSITION_18 1200
#define SHOT_POSITION_19 1380
#define SHOT_POSITION_20 1530
#define SHOT_POSITION_21 1700
#define SHOT_POSITION_22 1870


AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
Servo servo_under_arm;
Servo servo_finger;
Servo servo_arm;


int tasterPin = 8;
int pumpenPin = 12;
bool calibrated = false;
bool schlauch = false;
bool reihe1_finished = false;
void setup() {  
  
    stepper.setMaxSpeed(50);
    stepper.setAcceleration(500);
    stepper.setSpeed(50);
    stepper.move(-1000000);
    pinMode(tasterPin, INPUT_PULLUP);
    pinMode(pumpenPin, OUTPUT);
    pinMode(13, OUTPUT);
    digitalWrite(pumpenPin, HIGH);
    digitalWrite(pumpenPin, LOW);
    delay(6000);
    digitalWrite(pumpenPin, HIGH);

    servo_finger.attach(5);
    servo_under_arm.attach(6);
    servo_arm.attach(9);
    servo_finger.write(90);
    servo_under_arm.write(0);
    servo_arm.write(0);
    
}

void loop() {
    stepper.runSpeed();
    if (!calibrated && digitalRead(tasterPin) == LOW) { 
      stepper.setCurrentPosition(0);
      stepper.moveTo(1);
    }
    if(stepper.distanceToGo() == 0) {
        calibrated = true;
        digitalWrite(13, HIGH);
    }
    
    if(calibrated) {
      if(!schlauch) {
        grab_pipe();
        schlauch = true;
      }
      if(schlauch) {
        if(stepper.distanceToGo() == 0) {
          if(!reihe1_finished) {
            stepper.runToNewPosition(SHOT_POSITION_0);          
            servo_finger.write(FINGER_MIN_POS);
            servo_arm.write(50);
            servo_under_arm.write(35);
            fill_shot(SHOT_POSITION_0);
            fill_shot(SHOT_POSITION_1);
            fill_shot(SHOT_POSITION_2);
            fill_shot(SHOT_POSITION_3);
            fill_shot(SHOT_POSITION_4);
            fill_shot(SHOT_POSITION_5);
            fill_shot(SHOT_POSITION_6);
            fill_shot(SHOT_POSITION_7);
            fill_shot(SHOT_POSITION_8);
            fill_shot(SHOT_POSITION_9);
            fill_shot(SHOT_POSITION_10);
            fill_shot(SHOT_POSITION_11);
            servo_arm.write(10);
            reihe1_finished = true;
            calibrated = false;
            digitalWrite(13, LOW);
            stepper.move(-1000000);
          } else {
            stepper.runToNewPosition(SHOT_POSITION_0);          
            servo_finger.write(FINGER_MIN_POS);
            servo_arm.write(20);
            servo_under_arm.write(20);
            fill_shot(SHOT_POSITION_12);
            fill_shot(SHOT_POSITION_13);
            fill_shot(SHOT_POSITION_14);
            fill_shot(SHOT_POSITION_15);
            fill_shot(SHOT_POSITION_16);
            fill_shot(SHOT_POSITION_17);
            fill_shot(SHOT_POSITION_18);
            fill_shot(SHOT_POSITION_19);
            fill_shot(SHOT_POSITION_20);
            fill_shot(SHOT_POSITION_21);
            fill_shot(SHOT_POSITION_22);
            reihe1_finished = false;
            calibrated = false;
            digitalWrite(13, LOW);
            delay(3000);
            stepper.move(-1000000);
          }
        }
      }        
    }
}

void grab_pipe() {
  servo_arm.write(39);
  servo_under_arm.write(17);
  delay(1000);
  servo_finger.write(FINGER_MIN_POS);
  delay(1000);
  servo_under_arm.write(7);
  servo_arm.write(20);
  delay(1000);
}

void fill_shot(long position) {
  stepper.runToNewPosition(position);
  delay(500);
  digitalWrite(pumpenPin, LOW);
  delay(4500);
  digitalWrite(pumpenPin, HIGH);
  delay(500);
  
}
