#include "../includes/utils.hpp"

#include <iostream>
#include <chrono>
#include <limits>
#include <queue>
#include <vector>
#include <functional>

int main() {
  // MinHeap in memory to keep track of best time 
  std::priority_queue<int, std::vector<int>, std::greater<int>> scorekeeper{};
  while (true) {
    std::cout << "After the countdown from 3, when you see the cowboys on screen press SPACE as fast as you can." << '\n';
    buffer();
    countdown();
    printCowboys("cowboy_duel.txt");
    auto start = std::chrono::high_resolution_clock::now();
    char input = getKeypress();
    auto end = std::chrono::high_resolution_clock::now();
    auto len = end - start;
    auto timeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(len);
    int time = timeInMs.count();  // Extract the integer milliseconds
    scorekeeper.push(time);
    int cpuTime = cpuMockTime();
    if (time < cpuTime) {
      std::cout << "You win! Your time: " << time << "ms, NPC: " << cpuTime << "ms" << '\n';
    } else {
      std::cout << "You lose! Your time: " << time << "ms, NPC: " << cpuTime << "ms" << '\n';
    }
    std::cout << "Type 'q' and then enter to quit or any other key to continue:" << '\n';
    char cont;
    std::cin >> cont;
    if (cont == 'q' || cont == 'Q') break;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cout << "Here was your best time: " << scorekeeper.top() << "ms" << '\n';
  return 0;
}