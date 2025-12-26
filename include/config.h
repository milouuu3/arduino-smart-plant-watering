#pragma once

// Hardware pins
#define MOISTURE_SENSOR_PIN A0
#define RELAY_PIN 7

// Moisture level thresholds (percentage)
#define DRY_THRESHOLD 33.33
#define MODERATE_THRESHOLD 66.66

// Blynk virtual pins
#define VPIN_MOISTURE V0
#define VPIN_PUMP V1

// System configuration
#define SENSOR_INTERVAL 1000L // Send data every 1 second
#define ADC_RESOLUTION 12     // 12-bit ADC (0-4095)
#define EEPROM_ADDR 0         // Pump status storage address
