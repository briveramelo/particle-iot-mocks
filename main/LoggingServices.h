#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

// NOTE: This header defines various string constants. Ensure identical strings defined in different
// translation units get merged during linking (may require enabled optimizations)

#ifdef __cplusplus
extern "C" {
#endif

// Log level. Ensure log_level_name() is updated for newly added levels
typedef enum LogLevel {
    LOG_LEVEL_ALL = 1, // Log all messages
    LOG_LEVEL_TRACE = 1,
    LOG_LEVEL_INFO = 30,
    LOG_LEVEL_WARN = 40,
    LOG_LEVEL_ERROR = 50,
    LOG_LEVEL_PANIC = 60,
    LOG_LEVEL_NONE = 70, // Do not log any messages
    // Compatibility levels
    DEFAULT_LEVEL = 0,
    ALL_LEVEL = LOG_LEVEL_ALL,
    TRACE_LEVEL = LOG_LEVEL_TRACE,
    LOG_LEVEL = LOG_LEVEL_TRACE, // Deprecated
    DEBUG_LEVEL = LOG_LEVEL_TRACE, // Deprecated
    INFO_LEVEL = LOG_LEVEL_INFO,
    WARN_LEVEL = LOG_LEVEL_WARN,
    ERROR_LEVEL = LOG_LEVEL_ERROR,
    PANIC_LEVEL = LOG_LEVEL_PANIC,
    NO_LOG_LEVEL = LOG_LEVEL_NONE
} LogLevel;

// Log message attributes
// NOTE: Do not change types and order of the existent fields
typedef struct LogAttributes {
    size_t size; // Structure size
    union { // Attribute flags
        uint32_t flags;
        struct {
            // 1 - attribute is set, 0 - attribute is not set
            unsigned has_file: 1;
            unsigned has_line: 1;
            unsigned has_function: 1;
            unsigned has_time: 1;
            unsigned has_code: 1;
            unsigned has_details: 1;
            // <--- Add new attribute flag here
            unsigned has_end: 1; // Keep this field at the end of the structure
        };
    };
    const char *file; // Source file name
    int line; // Line number
    const char *function; // Function name
    uint32_t time; // Timestamp
    intptr_t code; // Status code
    const char *details; // Additional information
    // <--- Add new attribute field here
    char end[0]; // Keep this field at the end of the structure
} LogAttributes;

// Callback for message-based logging (used by log_message())
typedef void (*log_message_callback_type)(const char *msg, int level, const char *category, const LogAttributes *attr,
                                          void *reserved);

// Callback for direct logging (used by log_write(), log_printf(), log_dump())
typedef void (*log_write_callback_type)(const char *data, size_t size, int level, const char *category, void *reserved);

// Callback invoked to check whether logging is enabled for particular level and category (used by log_enabled())
typedef int (*log_enabled_callback_type)(int level, const char *category, void *reserved);

// Generates log message
void log_message(int level, const char *category, LogAttributes *attr, void *reserved, const char *fmt, ...);

// Variant of the log_message() function taking variable arguments via va_list
void log_message_v(int level, const char *category, LogAttributes *attr, void *reserved, const char *fmt,
                   va_list args);

// Forwards buffer to backend logger
void log_write(int level, const char *category, const char *data, size_t size, void *reserved);

// Writes formatted string to backend logger
void log_printf(int level, const char *category, void *reserved, const char *fmt, ...);

// Variant of the log_printf() function taking variable arguments via va_list
void log_printf_v(int level, const char *category, void *reserved, const char *fmt, va_list args);

// Encodes data in hex and writes resulting string to backend logger
void log_dump(int level, const char *category, const void *data, size_t size, int flags, void *reserved);

// Returns 1 if logging is enabled for specified level and category
int log_enabled(int level, const char *category, void *reserved);

// Returns log level name
const char* log_level_name(int level, void *reserved);

// Sets logger callbacks
void log_set_callbacks(log_message_callback_type log_msg, log_write_callback_type log_write,
                       log_enabled_callback_type log_enabled, void *reserved);

extern void HAL_Delay_Microseconds(uint32_t delay);

#ifdef __cplusplus
} // extern "C"
#endif

#ifndef LOG_COMPILE_TIME_LEVEL
#define LOG_COMPILE_TIME_LEVEL LOG_LEVEL_ALL
#endif

#ifndef LOG_MAX_STRING_LENGTH
#define LOG_MAX_STRING_LENGTH 160
#endif

#ifndef LOG_INCLUDE_SOURCE_INFO
#define LOG_INCLUDE_SOURCE_INFO 0
#endif

// Sets log message attribute
#define LOG_ATTR_SET(_attr, _name, _val) \
        do { \
            (_attr)._name = _val; \
            (_attr).has_##_name = 1; \
        } while (0)

