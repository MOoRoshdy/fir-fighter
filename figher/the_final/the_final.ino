#include <Servo.h>
#include <NewPing.h>

// توصيلة متحكم الماتور
#define ENA 5
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENB 10

//توصيلة الريلي واللمبة الي هي ثاني اكسيد الكربون
#define WATER_PUMP_PIN 11
#define RED_LED_PIN 4

//توصيل الفليم
#define FLAME_SENSOR_LEFT A0 //شمال
#define FLAME_SENSOR_FRONT A1//امام
#define FLAME_SENSOR_RIGHT A2// اليمين

//توصيل الخلية الشمسية
#define SOLAR_INPUT A3

#define SERVO_FIRE_PIN 12//سيرفو لالتؤا
#define SERVO_SOLAR_PIN 3//سيرفو الخلية الشمسية

//توصيل الالترا
#define ULTRASONIC_TRIG 13
#define ULTRASONIC_ECHO 11

// === Constants ===
#define FLAME_THRESHOLD 850
#define SOLAR_THRESHOLD 700
#define MAX_SPEED 100
#define TURN_DURATION 700
#define DISTANCE_TO_CHECK 40
#define FIRE_DISTANCE_THRESHOLD 15

// === Globals ===
Servo fireServo;
Servo solarServo;
NewPing mySensor(ULTRASONIC_TRIG, ULTRASONIC_ECHO, 400);

bool fireDetected = false;
bool approachingFire = false;
bool solarLocked = false;

int solarScanAngle = 90;
int solarScanDirection = 1;
unsigned long lastFireTime = 0;

void setup() {
  // Motor Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Other Pins
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Init Devices
  fireServo.attach(SERVO_FIRE_PIN);
  solarServo.attach(SERVO_SOLAR_PIN);
  fireServo.write(90);
  solarServo.write(90);

  // Initial States
  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

void loop() {
  int solarValue = analogRead(SOLAR_INPUT);

  // === Solar Check ===
  if (!solarLocked) {
    solarServo.write(solarScanAngle);
    delay(100);
    solarScanAngle += solarScanDirection * 10;
    if (solarScanAngle >= 180 || solarScanAngle <= 0) {
      solarScanDirection *= -1;
    }

    if (solarValue >= SOLAR_THRESHOLD) {
      solarLocked = true;
      digitalWrite(RED_LED_PIN, LOW);
    } else {
      stopMotors();
      deactivatePump();
      digitalWrite(RED_LED_PIN, HIGH);
      return;
    }
  }

  // === Once Solar is Good ===
  digitalWrite(RED_LED_PIN, LOW);

  // Move in direction of light once after lock
  if (solarLocked) {
    if (solarScanAngle < 60) {
      turnRight(); delay(700);
    } else if (solarScanAngle > 120) {
      turnLeft(); delay(700);
    } else {
      moveForward(); delay(700);
    }
    stopMotors();
    solarLocked = false;
  }

  // === Fire Sensor Readings ===
  int flameLeft = analogRead(FLAME_SENSOR_LEFT);
  int flameFront = analogRead(FLAME_SENSOR_FRONT);
  int flameRight = analogRead(FLAME_SENSOR_RIGHT);

  // === Fire Detection ===
  if (flameLeft < FLAME_THRESHOLD || flameFront < FLAME_THRESHOLD || flameRight < FLAME_THRESHOLD) {
    fireDetected = true;
    lastFireTime = millis();
  } else if (millis() - lastFireTime > 30000) {
    fireDetected = false;
    approachingFire = false;
  }

  // === Fire Modes ===
  if (fireDetected) {
    fireFighterMode(flameLeft, flameFront, flameRight);
  } else {
    autoCareDriveMode();
  }
}

// === FireFighter Mode ===
void fireFighterMode(int flameLeft, int flameFront, int flameRight) {
  int distance = mySensor.ping_cm();

  if (!approachingFire) {
    moveForward();
    if (distance > 0 && distance <= FIRE_DISTANCE_THRESHOLD) {
      stopMotors();
      approachingFire = true;
      delay(500);
    }
  } else {
    if (flameLeft < FLAME_THRESHOLD && flameFront < FLAME_THRESHOLD && flameRight < FLAME_THRESHOLD) {
      activatePump();
    } else {
      deactivatePump();
    }

    if (flameFront < FLAME_THRESHOLD) {
      moveForward();
    } else if (flameLeft < FLAME_THRESHOLD) {
      turnLeft();
    } else if (flameRight < FLAME_THRESHOLD) {
      turnRight();
    } else {
      stopMotors();
    }
  }
}

// === Auto Obstacle Avoidance ===
void autoCareDriveMode() {
  int distance = mySensor.ping_cm();

  if (distance > 0 && distance < DISTANCE_TO_CHECK) {
    stopMotors();
    delay(500);

    moveBackward();
    delay(500);

    stopMotors();
    delay(500);

    fireServo.write(180);
    delay(500);
    int distanceLeft = mySensor.ping_cm();

    fireServo.write(0);
    delay(500);
    int distanceRight = mySensor.ping_cm();

    fireServo.write(90);
    delay(500);

    if (distanceLeft == 0 || distanceLeft > distanceRight) {
      turnLeft(); delay(TURN_DURATION);
    } else {
      turnRight(); delay(TURN_DURATION);
    }
  } else {
    moveForward();
  }
}

// === Movement Functions ===
void moveForward() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// === Pump Control ===
void activatePump() {
  digitalWrite(WATER_PUMP_PIN, HIGH);
}

void deactivatePump() {
  digitalWrite(WATER_PUMP_PIN, LOW);
}
