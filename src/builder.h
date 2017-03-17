#ifndef BUILDER_H
#define BUILDER_H

#include "error.h"
#include "settings.h"

/*
 * A structure containing the url to make the request to
 * along with the query string.
 *
 * An example structure looks like the following:
 *
 *      {
 *              "http://www.google.com/search",
 *              "q=this is a example",
 *              372,
 *      }; 
 */
typedef struct g_request {
        char* url;
        char* query_string;
} * g_request;

/* 
 * Creates a request object to perform a search request with for
 * a specified settings, starting result, and page size.
 *
 * settings - must be a pointer to a properly initialized settings
 * structure.
 *
 * start_result - the number of results to skip over. must be greater 
 * than or equal to 0.
 *
 * page_size - the number of results per page. must be between 0 and
 * 100 if not then defaults to 10.
 *
 * Returns a g_request object that must be freed on success.
 * Returns NULL on failure and sets e accordingly.
 */
g_request create_request(const g_settings* settings_p, int start_result, 
                         int page_size, g_error *e);

/*
 * Frees a g_request object.
 *
 * request - must be created by create_g_request, otherwise undefined
 * behaviour will occur.
 */
void free_request(g_request* request);

#endif
