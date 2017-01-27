#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../src/settings.h"
#include "../src/options.h"
#include "../src/builder.c"
#include "minunit.h"

int tests_run = 0;

static char* build_search_string_test()
{
        settings.search_string = "Test";
        char* output = build_search_string(&settings);
        mu_assert("built_search_string != '#q=Test&'",
                  strcmp(output, "#q=Test&") == 0);
        return 0;
}
 
static char* search_string_test()
{
        settings.search_string = "Test string";
        settings.num_results = 20;

        gsearch_request request = create_gsearch_request(&settings);
        mu_assert("query_string != '#q=Test string&'", 
                  strcmp(request->query_string, "#q=Test string&") == 0);
        free_gsearch_request(&request);

        return 0;
}

static char* all_tests() 
{
        mu_run_test(build_search_string_test);
        mu_run_test(search_string_test);
        return 0;
}

int main() {
        char *result = all_tests();

        if (result != 0) {
                fprintf(stderr, "FAILED: %s\n", result);
        } else {
                fprintf(stderr, "OPTIONS TESTS PASSED\n");
        }

        fprintf(stderr, "Tests run: %d\n\n", tests_run);
                                                              
        return result != 0;
}
