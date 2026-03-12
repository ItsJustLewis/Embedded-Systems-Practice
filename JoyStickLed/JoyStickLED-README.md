# Arduino Joystick Direction Indicator

## Overview

This project uses an **Arduino Uno**, an **analog joystick**, and **four LEDs** to indicate the direction the joystick is pushed. Each LED represents one direction (up, down, left, right). When the joystick is moved, the corresponding LED lights up.

## Components

* Arduino Uno
* Analog Joystick Module
* 4 × LEDs
* 4 × 220Ω Resistors
* Breadboard
* Jumper Wires

## Wiring

### Joystick

| Joystick Pin | Arduino Pin                      |
| ------------ | -------------------------------- |
| VCC          | 5V                               |
| GND          | GND                              |
| VERT         | A0                               |
| HORZ         | A1                               |
| SEL          | D2 (optional, not used in logic) |

### LEDs

| Direction | Arduino Pin |
| --------- | ----------- |
| Up        | D8          |
| Right     | D9          |
| Down      | D10         |
| Left      | D11         |

Each LED is connected in series with a **220Ω resistor** to **GND**.

Circuit path:

```
Arduino Pin → LED → Resistor → GND
```

## How It Works

The joystick outputs **analog values between 0 and 1023** on the X and Y axes.

* Center position ≈ 512
* Moving the joystick changes these values.

The program reads the joystick values using `analogRead()` and checks if they exceed certain thresholds.

Example thresholds:

* **Up:** Y value > 700
* **Down:** Y value < 300
* **Right:** X value > 700
* **Left:** X value < 300

When a threshold is met, the corresponding LED is turned on.

## Running the Simulation

1. Open the project in **Wokwi**.
2. Start the simulation.
3. Move the joystick.
4. The LED representing the direction of movement will light up.

## Learning Goals

This project demonstrates:

* Reading **analog inputs**
* Controlling **digital outputs**
* Basic **sensor threshold detection**
* Using the **Serial Monitor for debugging**

## Possible Improvements

* Add **diagonal direction detection** (two LEDs at once).
* Use the joystick **button (SEL)** for additional input.
* Smooth joystick readings using **averaging or filtering**.
* Replace LEDs with a **direction display or motor control system**.
