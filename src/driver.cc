#include "../includes/utils.hpp"

int main() {
    std::cout << "After the countdown from 3, when you see the cowboys on screen press SPACE as fast as you can." << std::endl;
    buffer();
    countdown();
    printCowboys("cowboy_duel.txt");
    auto start = std::chrono::high_resolution_clock::now();
    char input = getKeypress();
    auto end = std::chrono::high_resolution_clock::now();
    auto len = end - start;
    auto timeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(len);
    int time = timeInMs.count();  // Extract the integer milliseconds
    int cpuTime = cpuMockTime();
    if (time < cpuTime) {
      std::cout << "You win! Your time: " << time << "ms, Computer: " << cpuTime << "ms" << std::endl;
    } else {
      std::cout << "You lose! Your time: " << time << "ms, Computer: " << cpuTime << "ms" << std::endl;
    }
    return 0;
}