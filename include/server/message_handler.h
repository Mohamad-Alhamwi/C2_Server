#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <stddef.h>

#define MSG_BUFF_SIZE 4096
#define MSG_ID_SIZE 32

void generateMessageID(char *msg_id);
void formatMessage(char *buffer, const char *type, const char *action, const char *data);

#endif
