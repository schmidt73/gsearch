#include <stdlib.h>

#include "builder.h"
#include "settings.h"
#include <string.h>
#include <stdio.h>

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
 * onto the query string, on error will return NULL. If 
 * the settings used to build the parameter are not valid, 
 * undefined behaviour will occur. The built string parameter must be freed.
 *      Example output to build the search string would be
 *      "q=This is an example."
 */
struct param {
        char* name;

        char* (*build)(const gsearch_settings*);
        int (*validate)(const gsearch_settings*);
};

/*
 * Rules to build parameters.
 */
static char* build_search_string(const gsearch_settings* settings_p)
{
        int len = snprintf(NULL, 0, "#q=%s&", settings_p->search_string);

        char* str = malloc(len + 1);
        if (str == NULL) {
                return NULL;
        }

        snprintf(str, len + 1, "#q=%s&", settings_p->search_string);
        return str;
}

static int validate_search_string(const gsearch_settings* settings_p)
{
        return settings_p->search_string == NULL;
}

/*
 * Orders parameters in an array.
 */
static struct param parameters[] = {
        {"search_string", build_search_string, validate_search_string},
};

/*
 * Appends a passed in string to the end of the other string,
 * allocating more memory if needed.
 *
 * dest points to a null terminated C string created using a member of
 * the alloc functions, or to dest points to NULL.
 *
 * src is a null terminated C string.
 *
 * If dest/src are not as defined, Undefined behaviour will occur.
 *
 * Returns 0 on success, -1 otherwise.
 */
static int append_string(char** dest, char* src)
{
        if (dest == NULL)  {
                return -1;
        }

        int src_len = strlen(src);
        int dest_len = 0;
        if (*dest != NULL) {
                dest_len = strlen(*dest);
        } 

        *dest = realloc(*dest, dest_len + src_len + 1);
        if (*dest == NULL) {
                return -1;
        }

        memcpy(*dest + dest_len, src, src_len);
        *(*dest + dest_len + src_len) = '\0';
        return 0;
}

gsearch_request create_gsearch_request(const gsearch_settings* settings_p)
{
        /* Validates each of the parameters with the given settings */
        size_t num_params = sizeof(parameters) / sizeof(parameters[0]);
        for (unsigned i = 0; i < num_params; i++) {
                if (parameters[i].validate(settings_p) != 0) {
                        return NULL;
                }
        }

        char* query_string = NULL;
        int error = 0;
        for (unsigned i = 0; i < num_params; i++) {
                char* parameter = parameters[i].build(settings_p);
                
                if (parameter != NULL) {
                        error = append_string(&query_string, parameter);
                        free(parameter);
                } else {
                        error = 1;
                }

                if (error != 0) {
                        if (query_string != NULL) {
                                free(query_string);
                        }

                        return NULL;
                }
        }
        
        gsearch_request request = malloc(sizeof(*request));
        if (request == NULL) {
                return NULL;
        }

        request->num_results = settings_p->num_results;
        request->url = REQUEST_URL;
        request->query_string = query_string;
        
        return request;
}

void free_gsearch_request(gsearch_request* request)
{
}
