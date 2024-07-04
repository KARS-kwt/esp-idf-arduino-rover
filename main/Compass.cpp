#include "AttitudeSensor.hpp"
#include <Arduino.h>

AttitudeSensor::AttitudeSensor() {}

void AttitudeSensor::begin() {
    Serial.begin(115200);
    while (!Serial) delay(10); // Wait for serial console to open

    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
    mpu.setMotionDetectionThreshold(1);
    mpu.setMotionDetectionDuration(20);
    mpu.setInterruptPinLatch(true); // Keep it latched. Will turn off when reinitialized.
    mpu.setInterruptPinPolarity(true);
    mpu.setMotionInterrupt(true);
}

bool AttitudeSensor::checkForMotion() {
    return mpu.getMotionInterruptStatus();
}

void AttitudeSensor::readSensors(float &accelX, float &accelY, float &accelZ, float &gyroX, float &gyroY, float &gyroZ) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    accelX = a.acceleration.x;
    accelY = a.acceleration.y;
    accelZ = a.acceleration.z;
    gyroX = g.gyro.x;
    gyroY = g.gyro.y;
    gyroZ = g.gyro.z;
}