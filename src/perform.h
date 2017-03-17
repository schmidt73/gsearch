#ifndef PERFORM_H
#define PERFORM_H

#include "error.h"
#include "builder.h"
#include "settings.h"

enum response_type {
        HTML_PAGE,
};

/*
 * A linked list of responses.
 * 
 * To be the last response in the list is to have
 * next be NULL.
 */
typedef struct g_raw_response *g_raw_response;

struct g_raw_response {
        enum response_type type;

        char* data;
        int data_len;
        
        g_raw_response next;
};

/*
 * Performs num_requests as specified by settings and the array
 * of requests.
 *
 * Will return NULL on any failure and set e accordingly.
 */
g_raw_response perform_request(const g_settings* settings_p, g_request request[], 
                               int num_requests, g_error* e);

/*
 * Frees the response object pointed to by response_p
 */
void free_response(g_raw_response* response);

#endif 
