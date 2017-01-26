#include <stdlib.h>

#include "builder.h"
#include "settings.h"

#define REQUEST_URL "http://www.google.com/search"

/* 
 * Defines a structure called param that defines one parameter of the
 * search query.
 *
 * name - the name of the parameter.
 *
 * validate - validates if the passed in settings will build a valid
 * parameter. Returns 0 if it is possible to build a valid parameter,
 * 1 otherwise.
 *
 * build - returns a built string parameter to be appended 
 * onto the query string. If the settings used to build
 * the parameter are not valid, undefined behaviour will occur.
 *      Example output to build the search string would be
 *      "q=This is an example."
 */
struct param {
        char* name;

        char* (*build)(gsearch_settings*);
        int (*validate)(gsearch_settings*);
};

static param parameters[] = {
        {"search_string", build_search_string, validate_search_string},
};

char* build_search_string

gsearch_request create_gsearch_request(const gsearch_settings* settings_p)
{
        gsearch_request request = malloc(sizeof(*request));
        if (request == NULL) {
                return NULL;
        }

        request->num_results = settings_p->num_results;
        request->url = REQUEST_URL;
        
        /* Validates each of the parameters with the given settings */
        size_t num_params = sizeof(parameters) / sizeof(parameters[0]);
        for (unsigned i = 0; i < num_params; i++) {
                if (parameters[i].validate(settings_p) != 0) {
                        return NULL;
                }
        }

        for (unsigned i = 0; i < num_params; i++) {
                char* parameter = parameters[i].build(settings_p);
                
        }

        return request;
}

void free_gsearch_request(gsearch_request* request)
{
}
