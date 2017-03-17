#include <stdio.h>
#include <assert.h>

#include "options.h"
#include "builder.h"
#include "error.h"
#include "perform.h"

#define MAX_TIME 50
//CONTINUE HERE

int main(int argc, char* argv[])
{
        g_error e;
        parse_arguments(argc, argv); 

        // Simple Case with only ten queries. Ignorning users input

        g_request request = create_request(&settings, 0, 10, &e);
        if (request == NULL) {
                char* msg = get_message(e);
                fprintf(stderr, "ERROR: %s\n", msg);
                return 1;
        }
        
        fprintf(stderr, "QUERY: %s\n", request->query_string);
        
        free_request(&request);

        return 0;
}
