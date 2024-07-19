# Simple OS Kernel Simulation in C++

This project implements a simple operating system kernel simulation using C++. It is designed to demonstrate fundamental concepts in operating system design, including process management, scheduling, and interrupt handling. The kernel manages process creation, execution, and termination, and simulates timer and I/O interrupts.

## Features

- **Process Management**: Create and manage multiple processes with unique IDs.
- **Scheduling**: A basic round-robin scheduler to switch between processes.
- **Memory Management**: Simple memory allocation and deallocation.
- **Interrupt Handling**: Simulation of timer and I/O interrupts.

## Files

- **Kernel.h**: Header file defining the `Kernel` class and process control block (PCB) structure.
- **Kernel.cpp**: Implementation of the `Kernel` class methods, including process management, scheduling, and interrupt handling.
- **main.cpp**: Example usage of the `Kernel` class, demonstrating process creation, execution, and interrupt handling.
