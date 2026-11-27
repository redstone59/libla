#include "logging.h"
#include <time.h>

#ifndef LA_LOG_NO_COLOUR
#   define ASCII_ESC(x) "\x1b[" x "m"
#else
#   define ASCII_ESC(x)
#endif
#define ASCII_RESET ASCII_ESC("0")

static const char *logLevelStrings[LA_LOGLEVEL_COUNT] = {
    "DEBUG" ASCII_RESET ASCII_ESC("36") "++",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
};

static const char *logLevelColours[LA_LOGLEVEL_COUNT] = {
    ASCII_ESC("1;36"), // Bold, Cyan
    ASCII_ESC("1;36"), // Bold, Cyan
    ASCII_ESC("1;37"), // Bold, White
    ASCII_ESC("1;33"), // Bold, Yellow
    ASCII_ESC("1;31"), // Bold, Red
};

static void PrintTime() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char buffer[256];
    strftime(buffer, sizeof(buffer), "%F %T", t);
    fprintf(stderr, "%s%s%s", ASCII_ESC("2"), buffer, ASCII_RESET);
}

static void PrintLevel(LiblaLogLevel level) {
    fprintf(stderr, 
        "%s%s%s", 
        logLevelColours[level], logLevelStrings[level], 
        ASCII_RESET
    );
}

void Libla_LogRaw(LiblaLogLevel level, char* message) {
    if (level < LA_LOG_THRESHOLD) {
        return;
    }

    PrintTime();
    fprintf(stderr, " ");
    PrintLevel(level);
    fprintf(stderr, ": ");
    fprintf(stderr, message);
    fprintf(stderr, "\n");
}