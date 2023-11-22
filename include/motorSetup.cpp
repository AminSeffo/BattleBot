#include "Arduino.h"
#include "batteryManager.h"
// Autor: Amin Seffo
// Project: BattleBot
unsigned long lastNonZeroTime = 0;
const unsigned long zeroDelayDuration = 1000;  // 5 seconds in millisecondsbool weaponOn = false;
struct MotorDrive
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

struct  MotorWeapon
{
  int ch3;
  int weopon_pin;
};


// Initialize the motor
void setupDrive(MotorDrive motor)
{
  pinMode(motor.ch1, INPUT);
  pinMode(motor.ch2, INPUT);
  pinMode(motor.enA, OUTPUT);
  pinMode(motor.enB, OUTPUT);
  pinMode(motor.in1, OUTPUT);
  pinMode(motor.in2, OUTPUT);
  pinMode(motor.in3, OUTPUT);
  pinMode(motor.in4, OUTPUT);
  //ensure the motor is off
  digitalWrite(motor.in1, LOW);
  digitalWrite(motor.in2, LOW);
  digitalWrite(motor.in3, LOW);
  digitalWrite(motor.in4, LOW);

}

// Initialize the motor
void setupWeapon(MotorWeapon motor)
{
  pinMode(motor.ch3, INPUT);
  pinMode(motor.weopon_pin, OUTPUT);
  //ensure the weapon is off
  digitalWrite(motor.weopon_pin, LOW);
  
  
}

// turn the weapon off
void turnWeaponOff(MotorWeapon motor)
{
  digitalWrite(motor.weopon_pin, LOW);
}

void turnWeaponOn(MotorWeapon motor)
{
  digitalWrite(motor.weopon_pin, HIGH);
}
//turn the motor off
void turnMotorOff(MotorDrive motor)
{
  digitalWrite(motor.in1, LOW);
  digitalWrite(motor.in2, LOW);
  digitalWrite(motor.in3, LOW);
  digitalWrite(motor.in4, LOW);
}


// Control the robot with tank drive
void tankSteering(MotorDrive motor,int ch1value,int ch2value)
{
  // This function will run the motors in different directions at a fixed speed

  // Forward
  if (ch1value > 5)
  {
    Serial.println("Forward");
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, HIGH);
    digitalWrite(motor.in3, LOW);
    digitalWrite(motor.in4, HIGH);

    // Set speed to motor.ch1 out of the possible range 0~255
    analogWrite(motor.enA, abs(ch1value));
    analogWrite(motor.enB, abs(ch1value));
  }
  // Backward
  else if (ch1value < -5)
  {
    Serial.println("Backward");
    digitalWrite(motor.in1, HIGH);
    digitalWrite(motor.in2, LOW);
    digitalWrite(motor.in3, HIGH);
    digitalWrite(motor.in4, LOW);

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
  else if (ch2value < -15)
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
void weoponControl(MotorWeapon weapon, int weapon_speed) {
  if (weapon_speed >0) {
    // Weapon speed is greater than 1500, keep the weapon on
    turnWeaponOn(weapon);
    lastNonZeroTime = millis();  // Update the time when the speed is non-zero
  } else if (weapon_speed == 0) {
    // Weapon speed is zero, check if it has been zero for 5 seconds
    if (millis() - lastNonZeroTime >= zeroDelayDuration) {
      turnWeaponOff(weapon);
    }
  }
}
void weoponControlnew(MotorWeapon weapon, int weapon_speed) {
  if (weapon_speed > 0) {
    // Weapon speed is greater than 1500, keep the weapon on
    turnWeaponOn(weapon);
  }
   else
   {
      turnWeaponOff(weapon);
   } 
  }
 void arcSteering(MotorDrive motor,int speed_a,int speed_b)

{
  speed_a = constrain(speed_a, -255, 255);
  speed_b = constrain(speed_b, -255, 255);
  Serial.println(speed_a);
  Serial.println(speed_b);
  Serial.println(" ");
  // set direction of motor A
  //speed between i -10 and 10 is considered as stop
  if (speed_a == 0)
  {
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, LOW);
    updateBatteryStatus();

  }
  else if (speed_a > 30)
  {
    digitalWrite(motor.in1, HIGH);
    digitalWrite(motor.in2, LOW);
  }
  else if (speed_a < -30)
  {
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, HIGH);
  }

  // set direction of motor B
  if (speed_b == 0)
  {
    digitalWrite(motor.in3, LOW);
    digitalWrite(motor.in4, LOW);
    updateBatteryStatus();
  }
  else if (speed_b > 30)
  {
    digitalWrite(motor.in3, HIGH);
    digitalWrite(motor.in4, LOW);
  }
  else if ((speed_b < -30))
  {
    digitalWrite(motor.in3, LOW);
    digitalWrite(motor.in4, HIGH);
    
  }
  // set speed of motor A and B
  analogWrite(motor.enA, abs(speed_a));
  analogWrite(motor.enB, abs(speed_b));



}