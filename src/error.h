#ifndef ERROR_H
#define ERROR_H

typedef enum g_error {
        OUT_OF_MEMORY = 0, 
        MISSING_REQ_PARAM,
        BUILD_QUERY,
} g_error; 

/* 
 * Gets the associated error message.
 *
 * Returns NULL if associated message can not be found.
 */
char* get_message(g_error error);

#endif