#ifndef LOG_DISABLE

#ifndef LOG_MODULE_CATEGORY
// #warning "Log category is not defined for a module"
#define LOG_MODULE_CATEGORY NULL
#endif

#ifdef __cplusplus

// Module category
template<typename T>
struct _LogCategoryWrapper {
    static const char* name() {
        return LOG_MODULE_CATEGORY;
    }
};

struct _LogGlobalCategory;
typedef _LogCategoryWrapper<_LogGlobalCategory> _LogCategory;

// Source file category
#define LOG_SOURCE_CATEGORY(_name) \
        template<> \
        struct _LogCategoryWrapper<_LogGlobalCategory> { \
            static const char* name() { \
                return _name; \
            } \
        };

// Scoped category
#define LOG_CATEGORY(_name) \
        struct _LogCategory { \
            static const char* name() { \
                return _name; \
            } \
        }

// Expands to current category name
#define LOG_THIS_CATEGORY() _LogCategory::name()

#else // !defined(__cplusplus)

// weakref allows to have different implementations of the same function in different translation
// units if target function is declared as static
static const char* _log_source_category() __attribute__((weakref("_log_source_category_impl"), unused));

// Source file category
#define LOG_SOURCE_CATEGORY(_name) \
        static const char* _log_source_category_impl() { \
            return _name; \
        }

// Dummy constant shadowed when scoped category is defined
static const char* const _log_category = NULL;

// Scoped category
#define LOG_CATEGORY(_name) \
        static const char* const _log_category = _name

// Expands to current category name
#define LOG_THIS_CATEGORY() \
        (_log_category ? _log_category : (_log_source_category ? _log_source_category() : LOG_MODULE_CATEGORY))

#endif // !defined(__cplusplus)

#if LOG_INCLUDE_SOURCE_INFO
#define _LOG_ATTR_SET_SOURCE_INFO(_attr) \
        LOG_ATTR_SET(_attr, file, __FILE__); \
        LOG_ATTR_SET(_attr, line, __LINE__); \
        LOG_ATTR_SET(_attr, function, __PRETTY_FUNCTION__)
#else
#define _LOG_ATTR_SET_SOURCE_INFO(_attr)
#endif

#define _LOG_ATTR_INIT(_name) \
        LogAttributes _name; \
        _name.size = sizeof(LogAttributes); \
        _name.flags = 0; \
        _LOG_ATTR_SET_SOURCE_INFO(_name)

// Generator macro for PP_FOR_EACH()
#define _LOG_ATTR_SET(_attr, _expr) \
        (_attr)._expr; /* attr.file = "logging.h"; */ \
        (_attr).has_##_expr ? 1 : 1; /* attr.has_file = "logging.h" ? 1 : 1; */

