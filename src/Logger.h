#pragma once

/**
 * This header serves as a junction for a vendor specific logging mechanism (first case: Espressif)
 */

#ifdef ESP32
#include <esp_log.h>
#define LOG_ERROR(tag, format, ...)   ESP_LOGE(tag, format, ##__VA_ARGS__)
#define LOG_WARN(tag, format, ...)    ESP_LOGW(tag, format, ##__VA_ARGS__)
#define LOG_INFO(tag, format, ...)    ESP_LOGI(tag, format, ##__VA_ARGS__)
#define LOG_DEBUG(tag, format, ...)   ESP_LOGD(tag, format, ##__VA_ARGS__)
#define LOG_VERBOSE(tag, format, ...) ESP_LOGV(tag, format, ##__VA_ARGS__)

typedef enum {
    LOG_LEVEL_NONE    = ESP_LOG_NONE,       /*!< No log output */
    LOG_LEVEL_ERROR   = ESP_LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    LOG_LEVEL_WARN    = ESP_LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    LOG_LEVEL_INFO    = ESP_LOG_INFO,       /*!< Information messages which describe normal flow of events */
    LOG_LEVEL_DEBUG   = ESP_LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    LOG_LEVEL_VERBOSE = ESP_LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} LogLevel;

inline void setLogLevel(const char* tag, LogLevel level)
{
    esp_log_level_set(tag, static_cast<esp_log_level_t>(level));  
}
#endif

#ifdef ARDUINO
#include <WString.h>

inline void logError(const char* tag, const String& message)
{
    LOG_ERROR(tag, "%s", message.c_str());
}

inline void logWarn(const char* tag, const String& message)
{
    LOG_WARN(tag, "%s", message.c_str());
}

inline void logInfo(const char* tag, const String& message)
{
    LOG_INFO(tag, "%s", message.c_str());
}

inline void logDebug(const char* tag, const String& message)
{
    LOG_DEBUG(tag, "%s", message.c_str());
}

inline void logVerbose(const char* tag, const String& message)
{
    LOG_VERBOSE(tag, "%s", message.c_str());
}
#endif
