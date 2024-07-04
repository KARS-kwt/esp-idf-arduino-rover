#ifndef GamePad_hpp
#define GamePad_hpp

#include <Bluepad32.h>

struct GamepadState {
    bool dpadUp = false;
    bool dpadDown = false;
    bool dpadLeft = false;
    bool dpadRight = false;
    bool L1 = false;
    bool R1 = false;
    bool A = false; // Circle
    bool B = false; // Cross
    bool X = false; // Square
    bool Y = false; // Triangle
    struct Analog {
        int x;
        int y;
    };
    Analog leftStick;
    Analog rightStick;
};

class GamePad {
public:
    GamePad();
    void setup(const char* controller_addr_string);
    void setup();
    bool update();
    void reset_allow_list();
    GamepadState getState();

private:
    static void onConnectedController(ControllerPtr ctl);
    static void onDisconnectedController(ControllerPtr ctl);
    static ControllerPtr myControllers[BP32_MAX_GAMEPADS];
    static GamepadState gamepadState;
};

#endif /* GamePad_hpp */