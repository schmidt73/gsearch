#include <stdio.h>
#include "minunit.h"

int tests_run = 0;
 
static char * test_square() 
{
        mu_assert("100 == 10 * 10", 10 * 10 == 100);
        return 0;
}

static char * all_tests() 
{
        mu_run_test(test_square);
        return 0;
}

int main() {
        char *result = all_tests();

        if (result != 0) {
                fprintf(stderr, "%s\n", result);
        } else {
                fprintf(stderr, "ALL GSEARCH TESTS PASSED\n");
        }

        fprintf(stderr, "Tests run: %d\n", tests_run);
                                                              
        return result != 0;
}
