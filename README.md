# 🤖 ESP32-Based Autonomous Path-Memorizing Robot

> Control, record, and replay paths with your ESP32 robot using a sleek Python GUI and real-time IP webcam streaming. Perfect for robotics enthusiasts, IoT lovers, and automation projects!  

[![Python](https://img.shields.io/badge/Python-3.11-blue?logo=python&logoColor=white)](https://www.python.org/)  
[![Arduino](https://img.shields.io/badge/Arduino-ESP32-green?logo=arduino&logoColor=white)](https://www.arduino.cc/)  

---

## **Features**

- Real-time video streaming from the robot’s camera using OpenCV and Tkinter.
- Arrow key controls (`Up`, `Down`, `Left`, `Right`) for manual movement.
- **Path recording**: Record a sequence of commands along with timestamps.
- **Path replay**: Replay the recorded path autonomously.
- **Reverse path**: After completion, the robot can retrace the path.
- Obstacle detection using ultrasonic sensors (front-left, front-right, rear).
- Capture images from the live camera feed.
- Reset recorded paths easily.

---

## **Hardware Requirements**

- ESP32 Development Board
- 2x DC motors + Motor Driver (L298N or similar)
- Ultrasonic sensors (HC-SR04)
- ESP32-CAM or IP webcam for video streaming
- Jumper wires, power supply, and basic chassis

---

## **Software Requirements**

- **Arduino IDE** for ESP32 code
- **Python 3.x**
- Required Python libraries:
