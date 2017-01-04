#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * Parses the cmd-line arguments into a settings structure
 * which contains the relevant information.
 *
 * On failure (such as invalid arguments), prints a message
 * to stderr and exits with EXIT_FAILURE.
 *
 * argc must equal the length of argv.
 */
void parse_arguments(int argc, char* argv[]);

#endif 
