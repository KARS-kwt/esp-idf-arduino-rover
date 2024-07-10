#include "GamePad.hpp"

GamePad gamepad;

const int left_pwm_pin = 26; // 32
const int left_dir_pin = 25; // 25
const int right_pwm_pin = 13; // 33
const int right_dir_pin = 12; // 26

const int left_forward_dir = 0; // 1
const int right_forward_dir = 1; // 0

const int max_pwm = 30; // 20

void setup() {
    Serial.begin(115200);
    gamepad.reset_allow_list();
    gamepad.setup("8C:41:F2:87:C3:6B"); // red: "23:86:70:7A:11:C3"
    // gamepad.setup();
    // gamepad.reset_allow_list();
    pinMode(right_pwm_pin, OUTPUT);
    pinMode(left_pwm_pin, OUTPUT);
    pinMode(right_dir_pin, OUTPUT);
    pinMode(left_dir_pin, OUTPUT);

    digitalWrite(left_dir_pin, left_forward_dir);
    digitalWrite(right_dir_pin, right_forward_dir);
}

void stop_all() {
    analogWrite(left_pwm_pin, 0);
    analogWrite(right_pwm_pin, 0);
}
void loop() {
    static int time_since_update = millis();

    if (gamepad.update()) {
        time_since_update = millis();
        GamepadState state = gamepad.getState();

        int left_pwm = map(abs(state.leftStick.y), 0, 500, 0, max_pwm);
        int right_pwm = map(abs(state.rightStick.y), 0, 500, 0, max_pwm);

        int left_dir = state.leftStick.y >= 0 ? left_forward_dir : !left_forward_dir;
        int right_dir = state.rightStick.y >= 0 ? right_forward_dir : !right_forward_dir;

        digitalWrite(left_dir_pin, left_dir);
        analogWrite(left_pwm_pin, left_pwm);

        digitalWrite(right_dir_pin, right_dir);
        analogWrite(right_pwm_pin, right_pwm);

        // Console.printf("Left PWM-DIR %d,%d Right PWM-DIR %d,%d\n", left_pwm, left_dir, right_pwm, right_dir);
    }

    if(millis() - time_since_update > 500) {
        stop_all();
        // Console.printf("Stopping\n");
    }

    delay(10);
}