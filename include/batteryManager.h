// BatteryManager.h

#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include "Arduino.h"
long lastTime = 0;

int value = 0;
float voltage;
float maped_voltage;
float R1 = 56000.0;
float R2 = 33000.0;
int relay = 13;

void setupBatteryManager();
void updateBatteryStatus();
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

#endif  // BATTERY_MANAGER_H
