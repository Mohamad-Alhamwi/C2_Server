# ifndef UTILS_H
# define UTILS_H

# define FALSE 0
# define TRUE 1
# define CLEANUP_FILE_DESCRIPTORS 1
# define CLEANUP_MEMORY  2

void abortOperation();
void throwError(const char *custom_err_msg, int should_abort);
void cleanUpResources(int cleanup_type, void *resource);

# endif
