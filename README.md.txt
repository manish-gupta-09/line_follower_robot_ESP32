# ESP32 PD Line Follower Robot using RLS08 and TB6612FNG

## Overview

This project is a high-speed Line Follower Robot built using an ESP32 microcontroller, RLS08 IR sensor array, TB6612FNG motor driver, and BO motors. The robot detects a black line on a white surface and follows it using a PD (Proportional-Derivative) control algorithm.

The PD controller continuously calculates the robot's position relative to the line and adjusts motor speeds to maintain smooth and accurate line tracking.

---

## Components Used

* ESP32 Development Board
* RLS08 8-Channel IR Sensor Array
* TB6612FNG Motor Driver
* 2 × BO Gear Motors
* Robot Chassis
* Wheels
* Castor Wheel
* 2 × 18650 Batteries
* Battery Holder
* Connecting Wires

---

## Features

* 8 Sensor Line Detection
* PD Based Line Following
* Smooth Turning Control
* Adjustable Kp and Kd Parameters
* High-Speed Performance
* Lost Line Recovery Logic
* ESP32 PWM Motor Control
* Serial Monitor Debugging

---

## Hardware Connections

### TB6612FNG Connections

| TB6612 Pin | ESP32 Pin |
| ---------- | --------- |
| PWMA       | GPIO 25   |
| AIN1       | GPIO 26   |
| AIN2       | GPIO 27   |
| PWMB       | GPIO 14   |
| BIN1       | GPIO 12   |
| BIN2       | GPIO 13   |
| STBY       | GPIO 33   |

### RLS08 Connections

| RLS08 Pin | ESP32 Pin |
| --------- | --------- |
| D1        | GPIO 4    |
| D2        | GPIO 5    |
| D3        | GPIO 18   |
| D4        | GPIO 19   |
| D5        | GPIO 21   |
| D6        | GPIO 22   |
| D7        | GPIO 23   |
| D8        | GPIO 32   |
| VCC       | 5V        |
| GND       | GND       |

---

## Sensor Weights

```text
D1  D2  D3  D4  D5  D6  D7  D8

-7  -5  -3  -1   1   3   5   7
```

These weights are used to calculate the robot's position relative to the line.

---

## PD Control Formula

```text
P = Kp × Error

D = Kd × (Error - Previous Error)

Correction = P + D
```

Motor Speeds:

```text
Left Motor  = Base Speed - Correction

Right Motor = Base Speed + Correction
```

---

## Default Parameters

```cpp
float Kp = 20;
float Kd = 30;

int baseSpeed = 150;
```

These values can be tuned according to track conditions and motor speed.

---

## Working Principle

1. RLS08 detects the black line.
2. Sensor values are converted into an error value.
3. PD controller calculates the correction.
4. Motor speeds are adjusted accordingly.
5. Robot continuously follows the line.

---

## Applications

* Robotics Competitions
* Autonomous Navigation
* Educational Projects
* Embedded Systems Learning
* PID Control Experiments

---

## Future Improvements

* Full PID Control
* Sharp 90° Turn Detection
* Junction Detection
* Maze Solving
* Encoder Feedback
* Wireless Tuning via Bluetooth

---

## Author

Manish Gupta

Built using ESP32, RLS08, TB6612FNG, and PD Control Algorithm.
