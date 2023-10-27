#include "Arduino.h"
struct Motor
{
  int ch1;
  int ch2;
  int enA;
  int enB;
  int in1;
  int in2;
  int in3;
  int in4;
};

// Initialize the motor
void setupMotor(Motor motor)
{
  pinMode(motor.enA, OUTPUT);
  pinMode(motor.enB, OUTPUT);
  pinMode(motor.in1, OUTPUT);
  pinMode(motor.in2, OUTPUT);
  pinMode(motor.in3, OUTPUT);
  pinMode(motor.in4, OUTPUT);
}

// Control the motor based on the struct
void motorControl(Motor motor,int ch1value,int ch2value)
{
  // This function will run the motors in different directions at a fixed speed

  // Forward
  if (ch1value > 5)
  {
    Serial.println("Forward");
    digitalWrite(motor.in1, HIGH);
    digitalWrite(motor.in2, LOW);
    digitalWrite(motor.in3, HIGH);
    digitalWrite(motor.in4, LOW);

    // Set speed to motor.ch1 out of the possible range 0~255
    analogWrite(motor.enA, abs(ch1value));
    analogWrite(motor.enB, abs(ch1value));
  }
  // Backward
  else if (ch1value < -5)
  {
    Serial.println("Backward");
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, HIGH);
    digitalWrite(motor.in3, LOW);
    digitalWrite(motor.in4, HIGH);

    // Set speed to abs(motor.ch1) out of the possible range 0~255
    analogWrite(motor.enA, abs(ch1value));
    analogWrite(motor.enB, abs(ch1value));
  }

  // Turn left
  else if (ch2value > 10)
  {
    Serial.println("Left");
    digitalWrite(motor.in1, HIGH);
    digitalWrite(motor.in2, LOW);
    digitalWrite(motor.in3, LOW);
    digitalWrite(motor.in4, HIGH);

    // Set speed to abs(motor.ch2) out of the possible range 0~255
    analogWrite(motor.enA, abs(ch2value));
    analogWrite(motor.enB, abs(ch2value));
  }
  // Turn right
  else if (ch2value < -10)
  {
    Serial.println("Turn right");
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, HIGH);
    digitalWrite(motor.in3, HIGH);
    digitalWrite(motor.in4, LOW);

    // Set speed to abs(motor.ch2) out of the possible range 0~255
    analogWrite(motor.enA, abs(ch2value));
    analogWrite(motor.enB, abs(ch2value));
  }
  // Stop the motor
  else if (ch1value >= -5 && ch1value <= 5 && ch2value >= -5 && ch2value <= 5)
  {
    Serial.println("Stop");
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, LOW);
    digitalWrite(motor.in3, LOW);
    digitalWrite(motor.in4, LOW);

    // Set speed to 0
    analogWrite(motor.enA, 0);
    analogWrite(motor.enB, 0);
  }
  else
  {
    Serial.println("Error");
    analogWrite(motor.enA, 0);
    analogWrite(motor.enB, 0);
  }
}
