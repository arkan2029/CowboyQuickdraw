#ifndef UTILS_HPP
#define UTILS_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <random>

using namespace std::chrono_literals;

void buffer();
void countdown();
void printCowboys(std::string filename);
char getKeypress();
int cpuMockTime();

#endif // UTILS_HPP