

#include <shared/time.h>
#include <shared/utils.h>
#include <shared/log_manager.h>
#include <server/message_handler.h>

void generateMessageID(char *msg_id)
{
    static uint32_t counter = 0;

    uint32_t nanoseconds = getNanoseconds(getTime());

    // Reset counter when it reaches max value (max value is never used).
    if (counter == UINT32_MAX)
    {
        counter = 0;
    }

    int bytes_written = snprintf(msg_id, MSG_ID_SIZE, "MID-%09u-%010u", nanoseconds, counter); 
    
    // Check for snprintf failure.
    if (bytes_written < 0)
    {
        throwError("Failed to write into msg_id buffer", NULL, TRUE);
    }

    // Check for truncation risk.
    if (bytes_written >= MSG_ID_SIZE)
    {
        logTerminal(LOG_WARNING, "Message ID truncation risk!");
        logTerminal(LOG_WARNING, "Increase MSG_ID_SIZE");
    }

    ++ counter;

    return;
}

const char * formatMessage(char *buffer, const char *type, const char *action, const char *data)
{
    // Generate a unique ID for each message.
    char msg_id[MSG_ID_SIZE];
    generateMessageID(msg_id);

    return msg_id;
}