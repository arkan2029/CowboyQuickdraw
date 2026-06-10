#include "../includes/utils.hpp"
#include "../includes/bst.hpp"

int main() {
  BST scorekeeper;
  while (true) {
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
    scorekeeper.insert(time);
    int cpuTime = cpuMockTime();
    if (time < cpuTime) {
      std::cout << "You win! Your time: " << time << "ms, NPC: " << cpuTime << "ms" << std::endl;
    } else {
      std::cout << "You lose! Your time: " << time << "ms, NPC: " << cpuTime << "ms" << std::endl;
    }
    std::cout << "Type 'q' and then enter to quit or any other key to continue:" << std::endl;
    char cont;
    std::cin >> cont;
    if (cont == 'q' || cont == 'Q') break;
  }
  std::cout << "Here was your best time: " << scorekeeper.findMin() << "ms" << std::endl;
  return 0;
}