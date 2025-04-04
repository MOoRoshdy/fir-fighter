#include <Servo.h>    //1    
#include <NewPing.h>      

// Motor Driver Pins (L298N)
#define ENA 5  
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENB 10

// Flame Sensor Pins
#define FLAME_SENSOR_LEFT A0 //
#define FLAME_SENSOR_FRONT A1
#define FLAME_SENSOR_RIGHT A2

// Water Pump Relay
#define WATER_PUMP_PIN 11

// Fire Detection Threshold
#define FLAME_THRESHOLD 850

// Ultrasonic Sensor & Servo
#define SERVO_PIN 12
#define ULTRASONIC_SENSOR_TRIG 13    
#define ULTRASONIC_SENSOR_ECHO 11    
#define MAX_SPEED 100   
#define TURN_DURATION 700  
#define DISTANCE_TO_CHECK 40 

NewPing mySensor(ULTRASONIC_SENSOR_TRIG, ULTRASONIC_SENSOR_ECHO, 400);
Servo myServo;

// Fire-fighting mode flag
bool fireDetected = false;
unsigned long lastFireTime = 0;

void setup() {
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(WATER_PUMP_PIN, OUTPUT);
    
    digitalWrite(WATER_PUMP_PIN, LOW);  // Keep pump OFF initially
    myServo.attach(SERVO_PIN);
    myServo.write(90);
}

void loop() {
    int flameLeft = analogRead(FLAME_SENSOR_LEFT);
    int flameFront = analogRead(FLAME_SENSOR_FRONT);
    int flameRight = analogRead(FLAME_SENSOR_RIGHT);

    // Check if fire is detected
    if (flameLeft < FLAME_THRESHOLD || flameFront < FLAME_THRESHOLD || flameRight < FLAME_THRESHOLD) {
        fireDetected = true;  
        lastFireTime = millis(); // Reset fire timer
    }

    if (fireDetected) {
        fireFighterMode(flameLeft, flameFront, flameRight);
    } else {
        unsigned long currentTime = millis();
        if (currentTime - lastFireTime > 30000) {  // Wait 30 seconds before switching back
            autoCareDriveMode();
        }
    }
}

// Fire-fighting mode function
void fireFighterMode(int flameLeft, int flameFront, int flameRight) {
    if (flameFront < FLAME_THRESHOLD) {
        moveForward();
    } else if (flameLeft < FLAME_THRESHOLD) {
        turnLeft();
    } else if (flameRight < FLAME_THRESHOLD) {
        turnRight();
    } else {
        stopMotors();
    }
    activatePump();
}

// Obstacle avoidance mode function
void autoCareDriveMode() {
    int distance = mySensor.ping_cm();

    if (distance > 0 && distance < DISTANCE_TO_CHECK) {
        stopMotors();
        delay(500);

        moveBackward();
        delay(500);

        stopMotors();
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
            turnLeft();
            delay(TURN_DURATION);
        } else {
            turnRight();
            delay(TURN_DURATION);
        }
    } else {
        moveForward();
    }
}

// Motor control functions
void moveForward() {
    analogWrite(ENA, MAX_SPEED);
    analogWrite(ENB, MAX_SPEED);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward() {
    analogWrite(ENA, MAX_SPEED);
    analogWrite(ENB, MAX_SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft() {
    analogWrite(ENA, MAX_SPEED);
    analogWrite(ENB, MAX_SPEED);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnRight() {
    analogWrite(ENA, MAX_SPEED);
    analogWrite(ENB, MAX_SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void stopMotors() {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

void activatePump() {
    digitalWrite(WATER_PUMP_PIN, HIGH);
}

void deactivatePump() {
    digitalWrite(WATER_PUMP_PIN, LOW);
}
