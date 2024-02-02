# Image Processing Optimization on Embedded System

# Project Introduction
Abundant image-processing applications in embedded systems have been extensively utilized in various thriving industries, including the automotive, medical, and IoT sectors. 
However, the processing efficiency and storage limitations on embedded systems pose persistent challenges. 
Therefore, in this project, our goal is to optimize video image processing using specific techniques such as multithreading, neon intrinsics, and cache blocking. 
The entire process will be executed on a Raspberry Pi 4B, where the video will be converted into grayscale and subjected to a Sobel filter to enhance the edges of shapes in the video. <br />

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
* Improved image processing speed by 4.5 times faster (from 4.17 FPS to 18.41 FPS)
* Executed multiple image processes simultaneously through software multithreading implementation
* Vectorized the computation of image processing through NEON intrinsics
* Optimized data structure alignment and reduced cache misses through compiler flag

# Floating Point
  Floating-point arithmetic typically provides higher precision compared to integer arithmetic. However, this precision comes at the cost of increased computation time.
  In other words, there is a trade-off between precision and performance. Thus, to reduce computation time, we can convert floating points to unsigned integers through bit manipulation. <br />
  Below are the Steps:<br />
1. Have floating points in binary
2. Shift the binary number left to move all digits to the left of the decimal
3. 

# Pointer (Call by reference)

# GCC Compiler Flag


# Division & Square Root Operations


# Memory Access Time


# Cache Blocking

# Demo
[![Demo](https://img.youtube.com/vi/lZQGizsCtnY/0.jpg)](https://youtu.be/lZQGizsCtnY)
