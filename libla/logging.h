#ifndef LA_LOGGING_H_
#define LA_LOGGING_H_

#include <stdio.h>

#ifndef LA_LOG_THRESHOLD
#   define LA_LOG_THRESHOLD LA_LOGLEVEL_ERR
#endif

typedef enum LiblaLogLevel {
    LA_LOGLEVEL_DEBUG,
    LA_LOGLEVEL_INFO,
    LA_LOGLEVEL_WARN,
    LA_LOGLEVEL_ERR,
    LA_LOGLEVEL_COUNT
} LiblaLogLevel;

#define LA_LOG_LENGTH 256

#define Libla_Log(level, ...) do { \
    char msg[LA_LOG_LENGTH];       \
    sprintf(msg, __VA_ARGS__);     \
    Libla_LogRaw(level, msg);      \
} while (0)

void Libla_LogRaw(LiblaLogLevel level, char* message);

#endif // LA_LOGGING_H_