#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include <stddef.h>

//
#define STDOUT_BUFF 4096 

//
#define MSG_BUFF_SIZE 1024

// Function prototypes.
void setBufferingMode();
void initializeBuffer(void * ptr, int value, size_t num);

// Function aliases.
extern void (*zeroBuffer)(void *, int, size_t);

#endif
