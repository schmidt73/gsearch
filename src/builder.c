#include <stdlib.h>

#include "builder.h"
#include "settings.h"
#include <string.h>
#include <stdio.h>

#define REQUEST_URL "http://www.google.com/search"

#define REQUIRED 1
#define OPTIONAL 0

/* 
 * Defines a structure called parameters that defines one parameter of the
 * search query.
 *
 * name - the name of the parameter.
 *
 * required - if set to 1 (REQUIRED) the parameter is required to build the 
 * query string, otherwise, if it set to 0 (OPTIONAL), it is an optional
 * parameter to build the query string.
 *
 * build - returns a built string parameter to be appended 
 * onto the query string, or if the parameter can not be built for any reason,
 * will return NULL. Example output of a built search string would be:
 *      "q=This is an example."
 */
struct parameter {
        char* name;
        int required;

        char* (*build)(const gsearch_settings*);
};

/*
 * Rules to build parameters.
 */

static char* build_start_result(const gsearch_settings* settings_p)
{
        if (settings_p->start_result < 1) {
                return NULL;
        }

        int len = snprintf(NULL, 0, "start=%i", settings_p->start_result) 
                  + 1;

        char* start_result = malloc(len);
        if (start_result == NULL) {
                return NULL;
        }

        snprintf(start_result, len, "start=%i", settings_p->start_result); 
        return start_result;
}

static char* build_search_string(const gsearch_settings* settings_p)
{
        if (settings_p->search_string == NULL) {
                return NULL;
        }

        int len = snprintf(NULL, 0, "#q=%s", settings_p->search_string) 
                  + 1;

        char* search_str = malloc(len);
        if (search_str == NULL) {
                return NULL;
        }

        snprintf(search_str, len, "#q=%s", settings_p->search_string);
        return search_str;
}

static char* build_country(const gsearch_settings* settings_p)
{
        if (settings_p->country == NULL) {
                return NULL;
        }

        int len = snprintf(NULL, 0, "cr=%s", settings_p->country)
                  + 1;

        char* country = malloc(len);
        if (country == NULL) {
                return NULL;
        }

        snprintf(country, len, "cr=%s", settings_p->country); 
        return country;
}

static char* build_lang(const gsearch_settings* settings_p)
{
        if (settings_p->lang == NULL) {
                return NULL;
        }

        int len = snprintf(NULL, 0, "lr=%s", settings_p->lang)
                  + 1;

        char* lang = malloc(len);
        if (lang == NULL) {
                return NULL;
        }

        snprintf(lang, len, "lr=%s", settings_p->lang); 
        return lang;
}

static char* build_time(const gsearch_settings* settings_p)
{
        if (settings_p->time == NULL) {
                return NULL;
        }

        int len = snprintf(NULL, 0, "as_qdr=%s", settings_p->time)
                  + 1;

        char* time = malloc(len);
        if (time == NULL) {
                return NULL;
        }

        snprintf(time, len, "as_qdr=%s", settings_p->time); 
        return time;
}

/*
 * Orders parameters in an array.
 */
static struct parameter parameters[] = {
        {"search_string", REQUIRED, build_search_string},
        {"country", OPTIONAL, build_country},
        {"lang", OPTIONAL, build_lang},
        {"time", OPTIONAL, build_time},
        {"start_result", OPTIONAL, build_start_result},
};

static void free_str_array(char* array[], size_t len)
{
        for (unsigned i = 0; i < len; i++) {
                if (array[i] != NULL) {
                        free(array[i]);
                }
        }
}

static char* build_query_string(char* built_params[], int num_params)
{
        int query_string_len = 0, offset = 0;
        char* query_string = NULL;

        for (int i = 0; i < num_params; i++) {
                if (built_params[i] == NULL) {
                        continue;
                }
                
                query_string_len += strlen(built_params[i]) + 1;
        }

        if (query_string_len < 1) {
                return NULL;
        }

        query_string = malloc(query_string_len);
        if (query_string == NULL) {
                return NULL;
        }

        for (int i = 0; i < num_params; i++) {
                if (built_params[i] == NULL) {
                        continue;
                }

                if (offset > 0) {
                        memcpy(query_string + offset, "&", 1);
                        offset += 1;
                }

                int len = strlen(built_params[i]);
                memcpy(query_string + offset, built_params[i], len); 
                offset += len;
        }

        query_string[offset] = '\0';
        return query_string;
}

gsearch_request create_gsearch_request(const gsearch_settings* settings_p)
{
        size_t num_params = sizeof(parameters) / sizeof(parameters[0]);
        char* built_params[num_params];
        for (unsigned i = 0; i < num_params; i++) {
                char* built_param = parameters[i].build(settings_p);
                if (built_param == NULL && parameters[i].required == REQUIRED) {
                        free_str_array(built_params, num_params);
                        return NULL;
                }

                built_params[i] = built_param;
        }

        gsearch_request request = malloc(sizeof(*request));
        if (request == NULL) {
                free_str_array(built_params, num_params);
                return NULL;
        }

        request->url = REQUEST_URL;
        request->query_string = build_query_string(built_params, num_params);

        if (request->query_string == NULL) {
                free(request);
                free_str_array(built_params, num_params);
                return NULL;
        }

        return request;
}

void free_gsearch_request(gsearch_request* request)
{
        if (request == NULL || *request == NULL) {
                return;
        }

        free((*request)->query_string);
        free((*request));

        *request = NULL;
}

#undef REQUIRED
#undef OPTIONAL
#undef REQUEST_URL
