# 🤖 ESP32-Based Autonomous Path-Memorizing Robot

*A low-cost autonomous robot that learns routes once and replays them automatically for repetitive indoor delivery tasks.*

---

## 📌 Project Overview

This project implements an **autonomous path-memorizing robot** using an **ESP32** microcontroller.  
The robot can:

1. **Record a path** during a manual “teaching run”
2. **Store the path in NVS flash memory**
3. **Replay the same route autonomously**
4. **Avoid obstacles** using ultrasonic sensors
5. **Correct drift** using wheel encoders

Designed for **budget-friendly delivery automation** in hospitals, offices, labs, and warehouses.

---

## 🎯 Key Features

### 🔹 Path Recording
- Manual driving via Python/Tkinter GUI  
- Logs: direction, speed, timestamp  
- Saves path into **NVS flash memory**

### 🔹 Autonomous Replay
- Loads stored path from flash  
- Executes movements using timestamp sequencing  
- Can replay **forward or reverse**

### 🔹 Obstacle Detection
- HC-SR04 ultrasonic sensor  
- Robot halts if an obstacle appears  
- Automatically resumes

### 🔹 Drift Correction
- Wheel encoders count rotations  
- Adjusts PWM in real time to maintain path accuracy

### 🔹 Optional Add-On
- Live video feed from ESP32  
- Snapshot capture  
- Record / Replay buttons in the GUI  

---

## 🧱 Hardware Components

| Component | Purpose |
|----------|---------|
| **ESP32 Dev Board** | Main controller |
| **DC Gear Motors** | Differential drive |
| **Motor Encoders** | Drift correction |
| **L298N Motor Driver** | PWM motor control |
| **HC-SR04 Ultrasonic** | Obstacle detection |
| **12V Lithium Battery** | Power source |
| **Buck Converter (5V)** | ESP32 power regulation |
| **Chassis** | Robot base |

---

