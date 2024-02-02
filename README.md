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
2. Move all digits to the left of the decimal by shifting the binary number left
3. After the calculation is done, shift the number right for whatever bits were shifted in the previous step

# Pointer (Call by reference)
When dealing with sizable data structures or arrays, copying data can be both time-consuming and resource-intensive. Pointers provide an alternative approach where the actual data doesn't need to be duplicated, resulting in improved performance. <br />

# GCC Compiler Flag
Optimization level flags are compiler options that control the degree of optimization applied to the generated machine code during the compilation process. <br />
1. "-O0" (No Optimization):<br />
   * This level turns off almost all optimizations, making the compilation faster and simplifying debugging.<br />
2. "-O1" (Basic Optimization):<br />
   * This level enables basic optimizations such as inlining of functions, simplification of expressions, and elimination of redundant code.<br />
3. "-O2" (Moderate Optimization):<br />
   * This level includes more aggressive optimizations compared to -O1. It may perform loop unrolling, instruction scheduling, and further inlining to enhance runtime performance.<br />
4. "-O3" (High Optimization):<br />
   * This level includes even more aggressive optimizations than -O2. It may perform inter-procedural optimizations, vectorization, and other advanced transformations. 
# Division & Square Root Operations


# Memory Access Time


# Cache Blocking

# Demo
[![Demo](https://img.youtube.com/vi/lZQGizsCtnY/0.jpg)](https://youtu.be/lZQGizsCtnY)
