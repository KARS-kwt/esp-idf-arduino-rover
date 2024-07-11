
In the `scripts` folder create a new venv and install from requirements
```bash
python -m venv env
```
```bash
pip install -r requirement.txt
```


## `joystick_simple.py`
This is a simple example that reads left/right analog sticks, and key buttons. Your joystick button mapping may be different. If so, experiment with changing the button numbering. 
```python
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
```
