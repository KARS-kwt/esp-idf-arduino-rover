#include "GamePad.hpp"
#include <Arduino.h>
#include <uni.h>
ControllerPtr GamePad::myControllers[BP32_MAX_GAMEPADS] = {nullptr};
GamepadState GamePad::gamepadState;

GamePad::GamePad() {}

void GamePad::setup(const char* controller_addr_string) {
    bd_addr_t controller_addr;
    sscanf_bd_addr(controller_addr_string, controller_addr);
    uni_bt_allowlist_add_addr(controller_addr);
    uni_bt_allowlist_set_enabled(true);

    Console.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Console.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    BP32.setup(&GamePad::onConnectedController, &GamePad::onDisconnectedController);
    BP32.enableBLEService(false);
}

void GamePad::setup() {
    uni_bt_allowlist_set_enabled(false);

    Console.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Console.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    BP32.setup(&GamePad::onConnectedController, &GamePad::onDisconnectedController);
    BP32.enableBLEService(false);
}

void GamePad::reset_allow_list() {
    uni_bt_allowlist_remove_all();
    
}

bool GamePad::update() {
    bool dataUpdated = BP32.update();
    if (dataUpdated) {
        for (auto ctl : myControllers) {
            if (ctl && ctl->isConnected() && ctl->hasData()) {
                if (ctl->isGamepad()) {
                    gamepadState.A = ctl->a();
                    gamepadState.B = ctl->b();
                    gamepadState.X = ctl->x();
                    gamepadState.Y = ctl->y();
                    gamepadState.leftStick.x = ctl->axisX();
                    gamepadState.leftStick.y = ctl->axisY();
                    gamepadState.rightStick.x = ctl->axisRX();
                    gamepadState.rightStick.y = ctl->axisRY();
                    gamepadState.L1 = ctl->l1();
                    gamepadState.R1 = ctl->r1();
                    // Console.printf("X: %d\n", ctl->axisX());
                } else {
                    Console.printf("Unsupported controller\n");
                }
            }
        }
    }
    return dataUpdated;
}

GamepadState GamePad::getState() {
    return gamepadState;
}

void GamePad::onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Console.printf("CALLBACK: Controller is connected, index=%d\n", i);
            ControllerProperties properties = ctl->getProperties();
            Console.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName(), properties.vendor_id, properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Console.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void GamePad::onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Console.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }
    if (!foundController) {
        Console.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}