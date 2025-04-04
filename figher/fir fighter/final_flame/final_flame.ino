// Motor Driver Pins (L298N)
#define ENA 5  // Speed control left motor
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENB 10 // Speed control right motor

// Flame Sensor Pins
#define FLAME_SENSOR_LEFT A0
#define FLAME_SENSOR_FRONT A1
#define FLAME_SENSOR_RIGHT A2

// Water Pump Relay
#define WATER_PUMP_PIN 11

// Fire Detection Threshold (Adjust based on testing)
#define FLAME_THRESHOLD 850

void setup() {
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(WATER_PUMP_PIN, OUTPUT);
    digitalWrite(WATER_PUMP_PIN, LOW);  // Keep pump OFF initially
}

void loop() {
    int flameLeft = analogRead(FLAME_SENSOR_LEFT);
    int flameFront = analogRead(FLAME_SENSOR_FRONT);
    int flameRight = analogRead(FLAME_SENSOR_RIGHT);

    if (flameFront < FLAME_THRESHOLD) {
        moveForward();
    } else if (flameLeft < FLAME_THRESHOLD) {
        turnLeft();
    } else if (flameRight < FLAME_THRESHOLD) {
        turnRight();
    } else {
        stopMotors();
    }

    // If fire detected, stop and activate the pump
    if (flameLeft < FLAME_THRESHOLD || flameFront < FLAME_THRESHOLD || flameRight < FLAME_THRESHOLD) {
        activatePump();
    } else {
        deactivatePump();
    }
}

// Motor Control Functions
void moveForward() {
    analogWrite(ENA, 150); // Adjust speed
    analogWrite(ENB, 150);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnLeft() {
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void turnRight() {
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void stopMotors() {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

void activatePump() {
    digitalWrite(WATER_PUMP_PIN, HIGH); // Turn ON pump
}

void deactivatePump() {
    digitalWrite(WATER_PUMP_PIN, LOW); // Turn OFF pump
}
