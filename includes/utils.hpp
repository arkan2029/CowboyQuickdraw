#ifndef UTILS_HPP
#define UTILS_HPP


#include <string>
#include <termios.h>
#include <unistd.h>
#include <chrono>

using namespace std::chrono_literals;

void buffer();
void countdown();
void printCowboys(std::string filename);
char getKeypress();
int cpuMockTime();

#endif // UTILS_HPP