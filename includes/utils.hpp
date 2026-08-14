#ifndef UTILS_HPP
#define UTILS_HPP

extern "C" {
    #include "../db/sqlite3.h"
}

#include <string>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <optional>

using namespace std::chrono_literals;

void buffer();
void countdown();
void printCowboys(std::string filename);
char getKeypress();
int cpuMockTime();
sqlite3* openDb();
long long startSession(sqlite3* db);
void insertMatch(sqlite3* db, long long sessionId, int reactionTimeMs, const std::string& result);
std::optional<int> lifetimeBestScore(sqlite3* db);


#endif // UTILS_HPP