#ifndef AttitudeSensor_hpp
#define AttitudeSensor_hpp

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class AttitudeSensor {
public:
    AttitudeSensor();
    void begin();
    bool checkForMotion();
    void readSensors(float &accelX, float &accelY, float &accelZ, float &gyroX, float &gyroY, float &gyroZ);

private:
    Adafruit_MPU6050 mpu;
};

#endif /* AttitudeSensor_hpp */