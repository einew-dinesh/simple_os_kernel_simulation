#include "Kernel.h"

void task1() {
    std::cout << "Running task 1" << std::endl;
}

void task2() {
    std::cout << "Running task 2" << std::endl;
}

int main() {
    Kernel kernel(1024);

    kernel.createProcess("Task1", task1);
    kernel.createProcess("Task2", task2);

    kernel.run();

    // Simulate timer interrupt
    kernel.handleInterrupt(TIMER_INTERRUPT);

    // Simulate I/O interrupt
    kernel.handleInterrupt(IO_INTERRUPT);

    return 0;
}
