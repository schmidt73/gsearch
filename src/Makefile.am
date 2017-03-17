bin_PROGRAMS = gsearch
gsearch_SOURCES = gsearch.c options.c settings.c builder.c error.c

# Compiler Flags
gsearch_CFLAGS = --pedantic -Wall -std=c99 

# Setting up with libCURL
gsearch_CFLAGS += `pkg-config libcurl --cflags`
gsearch_LDFLAGS = `pkg-config libcurl --libs`
