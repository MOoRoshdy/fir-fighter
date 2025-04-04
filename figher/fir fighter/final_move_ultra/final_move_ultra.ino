#include <Servo.h>         // Include library to control the servo motor
#include <NewPing.h>        // Include library to interface with the ultrasonic sensor

// Pin definitions
#define SERVO_PIN 12                // Pin connected to the servo motor
#define ULTRASONIC_SENSOR_TRIG 10    // Pin for the ultrasonic sensor trigger
#define ULTRASONIC_SENSOR_ECHO 11    // Pin for the ultrasonic sensor echo
#define MAX_REGULAR_MOTOR_SPEED 75  // Maximum speed for regular motor movement
#define MAX_MOTOR_ADJUST_SPEED 150   // Maximum speed when adjusting motor direction
#define DISTANCE_TO_CHECK 40         // Distance threshold (cm) to trigger object detection
#define TURN_DURATION 700            // Duration to rotate 100 degrees (adjust as needed)

// Right motor pin assignments
int enableRightMotor = 5;            // Pin to control the speed of the right motor
int rightMotorPin1 = 1;              // Pin 1 for controlling right motor direction
int rightMotorPin2 = 0;              // Pin 2 for controlling right motor direction

// Left motor pin assignments
int enableLeftMotor = 3;             // Pin to control the speed of the left motor
int leftMotorPin1 = 2;               // Pin 1 for controlling left motor direction
int leftMotorPin2 = 4;               // Pin 2 for controlling left motor direction

// Initialize ultrasonic sensor with trigger and echo pins, and a max distance of 400 cm
NewPing mySensor(ULTRASONIC_SENSOR_TRIG, ULTRASONIC_SENSOR_ECHO, 400);
Servo myServo;  // Create a servo object

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);

  rotateMotor(0, 0);   
}

void loop() {
  int distance = mySensor.ping_cm();

  if (distance > 0 && distance < DISTANCE_TO_CHECK) {
    rotateMotor(0, 0);
    delay(500);
    
    rotateMotor(-MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED);        
    delay(500);
    
    rotateMotor(0, 0);
    delay(500);
    
    myServo.write(180);
    delay(500);
    int distanceLeft = mySensor.ping_cm();
    
    myServo.write(0);    
    delay(500);    
    int distanceRight = mySensor.ping_cm();

    myServo.write(90); 
    delay(500);        
    
    if (distanceLeft == 0 || distanceLeft > distanceRight) {
      rotateMotor(MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED);
      delay(TURN_DURATION);
    } else {
      rotateMotor(-MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED);
      delay(TURN_DURATION);
    }

    rotateMotor(0, 0);    
    delay(200);     
  }
  else {
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);    
  }
  else if (rightMotorSpeed >= 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);      
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);    
  }
  else if (leftMotorSpeed >= 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);      
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
