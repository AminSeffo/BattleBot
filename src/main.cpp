/*
  Arduino FS-I6X Demo
  fsi6x-arduino-uno.ino
  Read output ports from FS-IA6B receiver module
  Display values on Serial Monitor
  
  Channel functions by Ricardo Paiva - https://gist.github.com/werneckpaiva/
  
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/
// Motor A
 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 10;
int in3 = 12;
int in4 = 13;
 
// Define Input Connections
#define CH2 3
#define CH1 5

#include <Arduino.h>
// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;


// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int channelMin,int channelMax, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  
  return map(ch, channelMin, channelMax, minLimit, maxLimit);
}


void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}
void demoOne(int speed)

{

  // This function will run the motors in both directions at a fixed speed

  // Turn on motor A

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enA, speed);

  // Turn on motor B

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enB, speed);

}
void motorControl(int ch1,int ch2)
{
  // This function will run the motors in both directions at a fixed speed

  // Turn on motor A and B - Forward
  if(ch1>0 && ch2 >= 0 && ch2 <= 10)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);	

    // Set speed to 200 out of possible range 0~255

    analogWrite(enA, ch1);
    analogWrite(enB, ch1);
  }
  // Turn on motor A and B - Backward
  else if(ch1<0 && ch2 >= 0 && ch2 <= 10)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);	

    // Set speed to 200 out of possible range 0~255

    analogWrite(enA, abs(ch1));
    analogWrite(enB, abs(ch1));
  }
  

  //turn it left
  else if( ch1 >= 0 && ch2 > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);	

    // Set speed to 200 out of possible range 0~255

    analogWrite(enA, abs(ch2));
    analogWrite(enB, abs(ch2));
  }
  //turn it right
  else if( ch1 >= 0 && ch2 < 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);	

    // Set speed to 200 out of possible range 0~255

    analogWrite(enA, abs(ch2));
    analogWrite(enB, abs(ch2));
  }

  // Stop the robot
  else if ( ch1 >= -2 && ch1 <= 3 && ch2 >= 0 && ch2 <= 10)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);	

    // Set speed to 200 out of possible range 0~255

    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  


}

void loop() {
  
  //demoOne();
  //delay(1000);
  // Get values for each channel
  ch1Value = readChannel(CH1, -250, 250, 1001,1991, 0);
  ch2Value = readChannel(CH2, -250, 250, 1004,1960, 0);
  //ch2Value = readChannel(CH2, -250, 250, 0);
  motorControl(ch1Value,ch2Value);
  
  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.println();


  
  delay(50);
}