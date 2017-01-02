#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * Parses the cmd-line arguments into a settings structure
 * which contains the relevant information.
 *
 * argc must equal the length of argv.
 */
void parse_arguments(int argc, char* argv[]);

void print_usage(void);

#endif 
