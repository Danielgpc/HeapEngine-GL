#include "engine.h"

#include <iostream>

int Engine::init() {
    std::cout << "Engine initialized.\n";
    return 0;
}

int Engine::run() {
    std::cout << "Hello, world from HeapEngine-GL!\n";
    return 0;
}

int Engine::cleanup() {
    std::cout << "Engine cleaned up.\n";
    return 0;
}
