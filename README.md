# Image Processing Optimization on Embedded System

# Project Introduction
Abundant image-processing applications in embedded systems have been highly used in several booming industries, such as fields in automobile, medical, and IoT. 
However, the processing efficiency and storage limitation on embedded systems is always a tough problem to deal with. 
Thus, in this project, we aim to optimize the image processing on videos through certain techniques such as multithreading, neon intrinsics, and cache blocking.
The entire process would be run on a Raspberry Pi 4B, and the video would be converted into gray-scale and applied with a Sobel filter to enhance the edges of the shapes in the video. <br />

# Table of Contents
* [Accomplishments](#accomplishments)
* [Floating Point](#Floating-Point)
* [Pointer (Call by reference)](#pointer-call-by-reference)
* [GCC Compiler Flag](#GCC-Compiler-Flag)
* [Division & Square Root Operations](#Division--Square-Root-Operations)
* [Memory Access Time](#Memory-Access-Time)
* [Cache Blocking](#Cache-Blocking)
* [Demo](#Demo)

# Accomplishments
* Automated the water-changing process and re-uses the water on plants based on the data/metrics collected
* Designed the sensing and controlling components that use ESP32 as MCU and connect ESP32 to nine different sensors to collect data and make corresponding decisions to achieve automation
* Enabled real-time monitoring by establishing the network between the sensing/controlling components and WebUI/App (in HTML, CSS, JavaScript, and Cordova) through the server created by ESP32


# Floating Point

| Components | Part # | Quantity |
| :-----------:  | :-----------: |:-----------: |
| Water Temparature Sensor| DS18B20 | 1 |
| Water Quality Sensor |TDS Meter V1.0|1|
| Water Lavel Sensor | HW-038 |1|
| Soil Moisture Sensor| YL-69 |1|
|Light Intensity Sensor|Photoresistance|1|
| Inertial measurement unit | MPU6050 |1|
| Water Pump (DC 3v ~ 5V) |---|2|
| Relay (DC 5V) | --- |3|
| UV Light (DC 5V) | --- |1|
| MCU | ESP32 |1|
| MCU | ESP32_CAM |1|

# Pointer (Call by reference)
<p align="center">
  <img src="Media/System_Structure.jpg" alt="" width="90%"/>
</p>

# GCC Compiler Flag
<p align="center">
  <img src="Media/ESP32_WiringDiagram.png" alt="" width="90%"/>
</p>

# Division & Square Root Operations
<p align="center">
  <img src="Media/WebUI.jpg" alt="" width="90%"/>
</p>

# Memory Access Time
<p align="center">
  <img src="Media/Mobile_App.jpg" alt="" width="90%"/>
</p>

# Cache Blocking
# Demo
[![Demo](https://img.youtube.com/vi/lZQGizsCtnY/0.jpg)](https://youtu.be/lZQGizsCtnY)
