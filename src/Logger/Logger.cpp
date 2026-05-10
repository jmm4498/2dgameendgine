#include "Logger.h"
#include <cstdarg>
#include <ctime>

FILE* Logger::__lDescriptor = nullptr;

namespace Colors {
    constexpr const char* RESET  = "\033[0m";
    constexpr const char* WHITE  = "\033[37m";   
    constexpr const char* RED    = "\033[31m"; 
    constexpr const char* ORANGE = "\033[33m"; 
}


void Logger::Init(FILE *output) {
    __lDescriptor = output ? output : stdout;
}

void Logger::SetLoggerOutput(FILE *output) {
    __lDescriptor = output ? output : stdout;
}

static void printTimestamp(FILE* f) {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    fprintf(f, "[%s] ", buf);
}

void Logger::__Log(const char* color, const char* level, const char* fmt, va_list args) {

    if (!__lDescriptor) {
        __lDescriptor = stdout;
    }

    printTimestamp(__lDescriptor);
    fprintf(__lDescriptor, "%s[%s]%s ", color, level, Colors::RESET);
    vfprintf(__lDescriptor, fmt, args);
    fprintf(__lDescriptor, "\n");

}

void Logger::Log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    __Log(Colors::WHITE, "INFO", fmt, args);
    va_end(args);
}

void Logger::Err(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    __Log(Colors::RED, "ERROR", fmt, args);
    va_end(args);
}

void Logger::Warn(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    __Log(Colors::ORANGE, "WARN", fmt, args);
    va_end(args);
}