#include <Servo.h>

// -------------------- Pins -----------------------
const int SERVO_PAN_PIN = 3;   // servosweep
const int SERVO_TILT_PIN = 9;  // servo2

// Motor 1 (left)
const int M1_IN1 = 4;
const int M1_IN2 = 5;

// Motor 2 (right)
const int M2_IN1 = 6;
const int M2_IN2 = 7;

// -------------------- State --------------------
int a = 90; // pan angle (servosweep) - starts centered
int b = 90; // mirror variable used by 'b' command in the report

Servo servosweep;  // pan mechanism
Servo servo2;      // angle presets

// -------------------- Motor helpers --------------------
void forward() {
  // motor1
  digitalWrite(M1_IN2, HIGH);
  digitalWrite(M1_IN1, LOW);
  // motor2
  digitalWrite(M2_IN2, HIGH);
  digitalWrite(M2_IN1, LOW);
}

void backward() {
  // motor1
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M1_IN1, HIGH);
  // motor2
  digitalWrite(M2_IN2, LOW);
  digitalWrite(M2_IN1, HIGH);
}

void right() {
  // spin right: left motor backward, right motor forward
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M2_IN2, HIGH);
  digitalWrite(M2_IN1, LOW);
}

void left() {
  // spin left: left motor forward, right motor backward
  digitalWrite(M1_IN2, HIGH);
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
  digitalWrite(M2_IN1, HIGH);
}

void stops() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
}

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600); // HC-05 default data-mode baud

  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);

  pinMode(SERVO_PAN_PIN, OUTPUT);
  pinMode(SERVO_TILT_PIN, OUTPUT);

  servosweep.attach(SERVO_PAN_PIN);
  servo2.attach(SERVO_TILT_PIN);

  servosweep.write(90);
  servo2.write(90);
}

// -------------------- Main loop --------------------
void loop() {
  if (Serial.available() > 0) {
    char ch = (char)Serial.read();

    if (ch == 'F') {
      forward();
    } else if (ch == 'B') {
      backward();
    } else if (ch == 'L') {
      left();
    } else if (ch == 'R') {
      right();
    } else if (ch == 'S') {
      stops();
    } else if (ch == 'a') {
      // Pan +5 degrees
      a += 5;
      if (a > 180) a = 180;
      servosweep.write(a);
      b = a; // mirrors the report’s behavior
    } else if (ch == 'b') {
      // Pan -5 degrees using 'b'
      b -= 5;
      if (b < 0) b = 0;
      servosweep.write(b);
    } else if (ch == 'c') {
      // Tilt preset ~20°
      servo2.write(20);
    } else if (ch == 'd') {
      // Tilt preset ~100°
      servo2.write(100);
    } else if (ch == 'e') {
      // Tilt preset ~160°
      servo2.write(160);
    }
  }
}
