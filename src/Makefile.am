AM_CFLAGS = --pedantic -Wall -std=c99 

# Setting up with libCURL
gsearch_CFLAGS = `pkg-config libcurl --cflags --libs`
gsearch_LDFLAGS = `pkg-config libcurl --cflags --libs`

bin_PROGRAMS = gsearch
gsearch_SOURCES = gsearch.c
