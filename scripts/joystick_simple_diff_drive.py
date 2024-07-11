import pygame
import sys
from pygame.locals import *
import json
import serial

class GamepadState:
    def __init__(self):
        self.leftStick = {'x': 0, 'y': 0}
        self.rightStick = {'x': 0, 'y': 0}
        
class JoystickHandler:
    def __init__(self, serial_port, baud_rate=115200):
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
        try:
            self.serial_connection = serial.Serial(serial_port, baud_rate)
        except serial.SerialException as e:
            print(f"Failed to connect to serial port {serial_port}. Error: {e}")
            pygame.quit()
            sys.exit()

    def map_value(self, value, from_min, from_max, to_min, to_max):
        return (value - from_min) * (to_max - to_min) / (from_max - from_min) + to_min
    
    def update(self):
        pygame.event.pump()
        self.state.leftStick['x'] = self.joystick.get_axis(0)
        self.state.leftStick['y'] = self.joystick.get_axis(1)
        self.state.rightStick['x'] = self.joystick.get_axis(2)
        self.state.rightStick['y'] = self.joystick.get_axis(3)

        left_speed = self.map_value(self.state.leftStick['y'], -1, 1, -100, 100)
        right_speed = self.map_value(self.state.rightStick['y'], -1, 1, -100, 100)

        motor_speeds = {
            "left_motor": int(left_speed),
            "right_motor": int(right_speed)
        }

        self.send_serial_data(motor_speeds)
    
    def send_serial_data(self, data):
        json_data = json.dumps(data)
        try:
            self.serial_connection.write(json_data.encode('utf-8'))
        except serial.SerialException as e:
            print(f"Failed to send data. Error: {e}")
    def read_serial_data(self):
        if self.serial_connection.in_waiting > 0:
            serial_data = self.serial_connection.readline()
            try:
                json_data = json.loads(serial_data.decode('utf-8').strip())
                print("Received JSON:", json_data)
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON: {e}")
            
    def quit(self):
        pygame.quit()
        self.serial_connection.close()
        
if __name__ == "__main__":
    # Replace  with your serial port. e.g. '/dev/ttyUSB0'
    joystick_handler = JoystickHandler(serial_port='COM6')
    running = True
    try:
        while running:
            joystick_handler.update()
            joystick_handler.read_serial_data()
            pygame.time.wait(10) 
    except KeyboardInterrupt:
        joystick_handler.quit()