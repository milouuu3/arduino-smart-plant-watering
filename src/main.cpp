#define BLYNK_PRINT Serial

#include "Arduino_LED_Matrix.h"
#include <Arduino.h>
#include <BlynkSimpleWifi.h>
#include <EEPROM.h>
#include <WiFiS3.h>

#include "config.h"
#include "credentials.h"
#include "led_frames.h"

BlynkTimer timer;
ArduinoLEDMatrix matrix;

int sensorValue = 0;
int pumpStatus = 0;
float moisturePercent = 0.0;

/**
 * Blynk callback to receive pump control commands from mobile app
 */
BLYNK_WRITE(VPIN_PUMP)
{
    pumpStatus = param.asInt();
    EEPROM.write(EEPROM_ADDR, pumpStatus);
}

/**
 * Sends current moisture percentage to Blynk cloud
 */
void sendSensorData()
{
    Blynk.virtualWrite(VPIN_MOISTURE, moisturePercent);
}

/**
 * Reads soil moisture sensor and updates LED matrix status
 */
void trackSoilMoisture()
{
    sensorValue = analogRead(MOISTURE_SENSOR_PIN);
    moisturePercent = 100.0 - ((float)sensorValue / 4096.0) * 100.0;

    if (moisturePercent >= 0 && moisturePercent < DRY_THRESHOLD)
    {
        Serial.println("DRY");
        matrix.loadFrame(SAD_STATUS);
    }
    else if (moisturePercent >= DRY_THRESHOLD && moisturePercent < MODERATE_THRESHOLD)
    {
        Serial.println("MODERATE");
        matrix.loadFrame(NORMAL_STATUS);
    }
    else if (moisturePercent >= MODERATE_THRESHOLD && moisturePercent <= 100)
    {
        Serial.println("WET");
        matrix.loadFrame(HAPPY_STATUS);
    }
}

/**
 * Initializes GPIO pins, ADC resolution, and LED matrix
 */
void initPeripherals()
{
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(MOISTURE_SENSOR_PIN, INPUT);
    analogReadResolution(ADC_RESOLUTION);
    matrix.begin();
}

/**
 * Arduino setup function - runs once at startup
 */
void setup()
{
    Serial.begin(9600);

    initPeripherals();

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    timer.setInterval(SENSOR_INTERVAL, sendSensorData);

    pumpStatus = EEPROM.read(EEPROM_ADDR);
}

/**
 * Arduino main loop - runs continuously
 */
void loop()
{
    Blynk.run();
    timer.run();
    trackSoilMoisture();

    if (pumpStatus == 0)
    {
        Serial.println("Water pump is off");
        digitalWrite(RELAY_PIN, LOW);
    }
    else if (pumpStatus == 1)
    {
        Serial.println("Water pump is on");
        digitalWrite(RELAY_PIN, HIGH);
    }

    delay(500);
}
