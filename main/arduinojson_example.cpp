#include <Arduino.h>
#include <ArduinoJson.h>

#define JSON_CAPACITY 200
#define period 1000

void setup() {
    Serial.begin(115200);
}

void loop() {
    StaticJsonDocument<JSON_CAPACITY> doc;

    auto now = millis();

    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n');
        DeserializationError error = deserializeJson(doc, receivedData);

        if (!error) {
            // Successfully parsed JSON, now extract the speed value
            if (doc.containsKey("speed")) {
                int speed = doc["speed"];
                int steering_angle = doc["steering-angle"];
                Serial.println("Speed: " + String(speed));
                Serial.println("Steering: " + String(steering_angle));
            }
        } else {
            Serial.println("JSON parsing failed!");
        }
    }
    auto velocity = 100.0 * sin(2 * PI * now / period);
    float angle = 2 * PI * now / period;
    const float radius = 20.0;
    float x_position = radius * cos(angle);
    float y_position = radius * sin(angle);
    

    doc.clear();
    doc["time"] = now;
    doc["velocity"] = velocity;
    doc["x"] = x_position;
    doc["y"] = y_position;

    serializeJson(doc, Serial);
    Serial.println();
    delay(100);
}
