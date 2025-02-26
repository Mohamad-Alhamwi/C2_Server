#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Boolean-like values for logical operations and flag checks.
#define FALSE 0
#define TRUE 1

// 
#define CUSTOM_ERR_NO -1

// Cleanup operation types for the cleanUp function.
#define CLEANUP_FILE_DESCRIPTORS 1
#define CLEANUP_MEMORY  2

/**
 * @brief Logs an abort message and terminates the program.
 *
 * @details 
 * - Logs the abort event.
 * - Calls `exit(EXIT_FAILURE)` to terminate execution.
 */
void abortOperation();

/**
 * @brief Logs an error message and optionally terminates the program.
 *
 * @param custom_err_msg A required error message describing the error context.
 * @param custom_err_description A detailed description for custom errors (set to NULL for system errors).
 * @param should_abort If TRUE, the program terminates with `exit(1)`, otherwise, it logs the error and continues execution.
 *
 * @details 
 * - If `should_abort` is TRUE, the program exits, as the error is considered fatal.
 * - If `errno` is nonzero, it indicates a system-level error, and `strerror(errno)` is used instead of `custom_err_description`.
 * - If `errno` is zero, it is a custom error, and `custom_err_description` must be provided.
 */
void throwError(const char *custom_err_msg, const char *custom_err_description, int should_abort);

void cleanUpResources(int cleanup_type, void *resource);

/**
 * @brief Trims leading whitespace from a string.
 *
 * @param[in] str The input string to trim.
 * 
 * @details 
 * - Iterates through the string and skips leading whitespace characters.
 * - Uses `isspace()` to identify whitespace characters such as spaces, tabs, and newlines.
 * - Returns a pointer to the first non-whitespace character in the string.
 *
 * @return A pointer to the trimmed string (unchanged if no leading whitespace).
 */
const char *trimLeading(const char *str);

/**
 * @brief Trims trailing whitespace from a string.
 *
 * Removes trailing whitespace and returns a newly allocated trimmed string. 
 * Uses `isspace()` to identify whitespace characters such as spaces, tabs, and newlines.
 * The caller **must free()** the returned pointer to avoid memory leaks.
 *
 * @param[in] str Input string to be trimmed.
 * 
 * @return A dynamically allocated trimmed string (must be freed by the caller).
 *
 * @warning Failing to free() the returned pointer will cause memory leaks. 
 *          Nullify (`ptr = NULL;`) after freeing to prevent dangling pointers.
 */
char *trimTrailing(const char *str);

/**
 * @brief Trims both leading and trailing whitespace from a string.
 *
 * This function utilizes `trimLeading()` to remove leading whitespace 
 * and `trimTrailing()` to remove trailing whitespace, ensuring a clean 
 * and formatted output.
 *
 * @param[in] str The input string to be trimmed.
 *
 * @return A newly allocated trimmed string. The caller is responsible for freeing it.
 *
 * @warning The returned string is dynamically allocated and must be 
 *          freed by the caller to prevent memory leaks. Additionally, 
 *          set the pointer to NULL after freeing to avoid dangling pointers.
 */
char *trimString(const char *str);

void initializeBuffer(void * ptr, size_t buf_size);

extern void (*zeroBuffer)(void *, size_t);

#endif