// Primary logging macros
#define LOG_C(_level, _category, _fmt, ...) \
        do { \
            if (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL) { \
                _LOG_ATTR_INIT(_attr); \
                log_message(LOG_LEVEL_##_level, _category, &_attr, NULL, _fmt, ##__VA_ARGS__); \
            } \
        } while (0)

#define LOG_ATTR_C(_level, _category, _attrs, _fmt, ...) \
        do { \
            if (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL) { \
                _LOG_ATTR_INIT(_attr); \
                PP_FOR_EACH(_LOG_ATTR_SET, _attr, PP_ARGS(_attrs)); \
                log_message(LOG_LEVEL_##_level, _category, &_attr, NULL, _fmt, ##__VA_ARGS__); \
            } \
        } while (0)

#define LOG_WRITE_C(_level, _category, _data, _size) \
        do { \
            if (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL) { \
                log_write(LOG_LEVEL_##_level, _category, _data, _size, NULL); \
            } \
        } while (0)

#define LOG_PRINT_C(_level, _category, _str) \
        do { \
            if (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL) { \
                const char* const _s = _str; \
                log_write(LOG_LEVEL_##_level, _category, _s, strlen(_s), NULL); \
            } \
        } while (0)

#define LOG_PRINTF_C(_level, _category, _fmt, ...) \
        do { \
            if (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL) { \
                log_printf(LOG_LEVEL_##_level, _category, NULL, _fmt, ##__VA_ARGS__); \
            } \
        } while (0)

#define LOG_DUMP_C(_level, _category, _data, _size) \
        do { \
            if (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL) { \
                log_dump(LOG_LEVEL_##_level, _category, _data, _size, 0, NULL); \
            } \
        } while (0)

#define LOG_ENABLED_C(_level, _category) \
        (LOG_LEVEL_##_level >= LOG_COMPILE_TIME_LEVEL && log_enabled(LOG_LEVEL_##_level, _category, NULL))

#else // LOG_DISABLE

#define LOG_CATEGORY(_name)
#define LOG_SOURCE_CATEGORY(_name)
#define LOG_THIS_CATEGORY() NULL

#define LOG_C(_level, _category, _fmt, ...)
#define LOG_ATTR_C(_level, _category, _attrs, _fmt, ...)
#define LOG_WRITE_C(_level, _category, _data, _size)
#define LOG_PRINT_C(_level, _category, _str)
#define LOG_PRINTF_C(_level, _category, _fmt, ...)
#define LOG_DUMP_C(_level, _category, _data, _size)
#define LOG_ENABLED_C(_level, _category) (0)

#endif // not LOG_DISABLE

#ifdef DEBUG_BUILD
#define LOG_DEBUG_C(_level, _category, _fmt, ...) LOG_C(_level, _category, _fmt, ##__VA_ARGS__)
#define LOG_DEBUG_ATTR_C(_level, _category, _attrs, _fmt, ...) LOG_ATTR_C(_level, _category, _attrs, _fmt, ##__VA_ARGS__)
#define LOG_DEBUG_WRITE_C(_level, _category, _data, _size) LOG_WRITE_C(_level, _category, _data, _size)
#define LOG_DEBUG_PRINT_C(_level, _category, _str) LOG_PRINT_C(_level, _category, _str)
#define LOG_DEBUG_PRINTF_C(_level, _category, _fmt, ...) LOG_PRINTF_C(_level, _category, _fmt, ##__VA_ARGS__)
#define LOG_DEBUG_DUMP_C(_level, _category, _data, _size) LOG_DUMP_C(_level, _category, _data, _size)
#else
#define LOG_DEBUG_C(_level, _category, _fmt, ...)
#define LOG_DEBUG_ATTR_C(_level, _category, _attrs, _fmt, ...)
#define LOG_DEBUG_WRITE_C(_level, _category, _data, _size)
#define LOG_DEBUG_PRINT_C(_level, _category, _str)
#define LOG_DEBUG_PRINTF_C(_level, _category, _fmt, ...)
#define LOG_DEBUG_DUMP_C(_level, _category, _data, _size)
#endif

// Macros using current category
#define LOG(_level, _fmt, ...) LOG_C(_level, LOG_THIS_CATEGORY(), _fmt, ##__VA_ARGS__)
#define LOG_ATTR(_level, _attrs, _fmt, ...) LOG_ATTR_C(_level, LOG_THIS_CATEGORY(), _attrs, _fmt, ##__VA_ARGS__)
#define LOG_WRITE(_level, _data, _size) LOG_WRITE_C(_level, LOG_THIS_CATEGORY(), _data, _size)
#define LOG_PRINT(_level, _str) LOG_PRINT_C(_level, LOG_THIS_CATEGORY(), _str)
#define LOG_PRINTF(_level, _fmt, ...) LOG_PRINTF_C(_level, LOG_THIS_CATEGORY(), _fmt, ##__VA_ARGS__)
#define LOG_DUMP(_level, _data, _size) LOG_DUMP_C(_level, LOG_THIS_CATEGORY(), _data, _size)
#define LOG_ENABLED(_level) LOG_ENABLED_C(_level, LOG_THIS_CATEGORY())

#define LOG_DEBUG(_level, _fmt, ...) LOG_DEBUG_C(_level, LOG_THIS_CATEGORY(), _fmt, ##__VA_ARGS__)
#define LOG_DEBUG_ATTR(_level, _attrs, _fmt, ...) LOG_DEBUG_ATTR_C(_level, LOG_THIS_CATEGORY(), _attrs, _fmt, ##__VA_ARGS__)
#define LOG_DEBUG_WRITE(_level, _data, _size) LOG_DEBUG_WRITE_C(_level, LOG_THIS_CATEGORY(), _data, _size)
#define LOG_DEBUG_PRINT(_level, _str) LOG_DEBUG_PRINT_C(_level, LOG_THIS_CATEGORY(), _str)
#define LOG_DEBUG_PRINTF(_level, _fmt, ...) LOG_DEBUG_PRINTF_C(_level, LOG_THIS_CATEGORY(), _fmt, ##__VA_ARGS__)
#define LOG_DEBUG_DUMP(_level, _data, _size) LOG_DEBUG_DUMP_C(_level, LOG_THIS_CATEGORY(), _data, _size)

#define PANIC(_code, _fmt, ...) \
        do { \
            LOG_DEBUG(PANIC, _fmt, ##__VA_ARGS__); \
            panic_(_code, NULL, HAL_Delay_Microseconds); \
        } while (0)