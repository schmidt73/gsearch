#include <stdio.h>
#include <unistd.h>

#include "../src/settings.h"
#include "../src/options.h"
#include "minunit.h"

int tests_run = 0;
 
static char * set_display_mode_test() 
{
        optind = 1;
        char* argv[] = {"gsearch", "-d", "list"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        parse_arguments(argc, argv);

        mu_assert("settings.display_mode != LIST_MODE",
                settings.display_mode == LIST_MODE);
        
        optind = 1;
        argv[2] = "table";
        parse_arguments(argc, argv);
        mu_assert("settings.display_mode != TABLE_MODE",
                   settings.display_mode == TABLE_MODE);

        return 0;
}

static char * set_multiple_flags_test() 
{
        optind = 1;
        char* argv[] = {
                        "gsearch", "--displaymode", "list", 
                        "-s", "test_string",
                        "--numresults", "45", "-N", "62",
                        "--searchintitle"
                       };

        int argc = sizeof(argv) / sizeof(argv[0]);
        parse_arguments(argc, argv);

        mu_assert("settings.display_mode != LIST_MODE",
                   settings.display_mode == LIST_MODE);

        mu_assert("settings.search_string != \"test_string\"",
                  strcmp(settings.search_string, "test_string") == 0);

        mu_assert("settings.num_results != 45", settings.num_results == 45);

        mu_assert("settings.start_result != 62", 
                   settings.start_result == 62);

        mu_assert("settings.search_in_title != 1", 
                   settings.search_in_title == 1);

        return 0;
}


static char * all_tests() 
{
        mu_run_test(set_display_mode_test);
        mu_run_test(set_multiple_flags_test);
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
