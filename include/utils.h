# ifndef UTILS_H
# define UTILS_H

void abortOperation();
void throwError(const char *custom_err_msg, int should_abort);
void cleanUpResources(int cleanup_type, void *resource)

# endif
