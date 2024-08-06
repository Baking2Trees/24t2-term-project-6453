#include "logger.h"
#include <sstream>

Logger::Logger(const std::string& logFilePath) {
    logFile.open(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file: " + logFilePath);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& username, const std::string& filename, const std::string& message) {
    if (logFile.is_open()) {
        logFile << username << "_" << getTimestamp() << "_" << filename << ": " << message << std::endl;
    }
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S");
    return ss.str();
}