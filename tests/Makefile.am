# Compiler Flags
AM_CFLAGS = --pedantic -Wall -std=c99 

# List of all the tests
check_PROGRAMS = options_test builder_test

# Sources for each test
options_test_SOURCES = options_test.c ../src/options.c ../src/settings.c
builder_test_SOURCES = builder_test.c ../src/options.c ../src/settings.c 

TESTS = $(check_PROGRAMS)
