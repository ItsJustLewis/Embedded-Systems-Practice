# Arduino Joystick Reaction Time Game

## Overview

This project is a simple reaction time game built using an **Arduino Uno**, a **joystick module**, and **four LEDs**.
The game measures how quickly a player reacts to a visual prompt by moving the joystick in the correct direction.

When the game starts, one of the four LEDs lights up randomly. The player must move the joystick in the matching direction as quickly as possible. The Arduino measures the reaction time and prints the result to the **Serial Monitor**.

This project was created and tested using the **Wokwi Arduino Simulator**.

---

## Components Used

* Arduino Uno
* Analog Joystick Module
* 4 × LEDs
* 4 × 220Ω Resistors
* Breadboard
* Jumper wires

---

## How the Game Works

1. The joystick must be in the **center position** before a round begins.
2. After a random delay, one of the four LEDs lights up:

   * Up LED
   * Down LED
   * Left LED
   * Right LED
3. The player must quickly move the joystick in the **same direction as the LED**.
4. The Arduino records how long it takes for the correct input.
5. The **reaction time (in milliseconds)** is printed to the Serial Monitor.
6. The player returns the joystick to the center to start the next round.

---

## Pin Configuration

| Component       | Arduino Pin |
| --------------- | ----------- |
| Joystick X-axis | A1          |
| Joystick Y-axis | A0          |
| Joystick Button | 2           |
| LED Up          | 8           |
| LED Right       | 9           |
| LED Down        | 10          |
| LED Left        | 11          |

---

## Running the Project in Wokwi

1. Open the project in **Wokwi**.
2. Start the simulation.
3. Open the **Serial Monitor**.
4. Move the joystick in the direction of the LED as quickly as possible.
5. The reaction time will be displayed in milliseconds.

---

## Example Output

```
Reaction Time Game Started!

LED: LEFT | Reaction Time: 312 ms
LED: UP | Reaction Time: 275 ms
LED: RIGHT | Reaction Time: 410 ms
```

---

## Learning Goals

This project demonstrates several embedded systems concepts:

* Reading **analog input** from sensors
* Using **conditional logic** to interpret joystick direction
* Measuring time using **millis()**
* Generating **random events**
* Interfacing with **LED outputs**
* Serial communication for debugging and feedback

---

## Possible Improvements

Future improvements could include:

* Score tracking system
* Best reaction time leaderboard
* Multiple difficulty levels
* Sound feedback using a buzzer
* Using the joystick button to start the game
* Adding an LCD or OLED display for reaction time

---

## Author

Lewis Evans
Software Engineering Student
De Montfort University
