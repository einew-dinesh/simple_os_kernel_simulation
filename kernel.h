#ifndef KERNEL_H
#define KERNEL_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <stdexcept>

#define TIMER_INTERRUPT 1
#define IO_INTERRUPT 2

class Kernel {
public:
    Kernel(size_t memorySize);
    ~Kernel();

    void createProcess(const std::string& name, std::function<void()> task);
    void killProcess(int pid);
    void run();
    void handleInterrupt(int interruptType);

private:
    struct PCB {
        int pid;
        std::string name;
        std::function<void()> task;
        bool running;
    };

    std::vector<PCB> processTable;
    std::queue<int> readyQueue;
    std::vector<bool> memory;
    size_t memorySize;
    int currentPID;
    int nextPID;

    void scheduler();
    void interruptHandler(int interruptType);
};

#endif // KERNEL_H
