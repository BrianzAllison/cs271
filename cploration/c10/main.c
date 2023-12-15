/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Brian Allison$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{
	instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));

	if(argc != 2){
		// incorrect number of arguemnts
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}

	FILE *fin = fopen(argv[1], "r");

	if (fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}

	int num_instructions = parse(fin, instructions);
	//symtable_print_labels();
	//symtable_display_table();
	fclose(fin);
	free(instructions);
	return 0;
			
}


