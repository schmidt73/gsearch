#ifndef BUILDER_H
#define BUILDER_H

#include "settings.h"

/*
 * A structure containing the url to make the request to
 * along with the query string and the desired number of results.
 *
 * An example structure looks like the following:
 *
 *      {
 *              "http://www.google.com/search",
 *              "q=this is a example",
 *              372,
 *      };
 */
typedef struct gsearch_request {
        char* url;
        char* query_string;

        int num_results;
} * gsearch_request;

/* 
 * Creates a gsearch_request object from a settings object.
 *
 * settings - must be a pointer to a properly initialized settings
 * structure.
 *
 * Returns a gsearch_request object that must be freed on success.
 * Returns NULL on failure.
 */
gsearch_request create_gsearch_request(const gsearch_settings* settings);

/*
 * Frees a gsearch_request object.
 *
 * request - must be created by create_gsearch_request, otherwise undefined
 * behaviour will occur.
 */
void free_gsearch_request(gsearch_request* request);

#endif
