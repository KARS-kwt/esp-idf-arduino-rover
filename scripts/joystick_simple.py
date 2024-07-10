import pygame
import sys
from pygame.locals import *

class GamepadState:
    def __init__(self):
        self.dpadUp = False
        self.dpadDown = False
        self.dpadLeft = False
        self.dpadRight = False
        self.L1 = False
        self.R1 = False
        self.A = False  # Circle
        self.B = False  # Cross
        self.X = False  # Square
        self.Y = False  # Triangle
        self.leftStick = {'x': 0, 'y': 0}
        self.rightStick = {'x': 0, 'y': 0}


class JoystickHandler:
    def __init__(self):
        pygame.init()
        self.joystick_count = pygame.joystick.get_count()
        if self.joystick_count == 0:
            print("Error, I did not find any joysticks")
            pygame.quit()
            sys.exit()
        else:
            self.joystick = pygame.joystick.Joystick(0)
            self.joystick.init()
        self.state = GamepadState()

    def update(self):
        for event in [pygame.event.wait(), ] + pygame.event.get():
            if event.type == QUIT:
                self.quit()
            elif event.type == KEYDOWN and event.key in [K_ESCAPE, K_q]:
                self.quit()
            # elif event.type == JOYAXISMOTION:
            #     if event.axis < 2:  # Usually axes 0 and 1 are for the left stick
            #         if event.axis == 0:
            #             self.state.leftStick['x'] = event.value
            #         elif event.axis == 1:
            #             self.state.leftStick['y'] = event.value
            #     elif event.axis >= 2:  # Axes 2 and 3 are usually the right stick
            #         if event.axis == 2:
            #             self.state.rightStick['x'] = event.value
            #         elif event.axis == 3:
            #             self.state.rightStick['y'] = event.value
            # elif event.type == JOYBUTTONDOWN:
            #     if event.button == 0:
            #         self.state.A = True
            #     elif event.button == 1:
            #         self.state.B = True
            #     elif event.button == 2:
            #         self.state.B = True
            #     elif event.button == 3:
            #         self.state.B = True
                
            # elif event.type == JOYBUTTONUP:
            #     # Reset button
            #     if event.button == 0:
            #         self.state.A = False
            #     elif event.button == 1:
            #         self.state.B = False
            else:
                self.state.leftStick['x'] = self.joystick.get_axis(0)
                self.state.leftStick['y'] = self.joystick.get_axis(1)
                self.state.rightStick['x'] = self.joystick.get_axis(2)
                self.state.rightStick['y'] = self.joystick.get_axis(3)
                self.state.A = self.joystick.get_button(0)
                self.state.B = self.joystick.get_button(1)
                self.state.X = self.joystick.get_button(2)
                self.state.Y = self.joystick.get_button(3)
                self.state.dpadUp = self.joystick.get_button(11)
                self.state.dpadDown = self.joystick.get_button(12)
                self.state.dpadLeft = self.joystick.get_button(13)
                self.state.dpadRight = self.joystick.get_button(14)
                self.state.L1 = self.joystick.get_button(9)
                self.state.R1 = self.joystick.get_button(10)

# Example usage
if __name__ == "__main__":
    joystick_handler = JoystickHandler()
    running = True
    while running:
        joystick_handler.update()
        print("A: " + str(joystick_handler.state.A))
        print("B: " + str(joystick_handler.state.B))
        print("X: " + str(joystick_handler.state.X))
        print("Y: " + str(joystick_handler.state.Y))
        print("dpadUp: " + str(joystick_handler.state.dpadUp))
        print("dpadDown: " + str(joystick_handler.state.dpadDown))
        print("dpadLeft: " + str(joystick_handler.state.dpadLeft))
        print("dpadRight: " + str(joystick_handler.state.dpadRight))
        print("L1: " + str(joystick_handler.state.L1))
        print("R1: " + str(joystick_handler.state.R1))
        print("left stick" + str(joystick_handler.state.leftStick))
        print("right stick" + str(joystick_handler.state.rightStick))
        pygame.time.wait(100)
