#include "../includes/utils.hpp"


#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <random>
#include <iostream>

//3 sec pause in terminal to let user read initial instructions
void buffer() {
    std::this_thread::sleep_for(3s);
}

//3 second countdown in terminal
void countdown() {
    for (int i = 3; i > 0; --i) {
        std::this_thread::sleep_for(1s);
        // no sleep after final count
        if (i == 1) {
            std::cout << i << std::endl;
            break;
        }
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

// create a lifetime score tracking .db file using SQLite3 C++ interface
// 2 tables, sessions and matches, for each run during a session time and what unique session 
// it belongs to held in matches with corresponding foreign key mapping to corresponding session in sessions table
sqlite3* openDb() {
    // db initialization
    sqlite3* db;
    int rc = sqlite3_open("quickdraw.db", &db);
    if (rc != SQLITE_OK) {
        std::string error = std::string("DB did not open: ") + sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error(error);
    }

    // table creation
    const char* db_schema =
        "CREATE TABLE IF NOT EXISTS sessions ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  started_at TEXT NOT NULL"
        ");"
        "CREATE TABLE IF NOT EXISTS matches ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  session_id INTEGER NOT NULL,"
        "  reaction_time_ms INTEGER NOT NULL,"
        "  result TEXT NOT NULL,"
        "  played_at TEXT NOT NULL,"
        "  FOREIGN KEY(session_id) REFERENCES sessions(id)"
        ");";
    char* errmsg = nullptr;
    rc = sqlite3_exec(db, db_schema, nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK) {
        std::string error = std::string("Couldn't create table: ") + (errmsg ? errmsg : "unknown error");
        sqlite3_free(errmsg);
        sqlite3_close(db);
        throw std::runtime_error(error);
    }
    return db;
}


long long startSession(sqlite3 *db) {
    const char* sql = "INSERT INTO sessions (started_at) VALUES (datetime('now'));";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error(std::string("Couldn't make session insert: ") + sqlite3_errmsg(db));
    }

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error(std::string("Could not inset to session: ") + sqlite3_errmsg(db));
    }

    return sqlite3_last_insert_rowid(db);
}

void insertMatch(sqlite3* db, long long sessionId, int reactionTimeMs, const std::string& result) {
    const char* sql =
        "INSERT INTO matches (session_id, reaction_time_ms, result, played_at) "
        "VALUES (?, ?, ?, datetime('now'));";
    
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error(std::string("Didn't make the match insertion: ") + sqlite3_errmsg(db));
    }

    sqlite3_bind_int64(stmt, 1, sessionId);
    sqlite3_bind_int(stmt, 2, reactionTimeMs);
    sqlite3_bind_text(stmt, 3, result.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        throw std::runtime_error(std::string("Failed to insert match: ") + sqlite3_errmsg(db));
    }
}