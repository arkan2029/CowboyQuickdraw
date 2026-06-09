#include "../includes/utils.hpp"

//3 sec pause in terminal to let user read initial instructions
void buffer() {
    std::this_thread::sleep_for(3s);
}

//3 second countdown in terminal
void countdown() {
    for (int i = 3; i > 0; --i) {
        std::this_thread::sleep_for(1s);
        std::cout << i << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

//reads ASCII art file line by line and prints to terminal
void printCowboys(std::string filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) throw std::runtime_error("cowboy image did not open");
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
}

// changes term settings to store intput other than enter, does not show keypress, reverts back to normal terminal settings on first input
char getKeypress() {
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    char c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    return c;
}

// random time generation to act as the npc for user, simulates avg human reaction time, adjusted slightly higher because keypress delay
int cpuMockTime() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist(200, 500); // normal range = 150 - 400
    return dist(gen);
}