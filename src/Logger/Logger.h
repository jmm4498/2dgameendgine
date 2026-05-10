#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

enum LogType {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

struct LogEntry {
    LogType type;
    std::string message;
};

class Logger {

    public:
        static std::vector<LogEntry> messages;
        static void Init(FILE *output = stdout);
        static void SetLoggerOutput(FILE *output);
        static void Log(const char* fmt, ...);
        static void Err(const char* fmt, ...);
        static void Warn(const char* fmt, ...);

        static void Flush() {
            if (__lDescriptor) {
                fflush(__lDescriptor);
            }
        }

    private:
        static FILE* __lDescriptor;
        static void __Log(const char* color, const char* level, const char* fmt, va_list args);
};


#endif // LOGGER_H