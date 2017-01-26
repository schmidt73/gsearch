#ifndef SETTINGS_H
#define SETTINGS_H

#define TABLE_MODE 0
#define LIST_MODE 1

typedef struct gsearch_settings {
        char* search_string; /* The string to put into the search query */

        int num_results; /* The number of results to display */
        int start_result; /* The result number to start at */

        /* Restricts search results to a certain country, lang, and time */
        char* country; /* country code ex. US*/
        char* lang; /* language code ex. en for english */  
        char* time; /* time code ex. d for the past day */
        
        /* 
         * Restricts search results to only those 
         * containing search query in title 
         */
        int search_in_title;
        
        /* Sets the display mode of the results (LIST or TABLE) */
        int display_mode;
} gsearch_settings;

extern gsearch_settings settings;

#endif
