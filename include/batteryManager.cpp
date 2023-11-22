#include "Arduino.h"
#include "batteryManager.h"

// Define a global variable to track the time elapsed after voltage drops below 11.80
unsigned long cutoffStartTime = 0;
const unsigned long cutoffDuration = 5000;  // 5 seconds in milliseconds
float previousVoltage = 0.0;

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    if (in_max - in_min == 0) {
        return 0.0;
    }
    
    float mappedValue = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

    return mappedValue;
}

void setupBatteryManager() {
    pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);
    Serial.println("Relay is on");
}


void updateBatteryStatus() {
    value = analogRead(A0);
    voltage = value * (5.0 / 1024) * ((R1 + R2) / R2);
    maped_voltage = mapFloat(voltage, 0.0, 12.46, 0.0, 12.59);

    if (maped_voltage < 11.90) {
        if (cutoffStartTime == 0) {
            // Record the start time only if it's the first time voltage is below 11.80
            cutoffStartTime = millis();
            Serial.println("Voltage is below 11.80. Start time recorded.");
        }

        // Check if 5 seconds have elapsed since the voltage dropped below 11.80
        if ((millis() - cutoffStartTime) >= cutoffDuration) {
            // Perform cutoff action here
            // For example, turn off another component
            Serial.println("Voltage has been below 11.80 for 5 seconds. Cutoff action performed.");
            digitalWrite(relay, LOW);
            cutoffStartTime = 0;  // Reset the cutoff timer
        } else {
            // Check if the voltage is still decreasing
            if (maped_voltage < previousVoltage) {
                // Calculate and print the remaining time
                unsigned long remainingTime = cutoffDuration - (millis() - cutoffStartTime);
                Serial.print("Waiting for ");
                Serial.print(remainingTime / 1000); // Convert to seconds
                Serial.println(" seconds before cutoff...");
            } else {
                // Reset the cutoff timer if the voltage is increasing
                cutoffStartTime = millis();
                Serial.println("Voltage is increasing. Timer reset.");
            }
        }
    } else {
        // Voltage is above 11.80, reset the cutoff timer
        cutoffStartTime = 0;
        Serial.println("Voltage is above 11.80. Timer reset.");
    }

    Serial.print("Battery Voltage = ");
    Serial.println(maped_voltage);
    
    // Save the current voltage for comparison in the next iteration
    previousVoltage = maped_voltage;
    
    //delay(1000);
}
