# Ultrasonic Surveillance System (Arduino)

## Overview

This project simulates a miniature surveillance system using an **ultrasonic sensor** mounted on a servo motor.  

The servo continuously sweeps **180° back and forth** like a scanning radar, while the ultrasonic sensor measures distances at regular intervals. An **RGB LED** provides visual feedback:

- **Green** under normal conditions  
- **Red** when an object comes within 10 cm  

When an object is detected, the servo halts and points at the object until it moves away, then resumes normal scanning.

---

## Key Features

- Continuous servo scanning: **0° → 180° → 0°**
- Distance measurement every **800 ms** using the ultrasonic sensor
- **State-based behavior**:
  - **Normal**: sweep servo + green LED
  - **Alert**: stop servo + red LED when object < 10 cm
- Non-blocking timing using `millis()` to handle servo motion and sensor reads concurrently

---

## Components Used

- Arduino board  
- Ultrasonic sensor (HC-SR04)  
- Servo motor (SG90 micro servo)  
- RGB LED (using only red and green channels) + resistors  
- Breadboard and jumper wires  

---

## System Design

The system uses a **simple state machine** to manage behavior:

- **Normal State**: Servo sweeps while monitoring distance; green LED on  
- **Alert State**: If an object is detected <10 cm, servo stops and points at the object; red LED on  
- **Resume**: Once the object moves away, scanning resumes  

**Timing and sensor reads** are handled using `millis()` for non-blocking multitasking.

---

## How to Run

1. Connect components according to your wiring setup.
2. Upload the `.cpp` / `.ino` file to the Arduino.
3. Power the board.
4. Observe the servo sweep and LED behavior.
5. Place an object within 10 cm to trigger the alert state.

---

## Project Image

![IMG_3545](https://github.com/user-attachments/assets/1e54deff-533c-4a58-a3de-07c3e664db6b)
