#include "Kernel.h"

Kernel::Kernel(size_t memorySize) : memorySize(memorySize), currentPID(-1), nextPID(0) {
    memory.resize(memorySize, false);
}

Kernel::~Kernel() {
    processTable.clear();
    while (!readyQueue.empty()) {
        readyQueue.pop();
    }
    memory.clear();

    std::cout << "Kernel shut down successfully." << std::endl;
}

void Kernel::createProcess(const std::string& name, std::function<void()> task) {
    PCB pcb;
    pcb.pid = nextPID++;
    pcb.name = name;
    pcb.task = task;
    pcb.running = false;

    processTable.push_back(pcb);
    readyQueue.push(pcb.pid);

    std::cout << "Process " << name << " created with PID " << pcb.pid << std::endl;
}

void Kernel::killProcess(int pid) {
    for (auto& pcb : processTable) {
        if (pcb.pid == pid) {
            pcb.running = false;
            std::cout << "Process " << pcb.name << " with PID " << pid << " killed" << std::endl;
            return;
        }
    }
    throw std::runtime_error("Invalid PID");
}

void Kernel::run() {
    while (!readyQueue.empty()) {
        scheduler();
    }
}

void Kernel::scheduler() {
    if (readyQueue.empty()) return;

    int pid = readyQueue.front();
    readyQueue.pop();

    for (auto& pcb : processTable) {
        if (pcb.pid == pid) {
            pcb.running = true;
            currentPID = pid;
            pcb.task();
            pcb.running = false;
            currentPID = -1;
            std::cout << "Process " << pcb.name << " with PID " << pid << " completed" << std::endl;
            break;
        }
    }
}

void Kernel::handleInterrupt(int interruptType) {
    interruptHandler(interruptType);
}

void Kernel::interruptHandler(int interruptType) {
    switch (interruptType) {
        case TIMER_INTERRUPT:
            std::cout << "Handling timer interrupt" << std::endl;
            scheduler();
            break;
        case IO_INTERRUPT:
            std::cout << "Handling I/O interrupt" << std::endl;
            if (currentPID != -1) {
                std::cout << "Process " << currentPID << " is performing I/O operation" << std::endl;
            }
            break;
        default:
            std::cout << "Unknown interrupt type: " << interruptType << std::endl;
            break;
    }
}
