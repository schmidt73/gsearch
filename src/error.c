#include <stdlib.h>
#include "error.h"

char* messages[] = {
        "Failed to allocate more memory",
        "Missing parameter required to build query string",
        "Failed to build query string"
};

char* get_message(g_error error)
{
        if (error >= sizeof(messages) / sizeof(messages[0]))
        {
                return NULL;
        }

        return messages[error];
}
