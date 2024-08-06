
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

class Logger {
public:
    Logger(const std::string& logFilePath);
    ~Logger();

    void log(const std::string& username, const std::string& filename, const std::string& message);

private:
    std::ofstream logFile;
    std::string getTimestamp();
};

#endif // LOGGER_H