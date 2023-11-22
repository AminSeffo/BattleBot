#include <Arduino.h>
#include <motorSetup.cpp>
#include <batteryManager.cpp>

// Define channel constants for drive
#define CH1 9  // right stick x-axis (left/right) - horizontal
#define CH2 10 // right stick y-axis (up/down) - vertical

// Define channel constants for weapon
#define CH3 11  // switch on the top left of the controller
#define CH5 3
 // Integers to represent values from sticks and pots
int ch3Value;
int raw_values;
int x;
int y;
int z;
// Motor A
int enA = 6;
int in1 = 4;
int in2 = 7;

// Motor B
int enB = 5;
int in3 = 2;
int in4 = 8;

//  Weapon pin
int weopon_pin = 12;


// MotorDrive struct to hold motor setup information
MotorDrive steering = {CH2, CH1, enA, enB, in1, in2, in3, in4};

// MotorWeapon struct to hold motor setup information
MotorWeapon weapon = {CH3, weopon_pin};

/**
 * Read the number of a specified channel and convert it to the given range.
 * If the channel is off, return the default value.
 *
 * @param channelInput  The input pin for the channel
 * @param minLimit      The minimum value for the output range
 * @param maxLimit      The maximum value for the output range
 * @param channelMin    The minimum pulse width for the channel when it's off
 * @param channelMax    The maximum pulse width for the channel when it's on
 * @param defaultValue  The value to return if the channel is off
 *
 * @return The mapped value within the specified range
 */
int readChannel(int channelInput, int minLimit, int maxLimit, int channelMin, int channelMax, int defaultValue) {
  // ToDo:
  // change 30000 to 25000
  int ch = pulseIn(channelInput, HIGH, 35000);
  //if (ch < 100) return defaultValue;


  return map(ch, channelMin, channelMax, minLimit, maxLimit);
}
int readChannel_raw(int channelInput, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 35000);
  //if (ch < 1000) return defaultValue;
  return ch;
}
void setup() {
  // Initialize the Serial Monitor
  Serial.begin(9600);
  // setup the battery manager
  setupBatteryManager();

  // Setup motor control for drive
  setupDrive(steering);
  delay(1000);
  // Setup motor control for weapon
  setupWeapon(weapon);
}

void loop() {
  // update the battery status
  
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // Read values from channels and map them to the desired range
  x = readChannel(CH2, -500, 500, 1003, 1989, 0);
  y = readChannel(CH1, -500, 500, 1001, 1989, 0);
  ch3Value = readChannel(CH3, -500, 500, 995, 1989, 0);
  x = constrain(x, -255, 255);
  y = constrain(y, -255, 255);
  z = constrain(ch3Value, -255, 255);
  delay(50);

  int right = y+x;
  int left = y-x;
  
  int raw_value_2 =readChannel_raw(CH2, 0);

  int raw_value_1 =readChannel_raw(CH1, 0);
  int raw_value_3 =readChannel_raw(CH3, 0);
  weoponControlnew(weapon, z);

  arcSteering(steering, left, right);
if (raw_value_1 == 0 && raw_value_2 == 0 && raw_value_3 == 0)
{
  turnMotorOff(steering);
  turnWeaponOff(weapon);
 }


  //if (raw_value_3 > 1000){
  //  weoponControl(weapon, z);
  //  }
 //if (raw_value_4 > 1000){
 // x = readChannel(CH1, -200, 200, 1001, 1987, 0);
 // y = readChannel(CH2, -200, 200, 1001, 1989, 0);
 //  tankSteering(steering, x, y);  
 // }
  // print them all in one line

  Serial.print("CH1: ");
  Serial.print(raw_value_1);
  Serial.print(" CH2: ");
  Serial.print(raw_value_2);
  Serial.print(" CH3: ");
  Serial.print(raw_value_3);
  Serial.print(" CH5: ");
  Serial.println("");
  
}