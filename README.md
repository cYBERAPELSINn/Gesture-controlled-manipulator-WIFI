# Gesture-controlled-manipulator-WIFI
1. Introduction
Gesture-controlled manipulators represent a promising field in robotics. They can be used in conditions that are dangerous to humans, such as radiation contamination zones, sealed rooms with biological threats, or spaces with limited access. The uniqueness of this project lies in the use of the ESP-NOW protocol for low-latency communication and modular architecture, which makes it available for further scaling and modification.
The purpose of the work: To create a working manipulator controlled by hand gestures in real time via Wi-Fi.
Tasks:
1. To develop a prototype manipulator with 4 control axes.
2. Implement a data transmission system based on ESP-NOW.
3. Write the program code for the chip.
4. Test the system and evaluate its performance.

















2. Theory
 In this section, we have described what I studied to create the project.
1. What is ESP-NOW
ESP-NOW is a communication protocol developed for the ESP8266 and ESP32 family of chips from Espressif Systems. It is designed to exchange data between devices without the need to connect to a Wi-Fi network.

2. How ESP-NOW works
ESP-NOW works as follows:
Initialization: Devices are configured as sender and receiver.
MAC address registration: Each device registers the MAC address of the other for direct communication.
Sending data: The sender transmits data using the esp_now_send() function.
Receiving data: The recipient receives data through the callback function.
Key Features of ESP-NOW:
1. Direct connection: Devices can communicate directly with each other via a radio channel, bypassing the Access Point. This makes it ideal for applications where fast data transfer between multiple devices is required.
2. Low latency: Due to the absence of intermediaries (such as routers), data transmission delays are minimal, which is especially important for real-time applications.
3. Energy saving: The protocol is optimized for low-power operation, allowing it to be used in battery-powered devices.
4. Easy setup: To use ESP-NOW, you do not need to configure complex network settings such as SSID and password, making it easier to integrate the protocol into projects.
5. Security: Data encryption is supported to protect the transmitted information.
3. MPU-6050 is an integrated motion sensor developed by InvenSense. It combines a three-axis gyroscope and a three-axis accelerometer to measure angular velocity and linear acceleration along three axes (X,Y,Z). The MPU-6050 is often used in robotics, stabilization systems, game controllers, and other applications that require precise motion tracking. I only use a gyroscope.




3. The main part
3.1. The development of manipulator control technologies using hand gestures is becoming more and more in demand in various industries. Such systems have a wide range of applications, among which stand out:
o Industry: in high-risk environments, for example, when working with chemicals, radioactive materials or in extremely hot/harsh conditions, the use of remotely controlled manipulators significantly increases operator safety. Gesture control allows you to perform tasks with high accuracy and speed, saving the lives and health of employees.
o Education: In the educational field, such systems contribute to teaching the basics of robotics and programming. 
The uniqueness of the project
One of the key advantages of the presented project is the use of the ESP-NOW protocol. This protocol provides a number of unique characteristics that make it an ideal solution for real-time manipulator control: aw
o Low data transmission delay: less than 50 ms. This is crucial to achieve smooth and natural control of the manipulator, which is especially important in situations where every fraction of a second is important.
o High reliability of communication: The ESP-NOW protocol is designed specifically for wireless data transmission between devices, ensuring stable and stable communication even in conditions of complex radio conditions.
I also haven't found any similar projects on the internet. There is a gesture-controlled manipulator project, but it is wired and also does not work.















3.2. Technical Specification
System components:
1. Microcontrollers:
o Wemos D1 Mini (ESP8266) – 2 pcs.
o Are used for data processing and system management.
2. Servos:
O SG90 – 4 pcs.
o Are used to perform manipulator movements.
3. Sensor:
o MPU-6050
O Measures the tilt angle, providing data for manipulator control.
System Characteristics:
o Control delay: 42 ± 5 ms
o Low latency ensures smooth and responsive real-time control of the manipulator.
o Positioning accuracy: ±1.5°
o High precision allows the manipulator to accurately repeat the movements of the user's hand.
o Working time: 4 hours (with 10,000mAh battery)
o Long battery life makes the system convenient for long-term use without the need for frequent battery charging.















3.3. System architecture
The system consists of two main modules: a transmitter (gloves) and a receiver (manipulator).
1. Transmitter (Glove)
The glove reads data from the MPU-6050 gyroscope and transmits it via ESP-NOW. It includes:
o MPU-6050 gyroscope, which measures the angular velocity of the arm.
o An ESP8266 microcontroller that processes data and sends it via ESP-NOW.
o Button, responsible for the grip.
o The Esp8266 module that sends data from the glove.
2. Receiver (Manipulator)
The manipulator receives data and converts it into signals for servos. It contains:
o The Esp8266 module, which receives data from the glove.
o A signal processor that filters and converts data into commands for servos.
o Servos that perform manipulator movements according to the received data.
The ESP-NOW protocol provides fast and direct communication between the glove and the manipulator, which is critical for real-time control.
